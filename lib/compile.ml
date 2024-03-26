open Core
open Async

module Input = struct
  module Symbol = struct
    type t =
      { offset : int
      ; size : int
      }
  end

  module Hook = struct
    type t =
      { address : int
      ; function_name : string
      }
    [@@deriving sexp]
  end

  type t =
    { dol : Dol.t
    ; chunk : string
    ; symbols : Symbol.t Map.M(String).t
    ; hooks : Hook.t list
    }

  (** Give a symbol, read the corresponding data from the chunk *)
  let read_from_chunk { symbols; chunk; _ } name =
    let Symbol.{ offset; size } = Map.find_exn symbols name in
    String.sub chunk ~pos:offset ~len:size
  ;;

  let hook_offset { symbols; _ } function_name =
    let symbol = Map.find_exn symbols function_name in
    symbol.offset
  ;;
end

module Output = struct
  module Write = struct
    type t =
      { address : int (* Virtual address *)
      ; value : [ `Relative_branch_to_chunk_offset of int ]
      }
  end

  type t =
    { chunk : string
    ; writes : Write.t list
    }
end

(* Either patch the iso or make an action replay code *)

let make_b ~from ~to_ =
  let relative_offset = to_ - from in
  assert (relative_offset % 4 = 0);
  assert (relative_offset >= -(1 lsl 23) && relative_offset < 1 lsl 23);
  let relative_offset =
    if relative_offset < 0 then relative_offset + (1 lsl 24) else relative_offset
  in
  0x48000000 lor relative_offset
;;

let make_bl ~from ~to_ = make_b ~from ~to_ lor 1

let int_to_string i =
  let buf = Bigstring.create 4 in
  Bigstring.set_uint32_be_exn buf ~pos:0 i;
  Bigstring.to_string buf
;;

let make_ar_code ~chunk_base (output : Output.t) : string =
  (* address, value *)
  let string_writes =
    let iobuf = Iobuf.of_string output.chunk in
    assert (Iobuf.length iobuf % 4 = 0);
    let results = ref [] in
    let address = ref chunk_base in
    while not (Iobuf.is_empty iobuf) do
      let value = Iobuf.Consume.uint32_be iobuf in
      results := (!address, value) :: !results;
      address := !address + 4
    done;
    !results
  in
  let explicit_writes =
    List.map output.writes ~f:(fun { address; value } ->
      match value with
      | `Relative_branch_to_chunk_offset offset ->
        let instruction = make_bl ~from:address ~to_:(chunk_base + offset) in
        address, instruction)
  in
  List.map (explicit_writes @ string_writes) ~f:(fun (address, value) ->
    let address = address land 0x00FFFFFF in
    sprintf "04%06X %08X" address value)
  |> String.concat ~sep:"\n"
;;

let go input =
  let chunk, writes =
    List.fold_map
      input.Input.hooks
      ~init:input.chunk
      ~f:(fun chunk { address; function_name } ->
        let hook_offset = Input.hook_offset input function_name in
        let bootstrap_offset = String.length chunk in
        let chunk_addition =
          let instruction =
            Dol.read_virtual input.dol ~address ~size:4 |> Option.value_exn
          in
          let save_state = Input.read_from_chunk input "save_state" in
          let b =
            make_b
              ~from:(bootstrap_offset + 4 + String.length save_state)
              ~to_:hook_offset
            |> int_to_string
          in
          let restore_state = Input.read_from_chunk input "restore_state" in
          let blr = int_to_string 0x4E800020 in
          save_state ^ b ^ restore_state ^ instruction ^ blr
        in
        let value = `Relative_branch_to_chunk_offset hook_offset in
        chunk ^ chunk_addition, Output.Write.{ address; value })
  in
  Output.{ chunk; writes }
;;

let input_of_world ~elf_file ~bin_file ~dol_file ~hook_file =
  let%bind chunk = Reader.file_contents bin_file
  and dol = Reader.file_contents dol_file >>| Dol.load in
  let%map symbols =
    Process.run_lines_exn ~prog:"nm" ~args:[ "-S"; elf_file ] ()
    >>| List.filter_map ~f:(fun line ->
      match String.split line ~on:' ' with
      | [ address; size; _; symbol ] ->
        let offset = Int.of_string ("0x" ^ address) in
        let size = Int.of_string ("0x" ^ size) in
        Some (symbol, Input.Symbol.{ offset; size })
      | _ -> None)
    >>| Map.of_alist_exn (module String)
  in
  let hooks = Sexp.load_sexp hook_file |> [%of_sexp: Input.Hook.t list] in
  Input.{ dol; chunk; symbols; hooks }
;;

let%expect_test "test action replay" =
  let _output =
    Output.
      { chunk = "AAAABBBB"
      ; writes = [ { address = 0x80000010; value = `Relative_branch_to_chunk_offset 0 } ]
      }
  in
  let codes = make_ar_code ~chunk_base:0x80100000 _output in
  print_endline codes;
  [%expect {|
    04000010 480FFFF1
    04100004 42424242
    04100000 41414141 |}];
  return ()
;;

let command =
  Command.async
    ~summary:""
    (let%map_open.Command elf_file =
       flag "-elf-file" ~doc:"FILE elf file" (required Filename_unix.arg_type)
     and bin_file =
       flag "-bin-file" ~doc:"FILE bin file" (required Filename_unix.arg_type)
     and dol_file =
       flag "-dol-file" ~doc:"FILE dol file" (required Filename_unix.arg_type)
     and hook_file =
       flag "-hook-file" ~doc:"FILE hook file" (required Filename_unix.arg_type)
     and chunk_base = flag "-chunk-base" ~doc:"INT chunk base" (required int) in
     fun () ->
       input_of_world ~elf_file ~bin_file ~dol_file ~hook_file
       >>| go
       >>| make_ar_code ~chunk_base
       >>| print_endline)
;;

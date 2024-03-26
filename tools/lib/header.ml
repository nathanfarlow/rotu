open! Core
open Async

module Mapping = struct
  type t =
    { name : string
    ; namespace : string
    ; address : int
    }
end

let parse_hex s =
  let without_prefix = String.chop_prefix_if_exists s ~prefix:"0x" in
  Int.of_string ("0x" ^ without_prefix)
;;

let filter_name name =
  String.filter name ~f:(fun c -> Char.is_alphanum c || Char.equal c '_')
;;

let mapping_of_line =
  let whitespace = Str.regexp "[ \t]+" in
  fun line ->
    match Str.split whitespace line with
    | [ address; _; _; _; name; namespace ] ->
      let address = parse_hex address in
      let name = filter_name name in
      let namespace = filter_name namespace in
      Mapping.{ name; namespace; address }
    | _ -> failwithf "Invalid line: %s" line ()
;;

let header_of_mappings (mappings : Mapping.t list) =
  let declarations =
    List.map mappings ~f:(fun { name; namespace; address } ->
      sprintf "static const void* s_%s_%s = (void*)0x%x;" namespace name address)
  in
  String.concat ~sep:"\n" ("#pragma once" :: declarations)
;;

let header_of_contents contents =
  String.split_lines contents |> List.map ~f:mapping_of_line |> header_of_mappings
;;

let command =
  Command.async
    ~summary:
      "Makes a header file given a map file. This map file should be exported by the \
       gamecube ghidra plugin after loading the elf file in the rotu iso."
    (let%map_open.Command map_file =
       flag "-map-file" ~doc:"FILE map file" (required Filename_unix.arg_type)
     in
     fun () -> Reader.file_contents map_file >>| header_of_contents >>| print_endline)
;;

let%expect_test _ =
  let contents =
    {|803f7210 000004 803f7210  4 @1018     Global
803f7214 000001 803f7214  8 _stack_end        Global|}
  in
  header_of_contents contents |> print_endline;
  [%expect
    {|
    #pragma once
    static const void* s_Global_1018 = (void*)0x803f7210;
    static const void* s_Global__stack_end = (void*)0x803f7214; |}];
  return ()
;;

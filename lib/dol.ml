open Core

let num_text_sections = 7
let num_data_sections = 11

type section =
  { address : int
  ; contents : string
  }
[@@deriving sexp, equal]

type t =
  { text : section list
  ; data : section list
  ; bss_address : int
  ; bss_size : int
  ; entry_point : int
  }
[@@deriving sexp, equal]

let read_u32 iobuf = Iobuf.Consume.uint32_be iobuf
let read_ints iobuf n = List.init n ~f:(fun _ -> read_u32 iobuf) |> List.rev

let make_sections iobuf offsets addresses sizes =
  List.map3_exn offsets addresses sizes ~f:(fun offset address size ->
    offset, address, size)
  |> List.filter ~f:(fun (offset, _, _) -> offset <> 0)
  |> List.map ~f:(fun (offset, address, size) ->
    let contents = Iobuf.Peek.To_string.sub iobuf ~pos:offset ~len:size in
    { address; contents })
;;

let load bytes =
  let iobuf = Iobuf.of_string bytes in
  let text_offsets = read_ints iobuf num_text_sections in
  let data_offsets = read_ints iobuf num_data_sections in
  let text_addresses = read_ints iobuf num_text_sections in
  let data_addresses = read_ints iobuf num_data_sections in
  let text_sizes = read_ints iobuf num_text_sections in
  let data_sizes = read_ints iobuf num_data_sections in
  let bss_address = read_u32 iobuf in
  let bss_size = read_u32 iobuf in
  let entry_point = read_u32 iobuf in
  Iobuf.reset iobuf;
  let text = make_sections iobuf text_offsets text_addresses text_sizes in
  let data = make_sections iobuf data_offsets data_addresses data_sizes in
  { text; data; bss_address; bss_size; entry_point }
;;

let write_u32 = Iobuf.Fill.uint32_be_trunc

let dump t =
  let header_size = 0x100 in
  let sections =
    let exactly n l =
      let l = List.map l ~f:(fun x -> Some x) in
      let len = List.length l in
      if len > n
      then raise_s [%message "too many sections" (len : int) (n : int)]
      else if len < n
      then l @ List.init (n - len) ~f:(fun _ -> None)
      else l
    in
    exactly num_text_sections t.text @ exactly num_data_sections t.data
  in
  let dol_size =
    header_size
    + List.sum
        (module Int)
        sections
        ~f:(function
          | None -> 0
          | Some { contents; _ } -> String.length contents)
  in
  let offsets =
    List.fold_map sections ~init:header_size ~f:(fun cur_offset section ->
      match section with
      | None -> cur_offset, None
      | Some { contents; _ } -> cur_offset + String.length contents, Some cur_offset)
    |> snd
  in
  let iobuf = Iobuf.create ~len:dol_size in
  let write_all l f = List.map l ~f |> List.iter ~f:(write_u32 iobuf) in
  write_all offsets (function
    | None -> 0
    | Some offset -> offset);
  write_all sections (function
    | None -> 0
    | Some { address; _ } -> address);
  write_all sections (function
    | None -> 0
    | Some { contents; _ } -> String.length contents);
  write_u32 iobuf t.bss_address;
  write_u32 iobuf t.bss_size;
  write_u32 iobuf t.entry_point;
  Iobuf.advance iobuf (0xff - 0xe4 + 1);
  List.filter_opt sections
  |> List.iter ~f:(fun { contents; _ } -> Iobuf.Fill.stringo iobuf contents);
  Iobuf.flip_lo iobuf;
  Iobuf.to_string iobuf
;;

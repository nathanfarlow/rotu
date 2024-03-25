open Core

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

let go input =
  let chunk, writes =
    List.fold_map
      input.Input.hooks
      ~init:input.chunk
      ~f:(fun chunk { address; function_name } ->
        let chunk_addition =
          let instruction =
            Dol.read_virtual input.dol ~address ~size:4 |> Option.value_exn
          in
          let save_state = Input.read_from_chunk input "save_state" in
          let restore_state = Input.read_from_chunk input "restore_state" in
          save_state ^ instruction ^ restore_state
        in
        let hook_offset = Input.hook_offset input function_name in
        let value = `Relative_branch_to_chunk_offset hook_offset in
        chunk ^ chunk_addition, Output.Write.{ address; value })
  in
  Output.{ chunk; writes }
;;

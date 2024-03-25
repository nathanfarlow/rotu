val num_text_sections : int
val num_data_sections : int

type section =
  { address : int
  ; contents : string
  }

type t =
  { text : section list
  ; data : section list
  ; bss_address : int
  ; bss_size : int
  ; entry_point : int
  }

val load : string -> t
val dump : t -> string
val read_virtual : t -> address:int -> size:int -> string option

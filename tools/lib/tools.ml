open! Core
open Async

let command =
  Command.group
    ~summary:"Tools to mod rotu"
    [ "make-header", Header.command; "make-ar", Compile.command ]
;;

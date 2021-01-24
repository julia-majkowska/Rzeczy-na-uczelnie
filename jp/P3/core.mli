(* module Core

   Core typechecking and evaluation functions
*)


open Syntax
open Support.Error
val get_type : term -> (etype list) -> (etype * etype) list -> string list -> (etype * ((etype * etype) list) * (string list)) ;;
(* module Core

   Core typechecking and evaluation functions
*)


open Syntax
open Support.Error
val get_type : term -> (etype list) -> (etype * etype) list -> int -> (etype * ((etype * etype) list) * int) ;;
val convert_type : etype -> etype array ->  etype;;
val resolve_binds : (etype * etype) list -> int -> etype->  (bool * etype array);;
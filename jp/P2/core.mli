(* module Core

   Core typechecking and evaluation functions
*)


open Syntax
open Support.Error
val reduce_head : term -> (result list * string list) -> result ;;
val get_type : term -> (etype list) -> (etype list) ->etype;;
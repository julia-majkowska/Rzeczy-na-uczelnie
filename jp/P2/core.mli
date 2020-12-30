(* module Core

   Core typechecking and evaluation functions
*)


open Syntax
open Support.Error
type frame = 
  | Frame of expr * (frame list);;
val get_free_var_names : expr -> string list;;
val reduce : expr -> frame list -> string list -> res_exp ;;
val compare : expr -> frame list -> expr -> frame list -> string list -> string list ->  (bool * string list * string list);;(*zwracam środowisko zmiennych wolnych*);;

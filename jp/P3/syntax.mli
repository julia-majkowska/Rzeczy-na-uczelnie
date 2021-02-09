(* module Syntax: syntax trees and associated support functions *)

open Support.Pervasive
open Support.Error

(* Data type definitions *)
type etype =
    | TyVar of int
    | TyArrow of etype * etype
    | TyUnit
    | TyProd of etype * etype
    | TySum of etype * etype
    | TyVoid

type term =
    | TmVar of info * int
    | TmLambda of info * term
    | TmApp of info * term * term
    | TmUnit of info
    | TmProd of info * term * term
    | TmElem of info * term * int
    | TmAbort of info * term
    | TmIn of info * term * int
    | TmCase of info * term * term * term

type binding =
    NameBind 


(* Contexts *)

type context = ((string * binding) list)*((string * binding) list)
val emptycontext : context 
val addname: context -> string -> context
val addexception: context -> string -> context
val name2index : info -> context -> string -> int
val exceptionname2index : info -> context -> string -> int
val isnamebound : context -> string -> bool
val isexceptionbound : context -> string -> bool
val print: term->string
val print_type: etype->string
val print_constraints:(etype * etype) list -> string

(* Misc *)
val tmInfo: term -> info
(* module Syntax: syntax trees and associated support functions *)

open Support.Pervasive
open Support.Error

(* Data type definitions *)
type term =
    | None
    | TmVar of info * string
    | TmTrue of info
    | TmFalse of info
    | TmLambda of info * string * term
    | TmApp of info * term * term
    | TmSucc of info * term
    | TmZero of info
    | TmAdd of info * term * term
    | TmMul of info * term * term
    | TmSub of info * term * term
    | TmEq of info * term * term
    | TmIf of info * term * term * term
    | TmFix of info * term
    | TmPair of info * term * term
    | TmFst of info * term
    | TmSnd of info * term 
    | TmNill of info
    | TmCons of info * term * term
    | TmHead of info * term
    | TmTail of info * term
    | TmIsNill of info * term

type binding =
    NameBind 


(* Contexts *)
type context
val emptycontext : context 
val ctxlength : context -> int
val addbinding : context -> string -> binding -> context
val addname: context -> string -> context
val index2name : info -> context -> int -> string
val name2index : info -> context -> string -> int
val isnamebound : context -> string -> bool
val print: term->string

(* Misc *)
val tmInfo: term -> info
(* module Syntax: syntax trees and associated support functions *)

open Support.Pervasive
open Support.Error

(* Data type definitions *)
type term =
    | TmVarF of info * string
    | TmVarB of info * int
    | TmTrue of info
    | TmFalse of info
    | TmLambda of info * term
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

type expr =
    | TsVarF of string
    | TsVarB of int
    | TsLambda of expr
    | TsApp of expr * expr

type res_exp = 
    | RsLambda of string * res_exp
    | RsApp of res_exp * res_exp
    | RsVar of string

type binding =
    NameBind 


(* Contexts *)
type context
val emptycontext : context 
val addname: context -> string -> context
val name2index : info -> context -> string -> int
val isnamebound : context -> string -> bool
val print: term->string
val print_e: expr->string
val print_r: res_exp->string
val translate : term -> expr

(* Misc *)
val tmInfo: term -> info
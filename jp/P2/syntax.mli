(* module Syntax: syntax trees and associated support functions *)

open Support.Pervasive
open Support.Error

(* Data type definitions *)
type etype = 
    | TyArrow of etype * etype
    | TyNum 
    | TyBool

type term =
    | TmVarB of info * int
    | TmBool of info * bool
    | TmLambda of info * etype * term
    | TmApp of info * term * term
    | TmNat of info * int
    | TmAdd of info * term * term
    | TmMul of info * term * term
    | TmSub of info * term * term
    | TmEq of info * term * term
    | TmIf of info * term * term * term
    | TmFix of info * term
    | TmException of info * string * etype * term
    | TmThrow of info * int * term *etype
    | TmTry of info * term * (int * term) list

type result = 
    | RBool of bool
    | RLambda of term
    | RFix of result * (result list)
    | RNat of int
    | RException of int * result

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
val print_result: result->string
val print_result_final: result-> (result list * string list)->string
val print_type: etype->string

(* Misc *)
val tmInfo: term -> info
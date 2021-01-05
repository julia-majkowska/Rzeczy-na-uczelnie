open Format
open Support.Error
open Support.Pervasive

exception NoRuleApplies


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


(* Datatypes *)

type binding =
    NameBind 

type context = ((string * binding) list)*((string * binding) list)

(* ---------------------------------------------------------------------- *)
(* Context management *)

let emptycontext = ([], [])

let addbinding ctx x bind = (x,bind)::ctx

let addname ctx x : context= 
  let c, ectx = ctx in 
  ((addbinding c x NameBind), ectx)

let addexception ctx x : context= 
  let c, ectx = ctx in 
  (c, (addbinding ectx x NameBind))

let rec findname ctx x = 
  match ctx with
    |  [] -> false
    | (y,_)::rest ->
        if y=x then true
        else findname rest x

let isnamebound ctx x =
  let c, ectx =  ctx in findname c x

let isexceptionbound ctx x =
    let c, ectx =  ctx in findname ectx x

let rec pickfreshname ctx x =
  if isnamebound ctx x then pickfreshname ctx (x^"'")
  else addname ctx x

let rec get_index fi ctx x = 
  match ctx with
  [] -> error fi ("Identifier " ^ x ^ " is unbound")
  | (y,_)::rest ->
      if y=x then 0
      else 1 + (get_index fi rest x)

let name2index fi ctx x =
  let c, ectx =  ctx in get_index fi c x

let exceptionname2index fi ctx x =
  let c, ectx =  ctx in get_index fi ectx x


let rec print_type (ty : etype) : string = 
  match ty with 
  | TyArrow (ty1, ty2) -> 
    String.concat "" ["["; (print_type ty1);"->"; (print_type ty2); "]"]
  | TyNum -> "TyNum"
  | TyBool -> "TyBool"

let rec print_clauses (clauses : (int*term)list) : string  = 
match clauses with 
| [] -> ""
| (i, ti) :: tail -> String.concat "" ["(";string_of_int i ; "=>" ; (print ti);");"; print_clauses tail]
and  print (e : term)  : string= 
    match e with 
        | TmLambda (_,t, e1) -> String.concat "" ["λ "; (print_type t);".("; (print e1); ")"]
        | TmApp (_, e1, e2) -> String.concat "" [(print e1); (print e2)]
        | TmVarB (_,i) -> String.concat "" ["v"; string_of_int i ]
        | TmBool  (_, b)-> if b then "true" else "false"
        | TmNat  (_,e1) -> string_of_int e1
        | TmAdd (_,e1, e2) -> String.concat "" ["("; (print e1); " + " ;(print e2); ")"]
        | TmMul (_,e1, e2) -> String.concat "" ["("; (print e1); " * " ;(print e2); ")"]
        | TmSub (_,e1, e2) -> String.concat "" ["("; (print e1); " - " ;(print e2); ")"]
        | TmEq (_,e1, e2) -> String.concat "" ["("; (print e1); " == " ;(print e2); ")"]
        | TmIf (_,e1, e2, e3) -> String.concat "" ["(if "; (print e1); "  then " ;(print e2); " else "; print e3; ")" ]
        | TmFix (_,e1) -> String.concat "" ["fix("; (print e1);")"]
        | TmException (_, str, ty, t) -> String.concat "" ["Exception(";str; " of " ; print_type(ty); " in "; (print t);")"]
        | TmThrow (_, i, t, ty) -> String.concat "" ["Trow(";string_of_int i ; " " ; (print t); " as "; print_type(ty);")"]
        | TmTry(_, t, clauses) -> String.concat "" ["Try("; (print t); " with {"; print_clauses(clauses);"})"]

let rec print_result (e:result) : string = 
  match e with 
        | RLambda ( e1) -> String.concat "" ["λ.("; (print e1); ")"]
        | RBool  (b)-> if b then "true" else "false"
        | RNat  (e1) -> string_of_int e1       
        | RException (i, t) -> 
          String.concat "" ["Exception(";string_of_int i; " of " ; (print_result t);")"]
        | RFix (t, _) -> 
          String.concat "" ["Fix(";(print_result t);")"]


let rec exception_lookup (num:int) (env:string list) : string= 
match env with 
| [] -> "undefined exception"
| t :: tail -> 
    match num with
    | 0 -> t
    | n -> exception_lookup (num-1) tail

let rec print_result_final (e:result) (env : (result list * string list)): string = 
  match e with 
        | RLambda ( e1) -> String.concat "" ["λ.("; (print e1); ")"]
        | RBool  (b)-> if b then "true" else "false"
        | RNat  (e1) -> string_of_int e1       
        | RException (i, t) -> 
          let _ , exenv = env in 
          String.concat "" ["Exception(";(exception_lookup i exenv) ; " of " ; (print_result t);")"]
        | RFix (t, _) -> 
          String.concat "" ["Fix(";(print_result t);")"]

(* ---------------------------------------------------------------------- *)
(* Extracting file info *)

let tmInfo e = match e with
  | TmLambda (fi,_, _) -> fi
  | TmApp (fi,_,_) -> fi
  | TmVarB (fi,_) -> fi
  | TmBool (fi, _) -> fi
  | TmNat (fi, _ ) -> fi
  | TmAdd (fi,_,_) -> fi
  | TmMul (fi,_,_) -> fi
  | TmSub (fi,_,_) -> fi
  | TmEq (fi,_,_) -> fi
  | TmIf (fi,_,_,_) -> fi
  | TmFix (fi,_) -> fi
  | TmException (fi, _, _, _) -> fi
  | TmThrow (fi, _, _, _ ) -> fi
  | TmTry (fi, _, _ ) -> fi
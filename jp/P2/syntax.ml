open Format
open Support.Error
open Support.Pervasive

exception NoRuleApplies
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

type etype = 
    | TyArrow of etype * etype
    | TyNum 
    | TyBool



(* Datatypes *)

type binding =
    NameBind 

type context = (string * binding) list

(* ---------------------------------------------------------------------- *)
(* Context management *)

let emptycontext = []

let addbinding ctx x bind = (x,bind)::ctx

let addname ctx x = addbinding ctx x NameBind

let rec isnamebound ctx x =
  match ctx with
      [] -> false
    | (y,_)::rest ->
        if y=x then true
        else isnamebound rest x

let rec pickfreshname ctx x =
  if isnamebound ctx x then pickfreshname ctx (x^"'")
  else ((x,NameBind)::ctx), x


let rec name2index fi ctx x =
  match ctx with
      [] -> error fi ("Identifier " ^ x ^ " is unbound")
    | (y,_)::rest ->
        if y=x then 0
        else 1 + (name2index fi rest x)

let rec print_type (ty : etype) : tring = 
  match ty with 
  | TyArrow (ty1, ty2) -> 
    String.concat "" ["["; (print_type ty1);"->"; (print_type ty2); "]"]
  | TyNum -> "TyNum"
  | TyBool -> "TyBool"

let rec print_clauses (clauses : (int*term)list) : string  = 
match clauses with 
| [] -> ""
| (i, ti) -> String.concat "" ["(";string_of_int i ; "=>" ; (print t);");"]

let rec print (e : term)  : string= 
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
        (* ---------------------------------------------------------------------- *)*)
(* Extracting file info *)

let tmInfo e = match e with
  | TmLambda (fi,_) -> fi
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
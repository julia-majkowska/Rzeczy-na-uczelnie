open Format
open Support.Error
open Support.Pervasive

exception NoRuleApplies


type etype =
    | TyVar of string
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
  | TyVar str -> str
  | TyArrow (ty1, ty2) -> 
    String.concat "" ["["; (print_type ty1);"->"; (print_type ty2); "]"]
  | TyProd (ty1, ty2) -> 
    String.concat "" ["["; (print_type ty1);" X "; (print_type ty2); "]"]
  | TySum (ty1, ty2) -> 
    String.concat "" ["["; (print_type ty1);" + "; (print_type ty2); "]"]
  | TyVoid -> "TyVoid"
  | TyUnit -> "TyUnit"

let rec print_clauses (clauses : (int*term)list) : string  = 
match clauses with 
| [] -> ""
| (i, ti) :: tail -> String.concat "" ["(";string_of_int i ; "=>" ; (print ti);");"; print_clauses tail]
and  print (e : term)  : string= 
    match e with 
        | TmLambda (_, e1) -> String.concat "" ["λ.("; (print e1); ")"]
        | TmApp (_, e1, e2) -> String.concat "" [(print e1); (print e2)]
        | TmVar (_,i) -> String.concat "" ["v"; string_of_int i ]
        | TmUnit  (_)-> "()"
        | TmProd (_,e1, e2) -> String.concat "" ["<"; (print e1); " , " ;(print e2); ">"]
        | TmIn (_,e1, i) -> String.concat "" ["("; (print e1); ".in" ;(string_of_int i); ")"]
        | TmElem (_,e1, i) -> String.concat "" ["("; (print e1); " ." ;(string_of_int i); ")"]
        | TmAbort (_,e1) -> String.concat "" ["abort("; (print e1);")"]
        | TmCase (_, e1, e2, e3) -> String.concat "" ["case ";print e1; " of " ; print e2; " | "; print e3;")"]
       


(* ---------------------------------------------------------------------- *)
(* Extracting file info *)

let tmInfo e = match e with
  | TmLambda (fi, _) -> fi
  | TmApp (fi,_,_) -> fi
  | TmVar (fi,_) -> fi
  | TmUnit (fi) -> fi
  | TmProd (fi, _, _ ) -> fi
  | TmIn (fi,_,_) -> fi
  | TmElem (fi,_,_) -> fi
  | TmAbort (fi,_) -> fi
  | TmCase (fi, _, _, _) -> fi
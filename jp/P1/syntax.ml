open Format
open Support.Error
open Support.Pervasive

exception NoRuleApplies
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

(* Datatypes *)

type binding =
    NameBind 

type context = (string * binding) list

(* ---------------------------------------------------------------------- *)
(* Context management *)

let emptycontext = []

let ctxlength ctx = List.length ctx

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

let index2name fi ctx x =
  try
    let (xn,_) = List.nth ctx x in
    xn
  with Failure _ ->
    (*let msg =
      Printf.sprintf "Variable lookup failure: offset: %d, ctx size: %d" in*)
    raise NoRuleApplies
    (*error fi (msg x (List.length ctx))*)

let rec name2index fi ctx x =
  match ctx with
      [] -> raise NoRuleApplies(*error fi ("Identifier " ^ x ^ " is unbound")*)
    | (y,_)::rest ->
        if y=x then 0
        else 1 + (name2index fi rest x)


let rec print (e : term)  : string= 
    match e with 
        | TmLambda (_, s, e1) -> String.concat "" ["λ"; s; ".("; (print e1); ")"]
        | TmApp (_, e1, e2) -> String.concat "" [(print e1); (print e2)]
        | TmVar (_,s) -> s
        | TmTrue _-> "True"
        | TmFalse _-> "False"
        | TmZero _-> "Zero"
        | TmSucc  (_,e1) -> String.concat "" ["succ("; (print e1);")"]
        | TmAdd (_,e1, e2) -> String.concat "" ["("; (print e1); " + " ;(print e2); ")"]
        | TmMul (_,e1, e2) -> String.concat "" ["("; (print e1); " * " ;(print e2); ")"]
        | TmSub (_,e1, e2) -> String.concat "" ["("; (print e1); " - " ;(print e2); ")"]
        | TmEq (_,e1, e2) -> String.concat "" ["("; (print e1); " == " ;(print e2); ")"]
        | TmIf (_,e1, e2, e3) -> String.concat "" ["(if "; (print e1); "  then " ;(print e2); " else "; print e3; ")" ]
        | TmFix (_,e1) -> String.concat "" ["fix("; (print e1);")"]
        | TmPair (_,e1, e2) -> String.concat "" ["pair("; (print e1); ", " ;(print e2); ")"]
        | TmFst  (_,e1) -> String.concat "" ["fst("; (print e1);")"]
        | TmSnd  (_,e1) -> String.concat "" ["snd("; (print e1);")"]
        | TmNill (_)-> "Nill"
        | TmCons (_, e1, e2) -> String.concat "" ["cons("; (print e1); "::" ;(print e2); ")"]
        | TmHead  (_, e1) -> String.concat "" ["head("; (print e1);")"]
        | TmTail  (_, e1) -> String.concat "" ["tail("; (print e1);")"]
        | TmIsNill  (_, e1) -> String.concat "" ["isnill("; (print e1);")"]
        | None -> ""

    (*let rec translate (e : term) : expr = 
    match e with 
        | Lambda e -> 
            Lambda (translate e)
        | Appl -> 
            Appl ((translate term), (translate term))
        | V v-> V v  
        | Zero -> Lambda (Lambda (Varb 0))
        | Succ of term
        | Add of term * term
        | Mul of term * term
        | Sub of term * term
        | Eq of term * term
        | True  -> Lambda (Lambda (Varb 1))
        | False -> Lambda (Lambda (Varb 0))
        | If of term * term * term
        | Fix of term
        | Pair (e1, e2) -> Apply(Lambda (Lambda (Lambda (Appl (Varb 0, Appl ( Varb 0, Varb 1))))), translate(
        | Fst -> 
            
        | Snd of term 
        | Nill -> Lambda (Lambda (Varb 0))
        | Cons of term * term
        | Head of term
        | Tail of term
        | IsNil of term*)

        (* ---------------------------------------------------------------------- *)
(* Extracting file info *)

let tmInfo e = match e with
  | TmLambda (fi,_,_) -> fi
  | TmApp (fi,_,_) -> fi
  | TmVar (fi,_) -> fi
  | TmTrue fi-> fi
  | TmFalse fi-> fi
  | TmZero fi-> fi
  | TmSucc  (fi,_) -> fi
  | TmAdd (fi,_,_) -> fi
  | TmMul (fi,_,_) -> fi
  | TmSub (fi,_,_) -> fi
  | TmEq (fi,_,_) -> fi
  | TmIf (fi,_,_,_) -> fi
  | TmFix (fi,_) -> fi
  | TmPair (fi,_,_) -> fi
  | TmFst  (fi,_) -> fi
  | TmSnd  (fi,_) -> fi
  | TmNill fi-> fi
  | TmCons (fi,_,_) -> fi
  | TmHead  (fi,_) -> fi
  | TmTail  (fi,_) -> fi
  | TmIsNill  (fi,_) -> fi
  | None -> dummyinfo

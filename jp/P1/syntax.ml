open Format
open Support.Error
open Support.Pervasive

exception NoRuleApplies
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
        | TmLambda (_, e1) -> String.concat "" ["λ.("; (print e1); ")"]
        | TmApp (_, e1, e2) -> String.concat "" [(print e1); (print e2)]
        | TmVarF (_,s) -> s
        | TmVarB (_,i) -> String.concat "" ["v"; string_of_int i ]
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

let rec print_e (e : expr)  : string= 
  match e with 
      | TsLambda e1 -> String.concat "" ["λ ("; (print_e e1); ")"]
      | TsApp (e1, e2) -> String.concat "" ["("; (print_e e1); (print_e e2); ")"]
      | TsVarF i -> i
      | TsVarB i -> string_of_int i


let rec print_r (e : res_exp)  : string= 
match e with 
    | RsLambda (v, e1) -> String.concat "" ["(λ "; v; "." ; (print_r e1); ")"]
    | RsApp (e1, e2) -> String.concat "" ["("; (print_r e1); (print_r e2); ")"]
    | RsVar i -> i


let rec translate (e : term) : expr = 
    match e with 
        | TmLambda (i, e) -> 
            TsLambda (translate e)
        | TmApp (i, e1, e2) -> 
            TsApp ((translate e1), (translate e2))
        | TmVarB (i, id) -> TsVarB id
        | TmVarF (i, id) -> TsVarF id
        | TmZero i -> TsLambda (TsLambda (TsVarB 0))
        | TmSucc (i, e1) -> 
          TsApp (
            TsLambda (
              TsLambda (
                TsLambda (
                  TsApp (
                    TsVarB 1, 
                    TsApp(
                      TsApp (
                        TsVarB 2,
                        TsVarB 1),  
                      TsVarB 0)
                    )
                  )
              )
           ),
          translate e1)
        | TmAdd (i, e1, e2) -> 
          TsApp(
            TsApp (
              TsLambda (
                TsLambda (
                  TsLambda (
                    TsLambda (
                      TsApp (
                        TsApp (TsVarB 3, TsVarB 1), 
                        TsApp(
                          TsApp (TsVarB 2, TsVarB 1), 
                          TsVarB 0)
                      )
                    )
                  )
                )
              ), 
            translate e1), 
          translate e2)
        | TmMul (i, e1, e2) -> 
          TsApp(
            TsApp (
              TsLambda (
                TsLambda (
                  TsLambda (
                    TsLambda (
                      TsApp (
                        TsApp (
                          TsVarB 3, 
                          TsApp (
                            TsVarB 2, 
                            TsVarB 1)),  
                        TsVarB 0)
                    )
                  )
                )
              ), 
            translate e1),
          translate e2)
        | TmSub (i, e1, e2)->
          let zz = TmPair(i, TmZero i , TmZero i ) in
          let ss = TmLambda(i, 
            TmPair(i,
              TmSnd(i,
                TmVarB(i, 0)
              ), 
              TmSucc(i, 
                TmSnd(i,
                  TmVarB(i, 0)
                )
              )
            )
          ) in 
          let prd = TmLambda(i, 
            TmFst(i, 
              TmApp(i,
                TmApp(i,
                  TmVarB(i ,0),
                  ss
                  ),
                  zz
                )
              )
            )in 
          let sub = TmLambda(i,
            TmLambda(i, 
              TmApp(i, 
                TmApp(i, 
                  TmVarB (i, 0), 
                  prd
                ), 
                TmVarB(i, 1)
              )
            )
          )in
          translate(TmApp(i, TmApp(i, sub, e1), e2))
        | TmEq (i, e1, e2)-> 
          let iszero = TmLambda(i,
            TmApp(i,
              TmApp(i,
                TmVarB (i,0), 
                TmLambda(i,
                  TmFalse(i)
                )
              ), 
              TmTrue(i)
            )
          )in 
          let andd = TmLambda(i, 
            TmLambda(i,
              TmApp(i, 
                TmApp(i, 
                  TmVarB(i, 1), 
                  TmVarB(i, 0)
                ),
                TmFalse(i)
              )
            )
          )in
          translate(
            TmApp(i,
              TmApp(i,
                TmLambda(i,
                  TmLambda(i, 
                    TmApp(i,
                      TmApp(i, 
                        andd,
                        TmApp(i, 
                          iszero,
                          TmSub(i, TmVarB(i, 0), TmVarB(i, 1))
                        )
                      ), 
                      TmApp(i, 
                          iszero,
                          TmSub(i, TmVarB(i, 0), TmVarB(i, 1))
                      )
                    )
                  ) 
                ),
              e1), 
              e2)
          )
        | TmTrue _ -> TsLambda (TsLambda (TsVarB 1))
        | TmFalse _-> TsLambda (TsLambda (TsVarB 0))
        | TmIf (i, e1, e2, e3) ->
          TsApp(
            TsApp(
              TsApp(
                TsLambda(
                  TsLambda(
                    TsLambda(
                      TsApp(
                        TsApp(
                          TsVarB 2, TsVarB 1
                        ), 
                        TsVarB 0
                      )
                    )
                  )
                ), 
                translate(e1)
              ), 
              translate(e2)
            ), 
            translate(e3)
          )
        | TmFix (i, e1)-> 
          TsApp(
            TsLambda(
              TsApp(
                TsLambda(
                  TsApp(
                    TsVarB 1, 
                    TsApp(
                      TsVarB 0, 
                      TsVarB 0
                    )
                  )
                ), 
                TsLambda(
                  TsApp(
                    TsVarB 1, 
                    TsApp(
                      TsVarB 0, 
                      TsVarB 0
                    )
                  )
                )
              )
            ), 
            translate(e1)
          )
        | TmPair (i, e1, e2) -> 
          TsApp(
            TsApp(
              TsLambda (
                TsLambda (
                  TsLambda (TsApp ( TsApp ( TsVarB 0, TsVarB 2), TsVarB 1)))), translate(e1)), translate(e2))
        | TmFst (i, e1)-> 
          TsApp(
            TsLambda(
              TsApp(
                TsVarB 0, TsLambda (TsLambda (TsVarB 1))
              )
            ), 
            translate e1
          )
        | TmSnd (i, e1)-> 
          TsApp(
            TsLambda(
              TsApp(
                TsVarB 0, TsLambda (TsLambda (TsVarB 0))
              )
            ), 
            translate e1
          )
        | TmNill i -> translate(TmPair(i, TmTrue(i), TmTrue(i)))
        | TmCons (i, e1, e2)-> translate(
          (*TmLambda(i, 
            TmLambda(i, *)
              TmPair(i, 
                TmFalse(i), 
                TmPair(i, 
                  (*TmVarB (i, 1), 
                  TmVarB (i, 0)*)
                  e1, e2
                )
              )
          (*  )
          )*)
        )
        | TmHead (i, e1)-> translate(TmFst(i, TmSnd(i, e1)))
        | TmTail (i, e1)-> translate(TmSnd(i, TmSnd(i, e1)))
        | TmIsNill (i, e1) -> translate(TmFst(i, e1))

        (* ---------------------------------------------------------------------- *)
(* Extracting file info *)

let tmInfo e = match e with
  | TmLambda (fi,_) -> fi
  | TmApp (fi,_,_) -> fi
  | TmVarB (fi,_) -> fi
  | TmVarF (fi,_) -> fi
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

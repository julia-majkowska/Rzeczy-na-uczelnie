open Format
open Syntax
open Support.Error
open Support.Pervasive

(* ------------------------   EVALUATION  ------------------------ *)

exception NoRuleApplies


exception NoRuleApplies

let rec var_lookup (inf : info) (num:int) (env:term list) : term= 
  match env with 
  | [] -> error info "undefined variable"
  | t :: tail -> 
      match num with
      | 0 -> t
      | n -> var_lookup inf (num-1) tail

let rec exception_lookup (inf : info) (num:int) (env:string list) : term= 
  match env with 
  | [] -> error info "undefined variable"
  | t :: tail -> 
      match num with
      | 0 -> t
      | n -> var_lookup inf (num-1) tail
        


let rec catch_exceptions inf1 i1 t1 ty1 clauses : term = 
  match clauses with 
  | [] -> TmException(inf1, i1, t1, ty1)
  | (i, ti) :: tail -> 
    if i == i1 then ti
    else catch_exceptions inf1 i1 t1 ty1 tail
  
let rec reduce_head (e:term) (env:term list * string list)) : term = 
     
      match e with 
      | TmApp (inf, e1, e2) -> 
        let rt1 = reduce_head e1 env in
        let rt2 = reduce_head e2 env in 
        match rt1 with 
        | TmLambda (inf1, _ , t) -> 
            reduce_head t (rt1 ::env.0, env.1)
        | _ -> error inf1 "runetime attempting to apply to non abstraction"
      | TmVarB (inf, n)-> (
        let e' = var_lookup n env.0 in 
        reduce_head e' env'
      )
      | TmAdd (inf, t1, t2) -> (
        let rt1 = reduce_head t1 [] env in
        let rt2 = reduce_head t2 [] env in 
        match (rt1, rt2) with 
        | TmNat n1, TmNat n2 -> TmNat (inf, n1 + n2)
        | _ -> error inf "runetime illegal additon"
      )
      | TmMul (inf, t1, t2) -> (
        let rt1 = reduce_head t1 [] env in
        let rt2 = reduce_head t2 [] env in 
        match (rt1, rt2) with 
        | TmNat n1, TmNat n2 -> TmNat (inf, n1 * n2)
        | _ -> error inf "runetime illegal multiplication"
      )
      | TmSub (inf, t1, t2) -> (
        let rt1 = reduce_head t1 env in
        let rt2 = reduce_head t2 env in 
        match (rt1, rt2) with 
        | TmNat n1, TmNat n2 -> 
          if n2 >= n1 then 
            TmNat 0 
          else TmNat (inf, n1 - n2)
        | _ -> error inf "runetime illegal substraction"
      )
      | TmEq (inf, t1, t2) -> (
        let rt1 = reduce_head t1 env in
        let rt2 = reduce_head t2 env in 
        match (rt1, rt2) with 
        | TmNat n1, TmNat n2 -> TmBool (inf, n1 == n2)
        | _ -> error inf "runetime illegal numeric comparison"
      )
      | TmIf (inf, t1, t2, t3) -> (
        match reduce_head t1 env with
        | TmBool (inf1, b) -> (
          if b then 
            reduce_head t2 env
          else
            reduce_head t3 env
        )
      )
      | TmException (inf, name, ty, t) -> (
        reduce_head t (env.0, name :: env.1)
      )
      | TmThrow (inf, i, t, ty) -> 
        let tt = reduce_head t env in
        TmException (inf, lookup_exception i env.1, ty, tt)
      | TmCatch (inf, t, clauses) -> 
        match reduce_head t env with
        | TmException (inf1, i1, t1, ty1) -> 
          catch_exceptions inf1 i1 t1 ty1 clauses
        | rt -> rt
        
      | _ -> e


let rec get_fresh_name (used_names : string list) (name : string) : string = 
  if List.mem name used_names 
  then    
    get_fresh_name used_names (String.concat "" [name;"'"])
  else
    name
            

let rec compare_type (ty1 : etype) (ty2 : etype) : bool = 
  match (ty1, ty2) with 
  | TyNum, TyNum -> true
  | TyBool, TyBool -> true
  | TyArrow (ty11, ty12) , TyArrow (ty21, ty22) -> 
    (compare_type ty11 ty21) & (compare_type ty12 ty22)
  | _ -> false

let rec lookup_type info ctx i = 
  match ctx with 
  | [] -> error info "undefined variable"
  | h :: t -> (
    match i with = 
    | 0 -> h
    | n -> lookup_type info t i-1
  )

let rec lookup_exception_type info ectx i = 
  match ctx with 
  | [] -> error info "undefined exception"
  | (hty, hname) :: t -> (
    match i with = 
    | 0 -> hty
    | n -> lookup_type info t i-1
  )


let rec get_type (e : term) (ctx : etype list) (ectx : (etype*string) list) : etype = 
  match e with 
  | TmVarB (info, i) -> lookup_type info ctx i
  | TmBool (_, b) -> TyBool
  | TmLambda (_, ty, t) -> TyArrow (ty, (get_type t (ty :: ctx) ectx))
  | TmApp (inf,t1, t2) -> 
    let ty1 = get_type t1 ctx ectx in
    match ty1 with 
    | TyArrow (ty11, ty12) -> 
      let ty2 = get_type t2 ctx ectx in 
        if compare_type ty2 ty11 then ty12 
        else error inf "type of argument does not match the abstraction"
  | TmAdd (inf, t1, t2) -> 
    let ty1 = get_type t1 ctx ectx in
    let ty2 = get_type t2 ctx ectx in
    if (compare_type ty1 TyNum) & (compare_type ty2 TyNum)
      then TyNum
    else error inf "attempting to add non numerical values"
  | TmMul (inf, t1, t2) -> 
    let ty1 = get_type t1 ctx ectx in
    let ty2 = get_type t2 ctx ectx in
    if (compare_type ty1 TyNum) & (compare_type ty2 TyNum)
      then TyNum
    else error inf "attempting to multiply non numerical values"
  | TmSub (inf, t1, t2) -> 
    let ty1 = get_type t1 ctx ectx in
    let ty2 = get_type t2 ctx ectx in
    if (compare_type ty1 TyNum) & (compare_type ty2 TyNum)
      then TyNum
    else error inf "attempting to substract non numerical values"
  | TmEq (inf, t1, t2) -> 
    let ty1 = get_type t1 ctx ectx in
    let ty2 = get_type t2 ctx ectx in
    if (compare_type ty1 TyNum) & (compare_type ty2 TyNum)
      then TyBool
    else error inf "attempting to add non numerical values"
  | TmIf (inf, t1, t2, t3) -> (
    let ty1 = get_type t1 ctx ectx in
    match ty1 with 
    | TyBool -> (
      let ty2 = get_type t2 ctx ectx in
      let ty3 = get_type t3 ctx ectx in 
      if compare_type ty2 t3
        then ty2
      else error inf "if branches have different types"
    )
    | _ -> error inf "if clause is not a boolean expression"
  )
    | TmFix (inf, t) -> 
      let ty1 = get_type t1 ctx ectx in
      match ty1 with 
      | TyArrow (t1, t2) -> 
        if compare_type t1 t2 then t1 
        else error inf "function aplied to fix has different argument and result types"
      | _ -> error inf "try to apply non function to fix"
    | TmException (inf, name, ety, t ) ->(
      get_type t ctx ((ety, name)::ectx)
    ) 
    | TmThrow (inf, i, t, resty) -> 
      let ty = get_type t ctx ectx in
      let ety = lookup_exception_type info ectx i in
      if compare_type ty ety then resty
      else error inf "applied expression and exception typed don't match"
    | TmTry (inf, t, cls) -> (
      let rec check_clauses clauses ty = 
        match clauses with 
        | [] -> ty
        | (i, ti) :: tl -> 
          let ety = lookup_exception_type info ectx i in
          let titype = get_type ti (ety :: ctx) ectx in
          if compare_type ty titype then check_clauses tl ty
          else error inf "catch clause type does not match expession"
        in
      let exprty = get_type t ctx ectx in
      check_clauses cls exprty
    )

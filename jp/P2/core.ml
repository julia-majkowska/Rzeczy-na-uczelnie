open Format
open Syntax
open Support.Error
open Support.Pervasive

(* ------------------------   EVALUATION  ------------------------ *)

exception NoRuleApplies


exception NoRuleApplies

let rec var_lookup (inf : info) (num:int) (env:result list) : result= 
  match env with 
  | [] -> error inf "undefined variable"
  | t :: tail -> 
      match num with
      | 0 -> t
      | n -> var_lookup inf (num-1) tail

let rec exception_lookup (inf : info) (num:int) (env:string list) : string= 
  match env with 
  | [] -> error inf "undefined exception"
  | t :: tail -> 
      match num with
      | 0 -> t
      | n -> exception_lookup inf (num-1) tail
        
let get_1_2 (a,_) = a
let get_2_2 (_,a) = a

let rec catch_exceptions i clauses : term option = 
  match clauses with 
  | [] -> None
  | (ei, ti) :: tail -> 
    if i  == ei then Some ti
    else catch_exceptions i tail
  
let rec print_env (env : result list) = 
  match env with 
  | [] -> ""
  | a :: b -> String.concat "" [(print_result a); ","; print_env b]
let rec reduce_head (e:term) (env:((result list) * (string list))) : (result * ((result list) * (string list))) =
  let _ = Printf.printf "Currently reducing: %s\n" (print e) in
  let _ = Printf.printf "Current environment: %s\n" (print_env (get_1_2 env)) in
     (*Dorzucic obsługe wyjatków*)
      match e with 
      | TmApp (inf, e1, e2) -> (
        let rt1, env1 = reduce_head e1 env in
        let rt2, env2 = reduce_head e2 env in 
        match rt1 with 
        | RException (i, t) -> RException(i, t), env1
        | RLambda (t) -> 
            reduce_head t (rt2 ::(get_1_2(env1)), get_2_2(env2))
        (* | RFix(arg) -> (
            match arg with
          | RLambda (ty,t) -> (
            match ty with
            | TyArrow (_, _) -> 
            | _ -> error inf "runtime aplying a non finctional fix expression"
          )
          | _ -> error inf "runtime non function as fix argument"*)
        | _ -> 
          error inf (Printf.sprintf "runtime attempting to apply to non abstraction  %s" (print_result rt1))
      )
      | TmVarB (inf, n)-> (
         match var_lookup inf n (get_1_2 env) with 
         | RFix (arg, env1) -> (
          match arg  with
            | RLambda t -> (
              (*jeśli wyrażenie pod spodem jest lambdą to zwróce tą lambdę jako wynik i będzie czekał na argument*)
                reduce_head t (RFix(RLambda(t), env1)::(get_1_2 env), get_2_2(env))
            )
            | _ -> error inf "runtime non function as fix argument"
          )
         | var -> (var, env)
      )

      | TmAdd (inf, t1, t2) -> (
        let rt1, _ = reduce_head t1 env in
        let rt2, _ = reduce_head t2 env in 
        match (rt1, rt2) with 
        | RNat (n1), RNat (n2) -> (RNat (n1 + n2), env)
        | _ -> error inf "runtime illegal additon"
      )
      | TmMul (inf, t1, t2) -> (
        let rt1, _ = reduce_head t1 env in
        let rt2, _ = reduce_head t2 env in 
        match (rt1, rt2) with 
        | RNat (n1), RNat (n2) -> (RNat (n1 * n2), env)
        | _ -> error inf "runtime illegal multiplication"
      )
      | TmSub (inf, t1, t2) -> (
        let rt1, _ = reduce_head t1 env in
        let rt2, _ = reduce_head t2 env in 
        match (rt1, rt2) with 
        | RNat (n1), RNat (n2) -> 
          if n2 >= n1 then 
            (RNat 0, env)
          else (RNat (n1 - n2), env)
        | _ -> 
          error inf (Printf.sprintf "illegal substraction  %s - %s" (print_result rt1) (print_result rt2))
      )
      | TmEq (inf, t1, t2) -> (
        let rt1, _ = reduce_head t1 env in
        let rt2, _ = reduce_head t2 env in 
        match (rt1, rt2) with 
        | RNat (n1), RNat (n2) -> (RBool (n1 == n2), env)
        | _ -> error inf "runtime illegal numeric comparison"
      )
      | TmIf (inf, t1, t2, t3) -> (
        match reduce_head t1 env with
        | RBool (b), _ -> (
          if b then 
            reduce_head t2 env
          else
            reduce_head t3 env
        )
        | _ -> error inf "runtime non bolean in if clause" 
        
      )
      | TmException (inf, name, ty, t) -> (
        reduce_head t (get_1_2(env), name :: get_2_2(env))
      )
      | TmThrow (inf, i, t, ty) -> 
        let tt, _ = reduce_head t env in
        (RException (i, tt), env)
      | TmTry (inf, t, clauses) -> (
        match reduce_head t env with
        | RException (i, tt), _ -> (
          match catch_exceptions i clauses with
          | Some catcht -> reduce_head catcht env
          | None -> (RException (i, tt), env)
        )
        | rt -> rt
      )
      (*Dodać fix*)
      | TmBool (_, b) -> (RBool(b), env)
      | TmNat (_, n) -> (RNat(n), env)
      | TmLambda(_, ty, t) -> (RLambda(t), env)
      | TmFix (inf, arg) -> (
        match reduce_head arg env with
        | RLambda(t), env1 -> (
          (*jeśli wyrażenie pod spodem jest lambdą to zwróce tą lambdę jako wynik i będzie czekał na argument*)
            reduce_head t (RFix(RLambda(t), get_1_2 env1)::get_1_2(env1), get_2_2(env1))
        )
        | _ -> error inf "runtime non function as fix argument"
      )


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
    (compare_type ty11 ty21) && (compare_type ty12 ty22)
  | _ -> false

let rec lookup_type info (ctx : etype list) (i:int) : etype = 
  match ctx with 
  | [] -> error info "undefined variable for type"
  | h :: t -> (
    match i with 
    | 0 -> h
    | n -> lookup_type info t (i-1)
  )

let rec lookup_exception_type info (ectx : etype list) (i:int) : etype = 
  match ectx with 
  | [] -> error info "undefined exception for type"
  | (hty) :: t -> (
    match i with 
    | 0 -> hty
    | n -> lookup_exception_type info t (i-1)
  )


let rec get_type (e : term) (ctx : etype list) (ectx : (etype) list) : etype = 
  match e with 
  | TmVarB (info, i) -> lookup_type info ctx i
  | TmBool (_, _) -> TyBool
  | TmNat (_, _) -> TyNum
  | TmLambda (_, ty, t) -> TyArrow (ty, (get_type t (ty :: ctx) ectx))
  | TmApp (inf,t1, t2) -> (
    let ty1 = get_type t1 ctx ectx in
    match ty1 with 
    | TyArrow (ty11, ty12) -> 
      let ty2 = get_type t2 ctx ectx in 
        if compare_type ty2 ty11 then ty12 
        else error inf "type of argument does not match the abstraction"
    | _ -> error inf "attempting to apply to non function"
        )
  | TmAdd (inf, t1, t2) -> 
    let ty1 = get_type t1 ctx ectx in
    let ty2 = get_type t2 ctx ectx in
    if (compare_type ty1 TyNum) && (compare_type ty2 TyNum)
      then TyNum
    else error inf "attempting to add non numerical values"
  | TmMul (inf, t1, t2) -> 
    let ty1 = get_type t1 ctx ectx in
    let ty2 = get_type t2 ctx ectx in
    if (compare_type ty1 TyNum) && (compare_type ty2 TyNum)
      then TyNum
    else error inf "attempting to multiply non numerical values"
  | TmSub (inf, t1, t2) -> 
    let ty1 = get_type t1 ctx ectx in
    let ty2 = get_type t2 ctx ectx in
    if (compare_type ty1 TyNum) && (compare_type ty2 TyNum)
      then TyNum
    else error inf "attempting to substract non numerical values"
  | TmEq (inf, t1, t2) -> 
    let ty1 = get_type t1 ctx ectx in
    let ty2 = get_type t2 ctx ectx in
    if (compare_type ty1 TyNum) && (compare_type ty2 TyNum)
      then TyBool
    else error inf "attempting to add non numerical values"
  | TmIf (inf, t1, t2, t3) -> (
    let ty1 = get_type t1 ctx ectx in
    match ty1 with 
    | TyBool -> (
      let ty2 = get_type t2 ctx ectx in
      let ty3 = get_type t3 ctx ectx in 
      if compare_type ty2 ty3
        then ty2
      else error inf "if branches have different types"
    )
    | _ -> error inf "if clause is not a boolean expression"
  )
    | TmFix (inf, t) -> (
      let ty1 = get_type t ctx ectx in
      match ty1 with 
      | TyArrow (t1, t2) -> 
        if compare_type t1 t2 then t1 
        else error inf "function aplied to fix has different argument and result types"
      | _ -> error inf "try to apply non function to fix"
    )
    | TmException (inf, name, ety, t ) ->(
      get_type t ctx (ety::ectx)
    ) 
    | TmThrow (inf, i, t, resty) -> 
      let ty = get_type t ctx ectx in
      let ety = lookup_exception_type inf ectx i in
      if compare_type ty ety then resty
      else error inf "applied expression and exception typed don't match"
    | TmTry (inf, t, cls) -> (
      let rec check_clauses clauses ty = 
        match clauses with 
        | [] -> ty
        | (i, ti) :: tl -> 
          let ety = lookup_exception_type inf ectx i in
          let titype = get_type ti (ety :: ctx) ectx in
          if compare_type ty titype then check_clauses tl ty
          else error inf "catch clause type does not match expession"
        in
      let exprty = get_type t ctx ectx in
      check_clauses cls exprty
    )

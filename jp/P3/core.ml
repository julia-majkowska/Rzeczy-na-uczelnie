open Format
open Syntax
open Support.Error
open Support.Pervasive

(* ------------------------   EVALUATION  ------------------------ *)

exception NoRuleApplies


exception NoRuleApplies

let get_1_2 (a,_) = a
let get_2_2 (_,a) = a



let rec get_fresh_name (used_names : string list) (name : string) : string = 
  if List.mem name used_names 
  then    
    get_fresh_name used_names (String.concat "" [name;"'"])
  else
    name
     
let rec lookup_type info (ctx : etype  list) (i:int) : etype = 
  match ctx with 
  | [] -> error info "undefined variable for type"
  | h :: t -> (
    match i with 
    | 0 -> h
    | n -> lookup_type info t (i-1)
  )


let rec get_type (e : term) (ctx : etype list) (constrs : (etype * etype) list) (type_vars : string list) : (etype * ((etype * etype) list) * (string list)) = 
  match e with 
  | TmVar (info, i) -> (lookup_type info ctx i), constrs, type_vars (*zwracam tu aby nie musieć kopiować list*)
  | TmUnit (_) -> TyUnit, constrs, type_vars
  | TmAbort (info, t1) -> (
      let r1, cons1, names1 = get_type t1 ctx constrs type_vars in
      let new_name = get_fresh_name names1 "x" in
      (TyVar new_name), ((r1, TyVoid) :: cons1 ), (new_name :: names1)
  )
  | TmLambda (_, t1) -> (
    let new_name = get_fresh_name type_vars "x"  in
    let r1, cons1, names1 = get_type t1 ((TyVar new_name) :: ctx) constrs (new_name :: type_vars) in
    TyArrow ((TyVar new_name), r1) , cons1, names1
  )
  | TmApp (inf,t1, t2) -> (
    let r1, cons1, names1 = get_type t1 ctx constrs type_vars in
    let r2, cons2, names2 = get_type t2 ctx cons1 names1 in 
    let new_name = get_fresh_name names2 "x"  in
    (TyVar new_name) , (r1, TyArrow (r2, (TyVar new_name))) :: cons2 , (new_name :: names2)
  )
  | TmProd (inf, t1, t2) -> 
    let r1, cons1, names1 = get_type t1 ctx constrs type_vars in
    let r2, cons2, names2 = get_type t2 ctx cons1 names1 in 
    (TyProd (r1, r2)), cons2, names2
  | TmElem (inf, t1, i) -> 
    let r1, cons1, names1 = get_type t1 ctx constrs type_vars in
    let new_name1 = get_fresh_name type_vars "x"  in
    let new_name2 = get_fresh_name (new_name1 :: type_vars) "x" in
    (
      match i with 
      | 1 -> (TyVar new_name1)
      | 2 -> (TyVar new_name2)
      | _ -> error inf "Product element index out of bound"
    ), ((r1, TyProd (TyVar new_name1, TyVar new_name2)) :: cons1), (new_name1 :: new_name2 :: type_vars)
  | TmIn (inf, t1, i) -> 
    let r1, cons1, names1 = get_type t1 ctx constrs type_vars in
    let new_name = get_fresh_name type_vars "x"  in (
      match i with 
      | 1 -> TySum(r1, (TyVar new_name))
      | 2 -> TySum((TyVar new_name), r1)
      | _ -> error inf "Product element index out of bound"
    ) , cons1 , (new_name :: type_vars)

  | TmCase (inf, t1, t2, t3) -> 
    let r, cons, names = get_type t1 ctx constrs type_vars in
    let new_name1 = get_fresh_name names "x" in
    let r2, cons2, names2 = get_type t2 ((TyVar new_name1) :: ctx) cons (new_name1 :: names) in
    let new_name2 = get_fresh_name names2 "x" in
    let r3, cons3, names3 = get_type t3 ((TyVar new_name2) :: ctx) cons2 (new_name2 :: names2) in
    r2 , ((r, TySum((TyVar new_name1), (TyVar new_name2))) :: (r2, r3) :: cons3 ), names3
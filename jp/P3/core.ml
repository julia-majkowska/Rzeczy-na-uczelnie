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


let rec get_type (e : term) (ctx : etype list) (constrs : (etype * etype) list) (last_var : int) : (etype * ((etype * etype) list) * int) = 
  match e with 
  | TmVar (info, i) -> (lookup_type info ctx i), constrs, last_var (*zwracam tu aby nie musieć kopiować list*)
  | TmUnit (_) -> TyUnit, constrs, last_var
  | TmAbort (info, t1) -> (
      let r1, cons1, last_var1 = get_type t1 ctx constrs last_var in
      let new_name = last_var1 in
      (TyVar new_name), ((r1, TyVoid) :: cons1 ), last_var1 +1
  )
  | TmLambda (_, t1) -> (
    let new_name = last_var  in
    let r1, cons1, last_var1 = get_type t1 (last_var +1) constrs (last_var+1) in
    TyArrow ((TyVar new_name), r1) , cons1, last_var1
  )
  | TmApp (inf,t1, t2) -> (
    let r1, cons1, last_var1 = get_type t1 ctx constrs last_var in
    let r2, cons2, last_var2 = get_type t2 ctx cons1 last_var1 in 
    let new_name = last_var2 in
    (TyVar new_name) , (r1, TyArrow (r2, (TyVar new_name))) :: cons2 , last_var2 + 1
  )
  | TmProd (inf, t1, t2) -> 
    let r1, cons1, last_var1 = get_type t1 ctx constrs last_var in
    let r2, cons2, last_var2 = get_type t2 ctx cons1 last_var1 in 
    (TyProd (r1, r2)), cons2, last_var2
  | TmElem (inf, t1, i) -> 
    let r1, cons1, last_var1 = get_type t1 ctx constrs last_var in
    let new_name1 = last_var1  in
    let new_name2 = last_var1 +1 in
    (
      match i with 
      | 1 -> (TyVar new_name1)
      | 2 -> (TyVar new_name2)
      | _ -> error inf "Product element index out of bound"
    ), ((r1, TyProd (TyVar new_name1, TyVar new_name2)) :: cons1), last_var1 + 2
  | TmIn (inf, t1, i) -> 
    let r1, cons1, last_var1 = get_type t1 ctx constrs last_var in
    let new_name = last_var1  in (
      match i with 
      | 1 -> TySum(r1, (TyVar new_name))
      | 2 -> TySum((TyVar new_name), r1)
      | _ -> error inf "Product element index out of bound"
    ) , cons1 , last_var1 +1

  | TmCase (inf, t1, t2, t3) -> 
    let r, cons, last_var1 = get_type t1 ctx constrs last_var in
    let new_name1 = last_var1 in
    let r2, cons2, last_var2 = get_type t2 ((TyVar new_name1) :: ctx) cons last_var1 + 1 in
    let new_name2 = last_var2 in
    let r3, cons3, last_var3= get_type t3 ((TyVar new_name2) :: ctx) cons2 last_var2 +1 in
    r2 , ((r, TySum((TyVar new_name1), (TyVar new_name2))) :: (r2, r3) :: cons3 ), last_var3


let type_eq (at : etype) (bt : etype)  : bool = 
  match at, bt with : 
  | TyVar a, TyVar b -> a == b 
  | TyUnit, TyUnit -> true
  | TyArrow (t1, t2) , TyArrow (t1', t2') -> 
    (type_eq t1 t1') && (type_eq t2 t2')
  | TyProd (t1, t2) , TyProd (t1', t2') -> 
    (type_eq t1 t1') && (type_eq t2 t2')
  | TySum (t1, t2) , TySum (t1', t2') -> 
    (type_eq t1 t1') && (type_eq t2 t2')
  | TyVoid, TyVoid -> true
  | _ -> false

let rec find (clusters : (a', b') t) (size_clusters : (a : a') : a' = 
    match Hashtbl.find clusters a with 
    | TyVar b when a == b -> TyVar b
    | TyVar b when a != b -> (
      let fb = find clusters b in 
        Hashtbl.replace clusters a fb; 
        fb
    )
    | x -> x

let union ((clusters : (a', b') t) (a : a') (b : a') : b' = 
    let fa = find clusters a in
    let fb = find clusters b in 
    Hashtbl.replace clusters a fb; 
    fb

let make_graph (substitutions : etype array) (ty : etype) :  ((etype list) array)  =
    


let resolve_binds (binds : (etype * etype) list) (last_var : int) (ty : etype) : etype array  = 
    let var_class = Array.create last_var (TyVar 0) in
    let clusters = Hashtbl.create last_var (2* (List.length binds)) in
    for i  = 0 to last_var-1
    do 
      Array.set var_class i (TyVar i); 
    done;

    let to_resove  = Queue.create() in
    let f : (etype * etype) -> unit = fun t -> Queue.push to_resove t in 
    List.iter f binds;
    let mut res = true; 
    while ! (Queue.is_empty to_resove) && res
    do
      let x, y = Queue.pop to_resove in
      fx = find clusters x
      fy = find clusters y
      if !(type_eq fx fy) 
      then 
        match fx, fy with
        | TyVar px, py -> 
          w = union clusters fx fy
          if (type_eq w py)  then Array.set px py
        | px, TyVar py -> 
          w = union clusters fx fy
          if (type_eq w px) then Array.set py px
        | TyArrow (t1, t2) , TyArrow (t1', t2') -> 
          Queue.push to_resove (t1, t1')
        | TyProd (t1, t2) , TyProd (t1', t2') -> 
          Queue.push to_resove (t1, t1')
        | TySum (t1, t2) , TySum (t1', t2') -> 
          Queue.push to_resove (t1, t1')
        | _ -> res := false; 
    done; 
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
    let r1, cons1, last_var1 = get_type t1 ((TyVar new_name) :: ctx) constrs (last_var+1) in
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
    let r2, cons2, last_var2 = get_type t2 ((TyVar new_name1) :: ctx) cons (last_var1 + 1) in
    let new_name2 = last_var2 in
    let r3, cons3, last_var3= get_type t3 ((TyVar new_name2) :: ctx) cons2 (last_var2 +1) in
    r2 , ((r, TySum((TyVar new_name1), (TyVar new_name2))) :: (r2, r3) :: cons3 ), last_var3


let rec type_eq (at : etype) (bt : etype)  : bool = 
  match at, bt with  
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

let rec find (clusters : (etype, etype) Hashtbl.t) (size_clusters : (etype, int) Hashtbl.t) (a : etype) : etype = 
    try 
      match Hashtbl.find clusters a with 
      | TyVar b when type_eq a (TyVar b) -> TyVar b
      | TyVar b when (not(type_eq a (TyVar b))) -> (
        let fb = find clusters size_clusters (TyVar b) in 
          Hashtbl.replace clusters a fb; 
          fb
      )
      | x -> x
    with e -> 
      Hashtbl.add clusters a a;
      Hashtbl.add size_clusters a 1;
      a

let union (clusters : (etype, etype) Hashtbl.t) (size_clusters : (etype, int) Hashtbl.t)  (a : etype) (b : etype) : etype = 
    let fa = find clusters size_clusters a in
    let fb = find clusters size_clusters b in 
    let sa = Hashtbl.find size_clusters fa in
    let sb = Hashtbl.find size_clusters fb in
    match fa, fb with
    | TyVar faa, TyVar fbb -> (
       if (Hashtbl.find size_clusters fa) < (Hashtbl.find size_clusters fb)
          then 
            let _ = Hashtbl.replace clusters fa fb in
            let _ = Hashtbl.replace size_clusters fb (sa + sb) in 
            fb
          else
            let _ = Hashtbl.replace clusters fb fa in
            let _ = Hashtbl.replace size_clusters fa (sa + sb) in 
          fa   
    )   
    | TyVar faa, fbb -> 
      let _ = Hashtbl.replace clusters fa fb in
      let _ = Hashtbl.replace size_clusters fb (sa + sb) in 
      fb  
    | faa, TyVar fbb -> 
      let _ = Hashtbl.replace clusters fb fa in
      let _ = Hashtbl.replace size_clusters fa (sa + sb) in 
      fa 
    | _, _ -> (
      Printf.printf "Merging two non trivial expressions";
      if (Hashtbl.find size_clusters fa) < (Hashtbl.find size_clusters fb)
        then 
          let _ = Hashtbl.replace clusters fa fb in
          let _ = Hashtbl.replace size_clusters fb (sa + sb) in 
          fb
        else
          let _ = Hashtbl.replace clusters fb fa in
          let _ = Hashtbl.replace size_clusters fa (sa + sb) in 
        fa    
    )  
  
let rec convert_type (ty : etype) (var_class : etype array) : etype = 
  match ty with  
  | TyVar a -> (
    match Array.get var_class a with
    | TyVar b when a == b -> TyVar a
    | TyVar b when a != b -> convert_type (TyVar b) var_class
    | x -> convert_type x var_class
  )
  | TyUnit -> TyUnit
  | TyVoid -> TyVoid
  | TyArrow (t1, t2) ->
    TyArrow (convert_type t1 var_class, convert_type t2 var_class)
  | TyProd (t1, t2) -> 
    TyProd (convert_type t1 var_class, convert_type t2 var_class)
  | TySum (t1, t2) -> 
    TySum (convert_type t1 var_class, convert_type t2 var_class)

(*let convert_to_queue (binds : (etype * etype) list) : (etype *etype) Queue.t =
   match binds with 
   [] -> Queue.create()
   h :: t -> Queue.push (convert_to_queue t) h*)
let rec make_graph (graph : (etype, etype list) Hashtbl.t) (indeg : ((etype, int) Hashtbl.t)) (clusters : (etype, etype) Hashtbl.t) (cluster_size: (etype, int) Hashtbl.t) (ty : etype) : unit = 
(* : ( (etype, etype list) Hashtbl.t) * ((etype, int) Hashtbl.t) = *)
  let fty = find clusters cluster_size ty in 
  if not (Hashtbl.mem indeg fty) then Hashtbl.add indeg fty 0;
  if not (Hashtbl.mem graph fty) then Hashtbl.add graph fty [];
  match ty with 
  | TyVar v -> ()
  | TyUnit -> ()
  | TyVoid -> ()
  | TyArrow (t1, t2) -> (
    let f1 = find clusters cluster_size t1 in 
    let f2 = find clusters cluster_size t2 in 
    if not (Hashtbl.mem indeg f1) then Hashtbl.add indeg f1 0;
    if not (Hashtbl.mem indeg f2) then Hashtbl.add indeg f2 0;
    if not (Hashtbl.mem graph f1) then Hashtbl.add graph f1 [];
    if not (Hashtbl.mem graph f2) then Hashtbl.add graph f2 [];
    let _= make_graph graph indeg clusters cluster_size t1 in 
    let _= make_graph graph indeg clusters cluster_size t2 in 
    let indeg1 = Hashtbl.find indeg f1 + 1 in
    Hashtbl.replace indeg f1 indeg1;
    let indeg2 = Hashtbl.find indeg f2 + 1 in
    Hashtbl.replace indeg f2 indeg2;
    let neighbours1  = f1::f2 :: (Hashtbl.find graph fty) in 
    Hashtbl.replace graph fty neighbours1
  )
  | TySum (t1, t2) -> (
    let f1 = find clusters cluster_size t1 in 
    let f2 = find clusters cluster_size t2 in 
    if not (Hashtbl.mem indeg f1) then Hashtbl.add indeg f1 0;
    if not (Hashtbl.mem indeg f2) then Hashtbl.add indeg f2 0;
    if not (Hashtbl.mem graph f1) then Hashtbl.add graph f1 [];
    if not (Hashtbl.mem graph f2) then Hashtbl.add graph f2 [];
    let _= make_graph graph indeg clusters cluster_size t1 in 
    let _= make_graph graph indeg clusters cluster_size t2 in 
    let indeg1 = Hashtbl.find indeg f1 + 1 in
    Hashtbl.replace indeg f1 indeg1;
    let indeg2 = Hashtbl.find indeg f2 + 1 in
    Hashtbl.replace indeg f2 indeg2;
    let neighbours1  = f1::f2 :: (Hashtbl.find graph fty) in 
    Hashtbl.replace graph fty neighbours1
  )
  | TyProd (t1, t2) -> (
    let f1 = find clusters cluster_size t1 in 
    let f2 = find clusters cluster_size t2 in 
    if not (Hashtbl.mem indeg f1) then Hashtbl.add indeg f1 0;
    if not (Hashtbl.mem indeg f2) then Hashtbl.add indeg f2 0;
    if not (Hashtbl.mem graph f1) then Hashtbl.add graph f1 [];
    if not (Hashtbl.mem graph f2) then Hashtbl.add graph f2 [];
    let _= make_graph graph indeg clusters cluster_size t1 in 
    let _= make_graph graph indeg clusters cluster_size t2 in 
    let indeg1 = Hashtbl.find indeg f1 + 1 in
    Hashtbl.replace indeg f1 indeg1;
    let indeg2 = Hashtbl.find indeg f2 + 1 in
    Hashtbl.replace indeg f2 indeg2;
    let neighbours1  = f1::f2 :: (Hashtbl.find graph fty) in 
    Hashtbl.replace graph fty neighbours1
    )


let top_sort (graph : (etype, etype list) Hashtbl.t) (indeg : ((etype, int) Hashtbl.t)) : bool = 
  let zero_deg : (etype) Queue.t  = Queue.create () in
  let f : (etype)-> int -> unit = (fun t i -> if i == 0 then  Queue.push t zero_deg) in
  let _ = Hashtbl.iter f indeg in 
  let sorted : int ref = {contents = 0} in 
  while not(Queue.is_empty zero_deg) do
    let x= Queue.pop zero_deg in
    sorted := !sorted +1;
    let neigh = Hashtbl.find graph x in 
    let f  = ( fun x -> 
      let ind = (Hashtbl.find indeg x) -1 in 
      Hashtbl.replace indeg x ind; 
      if ind == 0 then Queue.push x zero_deg ) in 
    List.iter f neigh
  done; 
  !sorted == Hashtbl.length graph


let resolve_binds (binds : (etype * etype) list) (last_var : int) (ty : etype) : (bool * etype array)  = 
    let var_class = Array.make last_var (TyVar 0) in
    let clusters = Hashtbl.create (2* (List.length binds)) in
    let cluster_size = Hashtbl.create (2* (List.length binds)) in
    for i  = 0 to last_var-1
    do 
      Array.set var_class i (TyVar i); 
    done;

    let to_resove : (etype * etype) Queue.t  = Queue.create() in
    let f : (etype * etype) -> unit = (fun t -> Queue.push t to_resove; ()) in
    let _ = List.iter f binds in 
    let res : bool ref = {contents = true} in 
    while (not(Queue.is_empty to_resove) && !res) do
      let x, y = Queue.pop to_resove in
      Printf.printf "Resolving :\n %s %s\n" (print_type x) (print_type y);
      let fx = find clusters cluster_size x in
      let fy = find clusters cluster_size y in
      Printf.printf "Resolving clusters :\n %s %s\n" (print_type fx) (print_type fy);
      if not(type_eq fx fy) 
      then ( 
        match fx, fy with
        | TyVar px, TyVar py -> 
          let w = union clusters cluster_size fx fy in
          if (type_eq w (TyVar py))  then (Array.set var_class px (TyVar py))
          else (Array.set var_class px (TyVar py))
        | TyVar px, py -> 
          let w = union clusters cluster_size fx fy in
          if (type_eq w py)  then (Array.set var_class px py)
        | px, TyVar py -> 
          let w = union clusters cluster_size fx fy in
          if (type_eq w px) then Array.set var_class py px
        | TyArrow (t1, t2) , TyArrow (t1', t2') -> 
          Queue.push (t1, t1') to_resove
        | TyProd (t1, t2) , TyProd (t1', t2') -> 
          Queue.push (t1, t1') to_resove
        | TySum (t1, t2) , TySum (t1', t2') -> 
          Queue.push (t1, t1') to_resove
        | _ -> res := false;
      )
  
    done;
    for i  = 0 to last_var-1
    do 
      Printf.printf "Variable :\n %s %d\n" (print_type (Array.get var_class i)) i;
    done; 
    if not !res then (!res, var_class)
    else
      let _ = Printf.printf "Unifiable maybe not finately\n" in
      let graph = Hashtbl.create (2* (List.length binds)) in 
      let indeg = Hashtbl.create (2* (List.length binds)) in 
      let f = (fun (x, y) -> make_graph graph indeg clusters cluster_size x; make_graph graph indeg clusters cluster_size y) in 
      let _ = List.iter f binds in 
      let _ = Printf.printf "Graph\n" in
      let _ = Hashtbl.iter (fun ty neigh -> 
        (Printf.printf "%s : " (print_type ty) ; 
        List.iter (fun x -> Printf.printf "%s, " (print_type x)  ) neigh; Printf.printf "\n" )) graph in
      let _ = Printf.printf "Clusters\n" in
      let _ = Hashtbl.iter (fun ty clust -> 
        (Printf.printf "%s : %s\n" (print_type ty) (print_type clust))) clusters in
      ((top_sort graph indeg), var_class)
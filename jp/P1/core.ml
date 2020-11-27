open Format
open Syntax
open Support.Error
open Support.Pervasive

(* ------------------------   EVALUATION  ------------------------ *)

exception NoRuleApplies

type frame = 
  | Frame of expr * (frame list);;

type wnf = 
  | WLambda of expr * frame list 
  | WApp of string * frame list;;

type wnf_comp = 
  | CmpLambda of expr * frame list 
  | CmpAppF of string * frame list
  | CmpAppB of int * frame list;;


exception NoRuleApplies

let rec var_lookup (num:int) (env:frame list) : (expr * (frame list))= 
  match num with 
      | 0 -> 
          (match env with 
              | Frame (t, e1)::tail ->
                  (t, e1)
              | _ -> raise NoRuleApplies)
      | _ -> 
          (match env with 
              | h::tail ->
                  var_lookup (num-1) tail
              | _ -> raise NoRuleApplies)
        
let rec print_stack (s:frame list)  : string= 
    match s with 
        |Frame (e, s2)::tail -> String.concat "" ["<"; print_e e;(* ","; print_stack s2; *)">::"; print_stack tail]
        |[] -> "<>"

  
let rec reduce_head (e:expr) (s:frame list) (env:frame list) : wnf = 
      let _ = Printf.printf "%s\n" (print_e e) in
      let _ = Printf.printf "%s\n" (print_stack s) in
      let _ = Printf.printf "%s\n______________\n" (print_stack env) in
      match e with 
      | TsApp (e1, e2) -> reduce_head e1 (Frame(e2, env)::s) env
      | TsLambda e1 ->(
          match s with 
          | h :: tail -> 
              reduce_head e1 tail (h::env)                                                                              
          | _ -> 
            WLambda (e1 , env)
          )
              
      (*| TsVarB 0-> (
          match env with 
          | Frame (None,[]) :: t -> WApp ("0", s) (*TO JEST NIEDOBRZE I DO NAPRAWY*)
          | Frame (e1, env1) :: t -> reduce_head e1 s env1
          | _ -> raise NoRuleApplies
      )*)
  
      | TsVarB n-> (
        let (e', env') = var_lookup n env in reduce_head e' s env'
          (*(match e' with 
            | (VarF-> WApp (string_of_int n, s) 
            (*Mogę mieć zmienną związaną w całym wyrażeniu która jest wolna jak redukuję pod lambdą*)
            | _ -> reduce_head e' s env'
          )*)
          (*match env with 
          | Frame (None,[]) :: t -> WApp (string_of_int n, s) (*TO JEST NIEDOBRZE I DO NAPRAWY*)
          | Frame (e1, env1) :: t -> reduce_head e1 s env1
          | h :: t -> reduce_head (TsVarB (n-1)) s t
          | _ -> raise NoRuleApplies*)
      )
      | TsVarF v -> WApp (v, s)
          
let rec get_free_var_names (e:expr) : string list = 
  match e with  
  | TsApp (e1, e2) -> List.concat [(get_free_var_names e1) ;(get_free_var_names e2)]
  | TsLambda e1 -> get_free_var_names(e1)
  | TsVarB n-> []
  | TsVarF v -> [v]

let rec get_fresh_name (used_names : string list) (name : string) : string = 
  if List.mem name used_names 
  then    
    get_fresh_name used_names (String.concat "" [name;"'"])
  else
    name
            
let rec reduce (e : expr) (env : frame list) (used_names : string list) : res_exp =
  let _ = Printf.printf " Wywołanie dla %s \n ~~~~~~~~~~~~~\n" (print_e e) in
    let r = reduce_head e [] env
    in match r with
        | WLambda (e', env1) -> 
          let nm : string = get_fresh_name used_names "x" in
          RsLambda(nm, reduce e' (Frame (TsVarF(nm), []) :: env1) (nm::used_names) )
        (*None na stosie odpowiada przesunięciem   indeksów zmiennych zwiazanych *)
        | WApp (name, stack) ->(
          let rec apply_stack e s= (
            match s with 
            | [] -> e
            | Frame (e', env') :: t -> 
              apply_stack (RsApp (e,(reduce e' env' used_names))) t 
              (*Wyrażenie są ciągiem aplikacji więc mogę ponownie wykorzystać nazwy zmiennych  *)
          )in 
          apply_stack (RsVar name) stack
        )

let rec update_free_vars n names = 
  match names with
  | [] -> [n]
  | n :: t -> n :: t
  | h :: t -> h :: (update_free_vars n t) 

let rec compare_vars name1 name2 free_vars1 free_vars2 : bool = 
  (*Fcja sprawdza czy występujące zmienne wolne wystąpiły na po raz pierwszy w tym samym miejscu*)
  match (free_vars1, free_vars2) with 
  | ([], []) -> true
  | (name1 :: t1, name2 :: t2) -> true
  | (name1 :: t1, _ :: t2) -> false
  | (_ :: t1, name2 :: t2) -> false
  | (h1 :: t1, h2 :: t2) -> compare_vars name1 name2 t1 t2
  | _ -> false


let rec reduce_head_cmp (e:expr) (s:frame list) (env:frame list) : wnf_comp = 
  let _ = Printf.printf "%s\n" (print_e e) in
  let _ = Printf.printf "%s\n" (print_stack s) in
  let _ = Printf.printf "%s\n______________\n" (print_stack env) in
  match e with 
  | TsApp (e1, e2) -> reduce_head_cmp e1 (Frame(e2, env)::s) env
  | TsLambda e1 ->(
      match s with 
      | h :: tail -> 
          reduce_head_cmp e1 tail (h::env)                                                                              
      | _ -> 
        CmpLambda (e1 , env)
      )

  | TsVarB n-> (
    let (e', env') = var_lookup n env in 
      (match e' with 
        | TsVarF "" -> CmpAppB (n, s) 
        (*Mogę mieć zmienną związaną w całym wyrażeniu która jest wolna jak redukuję pod lambdą*)
        | _ -> reduce_head_cmp e' s env'
      )
  )
  | TsVarF v -> CmpAppF (v, s)

let rec compare (e1 : expr) (env1 : frame list) 
                (e2 : expr) (env2 : frame list) 
                (free_vars1 : string list) (free_vars2 : string list)
                : (bool * string list * string list)  =(*zwracam środowisko zmiennych wolnych*)
  let _ = Printf.printf " Wywołanie dla %s \n ~~~~~~~~~~~~~\n" (print_e e1) in
  let _ = Printf.printf " Wywołanie dla %s \n ~~~~~~~~~~~~~\n" (print_e e2) in
    let r1 = reduce_head_cmp e1 [] env1 in
    let r2 = reduce_head_cmp e2 [] env2 in
    match (r1, r2) with
        | (CmpLambda (e1', env1'), CmpLambda (e2', env2')) -> (
          compare e1' (Frame (TsVarF "", []) :: env1') e2' (Frame (TsVarF "", []) :: env2') free_vars1 free_vars2)
        (*None na stosie odpowiada przesunięciem   indeksów zmiennych zwiazanych *)
        | (CmpAppF (name1, stack1),  CmpAppF (name2, stack2)) ->(
          let rec check_stack s1 s2 n1 n2 = (
            match s1, s2 with 
            | ([],  []) -> (true, n1, n2)
            | (Frame (e1', env1') :: t1, Frame (e2', env2') :: t2) -> 
              let same, n1', n2' = compare e1' env1' e2' env2' n1 n2 in
              if same
                then 
                  check_stack t1 t2 n1' n2'
                else 
                  (false, n1', n2')
            | _ -> false, n1, n2
          )in 
          let updated_free_vars1 = update_free_vars name1 free_vars1 in
          let updated_free_vars2 = update_free_vars name2 free_vars2 in
          if compare_vars name1 name2 free_vars1 free_vars2
            then 
              check_stack stack1 stack2 (updated_free_vars1) (updated_free_vars2)
            else
              false, updated_free_vars1, updated_free_vars2

        )
        | (CmpAppB (name1, stack1),  CmpAppB (name2, stack2)) ->(
          let rec check_stack s1 s2 n1 n2 = (
            match s1, s2 with 
            | ([],  []) -> true, n1, n2
            | (Frame (e1', env1') :: t1, Frame (e2', env2') :: t2) -> 
              let same, n1', n2' = compare e1' env1' e2' env2' n1 n2 in
              if same
                then 
                  check_stack t1 t2 n1' n2'
                else 
                  false, n1', n2'
            | _ -> false, n1, n2
          )in 
          if name1 == name2
            then 
              check_stack stack1 stack2 (free_vars1) (free_vars2)
            else
              false, free_vars1, free_vars2

        )
        | _ -> false, [], []

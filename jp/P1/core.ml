open Format
open Syntax
open Support.Error
open Support.Pervasive

(* ------------------------   EVALUATION  ------------------------ *)

exception NoRuleApplies

type frame = 
  | Frame of expr * (frame list);;

type wnf = 
  | None
  | WLambda of expr * frame list 
  | WApp of string * frame list;;



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
        let (e', env') = var_lookup n env in 
          (match e' with 
            | None -> WApp (string_of_int n, s)
            | _ -> reduce_head e' s env'
          )
          (*match env with 
          | Frame (None,[]) :: t -> WApp (string_of_int n, s) (*TO JEST NIEDOBRZE I DO NAPRAWY*)
          | Frame (e1, env1) :: t -> reduce_head e1 s env1
          | h :: t -> reduce_head (TsVarB (n-1)) s t
          | _ -> raise NoRuleApplies*)
      )
      | TsVarF v -> WApp (v, s)
      | None -> None
            
            
let rec reduce (e : expr) (env : frame list): expr =
  let _ = Printf.printf " Wywołanie dla %s \n ~~~~~~~~~~~~~\n" (print_e e) in
    let r = reduce_head e [] env
    in match r with
        | WLambda (e', env1) -> TsLambda(reduce e' (Frame (None, []) :: env1))
        | WApp (name, stack) ->(
          let rec apply_stack e s = (
            match s with 
            | [] -> e
            | Frame (e', env') :: t -> 
              apply_stack (TsApp (e,(reduce e' env'))) t
          )in 
          apply_stack (TsVarF name) stack
        )
        | None -> None


        
(*let t1 = reduce (Appl ((Lambda (Appl (Varb 0, Varb 0))), (Lambda (Varb 0)))) [] [] Empty
let t2 = Appl ((Lambda (Varb 0)), (Lambda (Varb 0)));;
let t3 = Appl ((Varf 0), (Appl(Lambda (Appl (Varb 0, Varf 0)), Varf 1)))
let ex2 = reduce t3 [] [] Empty;;


Printf.printf "%s" (print ex2);;*)
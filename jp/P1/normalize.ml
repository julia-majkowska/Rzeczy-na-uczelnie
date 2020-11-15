type ext =
    | Lambda of ext
    | Appl of ext * ext
    | V of string
    | Zero 
    | Succ of ext
    | Add of ext * ext
    | Mul of ext * ext
    | Sub of ext * ext
    | Eq of ext * ext
    | If of ext * ext * ext
    | Fix of ext
    | Pair of ext * ext
    | Fst of ext
    | Snd of ext 
    | Nill of ext
    | Cons of ext * ext
    | Head of ext
    | Tail of ext
    | IsNil of ext

type expr_sim =
    | Lambda of expr
    | Appl of expr * expr
    | V of string

type expr =
    | Lambda of expr
    | Appl of expr * expr
    | Varb of int
    | Varf of int;;
 

type value = 
    | Empty
    | Lambda of expr
    | H of int * value;;
    
    
type continuation = 
    | Empty
    | H of int * continuation;;
    
type frame = 
    | Frame of expr * (frame list);;


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
    
    
let rec apply (cont: continuation) (hole : expr) = 
    match cont with 
    | Empty -> hole
    | H (num, rest) -> apply rest (Appl ( (Varf num) , hole))    

        
        
let rec print (e : expr)  : string= 
    match e with 
        | Lambda e1 -> String.concat "" ["λ ("; (print e1); ")"]
        | Appl (e1, e2) -> String.concat "" [(print e1); (print e2)]
        | Varf i -> string_of_int i
        | Varb i -> string_of_int i
        
let rec print_stack (s:frame list)  : string= 
    match s with 
        |Frame (e, s2)::tail -> String.concat "" ["<"; print e; ","; print_stack s2; ">::"; print_stack tail]
        |[] -> "<>"

let rec reduce (e:expr) (s:frame list) (env:frame list) (cont: continuation) : expr = 
    let _ = Printf.printf "%s\n" (print e) in
    let _ = Printf.printf "%s\n" (print_stack s) in
    let _ = Printf.printf "%s\n" (print_stack env) in
    match e with 
    | Appl (e1, e2) -> reduce e1 (Frame(e2, env)::s) env cont
    | Lambda e1 -> 
        (match s with 
        | h :: tail -> 
            reduce e1 tail (h::env) cont
        | _ -> 
            apply cont (Lambda e1))
            
    | Varb v -> 
        let (t, e1) = var_lookup v env in
            reduce t s e1 cont
    | Varf v -> 
        (match s with 
                | Frame(t2, e2)::tail ->  
                    reduce t2 tail e2 (H (v, cont))
                | _ -> apply cont (Varf v))
                
    let rec reduce_head (e:expr) (s:frame list) (env:frame list) : expr = 
    let _ = Printf.printf "%s\n" (print e) in
    let _ = Printf.printf "%s\n" (print_stack s) in
    let _ = Printf.printf "%s\n" (print_stack env) in
    match e with 
    | Appl (e1, e2) -> reduce_head e1 (Frame(e2, env)::s) env
    | Lambda e1 -> 
        (match s with 
        | h :: tail -> 
            reduce_head e1 tail (h::env) cont
        | _ -> 
            Lambda e1
            
    | Varb v -> 
        let (t, e1) = var_lookup v env in
            reduce_head t s e1 cont
    | Varf v -> 
        (match s with 
                | Frame(t2, e2)::tail -> 
                    Appl ((Varf v), t2) (*możliwe że trzeba będzie jakieś shifty dodać*)
                    reduce_head t2 tail e2 (H (v, cont))
                | _ -> Varf v
            
            


        
let t1 = reduce (Appl ((Lambda (Appl (Varb 0, Varb 0))), (Lambda (Varb 0)))) [] [] Empty
let t2 = Appl ((Lambda (Varb 0)), (Lambda (Varb 0)));;
let t3 = Appl ((Varf 0), (Appl(Lambda (Appl (Varb 0, Varf 0)), Varf 1)))
let ex2 = reduce t3 [] [] Empty;;


Printf.printf "%s" (print ex2);;
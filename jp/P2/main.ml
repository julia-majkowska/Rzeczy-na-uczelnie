(* Module Main: The main program.  Deals with processing the command
   line, reading files, building and connecting lexers and parsers, etc. 
   
   For most experiments with the implementation, it should not be
   necessary to change this file.
*)

open Format
open Support.Pervasive
open Support.Error
open Syntax
open Core

let searchpath = ref [""]
let outFile = ref ""
let inFile = ref (None : string option)
let argDefs = [
  ("-i",
      Arg.String (fun f -> searchpath := f::!searchpath; inFile := Some(f)),
      "Append a directory to the search path"); 
  ("-o",
      Arg.String (fun s -> outFile := s ),
      "Append a directory to the search path")    ]

let parseArgs () =
  Arg.parse argDefs
     (fun s ->())
     "";
  match !inFile with
      None -> err "You must specify an input file"
    | Some(s) -> (
        if !outFile = "" 
          then err "You must specify an output file"
        else s, !outFile)

let openfile infile = 
  let rec trynext l = match l with
        [] -> err ("Could not find " ^ infile)
      | (d::rest) -> 
          let name = if d = "" then infile else (d ^ "/" ^ infile) in
          try open_in name
            with Sys_error m -> trynext rest
  in trynext !searchpath

let parseFile inFile =
  let pi = openfile inFile
  in let lexbuf = Lexer.create inFile pi
  in let result =
    try Parser.toplevel Lexer.main lexbuf with Parsing.Parse_error -> 
    error (Lexer.info lexbuf) "Parse error"
in
  Parsing.clear_parser(); close_in pi; result

let alreadyImported = ref ([] : string list)

let print_to_file file message= 
  let oc = open_out file in
  Printf.fprintf oc "%s\n" message; 
  close_out oc;
  ();;  
  
let process_input f f_out ctx =
  alreadyImported := f :: !alreadyImported;
  (*let cmds = parseFile f ctx in
  match cmds with 
  | [] -> 
      Printf.printf "Brak wyrażeń na wejściu\n";
      ()
  | e1::e2::t -> 
    Printf.printf "Porównuje dwa pierwsze wyrażenia\n";
    (*let _ = Printf.printf "%s\n%s\n" (print e1) (print e2) in*)
    let t1 = translate e1 in 
    let t2 = translate e2 in 
    Printf.printf "Odcukrzone wyrażenia:\n%s\n%s\n" (print_e t1) (print_e t2);
    let same, _, _ = compare t1 [] t2 [] [] [] in 
    if same 
      then (
        Printf.printf "Termy są równoważne";
        print_to_file f_out "true")
      else( 
        Printf.printf "Termy nie są równoważne\n %s \n %s\n" (print_r(reduce t1 [] (get_free_var_names t1))) (print_r(reduce t2 [] (get_free_var_names t2)));
        print_to_file f_out "false")
       
  | e1::t ->
    Printf.printf "Redukuję wyrażenie\n"; 
    (*let _ = Printf.printf "%s\n" (print e1) in*)
    let t = translate e1 in
    Printf.printf "Odcukrzone wyrażenie :\n %s\n" (print_e t);
    let reduced = reduce t [] (get_free_var_names t) in
    Printf.printf "Zredukowane wyrażenie :\n %s\n" (print_r reduced);*)
    
    print_to_file f_out (print_r reduced);;

    
let main () = 
  let (inFile, outFile) = parseArgs() in
  let _ = process_input inFile outFile emptycontext in
  ()

let () = set_max_boxes 1000
let () = set_margin 67
let res = 
  Printexc.catch (fun () -> 
    try main();0 
    with Exit x -> x) 
  ()
let () = print_flush()
let () = exit res

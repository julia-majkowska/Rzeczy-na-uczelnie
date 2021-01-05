# 9 "lexer.mll"
 
open Support.Error

let reservedWords = [
  (* Keywords *)
  ("if", fun i -> Parser.IF i);
  ("then", fun i -> Parser.THEN i);
  ("else", fun i -> Parser.ELSE i);
  ("true", fun i -> Parser.TRUE i);
  ("false", fun i -> Parser.FALSE i);
  ("lambda", fun i -> Parser.LAMBDA i);
  ("Nat", fun i -> Parser.NAT i);
  ("add", fun i -> Parser.ADD i);
  ("sub", fun i -> Parser.SUB i);
  ("mul", fun i -> Parser.MUL i);
  ("eq", fun i -> Parser.EQ i);
  ("fix", fun i -> Parser.FIX i);
  ("exception", fun i -> Parser.EXCEPTION i);
  ("in", fun i -> Parser.IN i);
  ("as", fun i -> Parser.AS i);
  ("throw", fun i -> Parser.THROW i);
  ("of", fun i -> Parser.OF i);
  ("try", fun i -> Parser.TRY i);
  ("catch", fun i -> Parser.CATCH i);
  ("TNum", fun i -> Parser.TNUM i);
  ("TBool", fun i -> Parser.TBOOL i);
  ("TArrow", fun i -> Parser.TARROW i);

  (* Symbols *)
  ("_", fun i -> Parser.USCORE i);
  ("'", fun i -> Parser.APOSTROPHE i);
  ("\"", fun i -> Parser.DQUOTE i);
  ("!", fun i -> Parser.BANG i);
  ("#", fun i -> Parser.HASH i);
  ("$", fun i -> Parser.TRIANGLE i);
  ("*", fun i -> Parser.STAR i);
  ("|", fun i -> Parser.VBAR i);
  (".", fun i -> Parser.DOT i);
  (";", fun i -> Parser.SEMI i);
  (",", fun i -> Parser.COMMA i);
  ("/", fun i -> Parser.SLASH i);
  (":", fun i -> Parser.COLON i);
  ("::", fun i -> Parser.COLONCOLON i);
  ("=", fun i -> Parser.EQ i);
  ("==", fun i -> Parser.EQEQ i);
  ("[", fun i -> Parser.LSQUARE i); 
  ("<", fun i -> Parser.LT i);
  ("{", fun i -> Parser.LCURLY i); 
  ("(", fun i -> Parser.LPAREN i); 
  ("<-", fun i -> Parser.LEFTARROW i); 
  ("{|", fun i -> Parser.LCURLYBAR i); 
  ("[|", fun i -> Parser.LSQUAREBAR i); 
  ("}", fun i -> Parser.RCURLY i);
  (")", fun i -> Parser.RPAREN i);
  ("]", fun i -> Parser.RSQUARE i);
  (">", fun i -> Parser.GT i);
  ("|}", fun i -> Parser.BARRCURLY i);
  ("|>", fun i -> Parser.BARGT i);
  ("|]", fun i -> Parser.BARRSQUARE i);

  (* Special compound symbols: *)
  (":=", fun i -> Parser.COLONEQ i);
  ("->", fun i -> Parser.ARROW i);
  ("=>", fun i -> Parser.DARROW i);
  ("==>", fun i -> Parser.DDARROW i);
]

(* Support functions *)

type buildfun = info -> Parser.token
let (symbolTable : (string,buildfun) Hashtbl.t) = Hashtbl.create 1024
let _ =
  List.iter (fun (str,f) -> Hashtbl.add symbolTable str f) reservedWords

let createID i str =
  try (Hashtbl.find symbolTable str) i
  with _ ->
    if (String.get str 0) >= 'A' && (String.get str 0) <= 'Z' then
       Parser.UCID {i=i;v=str}
    else 
       Parser.LCID {i=i;v=str}

let lineno   = ref 1
and depth    = ref 0
and start    = ref 0

and filename = ref ""
and startLex = ref dummyinfo

let create inFile stream =
  if not (Filename.is_implicit inFile) then filename := inFile
  else filename := Filename.concat (Sys.getcwd()) inFile;
  lineno := 1; start := 0; Lexing.from_channel stream

let newline lexbuf = incr lineno; start := (Lexing.lexeme_start lexbuf)

let info lexbuf =
  createInfo (!filename) (!lineno) (Lexing.lexeme_start lexbuf - !start)

let text = Lexing.lexeme

let stringBuffer = ref (String.create 2048)
let stringEnd = ref 0

let resetStr () = stringEnd := 0

let addStr ch =
  let x = !stringEnd in
  let buffer = !stringBuffer
in
  if x = String.length buffer then
    begin
      let newBuffer = String.create (x*2) in
      String.blit buffer 0 newBuffer 0 x;
      String.set newBuffer x ch;
      stringBuffer := newBuffer;
      stringEnd := x+1
    end
  else
    begin
      String.set buffer x ch;
      stringEnd := x+1
    end

let getStr () = String.sub (!stringBuffer) 0 (!stringEnd)

let extractLineno yytext offset =
  int_of_string (String.sub yytext offset (String.length yytext - offset))

# 132 "lexer.ml"
let __ocaml_lex_tables = {
  Lexing.lex_base = 
   "\000\000\242\255\243\255\244\255\245\255\091\000\006\000\101\000\
    \007\000\071\000\115\000\090\000\185\000\218\000\037\001\108\000\
    \099\000\095\000\254\255\001\000\157\000\004\000\253\255\252\255\
    \047\001\038\000\057\001\035\000\046\000\118\000\067\001\077\001\
    \247\255\092\000\154\000\251\255\252\255\253\255\109\000\115\000\
    \255\255\254\255\140\000\255\255\151\000\152\000\134\000\005\000\
    \161\000\251\255\252\255\253\255\254\255\255\255\114\001\249\255\
    \087\001\251\255\252\255\253\255\254\255\255\255\124\001\250\255\
    ";
  Lexing.lex_backtrk = 
   "\255\255\255\255\255\255\255\255\255\255\009\000\010\000\009\000\
    \010\000\010\000\009\000\010\000\009\000\007\000\006\000\010\000\
    \010\000\010\000\255\255\013\000\000\000\255\255\255\255\255\255\
    \255\255\255\255\004\000\255\255\255\255\255\255\255\255\005\000\
    \255\255\008\000\255\255\255\255\255\255\255\255\003\000\003\000\
    \255\255\255\255\255\255\255\255\255\255\000\000\255\255\000\000\
    \255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
    \006\000\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
    ";
  Lexing.lex_default = 
   "\001\000\000\000\000\000\000\000\000\000\255\255\255\255\255\255\
    \255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
    \255\255\255\255\000\000\255\255\255\255\255\255\000\000\000\000\
    \255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
    \000\000\255\255\036\000\000\000\000\000\000\000\255\255\255\255\
    \000\000\000\000\255\255\000\000\045\000\045\000\255\255\047\000\
    \049\000\000\000\000\000\000\000\000\000\000\000\055\000\000\000\
    \255\255\000\000\000\000\000\000\000\000\000\000\255\255\000\000\
    ";
  Lexing.lex_trans = 
   "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\020\000\018\000\018\000\020\000\019\000\018\000\255\255\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \020\000\004\000\003\000\015\000\005\000\005\000\005\000\004\000\
    \004\000\004\000\017\000\005\000\004\000\010\000\004\000\016\000\
    \014\000\014\000\014\000\014\000\014\000\014\000\014\000\014\000\
    \014\000\014\000\012\000\004\000\011\000\009\000\004\000\004\000\
    \005\000\013\000\013\000\013\000\013\000\013\000\013\000\013\000\
    \013\000\013\000\013\000\013\000\013\000\013\000\013\000\013\000\
    \013\000\013\000\013\000\013\000\013\000\013\000\013\000\013\000\
    \013\000\013\000\013\000\006\000\005\000\004\000\004\000\013\000\
    \005\000\013\000\013\000\013\000\013\000\013\000\013\000\013\000\
    \013\000\013\000\013\000\013\000\013\000\013\000\013\000\013\000\
    \013\000\013\000\013\000\013\000\013\000\013\000\013\000\013\000\
    \013\000\013\000\013\000\008\000\007\000\004\000\005\000\005\000\
    \005\000\005\000\032\000\032\000\033\000\032\000\005\000\032\000\
    \005\000\005\000\005\000\005\000\024\000\023\000\022\000\027\000\
    \005\000\028\000\005\000\029\000\032\000\005\000\030\000\005\000\
    \005\000\005\000\032\000\005\000\041\000\040\000\005\000\005\000\
    \005\000\255\255\255\255\032\000\035\000\005\000\020\000\018\000\
    \047\000\020\000\021\000\051\000\042\000\005\000\043\000\000\000\
    \000\000\032\000\000\000\005\000\000\000\000\000\000\000\005\000\
    \000\000\255\255\255\255\005\000\000\000\020\000\000\000\000\000\
    \000\000\005\000\032\000\053\000\038\000\005\000\000\000\000\000\
    \000\000\039\000\000\000\000\000\000\000\000\000\000\000\005\000\
    \000\000\000\000\000\000\005\000\000\000\000\000\032\000\005\000\
    \000\000\005\000\000\000\000\000\000\000\005\000\005\000\005\000\
    \000\000\005\000\032\000\005\000\005\000\000\000\005\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\005\000\
    \000\000\005\000\000\000\005\000\000\000\000\000\032\000\000\000\
    \000\000\005\000\000\000\000\000\000\000\052\000\000\000\000\000\
    \002\000\013\000\000\000\000\000\000\000\255\255\000\000\000\000\
    \000\000\000\000\013\000\013\000\013\000\013\000\013\000\013\000\
    \013\000\013\000\013\000\013\000\000\000\005\000\000\000\000\000\
    \000\000\005\000\000\000\013\000\013\000\013\000\013\000\013\000\
    \013\000\013\000\013\000\013\000\013\000\013\000\013\000\013\000\
    \013\000\013\000\013\000\013\000\013\000\013\000\013\000\013\000\
    \013\000\013\000\013\000\013\000\013\000\005\000\000\000\005\000\
    \000\000\013\000\000\000\013\000\013\000\013\000\013\000\013\000\
    \013\000\013\000\013\000\013\000\013\000\013\000\013\000\013\000\
    \013\000\013\000\013\000\013\000\013\000\013\000\013\000\013\000\
    \013\000\013\000\013\000\013\000\013\000\014\000\014\000\014\000\
    \014\000\014\000\014\000\014\000\014\000\014\000\014\000\026\000\
    \026\000\026\000\026\000\026\000\026\000\026\000\026\000\026\000\
    \026\000\026\000\026\000\026\000\026\000\026\000\026\000\026\000\
    \026\000\026\000\026\000\031\000\031\000\031\000\031\000\031\000\
    \031\000\031\000\031\000\031\000\031\000\031\000\031\000\031\000\
    \031\000\031\000\031\000\031\000\031\000\031\000\031\000\062\000\
    \062\000\062\000\062\000\062\000\062\000\062\000\062\000\062\000\
    \062\000\000\000\000\000\000\000\058\000\000\000\000\000\255\255\
    \255\255\057\000\037\000\025\000\000\000\000\000\000\000\000\000\
    \000\000\050\000\056\000\056\000\056\000\056\000\056\000\056\000\
    \056\000\056\000\056\000\056\000\063\000\063\000\063\000\063\000\
    \063\000\063\000\063\000\063\000\063\000\063\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\059\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \061\000\000\000\000\000\000\000\000\000\000\000\060\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\255\255\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000";
  Lexing.lex_check = 
   "\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
    \255\255\000\000\000\000\019\000\000\000\000\000\021\000\047\000\
    \255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
    \255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
    \000\000\000\000\000\000\000\000\000\000\000\000\000\000\005\000\
    \005\000\005\000\006\000\008\000\009\000\009\000\005\000\011\000\
    \005\000\007\000\007\000\007\000\015\000\016\000\017\000\025\000\
    \007\000\027\000\007\000\028\000\011\000\005\000\029\000\010\000\
    \010\000\010\000\033\000\005\000\038\000\039\000\010\000\007\000\
    \010\000\044\000\045\000\007\000\034\000\007\000\020\000\020\000\
    \046\000\020\000\020\000\048\000\042\000\010\000\042\000\255\255\
    \255\255\010\000\255\255\010\000\255\255\255\255\255\255\005\000\
    \255\255\044\000\045\000\005\000\255\255\020\000\255\255\255\255\
    \255\255\007\000\007\000\048\000\034\000\007\000\255\255\255\255\
    \255\255\034\000\255\255\255\255\255\255\255\255\255\255\010\000\
    \255\255\255\255\255\255\010\000\255\255\255\255\011\000\005\000\
    \255\255\005\000\255\255\255\255\255\255\012\000\012\000\012\000\
    \255\255\007\000\007\000\007\000\012\000\255\255\012\000\255\255\
    \255\255\255\255\255\255\255\255\255\255\255\255\255\255\010\000\
    \255\255\010\000\255\255\012\000\255\255\255\255\012\000\255\255\
    \255\255\012\000\255\255\255\255\255\255\048\000\255\255\255\255\
    \000\000\013\000\255\255\255\255\255\255\047\000\255\255\255\255\
    \255\255\255\255\013\000\013\000\013\000\013\000\013\000\013\000\
    \013\000\013\000\013\000\013\000\255\255\012\000\255\255\255\255\
    \255\255\012\000\255\255\013\000\013\000\013\000\013\000\013\000\
    \013\000\013\000\013\000\013\000\013\000\013\000\013\000\013\000\
    \013\000\013\000\013\000\013\000\013\000\013\000\013\000\013\000\
    \013\000\013\000\013\000\013\000\013\000\012\000\255\255\012\000\
    \255\255\013\000\255\255\013\000\013\000\013\000\013\000\013\000\
    \013\000\013\000\013\000\013\000\013\000\013\000\013\000\013\000\
    \013\000\013\000\013\000\013\000\013\000\013\000\013\000\013\000\
    \013\000\013\000\013\000\013\000\013\000\014\000\014\000\014\000\
    \014\000\014\000\014\000\014\000\014\000\014\000\014\000\024\000\
    \024\000\024\000\024\000\024\000\024\000\024\000\024\000\024\000\
    \024\000\026\000\026\000\026\000\026\000\026\000\026\000\026\000\
    \026\000\026\000\026\000\030\000\030\000\030\000\030\000\030\000\
    \030\000\030\000\030\000\030\000\030\000\031\000\031\000\031\000\
    \031\000\031\000\031\000\031\000\031\000\031\000\031\000\056\000\
    \056\000\056\000\056\000\056\000\056\000\056\000\056\000\056\000\
    \056\000\255\255\255\255\255\255\054\000\255\255\255\255\044\000\
    \045\000\054\000\034\000\024\000\255\255\255\255\255\255\255\255\
    \255\255\048\000\054\000\054\000\054\000\054\000\054\000\054\000\
    \054\000\054\000\054\000\054\000\062\000\062\000\062\000\062\000\
    \062\000\062\000\062\000\062\000\062\000\062\000\255\255\255\255\
    \255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
    \255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
    \255\255\255\255\255\255\255\255\255\255\255\255\054\000\255\255\
    \255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
    \255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
    \054\000\255\255\255\255\255\255\255\255\255\255\054\000\255\255\
    \255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
    \255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
    \255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
    \255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
    \255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
    \255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
    \255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
    \255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
    \255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
    \255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
    \255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
    \255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
    \255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
    \255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
    \255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
    \255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
    \255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
    \255\255\255\255\054\000\255\255\255\255\255\255\255\255\255\255\
    \255\255\255\255\255\255\255\255\255\255";
  Lexing.lex_base_code = 
   "";
  Lexing.lex_backtrk_code = 
   "";
  Lexing.lex_default_code = 
   "";
  Lexing.lex_trans_code = 
   "";
  Lexing.lex_check_code = 
   "";
  Lexing.lex_code = 
   "";
}

let rec main lexbuf =
    __ocaml_lex_main_rec lexbuf 0
and __ocaml_lex_main_rec lexbuf __ocaml_lex_state =
  match Lexing.engine __ocaml_lex_tables __ocaml_lex_state lexbuf with
      | 0 ->
# 143 "lexer.mll"
                           ( main lexbuf )
# 347 "lexer.ml"

  | 1 ->
# 145 "lexer.mll"
                                  ( newline lexbuf; main lexbuf )
# 352 "lexer.ml"

  | 2 ->
# 147 "lexer.mll"
       ( error (info lexbuf) "Unmatched end of comment" )
# 357 "lexer.ml"

  | 3 ->
# 149 "lexer.mll"
       ( depth := 1; startLex := info lexbuf; comment lexbuf; main lexbuf )
# 362 "lexer.ml"

  | 4 ->
# 152 "lexer.mll"
    ( lineno := extractLineno (text lexbuf) 2 - 1; getFile lexbuf )
# 367 "lexer.ml"

  | 5 ->
# 155 "lexer.mll"
    ( lineno := extractLineno (text lexbuf) 7 - 1; getFile lexbuf )
# 372 "lexer.ml"

  | 6 ->
# 158 "lexer.mll"
    ( Parser.INTV{i=info lexbuf; v=int_of_string (text lexbuf)} )
# 377 "lexer.ml"

  | 7 ->
# 165 "lexer.mll"
    ( createID (info lexbuf) (text lexbuf) )
# 382 "lexer.ml"

  | 8 ->
# 169 "lexer.mll"
    ( createID (info lexbuf) (text lexbuf) )
# 387 "lexer.ml"

  | 9 ->
# 172 "lexer.mll"
    ( createID (info lexbuf) (text lexbuf) )
# 392 "lexer.ml"

  | 10 ->
# 176 "lexer.mll"
    ( createID (info lexbuf) (text lexbuf) )
# 397 "lexer.ml"

  | 11 ->
# 178 "lexer.mll"
       ( resetStr(); startLex := info lexbuf; string lexbuf )
# 402 "lexer.ml"

  | 12 ->
# 180 "lexer.mll"
      ( Parser.EOF(info lexbuf) )
# 407 "lexer.ml"

  | 13 ->
# 182 "lexer.mll"
     ( error (info lexbuf) "Illegal character" )
# 412 "lexer.ml"

  | __ocaml_lex_state -> lexbuf.Lexing.refill_buff lexbuf; 
      __ocaml_lex_main_rec lexbuf __ocaml_lex_state

and comment lexbuf =
    __ocaml_lex_comment_rec lexbuf 34
and __ocaml_lex_comment_rec lexbuf __ocaml_lex_state =
  match Lexing.engine __ocaml_lex_tables __ocaml_lex_state lexbuf with
      | 0 ->
# 186 "lexer.mll"
    ( depth := succ !depth; comment lexbuf )
# 424 "lexer.ml"

  | 1 ->
# 188 "lexer.mll"
    ( depth := pred !depth; if !depth > 0 then comment lexbuf )
# 429 "lexer.ml"

  | 2 ->
# 190 "lexer.mll"
    ( error (!startLex) "Comment not terminated" )
# 434 "lexer.ml"

  | 3 ->
# 192 "lexer.mll"
    ( comment lexbuf )
# 439 "lexer.ml"

  | 4 ->
# 194 "lexer.mll"
    ( newline lexbuf; comment lexbuf )
# 444 "lexer.ml"

  | __ocaml_lex_state -> lexbuf.Lexing.refill_buff lexbuf; 
      __ocaml_lex_comment_rec lexbuf __ocaml_lex_state

and getFile lexbuf =
    __ocaml_lex_getFile_rec lexbuf 42
and __ocaml_lex_getFile_rec lexbuf __ocaml_lex_state =
  match Lexing.engine __ocaml_lex_tables __ocaml_lex_state lexbuf with
      | 0 ->
# 197 "lexer.mll"
            ( getName lexbuf )
# 456 "lexer.ml"

  | __ocaml_lex_state -> lexbuf.Lexing.refill_buff lexbuf; 
      __ocaml_lex_getFile_rec lexbuf __ocaml_lex_state

and getName lexbuf =
    __ocaml_lex_getName_rec lexbuf 44
and __ocaml_lex_getName_rec lexbuf __ocaml_lex_state =
  match Lexing.engine __ocaml_lex_tables __ocaml_lex_state lexbuf with
      | 0 ->
# 200 "lexer.mll"
                ( filename := (text lexbuf); finishName lexbuf )
# 468 "lexer.ml"

  | __ocaml_lex_state -> lexbuf.Lexing.refill_buff lexbuf; 
      __ocaml_lex_getName_rec lexbuf __ocaml_lex_state

and finishName lexbuf =
    __ocaml_lex_finishName_rec lexbuf 46
and __ocaml_lex_finishName_rec lexbuf __ocaml_lex_state =
  match Lexing.engine __ocaml_lex_tables __ocaml_lex_state lexbuf with
      | 0 ->
# 203 "lexer.mll"
                ( main lexbuf )
# 480 "lexer.ml"

  | __ocaml_lex_state -> lexbuf.Lexing.refill_buff lexbuf; 
      __ocaml_lex_finishName_rec lexbuf __ocaml_lex_state

and string lexbuf =
    __ocaml_lex_string_rec lexbuf 48
and __ocaml_lex_string_rec lexbuf __ocaml_lex_state =
  match Lexing.engine __ocaml_lex_tables __ocaml_lex_state lexbuf with
      | 0 ->
# 206 "lexer.mll"
       ( Parser.STRINGV {i = !startLex; v=getStr()} )
# 492 "lexer.ml"

  | 1 ->
# 207 "lexer.mll"
       ( addStr(escaped lexbuf); string lexbuf )
# 497 "lexer.ml"

  | 2 ->
# 208 "lexer.mll"
       ( addStr '\n'; newline lexbuf; string lexbuf )
# 502 "lexer.ml"

  | 3 ->
# 209 "lexer.mll"
       ( error (!startLex) "String not terminated" )
# 507 "lexer.ml"

  | 4 ->
# 210 "lexer.mll"
       ( addStr (Lexing.lexeme_char lexbuf 0); string lexbuf )
# 512 "lexer.ml"

  | __ocaml_lex_state -> lexbuf.Lexing.refill_buff lexbuf; 
      __ocaml_lex_string_rec lexbuf __ocaml_lex_state

and escaped lexbuf =
    __ocaml_lex_escaped_rec lexbuf 54
and __ocaml_lex_escaped_rec lexbuf __ocaml_lex_state =
  match Lexing.engine __ocaml_lex_tables __ocaml_lex_state lexbuf with
      | 0 ->
# 213 "lexer.mll"
       ( '\n' )
# 524 "lexer.ml"

  | 1 ->
# 214 "lexer.mll"
       ( '\t' )
# 529 "lexer.ml"

  | 2 ->
# 215 "lexer.mll"
        ( '\\' )
# 534 "lexer.ml"

  | 3 ->
# 216 "lexer.mll"
         ( '\034'  )
# 539 "lexer.ml"

  | 4 ->
# 217 "lexer.mll"
        ( '\'' )
# 544 "lexer.ml"

  | 5 ->
# 219 "lexer.mll"
    (
      let x = int_of_string(text lexbuf) in
      if x > 255 then
	error (info lexbuf) "Illegal character constant"
      else
	Char.chr x
    )
# 555 "lexer.ml"

  | 6 ->
# 227 "lexer.mll"
    ( error (info lexbuf) "Illegal character constant" )
# 560 "lexer.ml"

  | __ocaml_lex_state -> lexbuf.Lexing.refill_buff lexbuf; 
      __ocaml_lex_escaped_rec lexbuf __ocaml_lex_state

;;


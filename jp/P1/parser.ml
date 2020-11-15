type token =
  | IF of (Support.Error.info)
  | THEN of (Support.Error.info)
  | ELSE of (Support.Error.info)
  | TRUE of (Support.Error.info)
  | FALSE of (Support.Error.info)
  | LAMBDA of (Support.Error.info)
  | NAT of (Support.Error.info)
  | ADD of (Support.Error.info)
  | SUB of (Support.Error.info)
  | MUL of (Support.Error.info)
  | EQ of (Support.Error.info)
  | FIX of (Support.Error.info)
  | PAIR of (Support.Error.info)
  | FST of (Support.Error.info)
  | SND of (Support.Error.info)
  | NILL of (Support.Error.info)
  | CONS of (Support.Error.info)
  | HEAD of (Support.Error.info)
  | TAIL of (Support.Error.info)
  | ISNILL of (Support.Error.info)
  | UCID of (string Support.Error.withinfo)
  | LCID of (string Support.Error.withinfo)
  | INTV of (int Support.Error.withinfo)
  | STRINGV of (string Support.Error.withinfo)
  | APOSTROPHE of (Support.Error.info)
  | DQUOTE of (Support.Error.info)
  | ARROW of (Support.Error.info)
  | BANG of (Support.Error.info)
  | BARGT of (Support.Error.info)
  | BARRCURLY of (Support.Error.info)
  | BARRSQUARE of (Support.Error.info)
  | COLON of (Support.Error.info)
  | COLONCOLON of (Support.Error.info)
  | COLONEQ of (Support.Error.info)
  | COLONHASH of (Support.Error.info)
  | COMMA of (Support.Error.info)
  | DARROW of (Support.Error.info)
  | DDARROW of (Support.Error.info)
  | DOT of (Support.Error.info)
  | EOF of (Support.Error.info)
  | EQEQ of (Support.Error.info)
  | EXISTS of (Support.Error.info)
  | GT of (Support.Error.info)
  | HASH of (Support.Error.info)
  | LCURLY of (Support.Error.info)
  | LCURLYBAR of (Support.Error.info)
  | LEFTARROW of (Support.Error.info)
  | LPAREN of (Support.Error.info)
  | LSQUARE of (Support.Error.info)
  | LSQUAREBAR of (Support.Error.info)
  | LT of (Support.Error.info)
  | RCURLY of (Support.Error.info)
  | RPAREN of (Support.Error.info)
  | RSQUARE of (Support.Error.info)
  | SEMI of (Support.Error.info)
  | SLASH of (Support.Error.info)
  | STAR of (Support.Error.info)
  | TRIANGLE of (Support.Error.info)
  | USCORE of (Support.Error.info)
  | VBAR of (Support.Error.info)

open Parsing;;
let _ = parse_error;;
# 7 "parser.mly"
open Support.Error
open Support.Pervasive
open Syntax
# 70 "parser.ml"
let yytransl_const = [|
    0|]

let yytransl_block = [|
  257 (* IF *);
  258 (* THEN *);
  259 (* ELSE *);
  260 (* TRUE *);
  261 (* FALSE *);
  262 (* LAMBDA *);
  263 (* NAT *);
  264 (* ADD *);
  265 (* SUB *);
  266 (* MUL *);
  267 (* EQ *);
  268 (* FIX *);
  269 (* PAIR *);
  270 (* FST *);
  271 (* SND *);
  272 (* NILL *);
  273 (* CONS *);
  274 (* HEAD *);
  275 (* TAIL *);
  276 (* ISNILL *);
  277 (* UCID *);
  278 (* LCID *);
  279 (* INTV *);
  280 (* STRINGV *);
  281 (* APOSTROPHE *);
  282 (* DQUOTE *);
  283 (* ARROW *);
  284 (* BANG *);
  285 (* BARGT *);
  286 (* BARRCURLY *);
  287 (* BARRSQUARE *);
  288 (* COLON *);
  289 (* COLONCOLON *);
  290 (* COLONEQ *);
  291 (* COLONHASH *);
  292 (* COMMA *);
  293 (* DARROW *);
  294 (* DDARROW *);
  295 (* DOT *);
    0 (* EOF *);
  296 (* EQEQ *);
  297 (* EXISTS *);
  298 (* GT *);
  299 (* HASH *);
  300 (* LCURLY *);
  301 (* LCURLYBAR *);
  302 (* LEFTARROW *);
  303 (* LPAREN *);
  304 (* LSQUARE *);
  305 (* LSQUAREBAR *);
  306 (* LT *);
  307 (* RCURLY *);
  308 (* RPAREN *);
  309 (* RSQUARE *);
  310 (* SEMI *);
  311 (* SLASH *);
  312 (* STAR *);
  313 (* TRIANGLE *);
  314 (* USCORE *);
  315 (* VBAR *);
    0|]

let yylhs = "\255\255\
\001\000\001\000\002\000\002\000\002\000\003\000\003\000\003\000\
\003\000\003\000\003\000\003\000\003\000\003\000\003\000\003\000\
\003\000\003\000\003\000\004\000\004\000\004\000\004\000\004\000\
\004\000\000\000"

let yylen = "\002\000\
\001\000\001\000\001\000\006\000\004\000\001\000\002\000\003\000\
\003\000\003\000\003\000\002\000\003\000\002\000\002\000\003\000\
\002\000\002\000\002\000\003\000\001\000\001\000\001\000\001\000\
\001\000\002\000"

let yydefred = "\000\000\
\000\000\000\000\000\000\021\000\022\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\024\000\000\000\
\000\000\000\000\000\000\023\000\025\000\001\000\000\000\026\000\
\002\000\000\000\006\000\000\000\000\000\000\000\000\000\000\000\
\000\000\012\000\000\000\014\000\015\000\000\000\017\000\018\000\
\019\000\000\000\007\000\000\000\000\000\008\000\009\000\010\000\
\011\000\013\000\016\000\020\000\000\000\005\000\000\000\004\000"

let yydgoto = "\002\000\
\024\000\025\000\026\000\027\000"

let yysindex = "\002\000\
\004\000\000\000\013\255\000\000\000\000\236\254\033\255\033\255\
\033\255\033\255\033\255\033\255\033\255\033\255\000\000\033\255\
\033\255\033\255\033\255\000\000\000\000\000\000\013\255\000\000\
\000\000\033\255\000\000\003\255\223\254\033\255\033\255\033\255\
\033\255\000\000\033\255\000\000\000\000\033\255\000\000\000\000\
\000\000\211\254\000\000\013\255\013\255\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\005\255\000\000\013\255\000\000"

let yyrindex = "\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\001\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"

let yygindex = "\000\000\
\000\000\253\255\000\000\055\000"

let yytablesize = 309
let yytable = "\028\000\
\003\000\029\000\001\000\022\000\044\000\045\000\052\000\055\000\
\000\000\000\000\000\000\000\000\000\000\003\000\000\000\000\000\
\004\000\005\000\006\000\042\000\007\000\008\000\009\000\010\000\
\011\000\012\000\013\000\014\000\015\000\016\000\017\000\018\000\
\019\000\000\000\020\000\021\000\004\000\005\000\000\000\000\000\
\053\000\054\000\000\000\000\000\000\000\000\000\000\000\000\000\
\015\000\000\000\000\000\056\000\000\000\000\000\020\000\021\000\
\000\000\000\000\000\000\023\000\000\000\030\000\031\000\032\000\
\033\000\034\000\035\000\036\000\037\000\000\000\038\000\039\000\
\040\000\041\000\000\000\000\000\000\000\000\000\000\000\023\000\
\043\000\000\000\000\000\000\000\046\000\047\000\048\000\049\000\
\000\000\050\000\000\000\000\000\051\000\000\000\000\000\000\000\
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
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\003\000\003\000\003\000\000\000\000\000\004\000\
\005\000\006\000\000\000\007\000\008\000\009\000\010\000\011\000\
\012\000\013\000\014\000\015\000\016\000\017\000\018\000\019\000\
\000\000\020\000\021\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\023\000\000\000\003\000"

let yycheck = "\003\000\
\000\000\022\001\001\000\000\000\002\001\039\001\052\001\003\001\
\255\255\255\255\255\255\255\255\255\255\001\001\255\255\255\255\
\004\001\005\001\006\001\023\000\008\001\009\001\010\001\011\001\
\012\001\013\001\014\001\015\001\016\001\017\001\018\001\019\001\
\020\001\255\255\022\001\023\001\004\001\005\001\255\255\255\255\
\044\000\045\000\255\255\255\255\255\255\255\255\255\255\255\255\
\016\001\255\255\255\255\055\000\255\255\255\255\022\001\023\001\
\255\255\255\255\255\255\047\001\255\255\007\000\008\000\009\000\
\010\000\011\000\012\000\013\000\014\000\255\255\016\000\017\000\
\018\000\019\000\255\255\255\255\255\255\255\255\255\255\047\001\
\026\000\255\255\255\255\255\255\030\000\031\000\032\000\033\000\
\255\255\035\000\255\255\255\255\038\000\255\255\255\255\255\255\
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
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\002\001\003\001\001\001\255\255\255\255\004\001\
\005\001\006\001\255\255\008\001\009\001\010\001\011\001\012\001\
\013\001\014\001\015\001\016\001\017\001\018\001\019\001\020\001\
\255\255\022\001\023\001\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\047\001\255\255\052\001"

let yynames_const = "\
  "

let yynames_block = "\
  IF\000\
  THEN\000\
  ELSE\000\
  TRUE\000\
  FALSE\000\
  LAMBDA\000\
  NAT\000\
  ADD\000\
  SUB\000\
  MUL\000\
  EQ\000\
  FIX\000\
  PAIR\000\
  FST\000\
  SND\000\
  NILL\000\
  CONS\000\
  HEAD\000\
  TAIL\000\
  ISNILL\000\
  UCID\000\
  LCID\000\
  INTV\000\
  STRINGV\000\
  APOSTROPHE\000\
  DQUOTE\000\
  ARROW\000\
  BANG\000\
  BARGT\000\
  BARRCURLY\000\
  BARRSQUARE\000\
  COLON\000\
  COLONCOLON\000\
  COLONEQ\000\
  COLONHASH\000\
  COMMA\000\
  DARROW\000\
  DDARROW\000\
  DOT\000\
  EOF\000\
  EQEQ\000\
  EXISTS\000\
  GT\000\
  HASH\000\
  LCURLY\000\
  LCURLYBAR\000\
  LEFTARROW\000\
  LPAREN\000\
  LSQUARE\000\
  LSQUAREBAR\000\
  LT\000\
  RCURLY\000\
  RPAREN\000\
  RSQUARE\000\
  SEMI\000\
  SLASH\000\
  STAR\000\
  TRIANGLE\000\
  USCORE\000\
  VBAR\000\
  "

let yyact = [|
  (fun _ -> failwith "parser")
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Support.Error.info) in
    Obj.repr(
# 118 "parser.mly"
      ( fun ctx -> None,ctx )
# 338 "parser.ml"
               :  Syntax.context -> (Syntax.term * Syntax.context) ))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'Term) in
    Obj.repr(
# 120 "parser.mly"
      ( fun ctx ->_1 ctx, ctx)
# 345 "parser.ml"
               :  Syntax.context -> (Syntax.term * Syntax.context) ))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'AppTerm) in
    Obj.repr(
# 125 "parser.mly"
      ( _1 )
# 352 "parser.ml"
               : 'Term))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 5 : Support.Error.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 4 : 'Term) in
    let _3 = (Parsing.peek_val __caml_parser_env 3 : Support.Error.info) in
    let _4 = (Parsing.peek_val __caml_parser_env 2 : 'Term) in
    let _5 = (Parsing.peek_val __caml_parser_env 1 : Support.Error.info) in
    let _6 = (Parsing.peek_val __caml_parser_env 0 : 'Term) in
    Obj.repr(
# 127 "parser.mly"
      ( fun ctx -> TmIf(_1, _2 ctx, _4 ctx, _6 ctx))
# 364 "parser.ml"
               : 'Term))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 3 : Support.Error.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 2 : string Support.Error.withinfo) in
    let _3 = (Parsing.peek_val __caml_parser_env 1 : Support.Error.info) in
    let _4 = (Parsing.peek_val __caml_parser_env 0 : 'Term) in
    Obj.repr(
# 129 "parser.mly"
      ( fun ctx ->
          let ctx1 = addname ctx _2.v in
          TmLambda(_1, _2.v, _4 ctx1))
# 376 "parser.ml"
               : 'Term))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'ATerm) in
    Obj.repr(
# 136 "parser.mly"
      ( _1 )
# 383 "parser.ml"
               : 'AppTerm))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'AppTerm) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'ATerm) in
    Obj.repr(
# 138 "parser.mly"
        ( fun ctx ->
            let e1 = _1 ctx in
            let e2 = _2 ctx in
            TmApp(tmInfo e1,e1,e2) )
# 394 "parser.ml"
               : 'AppTerm))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : Support.Error.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : 'ATerm) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'ATerm) in
    Obj.repr(
# 143 "parser.mly"
        ( fun ctx -> TmAdd(_1, _2 ctx, _3 ctx) )
# 403 "parser.ml"
               : 'AppTerm))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : Support.Error.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : 'ATerm) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'ATerm) in
    Obj.repr(
# 145 "parser.mly"
        ( fun ctx -> TmSub(_1, _2 ctx, _3 ctx) )
# 412 "parser.ml"
               : 'AppTerm))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : Support.Error.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : 'ATerm) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'ATerm) in
    Obj.repr(
# 147 "parser.mly"
        ( fun ctx -> TmAdd(_1, _2 ctx, _3 ctx) )
# 421 "parser.ml"
               : 'AppTerm))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : Support.Error.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : 'ATerm) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'ATerm) in
    Obj.repr(
# 149 "parser.mly"
      ( fun ctx -> TmEq(_1, _2 ctx, _3 ctx) )
# 430 "parser.ml"
               : 'AppTerm))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : Support.Error.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'ATerm) in
    Obj.repr(
# 151 "parser.mly"
      ( fun ctx -> TmFix(_1, _2 ctx) )
# 438 "parser.ml"
               : 'AppTerm))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : Support.Error.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : 'ATerm) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'ATerm) in
    Obj.repr(
# 153 "parser.mly"
      ( fun ctx -> TmPair(_1, _2 ctx, _3 ctx) )
# 447 "parser.ml"
               : 'AppTerm))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : Support.Error.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'ATerm) in
    Obj.repr(
# 155 "parser.mly"
      ( fun ctx -> TmFst(_1, _2 ctx) )
# 455 "parser.ml"
               : 'AppTerm))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : Support.Error.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'ATerm) in
    Obj.repr(
# 157 "parser.mly"
      ( fun ctx -> TmSnd(_1, _2 ctx) )
# 463 "parser.ml"
               : 'AppTerm))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : Support.Error.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : 'ATerm) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'ATerm) in
    Obj.repr(
# 159 "parser.mly"
      ( fun ctx -> TmCons(_1, _2 ctx, _3 ctx) )
# 472 "parser.ml"
               : 'AppTerm))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : Support.Error.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'ATerm) in
    Obj.repr(
# 161 "parser.mly"
      ( fun ctx -> TmHead(_1, _2 ctx) )
# 480 "parser.ml"
               : 'AppTerm))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : Support.Error.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'ATerm) in
    Obj.repr(
# 163 "parser.mly"
      ( fun ctx -> TmTail(_1, _2 ctx) )
# 488 "parser.ml"
               : 'AppTerm))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : Support.Error.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'ATerm) in
    Obj.repr(
# 165 "parser.mly"
      ( fun ctx -> TmIsNill(_1, _2 ctx) )
# 496 "parser.ml"
               : 'AppTerm))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : Support.Error.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : 'Term) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : Support.Error.info) in
    Obj.repr(
# 170 "parser.mly"
      ( _2 )
# 505 "parser.ml"
               : 'ATerm))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Support.Error.info) in
    Obj.repr(
# 172 "parser.mly"
      ( fun ctx -> TmTrue(_1) )
# 512 "parser.ml"
               : 'ATerm))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Support.Error.info) in
    Obj.repr(
# 174 "parser.mly"
      ( fun ctx -> TmFalse(_1) )
# 519 "parser.ml"
               : 'ATerm))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : string Support.Error.withinfo) in
    Obj.repr(
# 176 "parser.mly"
      ( fun ctx -> 
        TmVar (_1.i, _1.v) )
# 527 "parser.ml"
               : 'ATerm))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Support.Error.info) in
    Obj.repr(
# 179 "parser.mly"
      ( fun ctx -> TmNill(_1) )
# 534 "parser.ml"
               : 'ATerm))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : int Support.Error.withinfo) in
    Obj.repr(
# 181 "parser.mly"
      ( fun ctx ->
          let rec f n = match n with
              0 -> TmZero(_1.i)
            | n -> TmSucc(_1.i, f (n-1))
          in f _1.v )
# 545 "parser.ml"
               : 'ATerm))
(* Entry toplevel *)
; (fun __caml_parser_env -> raise (Parsing.YYexit (Parsing.peek_val __caml_parser_env 0)))
|]
let yytables =
  { Parsing.actions=yyact;
    Parsing.transl_const=yytransl_const;
    Parsing.transl_block=yytransl_block;
    Parsing.lhs=yylhs;
    Parsing.len=yylen;
    Parsing.defred=yydefred;
    Parsing.dgoto=yydgoto;
    Parsing.sindex=yysindex;
    Parsing.rindex=yyrindex;
    Parsing.gindex=yygindex;
    Parsing.tablesize=yytablesize;
    Parsing.table=yytable;
    Parsing.check=yycheck;
    Parsing.error_function=parse_error;
    Parsing.names_const=yynames_const;
    Parsing.names_block=yynames_block }
let toplevel (lexfun : Lexing.lexbuf -> token) (lexbuf : Lexing.lexbuf) =
   (Parsing.yyparse yytables 1 lexfun lexbuf :  Syntax.context -> (Syntax.term * Syntax.context) )

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
  | EXCEPTION of (Support.Error.info)
  | IN of (Support.Error.info)
  | THROW of (Support.Error.info)
  | OF of (Support.Error.info)
  | AS of (Support.Error.info)
  | TRY of (Support.Error.info)
  | CATCH of (Support.Error.info)
  | TNUM of (Support.Error.info)
  | TBOOL of (Support.Error.info)
  | TARROW of (Support.Error.info)
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
# 72 "parser.ml"
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
  269 (* EXCEPTION *);
  270 (* IN *);
  271 (* THROW *);
  272 (* OF *);
  273 (* AS *);
  274 (* TRY *);
  275 (* CATCH *);
  276 (* TNUM *);
  277 (* TBOOL *);
  278 (* TARROW *);
  279 (* UCID *);
  280 (* LCID *);
  281 (* INTV *);
  282 (* STRINGV *);
  283 (* APOSTROPHE *);
  284 (* DQUOTE *);
  285 (* ARROW *);
  286 (* BANG *);
  287 (* BARGT *);
  288 (* BARRCURLY *);
  289 (* BARRSQUARE *);
  290 (* COLON *);
  291 (* COLONCOLON *);
  292 (* COLONEQ *);
  293 (* COLONHASH *);
  294 (* COMMA *);
  295 (* DARROW *);
  296 (* DDARROW *);
  297 (* DOT *);
    0 (* EOF *);
  298 (* EQEQ *);
  299 (* EXISTS *);
  300 (* GT *);
  301 (* HASH *);
  302 (* LCURLY *);
  303 (* LCURLYBAR *);
  304 (* LEFTARROW *);
  305 (* LPAREN *);
  306 (* LSQUARE *);
  307 (* LSQUAREBAR *);
  308 (* LT *);
  309 (* RCURLY *);
  310 (* RPAREN *);
  311 (* RSQUARE *);
  312 (* SEMI *);
  313 (* SLASH *);
  314 (* STAR *);
  315 (* TRIANGLE *);
  316 (* USCORE *);
  317 (* VBAR *);
    0|]

let yylhs = "\255\255\
\001\000\001\000\003\000\003\000\004\000\004\000\004\000\002\000\
\002\000\002\000\005\000\005\000\005\000\005\000\005\000\005\000\
\005\000\005\000\005\000\005\000\007\000\007\000\008\000\006\000\
\006\000\006\000\006\000\006\000\000\000"

let yylen = "\002\000\
\001\000\003\000\003\000\001\000\001\000\001\000\003\000\001\000\
\006\000\006\000\001\000\002\000\003\000\003\000\003\000\003\000\
\002\000\006\000\005\000\006\000\001\000\003\000\004\000\003\000\
\001\000\001\000\001\000\001\000\002\000"

let yydefred = "\000\000\
\000\000\000\000\000\000\025\000\026\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\027\000\028\000\
\001\000\000\000\029\000\000\000\000\000\011\000\000\000\000\000\
\000\000\000\000\000\000\000\000\017\000\000\000\000\000\000\000\
\000\000\000\000\012\000\000\000\000\000\013\000\014\000\015\000\
\016\000\000\000\000\000\000\000\024\000\002\000\000\000\006\000\
\005\000\000\000\000\000\000\000\004\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\019\000\000\000\000\000\
\000\000\009\000\003\000\007\000\010\000\018\000\000\000\020\000\
\000\000\000\000\022\000\023\000"

let yydgoto = "\002\000\
\019\000\020\000\052\000\053\000\021\000\022\000\064\000\065\000"

let yysindex = "\013\000\
\001\000\000\000\064\255\000\000\000\000\007\255\254\254\254\254\
\254\254\254\254\254\254\010\255\011\255\254\254\000\000\000\000\
\000\000\064\255\000\000\236\254\254\254\000\000\035\255\004\255\
\254\254\254\254\254\254\254\254\000\000\023\255\254\254\022\255\
\244\254\001\000\000\000\064\255\252\254\000\000\000\000\000\000\
\000\000\252\254\026\255\000\255\000\000\000\000\041\255\000\000\
\000\000\247\254\252\254\008\255\000\000\034\255\252\254\027\255\
\064\255\247\254\255\254\064\255\254\254\000\000\028\255\253\254\
\001\255\000\000\000\000\000\000\000\000\000\000\019\255\000\000\
\027\255\064\255\000\000\000\000"

let yyrindex = "\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\002\255\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\013\255\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000"

let yygindex = "\000\000\
\027\000\253\255\233\255\227\255\000\000\255\255\247\255\000\000"

let yytablesize = 306
let yytable = "\023\000\
\017\000\004\000\005\000\008\000\008\000\025\000\026\000\027\000\
\028\000\029\000\048\000\049\000\032\000\001\000\033\000\048\000\
\049\000\050\000\054\000\035\000\058\000\015\000\016\000\038\000\
\039\000\040\000\041\000\059\000\067\000\043\000\024\000\062\000\
\047\000\030\000\031\000\034\000\036\000\037\000\042\000\051\000\
\044\000\045\000\055\000\057\000\051\000\056\000\018\000\061\000\
\060\000\072\000\063\000\071\000\068\000\066\000\008\000\008\000\
\069\000\008\000\074\000\070\000\046\000\073\000\008\000\075\000\
\003\000\021\000\000\000\004\000\005\000\006\000\076\000\007\000\
\008\000\009\000\010\000\011\000\012\000\000\000\013\000\000\000\
\000\000\014\000\000\000\000\000\000\000\000\000\000\000\015\000\
\016\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\018\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
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
\000\000\003\000\000\000\000\000\004\000\005\000\006\000\000\000\
\007\000\008\000\009\000\010\000\011\000\012\000\000\000\013\000\
\000\000\000\000\014\000\000\000\000\000\000\000\000\000\000\000\
\015\000\016\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\018\000"

let yycheck = "\003\000\
\000\000\004\001\005\001\002\001\003\001\007\000\008\000\009\000\
\010\000\011\000\020\001\021\001\014\000\001\000\018\000\020\001\
\021\001\022\001\042\000\021\000\050\000\024\001\025\001\025\000\
\026\000\027\000\028\000\051\000\058\000\031\000\024\001\055\000\
\036\000\024\001\024\001\056\001\002\001\034\001\016\001\049\001\
\019\001\054\001\017\001\003\001\049\001\046\001\049\001\014\001\
\041\001\053\001\024\001\024\001\054\001\057\000\053\001\054\001\
\060\000\056\001\040\001\061\000\034\000\061\001\061\001\073\000\
\001\001\053\001\255\255\004\001\005\001\006\001\074\000\008\001\
\009\001\010\001\011\001\012\001\013\001\255\255\015\001\255\255\
\255\255\018\001\255\255\255\255\255\255\255\255\255\255\024\001\
\025\001\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\049\001\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
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
\255\255\001\001\255\255\255\255\004\001\005\001\006\001\255\255\
\008\001\009\001\010\001\011\001\012\001\013\001\255\255\015\001\
\255\255\255\255\018\001\255\255\255\255\255\255\255\255\255\255\
\024\001\025\001\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\049\001"

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
  EXCEPTION\000\
  IN\000\
  THROW\000\
  OF\000\
  AS\000\
  TRY\000\
  CATCH\000\
  TNUM\000\
  TBOOL\000\
  TARROW\000\
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
# 121 "parser.mly"
    ( fun ctx -> [] )
# 353 "parser.ml"
               :  Syntax.context -> ((Syntax.term list)) ))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'Term) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : Support.Error.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 :  Syntax.context -> ((Syntax.term list)) ) in
    Obj.repr(
# 123 "parser.mly"
    ( fun ctx ->
        let cmd = _1 ctx in
        let cmds = _3 ctx in
        (cmd::cmds) )
# 365 "parser.ml"
               :  Syntax.context -> ((Syntax.term list)) ))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : Support.Error.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : 'AtomicType) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'AtomicType) in
    Obj.repr(
# 130 "parser.mly"
  (TyArrow (_2, _3))
# 374 "parser.ml"
               : 'Type))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'AtomicType) in
    Obj.repr(
# 132 "parser.mly"
  (_1)
# 381 "parser.ml"
               : 'Type))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Support.Error.info) in
    Obj.repr(
# 136 "parser.mly"
  (TyBool)
# 388 "parser.ml"
               : 'AtomicType))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Support.Error.info) in
    Obj.repr(
# 138 "parser.mly"
  (TyNum)
# 395 "parser.ml"
               : 'AtomicType))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : Support.Error.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : 'Type) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : Support.Error.info) in
    Obj.repr(
# 140 "parser.mly"
  (_2)
# 404 "parser.ml"
               : 'AtomicType))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'AppTerm) in
    Obj.repr(
# 145 "parser.mly"
      ( _1 )
# 411 "parser.ml"
               : 'Term))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 5 : Support.Error.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 4 : 'Term) in
    let _3 = (Parsing.peek_val __caml_parser_env 3 : Support.Error.info) in
    let _4 = (Parsing.peek_val __caml_parser_env 2 : 'Term) in
    let _5 = (Parsing.peek_val __caml_parser_env 1 : Support.Error.info) in
    let _6 = (Parsing.peek_val __caml_parser_env 0 : 'Term) in
    Obj.repr(
# 147 "parser.mly"
      ( fun ctx -> TmIf(_1, _2 ctx, _4 ctx, _6 ctx))
# 423 "parser.ml"
               : 'Term))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 5 : Support.Error.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 4 : string Support.Error.withinfo) in
    let _3 = (Parsing.peek_val __caml_parser_env 3 : Support.Error.info) in
    let _4 = (Parsing.peek_val __caml_parser_env 2 : 'Type) in
    let _5 = (Parsing.peek_val __caml_parser_env 1 : Support.Error.info) in
    let _6 = (Parsing.peek_val __caml_parser_env 0 : 'Term) in
    Obj.repr(
# 149 "parser.mly"
      ( fun ctx ->
          let ctx1 = addname ctx _2.v in
          TmLambda(_1, _4,  _6 ctx1))
# 437 "parser.ml"
               : 'Term))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'ATerm) in
    Obj.repr(
# 156 "parser.mly"
      ( _1 )
# 444 "parser.ml"
               : 'AppTerm))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'AppTerm) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'ATerm) in
    Obj.repr(
# 158 "parser.mly"
        ( fun ctx ->
            let e1 = _1 ctx in
            let e2 = _2 ctx in
            TmApp(tmInfo e1,e1,e2) )
# 455 "parser.ml"
               : 'AppTerm))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : Support.Error.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : 'ATerm) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'ATerm) in
    Obj.repr(
# 163 "parser.mly"
        ( fun ctx -> TmAdd(_1, _2 ctx, _3 ctx) )
# 464 "parser.ml"
               : 'AppTerm))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : Support.Error.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : 'ATerm) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'ATerm) in
    Obj.repr(
# 165 "parser.mly"
        ( fun ctx -> TmSub(_1, _2 ctx, _3 ctx) )
# 473 "parser.ml"
               : 'AppTerm))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : Support.Error.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : 'ATerm) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'ATerm) in
    Obj.repr(
# 167 "parser.mly"
        ( fun ctx -> TmMul (_1, _2 ctx, _3 ctx) )
# 482 "parser.ml"
               : 'AppTerm))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : Support.Error.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : 'ATerm) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'ATerm) in
    Obj.repr(
# 169 "parser.mly"
      ( fun ctx -> TmEq(_1, _2 ctx, _3 ctx) )
# 491 "parser.ml"
               : 'AppTerm))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : Support.Error.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'ATerm) in
    Obj.repr(
# 171 "parser.mly"
      ( fun ctx -> TmFix(_1, _2 ctx) )
# 499 "parser.ml"
               : 'AppTerm))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 5 : Support.Error.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 4 : string Support.Error.withinfo) in
    let _3 = (Parsing.peek_val __caml_parser_env 3 : Support.Error.info) in
    let _4 = (Parsing.peek_val __caml_parser_env 2 : 'Type) in
    let _5 = (Parsing.peek_val __caml_parser_env 1 : Support.Error.info) in
    let _6 = (Parsing.peek_val __caml_parser_env 0 : 'ATerm) in
    Obj.repr(
# 173 "parser.mly"
      ( fun ctx -> 
        let ctx' = addexception ctx _2.v  in
        TmException(_1, _2.v, _4, _6 ctx'))
# 513 "parser.ml"
               : 'AppTerm))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 4 : Support.Error.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 3 : string Support.Error.withinfo) in
    let _3 = (Parsing.peek_val __caml_parser_env 2 : 'ATerm) in
    let _4 = (Parsing.peek_val __caml_parser_env 1 : Support.Error.info) in
    let _5 = (Parsing.peek_val __caml_parser_env 0 : 'Type) in
    Obj.repr(
# 177 "parser.mly"
      ( fun ctx -> 
        if isexceptionbound ctx _2.v
        then
          TmThrow(_1, (exceptionname2index _1 ctx _2.v), _3 ctx, _5)
        else error _1 "unbound exception identifier")
# 528 "parser.ml"
               : 'AppTerm))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 5 : Support.Error.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 4 : 'ATerm) in
    let _3 = (Parsing.peek_val __caml_parser_env 3 : Support.Error.info) in
    let _4 = (Parsing.peek_val __caml_parser_env 2 : Support.Error.info) in
    let _5 = (Parsing.peek_val __caml_parser_env 1 : 'ErrorCases) in
    let _6 = (Parsing.peek_val __caml_parser_env 0 : Support.Error.info) in
    Obj.repr(
# 183 "parser.mly"
      ( fun ctx -> TmTry(_1, _2 ctx, _5 ctx))
# 540 "parser.ml"
               : 'AppTerm))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'ErrorCase) in
    Obj.repr(
# 187 "parser.mly"
      ( fun ctx -> [_1 ctx] )
# 547 "parser.ml"
               : 'ErrorCases))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'ErrorCase) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : Support.Error.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'ErrorCases) in
    Obj.repr(
# 189 "parser.mly"
      ( fun ctx -> (_1 ctx) :: (_3 ctx) )
# 556 "parser.ml"
               : 'ErrorCases))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 3 : string Support.Error.withinfo) in
    let _2 = (Parsing.peek_val __caml_parser_env 2 : string Support.Error.withinfo) in
    let _3 = (Parsing.peek_val __caml_parser_env 1 : Support.Error.info) in
    let _4 = (Parsing.peek_val __caml_parser_env 0 : 'Term) in
    Obj.repr(
# 193 "parser.mly"
      ( fun ctx -> 
            let ctx1 = addname ctx _2.v in
            ((exceptionname2index _3 ctx _1.v), _4 ctx1) )
# 568 "parser.ml"
               : 'ErrorCase))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : Support.Error.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : 'Term) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : Support.Error.info) in
    Obj.repr(
# 200 "parser.mly"
      ( _2 )
# 577 "parser.ml"
               : 'ATerm))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Support.Error.info) in
    Obj.repr(
# 202 "parser.mly"
      ( fun ctx -> TmBool(_1, true) )
# 584 "parser.ml"
               : 'ATerm))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Support.Error.info) in
    Obj.repr(
# 204 "parser.mly"
      ( fun ctx -> TmBool(_1, false) )
# 591 "parser.ml"
               : 'ATerm))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : string Support.Error.withinfo) in
    Obj.repr(
# 206 "parser.mly"
      ( fun ctx -> 
        if isnamebound ctx _1.v 
        then 
            TmVarB(_1.i, name2index _1.i ctx _1.v)
        else
            error _1.i "Undefined variable"
      )
# 604 "parser.ml"
               : 'ATerm))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : int Support.Error.withinfo) in
    Obj.repr(
# 214 "parser.mly"
      ( fun ctx -> TmNat(_1.i, _1.v) )
# 611 "parser.ml"
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
   (Parsing.yyparse yytables 1 lexfun lexbuf :  Syntax.context -> ((Syntax.term list)) )

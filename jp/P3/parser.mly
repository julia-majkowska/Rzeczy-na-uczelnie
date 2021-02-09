/*  
 *  Yacc grammar for the parser.  The files parser.mli and parser.ml
 *  are generated automatically from parser.mly.
 */

%{
open Support.Error
open Support.Pervasive
open Syntax
%}

/* ---------------------------------------------------------------------- */
/* Preliminaries */

/* We first list all the tokens mentioned in the parsing rules
   below.  The names of the tokens are common to the parser and the
   generated lexical analyzer.  Each token is annotated with the type
   of data that it carries; normally, this is just file information
   (which is used by the parser to annotate the abstract syntax trees
   that it constructs), but sometimes -- in the case of identifiers and
   constant values -- more information is provided.
 */

/* Keyword tokens */
%token <Support.Error.info> IF
%token <Support.Error.info> THEN
%token <Support.Error.info> ELSE
%token <Support.Error.info> TRUE
%token <Support.Error.info> FALSE
%token <Support.Error.info> LAMBDA
%token <Support.Error.info> NAT
%token <Support.Error.info> ADD
%token <Support.Error.info> SUB
%token <Support.Error.info> MUL
%token <Support.Error.info> EQ
%token <Support.Error.info> FIX
%token <Support.Error.info> NAT
%token <Support.Error.info> EXCEPTION
%token <Support.Error.info> IN
%token <Support.Error.info> THROW
%token <Support.Error.info> OF
%token <Support.Error.info> AS
%token <Support.Error.info> TRY
%token <Support.Error.info> CATCH
%token <Support.Error.info> TNUM
%token <Support.Error.info> TBOOL
%token <Support.Error.info> TARROW
%token <Support.Error.info> TARROW
%token <Support.Error.info> TUNIT
%token <Support.Error.info> TVOID
%token <Support.Error.info> TSUM
%token <Support.Error.info> TPROD
%token <Support.Error.info> ABORT
%token <Support.Error.info> CASE
%token <Support.Error.info> IN1
%token <Support.Error.info> IN2
  


/* Identifier and constant value tokens */
%token <string Support.Error.withinfo> UCID  /* uppercase-initial */
%token <string Support.Error.withinfo> LCID  /* lowercase/symbolic-initial */
%token <int Support.Error.withinfo> INTV
%token <string Support.Error.withinfo> STRINGV

/* Symbolic tokens */
%token <Support.Error.info> APOSTROPHE
%token <Support.Error.info> DQUOTE
%token <Support.Error.info> ARROW
%token <Support.Error.info> BANG
%token <Support.Error.info> BARGT
%token <Support.Error.info> BARRCURLY
%token <Support.Error.info> BARRSQUARE
%token <Support.Error.info> COLON
%token <Support.Error.info> COLONCOLON
%token <Support.Error.info> COLONEQ
%token <Support.Error.info> COLONHASH
%token <Support.Error.info> COMMA
%token <Support.Error.info> DARROW
%token <Support.Error.info> DDARROW
%token <Support.Error.info> DOT
%token <Support.Error.info> EOF
%token <Support.Error.info> EQ
%token <Support.Error.info> EQEQ
%token <Support.Error.info> EXISTS
%token <Support.Error.info> GT
%token <Support.Error.info> HASH
%token <Support.Error.info> LCURLY
%token <Support.Error.info> LCURLYBAR
%token <Support.Error.info> LEFTARROW
%token <Support.Error.info> LPAREN
%token <Support.Error.info> LSQUARE
%token <Support.Error.info> LSQUAREBAR
%token <Support.Error.info> LT
%token <Support.Error.info> RCURLY
%token <Support.Error.info> RPAREN
%token <Support.Error.info> RSQUARE
%token <Support.Error.info> SEMI
%token <Support.Error.info> SLASH
%token <Support.Error.info> STAR
%token <Support.Error.info> TRIANGLE
%token <Support.Error.info> USCORE
%token <Support.Error.info> VBAR

/* ---------------------------------------------------------------------- */
/* The starting production of the generated parser is the syntactic class
   toplevel.  The type that is returned when a toplevel is recognized is
     Syntax.context -> (Syntax.command list * Syntax.context) 
   that is, the parser returns to the user program a function that,
   when given a naming context, returns a fully parsed list of
   Syntax.commands and the new naming context that results when
   all the names bound in these commands are defined.

   All of the syntactic productions in the parser follow the same pattern:
   they take a context as argument and return a fully parsed abstract
   syntax tree (and, if they involve any constructs that bind variables
   in some following phrase, a new context).
   
*/

%start toplevel
%type < Syntax.context -> ((Syntax.term list)) > toplevel
%%

/* ---------------------------------------------------------------------- */
/* Main body of the parser definition */

/* The top level of a file is a sequence of commands, each terminated
   by a semicolon. */
toplevel :
  | EOF
    { fun ctx -> [] }
  | Term SEMI toplevel
    { fun ctx ->
        let cmd = $1 ctx in
        let cmds = $3 ctx in
        (cmd::cmds) }

Type : 
| TARROW AtomicType AtomicType 
  {TyArrow ($2, $3)}
| TPROD AtomicType AtomicType 
  {TyProd ($2, $3)}
| TSUM AtomicType AtomicType 
  {TyArrow ($2, $3)}
| AtomicType
  {$1}

AtomicType : 
| TUNIT 
  {TyUnit}
| TVOID
  {TyVoid}
| LPAREN Type RPAREN
  {$2}


Term :
    AppTerm
      { $1 }
  | LAMBDA LCID DOT Term 
      { fun ctx ->
          let ctx1 = addname ctx $2.v in
          TmLambda($1,  $4 ctx1)}


AppTerm :
    | ATerm
      { $1 }
    | AppTerm ATerm
        { fun ctx ->
            let e1 = $1 ctx in
            let e2 = $2 ctx in
            TmApp(tmInfo e1,e1,e2) }
    | LT ATerm COMMA ATerm GT
        { fun ctx -> TmProd($1, $2 ctx, $4 ctx) }
    | ATerm DOT INTV 
        { fun ctx -> 
          if $3.v > 0 && $3.v < 3 
          then 
            TmElem($2, $1 ctx, $3.v)
          else 
            error $2 "Product element index out of range" }
    | ABORT ATerm
        { fun ctx -> TmAbort($1, $2 ctx) }
    | IN1 ATerm
        { fun ctx -> TmIn($1, $2 ctx, 1) }
    | IN2 ATerm
        { fun ctx -> TmIn($1, $2 ctx, 2) }
    | CASE ATerm OF IN1 LCID DARROW ATerm VBAR IN2 LCID DARROW ATerm
        { fun ctx -> 
          let ctx1 = addname ctx $5.v in
          let ctx2 = addname ctx $10.v in
          TmCase($1, $2 ctx, $7 ctx1, $12 ctx2) }
    

/* Atomic terms are ones that never require extra parentheses */
ATerm :
    LPAREN Term RPAREN  
      { $2 } 
  | LPAREN RPAREN
      { fun ctx -> TmUnit($1) }
  | LCID 
      { fun ctx -> 
        if isnamebound ctx $1.v 
        then 
            TmVar($1.i, name2index $1.i ctx $1.v)
        else
            error $1.i "Undefined variable"
      }


/*   */

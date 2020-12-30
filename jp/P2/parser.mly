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
%token <Support.Error.info> THROW
%token <Support.Error.info> TRY
%token <Support.Error.info> CATCH
%token <Support.Error.info> TNUM
%token <Support.Error.info> TBOOL
%token <Support.Error.info> TARROW

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
| AtomicType

AtomicType : 
| TBOOL 
  {TyBool}
| TNUM
  {TyNum}
| (Type)
  {$1}


Term :
    AppTerm
      { $1 }
  | IF Term THEN Term ELSE Term
      { fun ctx -> TmIf($1, $2 ctx, $4 ctx, $6 ctx)}
  | LAMBDA LCID COLON Type DOT Term 
      { fun ctx ->
          let ctx1 = addname ctx $2.v in
          TmLambda($1, $3,  $5 ctx1)}


AppTerm :
    | ATerm
      { $1 }
    | AppTerm ATerm
        { fun ctx ->
            let e1 = $1 ctx in
            let e2 = $2 ctx in
            TmApp(tmInfo e1,e1,e2) }
    | ADD ATerm ATerm
        { fun ctx -> TmAdd($1, $2 ctx, $3 ctx) }
    | SUB ATerm ATerm
        { fun ctx -> TmSub($1, $2 ctx, $3 ctx) }
    | MUL ATerm ATerm
        { fun ctx -> TmMul ($1, $2 ctx, $3 ctx) }
    | EQ ATerm ATerm
      { fun ctx -> TmEq($1, $2 ctx, $3 ctx) }
    | FIX ATerm
      { fun ctx -> TmFix($1, $2 ctx) }
    | EXCEPTION LCID OF Type IN Term 
      { fun ctx -> 
        let ctx' = add_exception $2.v ctx
        TmException($1, $2.v, $4, $6 ctx')}
    | THROW LCID Term AS Type 
      { fun ctx -> 
        if isexceptionbound ctx $2.value
        then
          TmThrow($1, exceptionnametoindex $2.v, $3 ctx, $5)}
    | TRY Term CATCH LCURLY ErrorCases RCURLY
      { fun ctx -> TmTry($1, $2 ctx, $5 ctx)}

ErrorCases :
    ErrorCase
      { fun ctx -> [$1 ctx] }
  | ErrorCase COLON ErrorCases
      { fun ctx -> ($1 ctx) :: ($3 ctx) }

ErrorCase :
    LCID LCID DDARROW Term
      { fun ctx -> 
            (($1.v, $2.v), $4 ctx) }

/* Atomic terms are ones that never require extra parentheses */
ATerm :
    LPAREN Term RPAREN  
      { $2 } 
  | TRUE
      { fun ctx -> TmBool($1, true) }
  | FALSE
      { fun ctx -> TmBool($1, false) }
  | LCID 
      { fun ctx -> 
        if isnamebound ctx $1.v 
        then 
            TmVarB($1.i, name2index $1.i ctx $1.v)
        else
            error $1 "Undefined variable"
      }
  | INTV
      { fun ctx -> TmNat($1, $1.v) }


/*   */

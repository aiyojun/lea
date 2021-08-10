%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lang/grammar.h"
void yyerror(const char* s);
extern int yylex(void);
extern int yyparse(void);
char lea_file[128];
%}

%union {
    char* ycText;
    char* ycType;
    int ycValueInt;
    double ycValueDouble;
    unsigned short ycValueBool;
    char ycValueChar;
    char* ycOther;
}

%token KW_EOF
%token COMMENT_SINGLE COMMENT_BEGIN COMMENT_END
%token KW_BYTE
%token KW_CHAR
%token KW_STRING
%token KW_INT
%token KW_DOUBLE
%token KW_BOOL
%token <ycBool> KW_TRUE
%token <ycBool> KW_FALSE
%token KW_IF KW_ELSE KW_FOR KW_WHILE KW_MATCH KW_CASE KW__ KW_CLASS KW_STRUCT
%token <ycText> KW_DEF
%token <ycText> KW_RETURN
%token AND OR NOT EQ NE GT GE LT LE
%token ARROW ASSIGN LPAREN RPAREN DOT COMMA SEMI NEWLINE BLOCK_BEGIN BLOCK_END
%token <ycText> COLON
%token <ycValueDouble> DOUBLE
%token <ycValueInt> INTEGER
%token <ycText> FIELD
%token <ycValueChar> CHAR
%token <ycText> STRING
%token OP_ADD OP_SUB OP_MUL OP_DIV OP_MOD

%type <ycText> variableName
%type <ycText> leaVal
%type <ycText> booExp
%type <ycText> booAtom
%type <ycText> calExp
%type <ycText> calExpPro
%type <ycText> calExpAtom
%type <ycText> leaNum

%start root

%%

root: {_lea(lea_file);} statement;

statement:
  KW_EOF                                            {printf("Grammar parsed success.\n"); complete(); exit(0);}
| ending statement
| commentDefine statement
| variableDefine statement
| variableAssign statement
| invokeDefine statement
| functionDefine statement
| stateIfDefine statement
| stateForDefine statement
| stateMatchDefine statement
| {_scope_ano(lea_line);} codeBlockDefine {_scope_end(NULL);} statement
;


baseInput: COMMENT_SINGLE|KW_BYTE|KW_CHAR|KW_STRING|KW_INT|KW_DOUBLE|KW_BOOL|
KW_TRUE|KW_FALSE|KW_IF|KW_ELSE|KW_FOR|KW_WHILE|KW_MATCH|KW_CASE|KW_DEF|KW__|KW_STRUCT|KW_CLASS|KW_RETURN|
AND|OR|NOT|EQ|NE|GT|GE|LT|LE|
ARROW|ASSIGN|LPAREN|RPAREN|DOT|COMMA|SEMI|COLON|BLOCK_BEGIN|BLOCK_END|
DOUBLE|INTEGER|FIELD|CHAR|STRING|
OP_ADD|OP_SUB|OP_MUL|OP_DIV|OP_MOD;

// --------------------------------------------
// define comment
// --------------------------------------------
commentDefine: sc | mc;
sc: COMMENT_SINGLE singleComment;
mc: COMMENT_BEGIN {_open_mc();} multiComment;
singleComment: baseInput singleComment | NEWLINE    {_p_yacc("-multiComment-end\n");}
;
multiComment: baseInput2 multiComment | COMMENT_END {_close_mc();_p_yacc("-multiComment-end\n");}
;
baseInput2: baseInput | COMMENT_BEGIN | NEWLINE;
// --------------------------------------------

// --------------------------------------------
// define variable
// --------------------------------------------
variableDefine: variableName COLON basicType   {_var_def($2);};
variableAssign:
  variableName COLON basicType ASSIGN leaVal   {_var_def_ass($1);_p_yacc("-assign-type\n");}
| variableName ASSIGN leaVal                   {_var_ass($1);_p_yacc("-assign\n");}
;
variableName: FIELD                            {$$ = $1; _push($1);};
// --------------------------------------------

// --------------------------------------------
// define function
// --------------------------------------------
functionDefine: KW_DEF FIELD {_scope_begin($2); _def($2);} functionOptions {_scope_end(NULL);};
functionOptions:
  functionBody                                  {_p_yacc("-{}\n");}
| COLON returnType functionBody                 {_p_yacc("-type-{}\n");}
| lparen argsList functionBody                  {_p_yacc("-()-{}\n");}
| lparen argsList COLON returnType functionBody {_p_yacc("-()-type-{}\n");}
;
lparen: LPAREN;
argsList: RPAREN | FIELD COLON basicType argsLoop;
argsLoop: COMMA FIELD COLON basicType argsList | RPAREN;
returnType: basicType;
functionBody: ARROW leaVal {_p_yacc("-lambda\n");} | codeBlockDefine;
// --------------------------------------------

// --------------------------------------------
// define function invoke
// --------------------------------------------
invokeDefine: variableName LPAREN invokeArgsList;
invokeArgsList: invokeArgsLoop | {_add_arg();} leaVal invokeArgsLoop;
invokeArgsLoop: {_add_arg();} COMMA leaVal invokeArgsList | RPAREN {_call(1);};
// --------------------------------------------

// --------------------------------------------
// define if-else if-else
// --------------------------------------------
stateIfDefine: stateIf stateElse;
stateIf: KW_IF {_scope_begin("if");} LPAREN leaVal RPAREN codeBlockDefine {_scope_end("if"); _if(); _p_yacc("-if\n");}
;
stateElse: ending | stateElseApp;
stateElseApp: ending | KW_ELSE stateElseLoop;
stateElseLoop:
  {_p_yacc("-elif\n"); _scope_begin("elif");} KW_IF LPAREN leaVal RPAREN codeBlockDefine {_scope_end("elif"); _elif();} stateElseApp
| {_p_yacc("-else\n"); _scope_begin("else");} codeBlockDefine {_scope_end("else"); _else();}
;
// --------------------------------------------

// --------------------------------------------
// define for-loop
// --------------------------------------------
stateForDefine: KW_FOR LPAREN stateForInit stateForCondition stateForUpdate {_scope_begin("for"); _for();} codeBlockDefine {_scope_end("for");}
;
stateForInit: SEMI | variableAssign SEMI;
stateForCondition: SEMI | leaVal SEMI;
stateForUpdate: RPAREN | variableAssign RPAREN;
// --------------------------------------------

// --------------------------------------------
// define match-case
// --------------------------------------------
stateMatchDefine: variableName KW_MATCH {_match();} stateMatchBlock;
stateMatchBlock: BLOCK_BEGIN stateCase;
stateCase:
  wordCase KW__ {_case();} ARROW stateCaseTail stateCaseLoop
| wordCase basicType {_case();} ARROW stateCaseTail stateCaseLoop
| wordCase leaVal {_case();} ARROW stateCaseTail stateCaseLoop
| ending stateCaseLoop
;
stateCaseLoop: stateCase | BLOCK_END;
wordCase: KW_CASE;
stateCaseTail: {_scope_begin("case");} codeBlockDefine {_scope_end("case");} | leaVal ending;
// --------------------------------------------

// --------------------------------------------
// define code block
// --------------------------------------------
codeBlockDefine: BLOCK_BEGIN {_block();} codeBlockLoop;
codeBlockLoop:
  ending codeBlockLoop
| variableDefine codeBlockLoop
| variableAssign codeBlockLoop
| invokeDefine codeBlockLoop
| commentDefine codeBlockLoop
| stateIfDefine codeBlockLoop
| stateForDefine codeBlockLoop
| stateMatchDefine statement
| {_scope_ano(lea_line);} codeBlockDefine {_scope_end(NULL);} codeBlockLoop
| BLOCK_END                                     {_block_();_p_yacc("-block-end\n");}
;
// --------------------------------------------


// --------------------------------------------
// define right value of variable and function return
// --------------------------------------------
// represent variable/function-invoking
leaVai: leaVar {_p_yacc("[y] is var\n");} | leaVar LPAREN leaInv {_p_yacc("[y] is invoke\n");};
leaVar: FIELD;
leaInv: RPAREN | leaInvOptions; // args list
leaInvOptions: leaBas leaInvLoop | leaVai leaInvLoop; // args list
leaInvLoop: COMMA leaInvOptions | RPAREN;
// --------------------------------------------

// --------------------------------------------
// define bool expression
// --------------------------------------------
leaVal: booExp;
booExp: // Don't use! inner implement!
  booAtom
| booAtom AND booAtom
| booAtom OR booAtom
| NOT booAtom
;
booAtom: // Don't use! inner implement!
  calExp
| calExp LT calExp
| calExp GT calExp
| calExp LE calExp
| calExp GE calExp
| calExp EQ calExp
| calExp NE calExp
| booBas
;
// --------------------------------------------

// --------------------------------------------
// define calculation expression
// --------------------------------------------
calExp:
  calExpPro
| calExp OP_ADD calExpPro
| calExp OP_SUB calExpPro
;
calExpPro: // Don't use! inner implement!
  calExpAtom
| calExpPro OP_MUL calExpAtom
| calExpPro OP_DIV calExpAtom
;
calExpAtom: // Don't use! inner implement!
  leaNum {$$ = "num";}
| CHAR {$$ = "char";}
| STRING {$$ = $1; printf("- %s\n", $1); _add_arg_str($1);}
| LPAREN booExp RPAREN {$$ = "(xxx)";} // solve "(" matching and loop back to the top level
| leaVai {$$ = "1.0";}
;
// --------------------------------------------

// --------------------------------------------
// common definition
// --------------------------------------------
leaBas: CHAR|OP_SUB INTEGER|INTEGER|DOUBLE|STRING|booBas; // specific value
leaNum: OP_SUB INTEGER|INTEGER|DOUBLE;
booBas: KW_TRUE|KW_FALSE;
ending: SEMI | NEWLINE;
basicType: KW_BYTE | KW_CHAR | KW_INT | KW_BOOL | KW_DOUBLE | KW_STRING;
// --------------------------------------------

%%

void yyerror(const char* s)
{
    printf("Grammar error : %s\n", s);
}
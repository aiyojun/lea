%{
#include <stdio.h>
#include <stdlib.h>
#include "grammar.h"
void yyerror(const char* s);
extern int yylex(void);
extern int yyparse(void);


%}

%token KW_EOF
%token COMMENT_SINGLE COMMENT_BEGIN COMMENT_END
%token KW_BYTE KW_CHAR KW_STRING KW_INT KW_DOUBLE KW_BOOL
%token KW_TRUE KW_FALSE
%token KW_IF KW_ELSE KW_FOR KW_WHILE KW_MATCH KW_CASE KW__ KW_DEF KW_CLASS KW_STRUCT
%token AND OR NOT EQ NE GT GE LT LE
%token ARROW ASSIGN LPAREN RPAREN DOT COMMA SEMI COLON NEWLINE BLOCK_BEGIN BLOCK_END
%token DOUBLE INTEGER FIELD CHAR STRING
%token OP_ADD OP_SUB OP_MUL OP_DIV OP_MOD

%start root

%%

root: statement;

statement:
  KW_EOF                                            {printf("Grammar parsed success.\n");exit(0);}
| ending statement
| commentDefine statement
| variableDefine statement
| variableAssign statement
| invokeDefine statement
| functionDefine statement
| stateIfDefine statement
| stateForDefine statement
| stateMatchDefine statement
| codeBlockDefine statement
;


baseInput: COMMENT_SINGLE|KW_BYTE|KW_CHAR|KW_STRING|KW_INT|KW_DOUBLE|KW_BOOL|
KW_TRUE|KW_FALSE|KW_IF|KW_ELSE|KW_FOR|KW_WHILE|KW_MATCH|KW_CASE|KW_DEF|KW__|KW_STRUCT|KW_CLASS|
AND|OR|NOT|EQ|NE|GT|GE|LT|LE|
ARROW|ASSIGN|LPAREN|RPAREN|DOT|COMMA|SEMI|COLON|BLOCK_BEGIN|BLOCK_END|
DOUBLE|INTEGER|FIELD|CHAR|STRING|
OP_ADD|OP_SUB|OP_MUL|OP_DIV|OP_MOD;

// --------------------------------------------
// define comment
// --------------------------------------------
commentDefine: sc | mc;
sc: COMMENT_SINGLE singleComment;
mc: COMMENT_BEGIN multiComment;
singleComment: baseInput singleComment | NEWLINE    {_p_yacc("-multiComment-end\n");}
;
multiComment: baseInput2 multiComment | COMMENT_END {_p_yacc("-multiComment-end\n");}
;
baseInput2: baseInput | COMMENT_BEGIN | NEWLINE;
// --------------------------------------------

// --------------------------------------------
// define variable
// --------------------------------------------
variableDefine: variableName COLON basicType   {_var_def();};
variableAssign:
  variableName COLON basicType ASSIGN leaVal   {_var_def_ass();_p_yacc("-assign-type\n");}
| variableName ASSIGN leaVal                   {_var_ass();_p_yacc("-assign\n");}
;
variableName: FIELD;
// --------------------------------------------

// --------------------------------------------
// define function
// --------------------------------------------
functionDefine: KW_DEF FIELD functionOptions    {_def();};
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
invokeDefine: variableName LPAREN invokeArgsList {_call(2);};
invokeArgsList: RPAREN | leaVal invokeArgsLoop;
invokeArgsLoop: COMMA leaVal invokeArgsList | RPAREN;
// --------------------------------------------

// --------------------------------------------
// define if-else if-else
// --------------------------------------------
stateIfDefine: stateIf stateElse;
stateIf: KW_IF LPAREN leaVal RPAREN codeBlockDefine {_if();_p_yacc("-if\n");}
;
stateElse: ending | stateElseApp;
stateElseApp: ending | KW_ELSE stateElseLoop;
stateElseLoop:
  {_p_yacc("-elif\n");} KW_IF LPAREN leaVal RPAREN codeBlockDefine {_elif();} stateElseApp
| {_p_yacc("-else\n");} codeBlockDefine {_else();}
;
// --------------------------------------------

// --------------------------------------------
// define for-loop
// --------------------------------------------
stateForDefine: KW_FOR LPAREN stateForInit stateForCondition stateForUpdate {_for();} codeBlockDefine
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
stateCaseTail: codeBlockDefine | leaVal ending;
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
| codeBlockDefine codeBlockLoop
| BLOCK_END                                     {_block_();_p_yacc("-block-end\n");}
;
// --------------------------------------------


// --------------------------------------------
// define right value of variable and function return
// --------------------------------------------
// represent variable/function-invoking
leaVai: leaVar {_p_yacc("[y] is var\n");} | leaVar LPAREN leaInv {_p_yacc("[y] is invoke\n");};
leaVar: FIELD;
leaInv: RPAREN {_call(0);} | leaInvOptions; // args list
leaInvOptions: leaBas leaInvLoop | leaVai leaInvLoop; // args list
leaInvLoop: COMMA leaInvOptions | RPAREN {_call(1);};
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
  leaNum
| CHAR
| STRING
| LPAREN booExp RPAREN // solve "(" matching and loop back to the top level
| leaVai
;
// --------------------------------------------

// --------------------------------------------
// common definition
// --------------------------------------------
leaBas: CHAR|OP_SUB INTEGER|INTEGER|DOUBLE|STRING|booBas; // specific value
leaNum: OP_SUB INTEGER|INTEGER|DOUBLE
booBas: KW_TRUE|KW_FALSE;
ending: SEMI | NEWLINE;
basicType: KW_BYTE | KW_CHAR | KW_INT | KW_BOOL | KW_DOUBLE | KW_STRING;
// --------------------------------------------

%%

void yyerror(const char* s)
{
    printf("Grammar error : %s\n", s);
}

int main()
{
    yyparse();
    return 0;
}

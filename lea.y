%{
#include <stdio.h>
#include <stdlib.h>
void yyerror(const char* s);
extern int yylex(void);
extern int yyparse(void);


%}

%token ANY
%token KW_EOF
%token COMMENT_SINGLE COMMENT_BEGIN COMMENT_END
%token KW_BYTE KW_CHAR KW_STRING KW_INT KW_DOUBLE KW_BOOL
%token KW_TRUE KW_FALSE
%token KW_IF KW_ELSE KW_FOR KW_WHILE KW_MATCH KW_CASE KW_DEF
%token AND OR NOT EQ NE GT GE LT LE
%token ARROW ASSIGN LPAREN RPAREN DOT COMMA SEMI COLON NEWLINE BLOCK_BEGIN BLOCK_END
%token DOUBLE INTEGER FIELD CHAR STRING
%token OP_ADD OP_SUB OP_MUL OP_DIV OP_MOD

%start statement

%%

root: statement;

statement:
  KW_EOF
| ending statement
| commentDefine statement
| variableDefine statement
| variableAssign statement
| invokeDefine statement
| functionDefine statement
| stateIfDefine statement
| stateForDefine statement
| codeBlockDefine statement
;


baseInput: COMMENT_SINGLE|KW_BYTE|KW_CHAR|KW_STRING|KW_INT|KW_DOUBLE|KW_BOOL|
KW_TRUE|KW_FALSE|KW_IF|KW_ELSE|KW_FOR|KW_WHILE|KW_MATCH|KW_CASE|KW_DEF|
AND|OR|NOT|EQ|NE|GT|GE|LT|LE|
ARROW|ASSIGN|LPAREN|RPAREN|DOT|COMMA|SEMI|COLON|BLOCK_BEGIN|BLOCK_END|
DOUBLE|INTEGER|FIELD|CHAR|STRING|
OP_ADD|OP_SUB|OP_MUL|OP_DIV|OP_MOD|ANY;

// --------------------------------------------
// define comment
// --------------------------------------------
commentDefine: sc | mc;
sc: COMMENT_SINGLE singleComment;
mc: COMMENT_BEGIN multiComment;
singleComment: baseInput singleComment | NEWLINE    {printf("-multiComment-end\n");}
;
multiComment: baseInput2 multiComment | COMMENT_END {printf("-multiComment-end\n");}
;
baseInput2: baseInput | COMMENT_BEGIN | NEWLINE;
// --------------------------------------------

// --------------------------------------------
// define variable
// --------------------------------------------
variableDefine: variableName COLON basicType;
variableAssign:
  variableName COLON basicType ASSIGN leaVal  {printf("-assign-type\n");}
| variableName ASSIGN leaVal                   {printf("-assign\n");}
;
variableName: FIELD;
// --------------------------------------------

// --------------------------------------------
// define function
// --------------------------------------------
functionDefine: KW_DEF FIELD functionOptions;
functionOptions:
  functionBody                                  {printf("-{}\n");}
| COLON returnType functionBody                 {printf("-type-{}\n");}
| lparen argsList functionBody                  {printf("-()-{}\n");}
| lparen argsList COLON returnType functionBody {printf("-()-type-{}\n");}
;
lparen: LPAREN;
argsList: RPAREN | FIELD COLON basicType argsLoop;
argsLoop: COMMA FIELD COLON basicType argsList | RPAREN;
returnType: basicType;
functionBody: ARROW leaVal {printf("-lambda\n");} | codeBlockDefine;
// --------------------------------------------

// --------------------------------------------
// define function invoke
// --------------------------------------------
invokeDefine: variableName LPAREN invokeArgsList;
invokeArgsList: RPAREN | leaVal invokeArgsLoop;
invokeArgsLoop: COMMA leaVal invokeArgsList | RPAREN;
// --------------------------------------------

// --------------------------------------------
// define if-else if-else
// --------------------------------------------
stateIfDefine: stateIf stateElse;
stateIf: KW_IF LPAREN leaVal RPAREN codeBlockDefine {printf("-if\n");}
;
stateElse: ending | stateElseApp;
stateElseApp: ending | KW_ELSE stateElseLoop;
stateElseLoop:
  {printf("-elif\n");} KW_IF LPAREN leaVal RPAREN codeBlockDefine stateElseApp
| {printf("-else\n");} codeBlockDefine
;
// --------------------------------------------

// --------------------------------------------
// define for-loop
// --------------------------------------------
stateForDefine: KW_FOR LPAREN stateForInit stateForCondition stateForUpdate RPAREN codeBlockDefine
;
stateForInit: SEMI | variableAssign SEMI;
stateForCondition: SEMI | leaVal SEMI;
stateForUpdate: variableAssign;
// --------------------------------------------

// --------------------------------------------
// define code block
// --------------------------------------------
codeBlockDefine: BLOCK_BEGIN codeBlockLoop;
codeBlockLoop:
  ending codeBlockLoop
| variableDefine codeBlockLoop
| variableAssign codeBlockLoop
| invokeDefine codeBlockLoop
| commentDefine codeBlockLoop
| stateIfDefine codeBlockLoop
| stateForDefine codeBlockLoop
| codeBlockDefine codeBlockLoop
| BLOCK_END                                     {printf("-block-end\n");}
;
// --------------------------------------------


// --------------------------------------------
// define right value of variable and function return
// --------------------------------------------
// represent variable/function-invoking
leaVai: leaVar {printf("[y] is var\n");} | leaVar LPAREN leaInv {printf("[y] is invoke\n");};
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
    printf("[y] error : %s\n", s);
}

int main()
{
    yyparse();
    return 0;
}

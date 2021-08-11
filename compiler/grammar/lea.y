%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "syntax.h"
void yyerror(const char* s);
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
%type <ycText> leaVar
//%type <ycText> leaVal
//%type <ycText> booExp
//%type <ycText> booAtom
//%type <ycText> calExp
//%type <ycText> calExpPro
//%type <ycText> calExpAtom
//%type <ycText> leaNum

%start root

%%

root: statement;

statement:
  KW_EOF {leaprintf("Grammar parsed success.\n"); exit(0);}
| ending statement
| commentDefine statement
| variableDefine statement
| variableAssign statement
| invokeDefine statement
| functionDefine statement
| stateIfDefine statement
| stateForDefine statement
| stateMatchDefine statement
| codeBlockDefine  statement
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
mc: COMMENT_BEGIN multiComment;
singleComment: baseInput singleComment | NEWLINE;
multiComment: baseInput2 multiComment | COMMENT_END;
baseInput2: baseInput | COMMENT_BEGIN | NEWLINE;
// --------------------------------------------

// --------------------------------------------
// define variable
// --------------------------------------------
variableDefine: variableName COLON basicType {leaprintf(":L%d\n", lealine);};
variableAssign:
  variableName COLON basicType ASSIGN {leaprintf("=L%d\n", lealine);} leaVal
| variableName ASSIGN {leaprintf("=L%d\n", lealine);} leaVal
;
variableName: FIELD;
// --------------------------------------------

// --------------------------------------------
// define function
// --------------------------------------------
functionDefine: KW_DEF FIELD functionOptions;
functionOptions:
  functionBody
| COLON returnType functionBody
| lparen argsList functionBody
| lparen argsList COLON returnType functionBody
;
lparen: LPAREN;
argsList: RPAREN | FIELD COLON basicType argsLoop;
argsLoop: COMMA FIELD COLON basicType argsList | RPAREN;
returnType: basicType;
functionBody: ARROW leaVal | codeBlockDefine;
// --------------------------------------------

// --------------------------------------------
// define function invoke
// --------------------------------------------
invokeDefine: variableName LPAREN invokeArgsList;
invokeArgsList: invokeArgsLoop | leaVal invokeArgsLoop;
invokeArgsLoop: COMMA leaVal invokeArgsList | RPAREN;
// --------------------------------------------

// --------------------------------------------
// define if-else if-else
// --------------------------------------------
stateIfDefine: stateIf stateElse;
stateIf: KW_IF LPAREN leaVal RPAREN codeBlockDefine;
stateElse: ending | stateElseApp;
stateElseApp: ending | KW_ELSE stateElseLoop;
stateElseLoop:
  KW_IF LPAREN leaVal RPAREN codeBlockDefine stateElseApp
| codeBlockDefine
;
// --------------------------------------------

// --------------------------------------------
// define for-loop
// --------------------------------------------
stateForDefine: KW_FOR LPAREN stateForInit stateForCondition stateForUpdate codeBlockDefine;
stateForInit: SEMI | variableAssign SEMI;
stateForCondition: SEMI | leaVal SEMI;
stateForUpdate: RPAREN | variableAssign RPAREN;
// --------------------------------------------

// --------------------------------------------
// define match-case
// --------------------------------------------
stateMatchDefine: variableName KW_MATCH stateMatchBlock;
stateMatchBlock: BLOCK_BEGIN stateCase;
stateCase:
  wordCase KW__ ARROW stateCaseTail stateCaseLoop
| wordCase basicType ARROW stateCaseTail stateCaseLoop
| wordCase leaVal ARROW stateCaseTail stateCaseLoop
| ending stateCaseLoop
;
stateCaseLoop: stateCase | BLOCK_END;
wordCase: KW_CASE;
stateCaseTail: codeBlockDefine | leaVal ending;
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
| stateMatchDefine statement
| codeBlockDefine codeBlockLoop
| BLOCK_END
;
// --------------------------------------------


// --------------------------------------------
// define right value of variable and function return
// --------------------------------------------
// represent variable/function-invoking
leaVai:
  leaVar
| leaVar LPAREN leaInv {};
leaVar: FIELD;
leaInv: RPAREN | leaInvOptions;
leaInvOptions: booExp leaInvLoop;
leaInvLoop: COMMA leaInvOptions | RPAREN;
// --------------------------------------------

// --------------------------------------------
// define bool expression
// --------------------------------------------
leaVal: booExp;
booExp:
  booExpNot
| booExp AND booExpNot
| booExp OR  booExpNot
;
booExpNot:
  booAtom
| NOT booAtom
;
booAtom:
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
| calExp OP_SUB calExpPro;

calExpPro:
  calExpAtom
| calExpPro OP_MUL calExpAtom
| calExpPro OP_DIV calExpAtom
;

calExpAtom:
  leaNum
| CHAR
| STRING
| LPAREN booExp RPAREN
| leaVai
;
// --------------------------------------------

// --------------------------------------------
// common definition
// --------------------------------------------
leaBas:
  CHAR
| op_sub INTEGER
| op_sub DOUBLE
| INTEGER
| DOUBLE
| STRING
| booBas
;
op_sub: OP_SUB;
leaNum:
  op_sub INTEGER
| INTEGER
| DOUBLE
| op_sub DOUBLE
;
booBas: KW_TRUE | KW_FALSE;
basicType: KW_BYTE | KW_CHAR | KW_INT | KW_BOOL | KW_DOUBLE | KW_STRING;
ending: SEMI | NEWLINE;
// --------------------------------------------

%%

void yyerror(const char* s)
{
    printf("Grammar error : %s\n", s);
}
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
%token <ycText> KW_TRUE
%token <ycText> KW_FALSE
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
%type <ycText> booBas
//%type <ycText> leaVal
//%type <ycText> booExp
//%type <ycText> booAtom
//%type <ycText> calExp
//%type <ycText> calExpPro
//%type <ycText> calExpAtom

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
variableDefine: variableName COLON basicType;
variableAssign:
  variableName COLON basicType ASSIGN leaVal
| variableName ASSIGN leaVal
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
invokeDefine: functionName LPAREN invokeArgsList;
invokeArgsList: invokeArgsLoop | leaVal invokeArgsLoop;
invokeArgsLoop: COMMA leaVal invokeArgsList | RPAREN;
functionName: FIELD;
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
  leaVar {vi_end_var();}
| leaVar LPAREN {} leaInv;
leaVar: FIELD {vi_register($1);};
leaInv: RPAREN {vi_end_inv();} | leaInvOptions;
leaInvOptions: booExp leaInvLoop;
leaInvLoop: COMMA {vi_args();} leaInvOptions | RPAREN {vi_args();vi_end_inv();};
// --------------------------------------------

// --------------------------------------------
// define bool expression
// --------------------------------------------
leaVal: booExp {ex_close();};
booExp:
  booExpNot
| booExp AND booExpNot {ex_calc(2, "&&");}
| booExp OR  booExpNot {ex_calc(2, "||");}
;
booExpNot:
  booAtom
| NOT booAtom {ex_calc(1, "!");}
;
booAtom:
  calExp
| calExp LT calExp {ex_calc(2, "<");}
| calExp GT calExp {ex_calc(2, ">");}
| calExp LE calExp {ex_calc(2, "<=");}
| calExp GE calExp {ex_calc(2, ">=");}
| calExp EQ calExp {ex_calc(2, "==");}
| calExp NE calExp {ex_calc(2, "!=");}
| booBas
;
booBas: 
  KW_TRUE {ex_push_i(1);}
| KW_FALSE  {ex_push_i(0);}
;
// --------------------------------------------

// --------------------------------------------
// define calculation expression
// --------------------------------------------
calExp:
  calExpPro
| calExp OP_ADD calExpPro {ex_calc(2, "+");}
| calExp OP_SUB calExpPro {ex_calc(2, "-");}
;

calExpPro:
  calExpAtom
| calExpPro OP_MUL calExpAtom {ex_calc(2, "*");}
| calExpPro OP_DIV calExpAtom {ex_calc(2, "/");}
;

calExpAtom:
  LPAREN booExp RPAREN
| op_sub INTEGER {ex_push_i(0-$2);}
| op_sub DOUBLE {ex_push_d(0-$2);}
| INTEGER {ex_push_i($1);}
| DOUBLE {ex_push_d($1);}
| CHAR {ex_push_c($1);}
| STRING {ex_push_s($1);}
| leaVai
;
// --------------------------------------------

// --------------------------------------------
// common definition
// --------------------------------------------
op_sub: OP_SUB;
basicType: KW_BYTE | KW_CHAR | KW_INT | KW_BOOL | KW_DOUBLE | KW_STRING;
ending: SEMI | NEWLINE;
// --------------------------------------------

%%

void yyerror(const char* s)
{
    printf("Grammar error : %s\n", s);
}
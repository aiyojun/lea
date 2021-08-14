%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "syntax.h"
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

%token <ycText> KW_BYTE
%token <ycText> KW_CHAR
%token <ycText> KW_STRING
%token <ycText> KW_INT
%token <ycText> KW_DOUBLE
%token <ycText> KW_BOOL

%token <ycText> KW_TRUE
%token <ycText> KW_FALSE
%token KW_IF KW_ELSE KW_FOR KW_WHILE KW_MATCH KW_CASE KW__ KW_CLASS KW_STRUCT
%token <ycText> KW_DEF
%token <ycText> KW_RETURN
%token AND OR NOT EQ NE GT GE LT LE
%token ARROW ASSIGN LPAREN RPAREN DOT COMMA SEMI NEWLINE BLOCK_BEGIN BLOCK_END
%token COLON
%token <ycValueDouble> DOUBLE
%token <ycValueInt> INTEGER
%token <ycText> FIELD
%token <ycValueChar> CHAR
%token <ycText> STRING
%token OP_ADD OP_SUB OP_MUL OP_DIV OP_MOD

// %type <ycText> statementV2
%type <ycText> basicTypeX0
%type <ycText> variableName
%type <ycText> leaVar
%type <ycText> booBas

%start root

%%

root: statementV2;

statementV2: statementV2 real | real;

real:
  KW_EOF {print_symbols(); leaprintf("Grammar parsed success.\n"); exit(0);}
| ending
| commentDefine
| FIELD {bs_variable_name($1);} variableMany;
| functionDefine
| stateIfDefine
| stateForDefine
| codeBlockDefine
;

variableMany:
  COLON basicTypeX0 {bs_variable_type(1);bs_variable_record();}
| COLON basicTypeX0 ASSIGN leaVal {bs_variable_type(2);bs_variable_record();}
| ASSIGN leaVal {bs_variable_type(3);bs_variable_type_judge();bs_variable_record();}
| LPAREN invokeArgsList
| KW_MATCH stateMatchBlock
;

// statement:
//   KW_EOF {print_symbols(); leaprintf("Grammar parsed success.\n"); exit(0);}
// | ending statement
// | commentDefine statement
// | FIELD COLON basicTypeX0
// | FIELD COLON basicTypeX0 ASSIGN leaVal
// | variableDefine statement
// | variableAssign statement
// | invokeDefine statement
// | functionDefine statement
// | stateIfDefine statement
// | stateForDefine statement
// | stateMatchDefine statement
// | codeBlockDefine  statement
// ;


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
mc: COMMENT_BEGIN multiComment COMMENT_END;
singleComment: singleComment baseInput | baseInput;
multiComment: multiComment baseInput2 | baseInput2;
baseInput2: baseInput | COMMENT_BEGIN | NEWLINE;
// --------------------------------------------

// --------------------------------------------
// define variable
// --------------------------------------------
// variableDefine: variableName COLON basicTypeX0 {bs_variable_record();};
variableAssign:
  variableName COLON basicTypeX0 ASSIGN leaVal {bs_variable_record();}
| variableName ASSIGN leaVal {bs_variable_type_judge();bs_variable_record();}
;
variableName: FIELD {$$ = $1;};
basicTypeX0: 
  KW_BYTE    {$$ = $1;bs_variable_type_sign("byte");}
| KW_CHAR    {$$ = $1;bs_variable_type_sign("char");}
| KW_INT     {$$ = $1;bs_variable_type_sign("int");}
| KW_BOOL    {$$ = $1;bs_variable_type_sign("bool");}
| KW_DOUBLE  {$$ = $1;bs_variable_type_sign("double");}
| KW_STRING  {$$ = $1;bs_variable_type_sign("string");}
;
// --------------------------------------------

// --------------------------------------------
// define function
// --------------------------------------------
functionDefine: KW_DEF FIELD {scope_enter($2);} functionOptions {scope_exit();};
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
codeBlockDefine: BLOCK_BEGIN codeBlockLoop BLOCK_END;
codeBlockLoop: codeBlockLoop realV2 | realV2;
realV2: 
  ending
| commentDefine
| FIELD {bs_variable_name($1);} variableMany;
| stateIfDefine
| stateForDefine
| codeBlockDefine
;
// codeBlockDefine: BLOCK_BEGIN codeBlockLoop;
// codeBlockLoop:
//   ending codeBlockLoop
// | variableDefine codeBlockLoop
// | variableAssign codeBlockLoop
// | invokeDefine codeBlockLoop
// | commentDefine codeBlockLoop
// | stateIfDefine codeBlockLoop
// | stateForDefine codeBlockLoop
// | stateMatchDefine statement
// | codeBlockDefine codeBlockLoop
// | BLOCK_END
// ;
// --------------------------------------------


// --------------------------------------------
// define right value of variable and function return
// --------------------------------------------
// represent variable/function-invoking
leaVai:
  leaVar {vi_end_var();}
| leaVar LPAREN leaInv;
leaVar: FIELD {vi_register($1);};
leaInv:
  RPAREN {vi_end_inv();}
| leaInvOptions;
leaInvOptions: booExp leaInvLoop;
leaInvLoop:
  COMMA leaInvOptions {vi_args();}
| RPAREN {vi_args();vi_end_inv();}
;
// --------------------------------------------

// --------------------------------------------
// define bool expression
// --------------------------------------------
leaVal: booExp {ex_close();};
booExp:
  booExpNot
| booExp AND booExpNot {ex_calculate(2, "&&");}
| booExp OR  booExpNot {ex_calculate(2, "||");}
;
booExpNot:
  booAtom
| NOT booAtom {ex_calculate(1, "!");}
;
booAtom:
  calExp
| calExp LT calExp {ex_calculate(2, "<");}
| calExp GT calExp {ex_calculate(2, ">");}
| calExp LE calExp {ex_calculate(2, "<=");}
| calExp GE calExp {ex_calculate(2, ">=");}
| calExp EQ calExp {ex_calculate(2, "==");}
| calExp NE calExp {ex_calculate(2, "!=");}
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
| calExp OP_ADD calExpPro {ex_calculate(2, "+");}
| calExp OP_SUB calExpPro {ex_calculate(2, "-");}
;

calExpPro:
  calExpAtom
| calExpPro OP_MUL calExpAtom {ex_calculate(2, "*");}
| calExpPro OP_DIV calExpAtom {ex_calculate(2, "/");}
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


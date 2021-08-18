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
%token COMMENT_SINGLE
%token COMMENT_BEGIN
%token COMMENT_END

%token <ycText> KW_VOID
%token <ycText> KW_BYTE
%token <ycText> KW_CHAR
%token <ycText> KW_STRING
%token <ycText> KW_INT
%token <ycText> KW_DOUBLE
%token <ycText> KW_BOOL

%token KW_IF
%token KW_ELSE
%token KW_FOR
%token KW_WHILE
%token KW_MATCH
%token KW_CASE
%token KW__
%token KW_CLASS
%token KW_STRUCT
%token <ycText> KW_DEF
%token <ycText> KW_RETURN

%token EQ
%token NE
%token GT
%token GE
%token LT
%token LE
%token OR
%token AND
%token NOT
%token <ycText> KW_TRUE
%token <ycText> KW_FALSE

%token ARROW
%token ASSIGN
%token LPAREN
%token RPAREN
%token DOT
%token COMMA
%token COLON
%token SEMI
%token NEWLINE
%token BLOCK_BEGIN
%token BLOCK_END

%token <ycText> FIELD
%token <ycText> STRING
%token <ycText> CHAR
%token <ycText> INTEGER
%token <ycText> DOUBLE

%token OP_ADD
%token OP_SUB
%token OP_MUL
%token OP_DIV
%token OP_MOD

%type <ycText> basicTypeX0
%type <ycText> variableName
%type <ycText> leaVar
%type <ycText> booBas

%start root

%%

root: statement;

statement: statement real | real;

baseInput:
COMMENT_SINGLE|KW_VOID|KW_BYTE|KW_CHAR|KW_STRING|KW_INT|KW_DOUBLE|KW_BOOL|
KW_TRUE|KW_FALSE|KW_IF|KW_ELSE|KW_FOR|KW_WHILE|KW_MATCH|KW_CASE|KW_DEF|KW__|KW_STRUCT|KW_CLASS|KW_RETURN|
AND|OR|NOT|EQ|NE|GT|GE|LT|LE|
ARROW|ASSIGN|LPAREN|RPAREN|DOT|COMMA|SEMI|COLON|BLOCK_BEGIN|BLOCK_END|
DOUBLE|INTEGER|FIELD|CHAR|STRING|
OP_ADD|OP_SUB|OP_MUL|OP_DIV|OP_MOD;

real:
  KW_EOF {
    heap_print();
    symbol_print();
    leaprintf("Grammar parsed success.\n");
    exit(0);
  }
| ending
| commentDefine
| FIELD {val_register2($1);} variableMany {stack_clear();}
| functionDefine
| stateIfDefine
| stateForDefine
| codeBlockDefine {}
;

variableMany:
  COLON basicTypeX0 {
    variable_register(0);
    variable_record();
  }
| COLON basicTypeX0 ASSIGN leaVal {
    variable_register(0);
    variable_record();
    variable_assign_v2();
  }
| ASSIGN leaVal {
    variable_register(1);
    variable_already_exist();
    variable_assign_v2();
  }
;

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
variableAssign:
  variableName COLON basicTypeX0 ASSIGN leaVal {

  }
| variableName ASSIGN leaVal {

  }
;
variableName: FIELD {};
basicTypeX0: 
  KW_BYTE    {variable_type("byte");}
| KW_CHAR    {variable_type("char");}
| KW_INT     {variable_type("int");}
| KW_BOOL    {variable_type("bool");}
| KW_DOUBLE  {variable_type("double");}
| KW_STRING  {variable_type("string");}
;
// --------------------------------------------

// --------------------------------------------
// define function
// --------------------------------------------
functionDefine:
  KW_DEF functionName {
    function_record();
  }
| KW_DEF functionName functionMany {
    function_record();
  }
;
functionName: FIELD {
    function_name($1);
}
;
functionMany:
  returnDefine
| LPAREN functionArgsApp returnDefine
;
returnDefine:
  COLON returnType              {}
| COLON returnType functionBody {function_type(5);}
| functionBody                  {function_type(5);}
;
functionArgsApp:
  RPAREN
| functionArgs RPAREN
;
functionArgs: 
  functionArgs COMMA argDefine
| argDefine
;
argDefine: FIELD COLON paramType;
functionBody: 
  ARROW {} leaVal
| BLOCK_BEGIN {} codeBlockLoop BLOCK_END {}
;
paramType:
  KW_BYTE   {function_push_args_type("type");}
| KW_CHAR   {function_push_args_type("char");}
| KW_INT    {function_push_args_type("int");}
| KW_BOOL   {function_push_args_type("bool");}
| KW_DOUBLE {function_push_args_type("double");}
| KW_STRING {function_push_args_type("string");}
| KW_VOID   {function_push_args_type("void");}
;
returnType:
  KW_BYTE   {function_return("byte");}
| KW_CHAR   {function_return("char");}
| KW_INT    {function_return("int");}
| KW_BOOL   {function_return("bool");}
| KW_DOUBLE {function_return("double");}
| KW_STRING {function_return("string");}
| KW_VOID   {function_return("void");}
;
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
| FIELD {val_register2($1);} variableManyV2 {stack_clear();}
| stateIfDefine
| stateForDefine
| codeBlockDefine {}
;
variableManyV2:
  COLON basicTypeX0 {
    variable_register(0);
    variable_record();
  }
| COLON basicTypeX0 ASSIGN {} leaVal {
    variable_register(0);
    variable_record();
    variable_assign_v2();
  }
| ASSIGN leaVal {
    variable_register(1);
    variable_already_exist();
    variable_assign_v2();
  }
| LPAREN {heap_inv2();heap_deep_inc();} leaInv
//| LPAREN {invoking_register();} invokeArgsDefine {
//    invoking_exe();
//  }
| KW_MATCH {} stateMatchBlock
;
//invokeArgsDefine:
//  RPAREN
//| invokeArgsLoop RPAREN
//;
//invokeArgsLoop:
//  invokeArgsLoop COMMA leaVal {}
//| leaVal                      {}
//;
// --------------------------------------------


// --------------------------------------------
// define right value of variable and function return
// --------------------------------------------
// represent variable/function-invoking
leaVai:
  leaVar                     {heap_var_validate();heap_var();}
| leaVar LPAREN {heap_inv();heap_deep_inc();} leaInv
;
leaVar: FIELD                {val_register($1);}
;
leaInv:
  RPAREN                     {heap_inv_validate();heap_inv_exe();heap_deep_dec();}
| leaInvOptions RPAREN       {heap_inv_validate();heap_inv_exe();heap_deep_dec();}
;
leaInvOptions:
  leaInvOptions COMMA {heap_inv_args_inc();} booExp
| booExp                     {heap_inv_args_inc();}
;
// --------------------------------------------

// --------------------------------------------
// define bool expression
// --------------------------------------------
leaVal: booExp;
booExp:
  booExpNot
| booExp AND booExpNot {comp_and();}
| booExp OR  booExpNot {comp_or();}
;
booExpNot:
  booAtom
| NOT booAtom          {comp_not();}
;
booAtom:
  calExp
| calExp LT calExp     {comp_lt();}
| calExp GT calExp     {comp_gt();}
| calExp LE calExp     {comp_lte();}
| calExp GE calExp     {comp_gte();}
| calExp EQ calExp     {comp_eq();}
| calExp NE calExp     {comp_ne();}
| booBas
;
booBas: 
  KW_TRUE              {heap_value("", "1", "bool");}
| KW_FALSE             {heap_value("", "0", "bool");}
;
// --------------------------------------------

// --------------------------------------------
// define calculation expression
// --------------------------------------------
calExp:
  calExpPro
| calExp OP_ADD calExpPro {calc_add();}
| calExp OP_SUB calExpPro {calc_sub();}
;

calExpPro:
  calExpAtom
| calExpPro OP_MUL calExpAtom {calc_mul();}
| calExpPro OP_DIV calExpAtom {calc_div();}
;

calExpAtom:
  LPAREN booExp RPAREN
| OP_SUB INTEGER {heap_value("-", $2, "int");}
| OP_SUB DOUBLE  {heap_value("-", $2, "double");}
| INTEGER        {heap_value("", $1, "int");}
| DOUBLE         {heap_value("", $1, "double");}
| CHAR           {heap_value("", $1, "char");}
| STRING         {heap_value("", $1, "string");}
| leaVai
;
// --------------------------------------------

// --------------------------------------------
// common definition
// --------------------------------------------
basicType: KW_BYTE | KW_CHAR | KW_INT | KW_BOOL | KW_DOUBLE | KW_STRING;
ending: SEMI | NEWLINE;
// --------------------------------------------

%%


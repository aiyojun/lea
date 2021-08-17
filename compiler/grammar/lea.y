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
    print_symbols();
    check_main();
    leaprintf("Grammar parsed success.\n");
    write_file();
    exit(0);
  }
| ending
| commentDefine
| FIELD {bs_variable_name($1);} variableMany {ex_close();}
| functionDefine
| stateIfDefine
| stateForDefine
| codeBlockDefine {ex_close();}
;

variableMany:
  COLON basicTypeX0 {
    bs_variable_type(1);
    bs_variable_record();
  }
| COLON basicTypeX0 ASSIGN leaVal {
    bs_variable_type(2);
    bs_variable_record();
  }
| ASSIGN leaVal {
    bs_variable_type(3);
    bs_variable_type_judge();
    bs_variable_record();
  }
| KW_MATCH stateMatchBlock
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
  variableName COLON basicTypeX0 ASSIGN leaVal {bs_variable_record();}
| variableName ASSIGN leaVal {
    bs_variable_type_judge();
    bs_variable_record();
  }
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
functionDefine:
  KW_DEF functionName {
    bs_function_type(6);
    bs_function_return_type("void");
    scope_exit();
    bs_function_record();
  }
| KW_DEF functionName functionMany {
    scope_exit();
    bs_function_record();
  }
;
functionName: FIELD {
  bs_function_name($1);
  scope_enter($1);
}
;
functionMany:
  returnDefine
| LPAREN functionArgsApp returnDefine
;
returnDefine:
  COLON returnType              {bs_function_type(6);}
| COLON returnType functionBody {bs_function_type(5);}
| functionBody
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
  ARROW {declare_function();} leaVal
| BLOCK_BEGIN {declare_function();} codeBlockLoop BLOCK_END {return_function();}
;
paramType:
  KW_BYTE   {bs_function_arg_type("byte");}
| KW_CHAR   {bs_function_arg_type("char");}
| KW_INT    {bs_function_arg_type("int");}
| KW_BOOL   {bs_function_arg_type("bool");}
| KW_DOUBLE {bs_function_arg_type("double");}
| KW_STRING {bs_function_arg_type("string");}
| KW_VOID   {bs_function_arg_type("void");}
;
returnType:
  KW_BYTE   {bs_function_return_type("byte");}
| KW_CHAR   {bs_function_return_type("char");}
| KW_INT    {bs_function_return_type("int");}
| KW_BOOL   {bs_function_return_type("bool");}
| KW_DOUBLE {bs_function_return_type("double");}
| KW_STRING {bs_function_return_type("string");}
| KW_VOID   {bs_function_return_type("void");}
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
| FIELD {bs_variable_name($1);} variableManyV2 {ex_close();}
| stateIfDefine
| stateForDefine
| codeBlockDefine {ex_close();}
;
variableManyV2:
  COLON basicTypeX0 {
    bs_variable_type(1);
    variable_declare();
    bs_variable_record();
  }
| COLON basicTypeX0 ASSIGN leaVal {
    bs_variable_type(2);
    variable_declare();
    variable_assign();
    bs_variable_record();
  }
| ASSIGN leaVal {
    bs_variable_type(3);
    bs_variable_type_judge();
    bs_variable_assign();
  }
| LPAREN {invoke_move();} invokeArgsDefine {
    invoke();
    invoke_close();
  }
| KW_MATCH stateMatchBlock
;
invokeArgsDefine:
  RPAREN
| invokeArgsLoop RPAREN
;
invokeArgsLoop:
  invokeArgsLoop COMMA leaVal {invoke_args_push();}
| leaVal                      {invoke_args_push();}
;
// --------------------------------------------


// --------------------------------------------
// define right value of variable and function return
// --------------------------------------------
// represent variable/function-invoking
leaVai:
  leaVar                     {heap_var();}
| leaVar LPAREN {heap_inv();heap_deep_inc();} leaInv
;
leaVar: FIELD                {val_register($1);}
;
leaInv:
  RPAREN                     {heap_deep_dec();}
| leaInvOptions RPAREN       {heap_deep_dec();}
;
leaInvOptions:
  leaInvOptions COMMA booExp {heap_inv_args_inc();}
| booExp                     {heap_inv_args_inc();}
;
// --------------------------------------------

// --------------------------------------------
// define bool expression
// --------------------------------------------
leaVal: booExp;
booExp:
  booExpNot
| booExp AND booExpNot {ex_calculate(2, "&&");}
| booExp OR  booExpNot {ex_calculate(2, "||");}
;
booExpNot:
  booAtom
| NOT booAtom          {ex_calculate(1, "!");}
;
booAtom:
  calExp
| calExp LT calExp     {ex_calculate(2, "<");}
| calExp GT calExp     {ex_calculate(2, ">");}
| calExp LE calExp     {ex_calculate(2, "<=");}
| calExp GE calExp     {ex_calculate(2, ">=");}
| calExp EQ calExp     {ex_calculate(2, "==");}
| calExp NE calExp     {ex_calculate(2, "!=");}
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
| OP_SUB INTEGER {heap_value("-", $2, "int");}
| OP_SUB DOUBLE  {heap_value("-", $2, "double");}
| INTEGER        {heap_value("", $2, "int");}
| DOUBLE         {heap_value("", $2, "double");}
| CHAR           {heap_value("", $2, "char");}
| STRING         {heap_value("", $2, "string");}
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


%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grammar.h"
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

%token <ycText> KW_EOF
%token <ycText> COMMENT_SINGLE
%token <ycText> COMMENT_BEGIN
%token <ycText> COMMENT_END

%token <ycText> KW_VOID
%token <ycText> KW_BYTE
%token <ycText> KW_CHAR
%token <ycText> KW_STRING
%token <ycText> KW_INT
%token <ycText> KW_DOUBLE
%token <ycText> KW_BOOL

%token <ycText> KW_IF
%token <ycText> KW_ELSE
%token <ycText> KW_FOR
%token <ycText> KW_WHILE
%token <ycText> KW_MATCH
%token <ycText> KW_CASE
%token <ycText> KW__
%token <ycText> KW_CLASS
%token <ycText> KW_STRUCT
%token <ycText> KW_DEF
%token <ycText> KW_RETURN

%token <ycText> EQ
%token <ycText> NE
%token <ycText> GT
%token <ycText> GE
%token <ycText> LT
%token <ycText> LE
%token <ycText> OR
%token <ycText> AND
%token <ycText> NOT
%token <ycText> KW_TRUE
%token <ycText> KW_FALSE

%token <ycText> ARROW
%token <ycText> ASSIGN
%token <ycText> LPAREN
%token <ycText> RPAREN
%token <ycText> DOT
%token <ycText> COMMA
%token <ycText> COLON
%token <ycText> SEMI
%token <ycText> NEWLINE
%token <ycText> BLOCK_BEGIN
%token <ycText> BLOCK_END

%token <ycText> FIELD
%token <ycText> STRING
%token <ycText> CHAR
%token <ycText> INTEGER
%token <ycText> DOUBLE

%token <ycText> OP_ADD
%token <ycText> OP_SUB
%token <ycText> OP_MUL
%token <ycText> OP_DIV
%token <ycText> OP_MOD

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
    print_gas();
    leaprintf("Grammar parsed success.\n");
    exit(0);
  }
| ending
| commentDefine
| FIELD {val_register2($1);} variableMany {stack_clear();}
| functionDefine
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
  ARROW {g_function_imp();} leaVal {g_function_return();g_function_over();}
| BLOCK_BEGIN {g_function_imp();} codeBlockLoopV3 BLOCK_END {g_function_over();}
;
codeBlockLoopV3: codeBlockLoopV3 realV3 | realV3;
realV3:
  ending
| commentDefine
| FIELD {val_register2($1);} variableManyV2 {stack_clear();}
| KW_RETURN leaVal {g_function_return();}
| stateIfDefine
| stateForDefine
| codeBlockDefine {}
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
stateIfDefine:
  stateIf
| stateIf KW_ELSE codeBlockDefine {}
stateIf:
  stateIf KW_ELSE KW_IF LPAREN {} leaVal RPAREN {} codeBlockDefine {}
| KW_IF LPAREN {} leaVal RPAREN {} codeBlockDefine {}
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
//stateMatchDefine: variableName KW_MATCH stateMatchBlock;
//stateMatchBlock: BLOCK_BEGIN stateCase;
//stateCase:
//  wordCase KW__ ARROW stateCaseTail stateCaseLoop
//| wordCase basicType ARROW stateCaseTail stateCaseLoop
//| wordCase leaVal ARROW stateCaseTail stateCaseLoop
//| ending stateCaseLoop
//;
//stateCaseLoop: stateCase | BLOCK_END;
//wordCase: KW_CASE;
//stateCaseTail: codeBlockDefine | leaVal ending;
// --------------------------------------------

// --------------------------------------------
// define code block
// --------------------------------------------
codeBlockDefine:
  BLOCK_BEGIN BLOCK_END
| BLOCK_BEGIN codeBlockLoop BLOCK_END;
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
//| KW_MATCH {} stateMatchBlock
;
// --------------------------------------------


// --------------------------------------------
// define right value of variable and function return
// --------------------------------------------
// represent variable/function-invoking
leaVai:
  leaVar                     {heap_var_validate();heap_var();heap_variable();}
| leaVar LPAREN {heap_inv();heap_deep_inc();heap_invoking();invoking_deep_inc();} leaInv
;
leaVar: FIELD                {val_register($1);heap_register($1);}
;
leaInv:
  RPAREN                     {heap_inv_validate();heap_inv_exe();heap_deep_dec();invoking_deep_dec();}
| leaInvOptions RPAREN       {heap_inv_validate();heap_inv_exe();heap_deep_dec();heap_invoking_args_link();invoking_deep_dec();}
;
leaInvOptions:
  leaInvOptions COMMA {heap_inv_args_inc();} booOrExp
| booOrExp                   {heap_inv_args_inc();}
;
// --------------------------------------------

// --------------------------------------------
// define bool expression
// --------------------------------------------
leaVal: booOrExp {tree_node_deep_assign(); tree_node_print();/*tree_node_modify(); tree_node_print();*/};
booOrExp:
  booOrExp OR {} booAndExp { tree_node_link("||");}
| booAndExp {}
;
booAndExp:
  booAndExp AND {} booExpNot { tree_node_link("&&");}
| booExpNot {}
;
booExpNot:
  booAtom              {/*tree_append(4);*/}
| NOT {} booAtom          {comp_not(); tree_node_link("!");}
;
booAtom:
  calExp
| calExp LT {} calExp     {comp_lt(); tree_node_link("<");}
| calExp GT {} calExp     {comp_gt(); tree_node_link(">");}
| calExp LE {} calExp     {comp_lte(); tree_node_link("<=");}
| calExp GE {} calExp     {comp_gte(); tree_node_link(">=");}
| calExp EQ {} calExp     {comp_eq(); tree_node_link("==");}
| calExp NE {} calExp     {comp_ne(); tree_node_link("!=");}
| booBas
;
booBas: 
  KW_TRUE              {heap_value("", "1", "bool"); tree_node_create("", "true", "bool");}
| KW_FALSE             {heap_value("", "0", "bool"); tree_node_create("", "false", "bool");}
;
// --------------------------------------------

// --------------------------------------------
// define calculation expression
// --------------------------------------------
calExp:
  calExpPro
| calExp OP_ADD {} calExpPro {calc_add(); tree_node_link("+");}
| calExp OP_SUB {} calExpPro {calc_sub(); tree_node_link("-");}
;

calExpPro:
  calExpAtom
| calExpPro OP_MUL {} calExpAtom {calc_mul(); tree_node_link("*");}
| calExpPro OP_DIV {} calExpAtom {calc_div(); tree_node_link("/");}
;

calExpAtom:
  LPAREN {
//    bo_deep_inc();
//    tree_append(3);
//    paren_deep_inc();
//    tree_node_create("", "(", "lparen");
  }
  booOrExp RPAREN {
//    bo_deep_dec();
//    paren_pop();
//    paren_deep_dec();
//    tree_node_create("", ")", "rparen");
    tree_node_link("()");
  }
| OP_SUB INTEGER {heap_value("-", $2, "int");    tree_node_create("-", $2, "int");}
| OP_SUB DOUBLE  {heap_value("-", $2, "double"); tree_node_create("-", $2, "double");}
| INTEGER        {heap_value("", $1, "int");     tree_node_create("", $1, "int");}
| DOUBLE         {heap_value("", $1, "double");  tree_node_create("", $1, "double");}
| CHAR           {heap_value("", $1, "char");    tree_node_create("", $1, "char");}
| STRING         {heap_value("", $1, "string");  tree_node_create("", $1, "string");}
| leaVai
;
// --------------------------------------------

// --------------------------------------------
// common definition
// --------------------------------------------
//basicType: KW_BYTE | KW_CHAR | KW_INT | KW_BOOL | KW_DOUBLE | KW_STRING;
ending: SEMI | NEWLINE;
// --------------------------------------------

%%


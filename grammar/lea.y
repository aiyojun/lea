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

statement: statement globalContext | globalContext;

baseInput:
COMMENT_SINGLE|KW_VOID|KW_BYTE|KW_CHAR|KW_STRING|KW_INT|KW_DOUBLE|KW_BOOL|
KW_TRUE|KW_FALSE|KW_IF|KW_ELSE|KW_FOR|KW_WHILE|KW_MATCH|KW_CASE|KW_DEF|KW__|KW_STRUCT|KW_CLASS|KW_RETURN|
AND|OR|NOT|EQ|NE|GT|GE|LT|LE|
ARROW|ASSIGN|LPAREN|RPAREN|DOT|COMMA|SEMI|COLON|BLOCK_BEGIN|BLOCK_END|
DOUBLE|INTEGER|FIELD|CHAR|STRING|
OP_ADD|OP_SUB|OP_MUL|OP_DIV|OP_MOD;

globalContext:
  KW_EOF {
    symbol_print();
    print_gas();
    leaprintf("Grammar parsed success.\n");
    exit(0);
  }
| ending
| commentDefine
| FIELD {keep($1);keep_variable();/*val_register2($1);*/} variableMany {}
| functionDefine
;

variableMany:
  COLON basicTypeX0 {
    record_variable();
//    variable_register(0);
//    variable_record();
  }
| COLON basicTypeX0 ASSIGN leaVal {
    record_variable();
//    variable_register(0);
//    variable_record();
//    variable_assign_v2();
  }
//| ASSIGN leaVal {
//    variable_register(1);
//    variable_already_exist();
//    variable_assign_v2();
//  }
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
    record_variable();
  }
| variableName ASSIGN leaVal {

  }
;
variableName: FIELD {keep($1);};
basicTypeX0: 
  KW_BYTE    {keep_variable_type("byte");/*variable_type("byte");*/}
| KW_CHAR    {keep_variable_type("char");/*variable_type("char");*/}
| KW_INT     {keep_variable_type("int");/*variable_type("int");*/}
| KW_BOOL    {keep_variable_type("bool");/*variable_type("bool");*/}
| KW_DOUBLE  {keep_variable_type("double");/*variable_type("double");*/}
| KW_STRING  {keep_variable_type("string");/*variable_type("string");*/}
;
// --------------------------------------------

// --------------------------------------------
// define function
// --------------------------------------------
functionDefine:
  KW_DEF functionName {
    keep_function();
//    function_record();
  }
| KW_DEF functionName functionMany {
//    function_record();
  }
;
functionName: FIELD {
    check($1); keep($1);
//    function_name($1);
}
;
functionMany:
  returnDefine
| LPAREN functionArgsApp returnDefine
;
returnDefine:
  COLON returnType              {}
| COLON returnType functionBody {/*function_type(5);*/}
| functionBody                  {/*function_type(5);*/}
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
  ARROW {record_function();/*g_function_imp();*/} leaVal {/*g_function_return();g_function_over();*/}
| BLOCK_BEGIN {record_function();enter_scope();/*g_function_imp();*/} codeBlockLoopV3 BLOCK_END {exit_scope();/*g_function_over();*/}
;
codeBlockLoopV3: codeBlockLoopV3 functionContext | functionContext;
functionContext:
  ending
| commentDefine
| FIELD {/*val_register2($1);*/heap_register($1);} variableManyV2 {tree_clear();}
| KW_RETURN leaVal {/*g_function_return();*/}
| stateIfDefine
| stateForDefine
| codeBlockDefine {}
;
paramType:
  KW_BYTE   {keep_function_sign("type");/*function_push_args_type("type");*/}
| KW_CHAR   {keep_function_sign("char");/*function_push_args_type("char");*/}
| KW_INT    {keep_function_sign("int");/*function_push_args_type("int");*/}
| KW_BOOL   {keep_function_sign("bool");/*function_push_args_type("bool");*/}
| KW_DOUBLE {keep_function_sign("double");/*function_push_args_type("double");*/}
| KW_STRING {keep_function_sign("string");/*function_push_args_type("string");*/}
;
returnType:
  KW_BYTE   {keep_function_type("type");/*function_return("byte");*/}
| KW_CHAR   {keep_function_type("char");/*function_return("char");*/}
| KW_INT    {keep_function_type("int");/*function_return("int");*/}
| KW_BOOL   {keep_function_type("bool");/*function_return("bool");*/}
| KW_DOUBLE {keep_function_type("double");/*function_return("double");*/}
| KW_STRING {keep_function_type("string");/*function_return("string");*/}
| KW_VOID   {keep_function_type("void");/*function_return("void");*/}
;
// --------------------------------------------

// --------------------------------------------
// define if-else if-else
// --------------------------------------------
stateIfDefine:
  stateIf
| stateIf KW_ELSE codeBlockDefine {}
stateIf:
  stateIf KW_ELSE KW_IF LPAREN {tree_clear();} leaVal RPAREN {tree_clear();} codeBlockDefine {}
| KW_IF LPAREN {tree_clear();} leaVal RPAREN {tree_clear();} codeBlockDefine {}
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
codeBlockLoop: codeBlockLoop blockContext | blockContext;
blockContext: 
  ending
| commentDefine
| FIELD {/*val_register2($1);*/heap_register($1);} variableManyV2 {tree_clear();}
| stateIfDefine
| stateForDefine
| codeBlockDefine {}
;
variableManyV2:
  COLON basicTypeX0 {
//    variable_register(0);
//    variable_record();
  }
| COLON basicTypeX0 ASSIGN {} leaVal {
//    variable_register(0);
//    variable_record();
//    variable_assign_v2();
  }
| ASSIGN leaVal {
//    variable_register(1);
//    variable_already_exist();
//    variable_assign_v2();
  }
| LPAREN {heap_invoking();invoking_deep_inc();} leaInv
//| KW_MATCH {} stateMatchBlock
;
// --------------------------------------------


// --------------------------------------------
// define right value of variable and function return
// --------------------------------------------
// represent variable/function-invoking
leaVai:
  leaVar                     {heap_variable();}
| leaVar LPAREN {heap_invoking();invoking_deep_inc();} leaInv
;
leaVar: FIELD                {heap_register($1);}
;
leaInv:
  RPAREN                     {invoking_deep_dec();}
| leaInvOptions RPAREN       {heap_invoking_args_link();invoking_deep_dec();}
;
leaInvOptions:
  leaInvOptions COMMA {} booOrExp
| booOrExp                   {}
;
// --------------------------------------------

// --------------------------------------------
// define bool expression
// --------------------------------------------
leaVal: booOrExp {tree_node_deep_assign(); tree_node_print();};
booOrExp:
  booOrExp OR {} booAndExp { tree_node_link("||");}
| booAndExp {}
;
booAndExp:
  booAndExp AND {} booExpNot { tree_node_link("&&");}
| booExpNot {}
;
booExpNot:
  booAtom              {}
| NOT {} booAtom          {tree_node_link("!");}
;
booAtom:
  calExp
| calExp LT {} calExp     {tree_node_link("<");}
| calExp GT {} calExp     {tree_node_link(">");}
| calExp LE {} calExp     {tree_node_link("<=");}
| calExp GE {} calExp     {tree_node_link(">=");}
| calExp EQ {} calExp     {tree_node_link("==");}
| calExp NE {} calExp     {tree_node_link("!=");}
| booBas
;
booBas: 
  KW_TRUE              {tree_node_create("", "true", "bool");}
| KW_FALSE             {tree_node_create("", "false", "bool");}
;
// --------------------------------------------

// --------------------------------------------
// define calculation expression
// --------------------------------------------
calExp:
  calExpPro
| calExp OP_ADD {} calExpPro {tree_node_link("+");}
| calExp OP_SUB {} calExpPro {tree_node_link("-");}
;

calExpPro:
  calExpAtom
| calExpPro OP_MUL {} calExpAtom {tree_node_link("*");}
| calExpPro OP_DIV {} calExpAtom {tree_node_link("/");}
;

calExpAtom:
  LPAREN {} booOrExp RPAREN {tree_node_link("()");}
| OP_SUB INTEGER {tree_node_create("-", $2, "int");}
| OP_SUB DOUBLE  {tree_node_create("-", $2, "double");}
| INTEGER        {tree_node_create("", $1, "int");}
| DOUBLE         {tree_node_create("", $1, "double");}
| CHAR           {tree_node_create("", $1, "char");}
| STRING         {tree_node_create("", $1, "string");}
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


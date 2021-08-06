%{
#include <stdio.h>
#include <stdlib.h>
void yyerror(const char* s);
extern int yylex(void);
extern int yyparse(void);


%}

%token ANY
%token COMMENT_SINGLE COMMENT_BEGIN COMMENT_END
%token KW_EOF
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
  variableName COLON basicType ASSIGN lea_val  {printf("-assign-type\n");}
| variableName ASSIGN lea_val                   {printf("-assign\n");}
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
functionBody: ARROW lea_val {printf("-lambda\n");} | codeBlockDefine;
// --------------------------------------------

// --------------------------------------------
// define function invoke
// --------------------------------------------
invokeDefine: variableName LPAREN invokeArgsList;
invokeArgsList: RPAREN | lea_val invokeArgsLoop;
invokeArgsLoop: COMMA lea_val invokeArgsList | RPAREN;
// --------------------------------------------

// --------------------------------------------
// define if-else if-else
// --------------------------------------------
stateIfDefine: stateIf stateElse;
stateIf: KW_IF LPAREN lea_val RPAREN codeBlockDefine {printf("-if\n");}
;
stateElse: ending | stateElseApp;
stateElseApp: ending | KW_ELSE stateElseLoop;
stateElseLoop:
  {printf("-elif\n");} KW_IF LPAREN lea_val RPAREN codeBlockDefine stateElseApp
| {printf("-else\n");} codeBlockDefine
;
// --------------------------------------------

// --------------------------------------------
// define for-loop
// --------------------------------------------
stateForDefine: KW_FOR LPAREN stateForInit stateForCondition stateForUpdate RPAREN codeBlockDefine
;
stateForInit: SEMI | variableAssign SEMI;
stateForCondition: SEMI | lea_val SEMI;
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

// specific value
lea_bas: CHAR|OP_SUB INTEGER|INTEGER|DOUBLE|STRING|boo_bas;
lea_num: OP_SUB INTEGER|INTEGER|DOUBLE
lea_vai: lea_var {printf("[y] is var\n");} | lea_var LPAREN lea_inv_001 {printf("[y] is invoke\n");};
lea_var: FIELD;
//lea_inv: FIELD LPAREN lea_inv_001;
lea_inv_001: RPAREN | lea_inv_002;// args list
lea_inv_002: lea_bas lea_inv_003 | lea_vai lea_inv_003; // args list
lea_inv_003:
  COMMA lea_inv_002
| RPAREN
;

lea_val:
  boo_exp_001// SEMI{printf("over\n");};
;
boo_exp_001:
  boo_exp_002
| boo_exp_002 AND boo_exp_002
| boo_exp_002 OR boo_exp_002
| NOT boo_exp_002
;
boo_exp_002:
  cal_exp
| cal_exp LT cal_exp
| cal_exp GT cal_exp
| cal_exp LE cal_exp
| cal_exp GE cal_exp
| cal_exp EQ cal_exp
| cal_exp NE cal_exp
| boo_bas
;

cal_exp:
  {printf("[y] through\n");} cal_exp_001
| cal_exp OP_ADD cal_exp_001
| cal_exp OP_SUB cal_exp_001
;
cal_exp_001:
  cal_exp_002
| cal_exp_001 OP_MUL cal_exp_002
| cal_exp_001 OP_DIV cal_exp_002
;
cal_exp_002:
  lea_num
| CHAR
| STRING
| LPAREN boo_exp_001 RPAREN
| {printf("[y] vai\n");} lea_vai
;

boo_bas: KW_TRUE|KW_FALSE;

ending: SEMI | NEWLINE;

basicType: KW_BYTE | KW_CHAR | KW_INT | KW_BOOL | KW_DOUBLE | KW_STRING;

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

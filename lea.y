%{
#include <stdio.h>
#include <stdlib.h>
void yyerror(const char* s);
extern int yylex(void);
extern int yyparse(void);


%}

%token ANY
%token KW_EOF
%token KW_BYTE KW_CHAR KW_INT KW_BOOL KW_TRUE KW_FALSE KW_DOUBLE KW_STRING KW_DEF
%token KW_IF KW_ELSE KW_FOR KW_WHILE KW_MATCH KW_CASE
%token BOOL_AND BOOL_OR BOOL_NOT BOOL_EQ BOOL_NE BOOL_GT BOOL_GTE BOOL_LT BOOL_LTE
%token ARROW ASSIGN PAREN_LEFT PAREN_RIGHT DOT COMMA SEMI COLON NEWLINE BLOCK_BEGIN BLOCK_END
%token DOUBLE INTEGER FIELD CHAR STRING
%token OP_ADD OP_SUB OP_MUL OP_DIV OP_MOD
%%

test: bool_expr
;

root: 
  {printf(">> 0\n");} FIELD statement_variable root
| {printf(">> 1\n");} KW_IF statement_if root
| {printf(">> 2\n");} KW_ELSE statement_else root
| {printf(">> 3\n");} KW_FOR statement_for root
| {printf(">> 4\n");} KW_DEF FIELD function_define root
| line_end root
| KW_EOF {exit(0);}
| {printf(">> Any\n");} ANY
;


function_define: 
  PAREN_LEFT func_args_list COLON func_return_type
| COLON func_return_type
| func_return
;

func_return_type:
  basic_type func_return
| func_return
;

func_return:
  ARROW right_value_v2
| code_block
;

func_args_list:
  FIELD COLON basic_type func_args_app
| PAREN_RIGHT
;

func_args_app: 
  COMMA FIELD COLON basic_type func_args_list
| PAREN_RIGHT
;




statement_exec: FIELD statement_exec_app
;

statement_exec_app:
  PAREN_LEFT statement_invoking
| ASSIGN right_value_v2
;



statement_variable: 
  {printf("## 0\n");} COLON basic_type variable_define
| {printf("## 1\n");} PAREN_LEFT statement_invoking
| {printf("## 2\n");} variable_define
;

variable_define:
  {printf("## =\n");} ASSIGN right_value_v2
| line_end
;

statement_if: PAREN_LEFT right_value PAREN_RIGHT code_block
;

statement_if_v2: PAREN_LEFT statement_if_v2_div;
statement_if_v2_div:
  PAREN_LEFT statement_if_v2_div
| BOOL_NOT statement_if_v2_div
| bool_atom statement_if_v2_div_app
;
statement_if_v2_div_app:
  BOOL_AND statement_if_v2_div
| BOOL_OR statement_if_v2_div
| PAREN_RIGHT code_block
;
//statement_if_v2_app: code_block
//;

statement_else: KW_IF statement_if
| code_block
;

statement_for: PAREN_LEFT right_value PAREN_RIGHT code_block
;

statement_invoking: 
  PAREN_RIGHT
| right_value invoking_args
;

invoking_args: 
  COMMA right_value invoking_args
| PAREN_RIGHT
;

right_value: CHAR | INTEGER | STRING | bool_value;

right_value_v2: 
  {printf("#v2-char\n");} CHAR
| {printf("#v2-str\n");} STRING
| {printf("#v2-true\n");} KW_TRUE
| {printf("#v2-false\n");} KW_FALSE
| {printf("#v2-expr\n");} calc_expr
|
;

//bool_expr:
//  PAREN_LEFT bool_expr bool_expr_app PAREN_RIGHT
//| BOOL_NOT bool_expr bool_expr_app
//| bool_atom bool_expr_app
//;
//
//bool_expr_app:
//  BOOL_AND bool_expr
//| BOOL_OR bool_expr
//| PAREN_RIGHT statement_if_v2_app /* Here, for if/else if, and return code_block */
//| SEMI    /* Here, for assignment */
//| NEWLINE /* Here, for assignment */
//| COMMA
//;

bool_atom:
  FIELD bool_atom_expr_1
| basic_data bool_op bool_expr_atom
| KW_TRUE
| KW_FALSE
;

bool_expr_atom:
  basic_data
| FIELD statement_invoking
;

bool_atom_expr_1:
  PAREN_LEFT statement_invoking
| PAREN_LEFT statement_invoking bool_op bool_expr_atom
;

right_value_v3:
  CHAR right_value_char
| STRING right_value_string
| OP_SUB INTEGER right_value_int
| INTEGER right_value_int
| DOUBLE right_value_double
| KW_TRUE right_value_bool
| KW_FALSE right_value_bool
| FIELD right_value_about_var
| PAREN_LEFT right_value_paren_left
;

right_value_about_var:
  SEMI
| NEWLINE
|
;

calc_expr: 
  {printf(">11\n");} PAREN_LEFT calc_expr expr_1 /* bug 01 */
| {printf(">12\n");} INTEGER expr_3
| {printf(">12\n");} DOUBLE expr_1 /* bug 01 */
| {printf(">13\n");} FIELD expr_2
;

expr_3:
  SEMI     /* Single integer */
| NEWLINE  /* Single integer */
| expr_1;

expr_2: 
  PAREN_LEFT statement_invoking expr_1
| expr_1;

 /* Here, all operator without priority! */
expr_1: 
  {printf(">21\n");} OP_ADD calc_expr
| {printf(">22\n");} OP_SUB calc_expr
| {printf(">23\n");} OP_MUL calc_expr
| {printf(">24\n");} OP_DIV calc_expr
| {printf(">25\n");} PAREN_RIGHT /* bug 01 */
| {printf(">26\n");} SEMI
| {printf(">26\n");} NEWLINE
;


code_block: BLOCK_BEGIN code_block_app
;

code_block_app:
  line_end code_block_app
| FIELD code_block_app_1
| BLOCK_END
;

code_block_app_1:
  {printf("&& exec\n");} statement_exec_app code_block_app
| {printf("&& var\n");}  statement_variable code_block_app
;

line_end: SEMI | NEWLINE;

basic_type: KW_BYTE | KW_CHAR | KW_INT | KW_BOOL | KW_DOUBLE | KW_STRING;

basic_data:
  INTEGER
| DOUBLE
| STRING
| CHAR
;

bool_op: BOOL_EQ | BOOL_NE | BOOL_GT | BOOL_GTE | BOOL_LT | BOOL_LTE
;

bool_link: BOOL_AND | BOOL_OR
;

bool_not: BOOL_NOT
;

bool_value: KW_TRUE | KW_FALSE;

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

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
%token ASSIGN PAREN_LEFT PAREN_RIGHT DOT COMMA SEMI COLON NEWLINE BLOCK_BEGIN BLOCK_END
%token DOUBLE INTEGER FIELD CHAR STRING
%token OP_ADD OP_SUB OP_MUL OP_DIV OP_MOD
%%



root: 
  {printf(">> 0\n");} FIELD statement_variable root
| {printf(">> 1\n");} KW_IF statement_if root
| {printf(">> 2\n");} KW_ELSE statement_else root
| {printf(">> 3\n");} KW_FOR statement_for root
| KW_EOF
| {printf(">> Any\n");} ANY
;

statement_variable: 
  {printf("## 0\n");} COLON basic_type variable_define
| {printf("## 1\n");} PAREN_LEFT statement_invoking
;

variable_define:
  line_end
| {printf("## =\n");} ASSIGN right_value_v2
;

statement_if: PAREN_LEFT right_value PAREN_RIGHT code_block
;

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
  {printf("#v2-char\n");} CHAR line_end
| {printf("#v2-str\n");} STRING line_end
| {printf("#v2-true\n");} KW_TRUE line_end
| {printf("#v2-false\n");} KW_FALSE line_end
| {printf("#v2-expr\n");} calc_expr
;

calc_expr: 
  {printf(">11\n");} PAREN_LEFT calc_expr expr_1
| {printf(">12\n");} INTEGER expr_3
| {printf(">12\n");} DOUBLE expr_1
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
| {printf(">25\n");} PAREN_RIGHT
| {printf(">26\n");} SEMI
| {printf(">26\n");} NEWLINE
;


code_block: BLOCK_BEGIN BLOCK_END
;

line_end: SEMI | NEWLINE;


basic_type: KW_BYTE | KW_CHAR | KW_INT | KW_BOOL | KW_DOUBLE | KW_STRING;

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

%{
#include <stdio.h>
#include <stdlib.h>
void yyerror(const char* s);
extern int yylex(void);
extern int yyparse(void);


%}

%token KW_EOF
%token KW_BYTE KW_CHAR KW_INT KW_BOOL KW_TRUE KW_FALSE KW_DOUBLE KW_STRING KW_DEF
%token KW_IF KW_ELSE KW_FOR KW_WHILE KW_MATCH KW_CASE
%token ASSIGN PAREN_LEFT PAREN_RIGHT DOT COMMA SEMI COLON NEWLINE BLOCK_BEGIN BLOCK_END
%token INTEGER FIELD CHAR STRING
%%

root: 
  {printf(">> 0\n");} FIELD statement_variable root
| {printf(">> 1\n");} KW_IF statement_if root
| {printf(">> 2\n");} KW_ELSE statement_else root
| {printf(">> 3\n");} KW_FOR statement_for root
| KW_EOF
;

statement_variable: 
  COLON basic_type variable_define
| PAREN_LEFT statement_invoking
;

variable_define:
  line_end
| ASSIGN right_value line_end
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

code_block: BLOCK_BEGIN BLOCK_END
;

line_end: SEMI | NEWLINE;


basic_type: KW_BYTE | KW_CHAR | KW_INT | KW_BOOL | KW_DOUBLE | KW_STRING;

right_value: CHAR | INTEGER | STRING | bool_value;

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

%{
#include <stdio.h>
#include <stdlib.h>
void yyerror(const char* s);
extern int yylex(void);
extern int yyparse(void);


%}

%token KW_BYTE KW_CHAR KW_INT KW_BOOL KW_TRUE KW_FALSE KW_DOUBLE KW_STRING KW_DEF
%token KW_IF KW_ELIF KW_ELSE KW_FOR KW_WHILE KW_MATCH KW_CASE
%token ASSIGN PAREN_LEFT PAREN_RIGHT SEMI COLON NEWLINE BLOCK_BEGIN BLOCK_END
%token INTEGER FIELD CHAR STRING
%%

define_var: 
FIELD {printf("[y] begin 01\n");} COLON basic_type line_end {
    printf("[y] define var\n");
}
| FIELD {printf("[y] begin02\n");} COLON basic_type ASSIGN right_value line_end {
    printf("[y] define var, with right value\n");
}
| statement_if 
;

 /* simple: KW_IF line_end {printf("test simple\n");};*/

statement_if: KW_IF PAREN_LEFT right_value PAREN_RIGHT code_block {
    printf("[y] if expr\n");
}
;

code_block: BLOCK_BEGIN BLOCK_END
;

line_end: SEMI {printf("[y] semi;\n");} | NEWLINE;


basic_type: KW_BYTE | KW_CHAR | KW_INT | KW_BOOL | KW_DOUBLE | KW_STRING;

right_value: CHAR | INTEGER | STRING | bool_value;

bool_value: KW_TRUE | KW_FALSE;

 /*{printf("[y] \n");}*/

%%

void yyerror(const char* s)
{
	printf("[yacc] error : %s\n", s);
}

int main()
{
    yyparse();
    return 0;
}

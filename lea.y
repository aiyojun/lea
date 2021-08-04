%{
#include <stdio.h>
#include <stdlib.h>
void yyerror();
extern int yylex(void);
extern int yyparse(void);


%}

%token SEMI BLOCK_BEGIN BLOCK_END IF ELIF ELSE INTEGER FIELD

%%

prog: IF SEMI {printf("[y] IF\n"); exit(0);}
| IF ELSE SEMI {printf("[y] IF ELSE\n"); exit(0);}
| IF ELIF ELSE SEMI {printf("[y] IF ELIF ELSE\n"); exit(0);}
;
 /*
expression: ;

expression_assign: ;

expression_invoke: ;

statement_if: IF;

statement_elif: ELIF;

statement_else: ELSE;*/



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

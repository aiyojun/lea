%{
#include <stdio.h>
#include "lea.tab.h"

%}

field [a-zA-Z_][0-9a-zA-Z_]*
integer -?[0-9]+


%%
"EOF"                   {exit(0);}
";"                     {
                            return SEMI;
                        }
[ ]                     {;}
\n                      {;}
"if"                    {
	                        printf("[lex] if : %s\n", yytext);
                            return IF; 
                        }
"else if"               {
                            printf("[lex] else if : %s\n", yytext);
                            return ELIF;
                        }
"else"                  {
                            printf("[lex] else : %s\n", yytext);
                            return ELSE;
                        }
"{"                     { return BLOCK_BEGIN; }
"}"                     { return BLOCK_END; }
-?[0-9]+                {
	                        printf("[lex] INT : %s\n", yytext);
                            return INTEGER;
                        }
[a-zA-Z_][0-9a-zA-Z_]*  {
                            printf("[lex] FIELD : %s\n", yytext);
                            return FIELD;
                        }

%%
int yywrap()
{

	return 1;
}
%{
#include <stdio.h>
#include "lea.tab.h"

%}

field [a-zA-Z_][0-9a-zA-Z_]*
integer -?[0-9]+


%%
"EOF"                   {exit(0);}
[)]                     {
                            printf("[lex] PAREN_RIGHT : %s\n", yytext);
                            return PAREN_RIGHT;
                        }
[(]                     {
                            printf("[lex] PAREN_LEFT : %s\n", yytext);
                            return PAREN_LEFT;
                        }
"{"                     {
                            printf("[lex] { : %s\n", yytext);
                            return BLOCK_BEGIN; }
"}"                     {
                            printf("[lex] } : %s\n", yytext);
                            return BLOCK_END; }
":"                     {
                            printf("[lex] COLON : %s\n", yytext);
                            return COLON;
                        }
";"                     {
                            return SEMI;
                        }
[ ]                     {;}
\n                      {
                            return NEWLINE;
                        }
"="                     {
                            return ASSIGN;
                        }
"byte"                  {
                            return KW_BYTE;
                        }
"char"                  {
                            return KW_CHAR;
                        }
"int"                   {
                            return KW_INT;
                        }
"bool"                  {
                            return KW_BOOL;
                        }
"true"                  {
                            printf("[lex] TRUE : %s\n", yytext);
                            return KW_TRUE;
                        }
"false"                 {
                            return KW_FALSE;
                        }
"double"                {
                            return KW_DOUBLE;
                        }
"string"                {
                            printf("[lex] KW_STRING : %s\n", yytext);
                            return KW_STRING;
                        }
"def"                   {
                            return KW_DEF;
                        }
"if"                    {
	                        printf("[lex] if : %s\n", yytext);
                            return KW_IF; 
                        }
"else if"               {
                            printf("[lex] else if : %s\n", yytext);
                            return KW_ELIF;
                        }
"else"                  {
                            printf("[lex] else : %s\n", yytext);
                            return KW_ELSE;
                        }
"for"                   {
                            return KW_FOR;
                        }
"while"                 {
                            return KW_WHILE;
                        }
"match"                 {
                            return KW_MATCH;
                        }
"case"                  {
                            return KW_CASE;
                        }

(')(.|\n|\r)(')         {
                            printf("[lex] CHAR : %s\n", yytext);
                            return CHAR;
                        }
"\""([^"\""\\]|\\"\"")*"\""         {
                            printf("[lex] STRING : %s\n", yytext);
                            return STRING;
                        }
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
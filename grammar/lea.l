%{
#include <stdio.h>
#include "lea.tab.h"

%}

field [a-zA-Z_][0-9a-zA-Z_]*
integer -?[0-9]+


%%
<<EOF>>                 {return KW_EOF;}
"/*"                    {return COMMENT_BEGIN;}
"*/"                    {return COMMENT_END;}
"//"                    {
                            printf("[lex] single comment : %s\n", yytext);
                            return COMMENT_SINGLE;
                        }
[)]                     {
                            printf("[lex] PAREN_RIGHT : %s\n", yytext);
                            return RPAREN;
                        }
[(]                     {
                            printf("[lex] PAREN_LEFT : %s\n", yytext);
                            return LPAREN;
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
","                     {
                            printf("[lex] COMMA : %s\n", yytext);
                            return COMMA;
                        }
"."                     {
                            return DOT;
                        }
"+"                     {
                            printf("[lex] + : %s\n", yytext);
                            return OP_ADD;
                        }
"-"                     {
                            printf("[lex] - : %s\n", yytext);
                            return OP_SUB;
                        }
"*"                     {
                            printf("[lex] * : %s\n", yytext);
                            return OP_MUL;
                        }
"/"                     {
                            return OP_DIV;
                        }
[ \t]                     {;}
\n                      {
                            printf("[lex] newline\n");
                            return NEWLINE;
                        }
"->"                    {
                            return ARROW;
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
"&&"                    {
                            return AND;
                        }
"||"                    {
                            return OR;
                        }
"=="                    {
                            return EQ;
                        }
"!="                    {
                            return NE;
                        }
">="                    {
                            return GE;
                        }
"<="                    {
                            return LE;
                        }
">"                     {
                            return GT;
                        }
"<"                     {
                            return LT;
                        }
"!"                     {
                            return NOT;
                        }
"def"                   {
                            return KW_DEF;
                        }
"class"                 {
                            printf("[lex] else : %s\n", yytext);
                            return KW_CLASS;
                        }
"struct"                {
                            printf("[lex] else : %s\n", yytext);
                            return KW_STRUCT;
                        }
"if"                    {
	                        printf("[lex] if : %s\n", yytext);
                            return KW_IF; 
                        }
"else"                  {
                            printf("[lex] else : %s\n", yytext);
                            return KW_ELSE;
                        }
"for"                   {
                            printf("[lex] for : %s\n", yytext);
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
"_"                     {
                            return KW__;
                        }
(')(.|\n|\r)(')         {
                            printf("[lex] CHAR : %s\n", yytext);
                            return CHAR;
                        }
"\""([^"\""\\]|\\"\"")*"\""         {
                            printf("[lex] STRING : %s\n", yytext);
                            return STRING;
                        }
[0-9]+                  {
                            printf("[lex] POS_INT : %s\n", yytext);
                            return INTEGER;
                        }
[0-9]+"."[0-9]+         {
                            printf("[lex] DOUBLE : %s\n", yytext);
                            return DOUBLE;
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
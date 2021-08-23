%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grammar.h"
#include "lea.tab.h"
extern YYSTYPE yylval;
%}

%%
<<EOF>>                 {
                            expects_push(yytext); _p_lex("[lex] >> : %s\n", yytext);
                            return KW_EOF;}
"/*"                    {
                            expects_push(yytext); _p_lex("[lex] >> : %s\n", yytext);
                            return COMMENT_BEGIN;
                        }
"*/"                    {
                            expects_push(yytext); _p_lex("[lex] >> : %s\n", yytext);
                            return COMMENT_END;}
"//"                    {
                            expects_push(yytext); _p_lex("[lex] single comment : %s\n", yytext);
                            return COMMENT_SINGLE;
                        }
[)]                     {
                            expects_push(yytext); _p_lex("[lex] PAREN_RIGHT : %s\n", yytext);
                            return RPAREN;
                        }
[(]                     {
                            expects_push(yytext); _p_lex("[lex] PAREN_LEFT : %s\n", yytext);
                            return LPAREN;
                        }
"{"                     {
                            expects_push(yytext); _p_lex("[lex] { : %s\n", yytext);
                            return BLOCK_BEGIN; }
"}"                     {
                            expects_push(yytext); _p_lex("[lex] } : %s\n", yytext);
                            return BLOCK_END; }
":"                     {
                            yylval.ycText = yytext;
                            expects_push(yytext); _p_lex("[lex] COLON : %s\n", yytext);
                            return COLON;
                        }
";"                     {
                            expects_push(yytext); _p_lex("[lex] >> : %s\n", yytext);
                            return SEMI;
                        }
","                     {
                            expects_push(yytext); _p_lex("[lex] COMMA : %s\n", yytext);
                            return COMMA;
                        }
"."                     {
                            expects_push(yytext); _p_lex("[lex] >> : %s\n", yytext);
                            return DOT;
                        }
"+"                     {
                            expects_push(yytext); _p_lex("[lex] + : %s\n", yytext);
                            return OP_ADD;
                        }
"-"                     {
                            expects_push(yytext); _p_lex("[lex] - : %s\n", yytext);
                            return OP_SUB;
                        }
"*"                     {
                            expects_push(yytext); _p_lex("[lex] * : %s\n", yytext);
                            return OP_MUL;
                        }
"/"                     {
                            expects_push(yytext); _p_lex("[lex] >> : %s\n", yytext);
                            return OP_DIV;
                        }
[ \t]                   {;}
\n                      {
                            expects_push(yytext); _p_lex("[lex] newline\n");
                            // _line_inc();
                            lealine++;
                            return NEWLINE;
                        }
"->"                    {
                            expects_push(yytext); _p_lex("[lex] >> : %s\n", yytext);
                            return ARROW;
                        }
"="                     {
                            expects_push(yytext); _p_lex("[lex] >> : %s\n", yytext);
                            return ASSIGN;
                        }
"void"                  {
                            expects_push(yytext); _p_lex("[lex] >> : %s\n", yytext);
                            yylval.ycText = yytext;
                            return KW_VOID;
                        }
"byte"                  {
                            expects_push(yytext); _p_lex("[lex] >> : %s\n", yytext);
                            yylval.ycText = yytext;
                            return KW_BYTE;
                        }
"char"                  {
                            expects_push(yytext); _p_lex("[lex] >> : %s\n", yytext);
                            yylval.ycText = yytext;
                            return KW_CHAR;
                        }
"int"                   {
                            expects_push(yytext); _p_lex("[lex] >> : %s\n", yytext);
                            yylval.ycText = yytext;
                            return KW_INT;
                        }
"bool"                  {
                            expects_push(yytext); _p_lex("[lex] >> : %s\n", yytext);
                            yylval.ycText = yytext;
                            return KW_BOOL;
                        }
"true"                  {
                            // yylval.ycValueBool = 1;
                            yylval.ycText = yytext;
                            expects_push(yytext); _p_lex("[lex] TRUE : %s\n", yytext);
                            return KW_TRUE;
                        }
"false"                 {
                            expects_push(yytext); _p_lex("[lex] >> : %s\n", yytext);
                            yylval.ycText = yytext;
                            ; yylval.ycValueBool = 0;
                            return KW_FALSE;
                        }
"double"                {
                            expects_push(yytext); _p_lex("[lex] >> : %s\n", yytext);
                            yylval.ycText = yytext;
                            return KW_DOUBLE;
                        }
"string"                {
                            expects_push(yytext); _p_lex("[lex] >> : %s\n", yytext);
                            expects_push(yytext); _p_lex("[lex] KW_STRING : %s\n", yytext);
                            yylval.ycText = yytext;
                            return KW_STRING;
                        }
"&&"                    {
                            expects_push(yytext); _p_lex("[lex] >> : %s\n", yytext);
                            return AND;
                        }
"||"                    {
                            expects_push(yytext); _p_lex("[lex] >> : %s\n", yytext);
                            return OR;
                        }
"=="                    {
                            expects_push(yytext); _p_lex("[lex] >> : %s\n", yytext);
                            return EQ;
                        }
"!="                    {
                            expects_push(yytext); _p_lex("[lex] >> : %s\n", yytext);
                            return NE;
                        }
">="                    {
                            expects_push(yytext); _p_lex("[lex] >> : %s\n", yytext);
                            return GE;
                        }
"<="                    {
                            expects_push(yytext); _p_lex("[lex] >> : %s\n", yytext);
                            return LE;
                        }
">"                     {
                            expects_push(yytext); _p_lex("[lex] >> : %s\n", yytext);
                            return GT;
                        }
"<"                     {
                            expects_push(yytext); _p_lex("[lex] >> : %s\n", yytext);
                            return LT;
                        }
"!"                     {
                            expects_push(yytext); _p_lex("[lex] >> : %s\n", yytext);
                            return NOT;
                        }
"def"                   {
                            expects_push(yytext); _p_lex("[lex] >> : %s\n", yytext);
                            yylval.ycText = yytext;
                            return KW_DEF;
                        }
"return"                   {
                            expects_push(yytext); _p_lex("[lex] >> : %s\n", yytext);
                            yylval.ycText = yytext;
                            return KW_RETURN;
                        }
"class"                 {
                            expects_push(yytext); _p_lex("[lex] else : %s\n", yytext);
                            return KW_CLASS;
                        }
"struct"                {
                            expects_push(yytext); _p_lex("[lex] else : %s\n", yytext);
                            return KW_STRUCT;
                        }
"if"                    {
	                        expects_push(yytext); _p_lex("[lex] if : %s\n", yytext);
                            return KW_IF; 
                        }
"else"                  {
                            expects_push(yytext); _p_lex("[lex] else : %s\n", yytext);
                            return KW_ELSE;
                        }
"for"                   {
                            expects_push(yytext); _p_lex("[lex] for : %s\n", yytext);
                            return KW_FOR;
                        }
"while"                 {
                            expects_push(yytext); _p_lex("[lex] >> : %s\n", yytext);
                            return KW_WHILE;
                        }
"match"                 {
                            expects_push(yytext); _p_lex("[lex] >> : %s\n", yytext);
                            return KW_MATCH;
                        }
"case"                  {
                            expects_push(yytext); _p_lex("[lex] >> : %s\n", yytext);
                            return KW_CASE;
                        }
"_"                     {
                            expects_push(yytext); _p_lex("[lex] >> : %s\n", yytext);
                            return KW__;
                        }
(')(.|\n|\r)(')         {
                            yylval.ycText = yytext;
                            expects_push(yytext); _p_lex("[lex] CHAR : %s\n", yytext);
                            return CHAR;
                        }
"\""([^"\""\\]|\\"\""|(\\[nr]))*"\""         {
                            yylval.ycText = yytext;
                            expects_push(yytext); _p_lex("[lex] STRING : %s\n", yytext);
                            return STRING;
                        }
[0-9]+                  {
                            yylval.ycText = yytext;
                            expects_push(yytext); _p_lex("[lex] POS_INT : %s\n", yytext);
                            return INTEGER;
                        }
[0-9]+"."[0-9]+         {
                            yylval.ycText = yytext;
                            expects_push(yytext); _p_lex("[lex] DOUBLE : %s\n", yytext);
                            return DOUBLE;
                        }
[a-zA-Z_][0-9a-zA-Z_]*  {
                            yylval.ycText = yytext;
                            expects_push(yytext); _p_lex("[lex] FIELD : %s\n", yytext);
                            return FIELD;
                        }

%%
int yywrap()
{
    return 1;
}
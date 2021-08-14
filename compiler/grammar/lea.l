%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "syntax.h"
#include "lea.tab.h"
extern YYSTYPE yylval;
%}

%%
<<EOF>>                 {
                            _p_lex("[lex] >> : %s\n", yytext);
                            return KW_EOF;}
"/*"                    {
                            _p_lex("[lex] >> : %s\n", yytext);
                            return COMMENT_BEGIN;
                        }
"*/"                    {
                            _p_lex("[lex] >> : %s\n", yytext);
                            return COMMENT_END;}
"//"                    {
                            _p_lex("[lex] single comment : %s\n", yytext);
                            return COMMENT_SINGLE;
                        }
[)]                     {
                            _p_lex("[lex] PAREN_RIGHT : %s\n", yytext);
                            return RPAREN;
                        }
[(]                     {
                            _p_lex("[lex] PAREN_LEFT : %s\n", yytext);
                            return LPAREN;
                        }
"{"                     {
                            _p_lex("[lex] { : %s\n", yytext);
                            return BLOCK_BEGIN; }
"}"                     {
                            _p_lex("[lex] } : %s\n", yytext);
                            return BLOCK_END; }
":"                     {
                            yylval.ycText = yytext;
                            _p_lex("[lex] COLON : %s\n", yytext);
                            return COLON;
                        }
";"                     {
                            _p_lex("[lex] >> : %s\n", yytext);
                            return SEMI;
                        }
","                     {
                            _p_lex("[lex] COMMA : %s\n", yytext);
                            return COMMA;
                        }
"."                     {
                            _p_lex("[lex] >> : %s\n", yytext);
                            return DOT;
                        }
"+"                     {
                            _p_lex("[lex] + : %s\n", yytext);
                            return OP_ADD;
                        }
"-"                     {
                            _p_lex("[lex] - : %s\n", yytext);
                            return OP_SUB;
                        }
"*"                     {
                            _p_lex("[lex] * : %s\n", yytext);
                            return OP_MUL;
                        }
"/"                     {
                            _p_lex("[lex] >> : %s\n", yytext);
                            return OP_DIV;
                        }
[ \t]                   {;}
\n                      {
                            _p_lex("[lex] newline\n");
                            // _line_inc();
                            lealine++;
                            return NEWLINE;
                        }
"->"                    {
                            _p_lex("[lex] >> : %s\n", yytext);
                            return ARROW;
                        }
"="                     {
                            _p_lex("[lex] >> : %s\n", yytext);
                            return ASSIGN;
                        }
"byte"                  {
                            _p_lex("[lex] >> : %s\n", yytext);
                            yylval.ycText = yytext;
                            return KW_BYTE;
                        }
"char"                  {
                            _p_lex("[lex] >> : %s\n", yytext);
                            yylval.ycText = yytext;
                            return KW_CHAR;
                        }
"int"                   {
                            _p_lex("[lex] >> : %s\n", yytext);
                            yylval.ycText = yytext;
                            return KW_INT;
                        }
"bool"                  {
                            _p_lex("[lex] >> : %s\n", yytext);
                            yylval.ycText = yytext;
                            return KW_BOOL;
                        }
"true"                  {
                            // yylval.ycValueBool = 1;
                            yylval.ycText = yytext;
                            _p_lex("[lex] TRUE : %s\n", yytext);
                            return KW_TRUE;
                        }
"false"                 {
                            _p_lex("[lex] >> : %s\n", yytext);
                            yylval.ycText = yytext;
                            ; yylval.ycValueBool = 0;
                            return KW_FALSE;
                        }
"double"                {
                            _p_lex("[lex] >> : %s\n", yytext);
                            yylval.ycText = yytext;
                            return KW_DOUBLE;
                        }
"string"                {
                            _p_lex("[lex] >> : %s\n", yytext);
                            _p_lex("[lex] KW_STRING : %s\n", yytext);
                            yylval.ycText = yytext;
                            return KW_STRING;
                        }
"&&"                    {
                            _p_lex("[lex] >> : %s\n", yytext);
                            return AND;
                        }
"||"                    {
                            _p_lex("[lex] >> : %s\n", yytext);
                            return OR;
                        }
"=="                    {
                            _p_lex("[lex] >> : %s\n", yytext);
                            return EQ;
                        }
"!="                    {
                            _p_lex("[lex] >> : %s\n", yytext);
                            return NE;
                        }
">="                    {
                            _p_lex("[lex] >> : %s\n", yytext);
                            return GE;
                        }
"<="                    {
                            _p_lex("[lex] >> : %s\n", yytext);
                            return LE;
                        }
">"                     {
                            _p_lex("[lex] >> : %s\n", yytext);
                            return GT;
                        }
"<"                     {
                            _p_lex("[lex] >> : %s\n", yytext);
                            return LT;
                        }
"!"                     {
                            _p_lex("[lex] >> : %s\n", yytext);
                            return NOT;
                        }
"def"                   {
                            _p_lex("[lex] >> : %s\n", yytext);
                            yylval.ycText = yytext;
                            return KW_DEF;
                        }
"return"                   {
                            _p_lex("[lex] >> : %s\n", yytext);
                            yylval.ycText = yytext;
                            return KW_RETURN;
                        }
"class"                 {
                            _p_lex("[lex] else : %s\n", yytext);
                            return KW_CLASS;
                        }
"struct"                {
                            _p_lex("[lex] else : %s\n", yytext);
                            return KW_STRUCT;
                        }
"if"                    {
	                        _p_lex("[lex] if : %s\n", yytext);
                            return KW_IF; 
                        }
"else"                  {
                            _p_lex("[lex] else : %s\n", yytext);
                            return KW_ELSE;
                        }
"for"                   {
                            _p_lex("[lex] for : %s\n", yytext);
                            return KW_FOR;
                        }
"while"                 {
                            _p_lex("[lex] >> : %s\n", yytext);
                            return KW_WHILE;
                        }
"match"                 {
                            _p_lex("[lex] >> : %s\n", yytext);
                            return KW_MATCH;
                        }
"case"                  {
                            _p_lex("[lex] >> : %s\n", yytext);
                            return KW_CASE;
                        }
"_"                     {
                            _p_lex("[lex] >> : %s\n", yytext);
                            return KW__;
                        }
(')(.|\n|\r)(')         {
                            yylval.ycValueChar = yytext[0];
                            _p_lex("[lex] CHAR : %s\n", yytext);
                            return CHAR;
                        }
"\""([^"\""\\]|\\"\""|(\\[nr]))*"\""         {
                            yylval.ycText = yytext;
                            _p_lex("[lex] STRING : %s\n", yytext);
                            return STRING;
                        }
[0-9]+                  {
                            yylval.ycValueInt = atoi(yytext);
                            _p_lex("[lex] POS_INT : %s\n", yytext);
                            return INTEGER;
                        }
[0-9]+"."[0-9]+         {
                            yylval.ycValueDouble = atof(yytext);
                            _p_lex("[lex] DOUBLE : %s\n", yytext);
                            return DOUBLE;
                        }
[a-zA-Z_][0-9a-zA-Z_]*  {
                            yylval.ycText = yytext;
                            _p_lex("[lex] FIELD : %s\n", yytext);
                            return FIELD;
                        }

%%
int yywrap()
{
    return 1;
}
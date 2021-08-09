%{
#include <stdio.h>
#include <stdlib.h>
#include "lea.tab.h"
#include "lang/grammar.h"
extern YYSTYPE yylval;
%}

field [a-zA-Z_][0-9a-zA-Z_]*
integer -?[0-9]+


%%
<<EOF>>                 {return KW_EOF;}
"/*"                    {return COMMENT_BEGIN;}
"*/"                    {return COMMENT_END;}
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
                            return SEMI;
                        }
","                     {
                            _p_lex("[lex] COMMA : %s\n", yytext);
                            return COMMA;
                        }
"."                     {
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
                            return OP_DIV;
                        }
[ \t]                   {;}
\n                      {
                            _p_lex("[lex] newline\n");
                            _line_inc();
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
                            yylval.ycValueBool = 1;
                            _p_lex("[lex] TRUE : %s\n", yytext);
                            return KW_TRUE;
                        }
"false"                 {
                            yylval.ycValueBool = 0;
                            return KW_FALSE;
                        }
"double"                {
                            return KW_DOUBLE;
                        }
"string"                {
                            _p_lex("[lex] KW_STRING : %s\n", yytext);
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
                            yylval.ycText = yytext;
                            return KW_DEF;
                        }
"return"                   {
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
                            yylval.ycValueChar = yytext[0];
                            _p_lex("[lex] CHAR : %s\n", yytext);
                            return CHAR;
                        }
"\""([^"\""\\]|\\"\"")*"\""         {
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
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grammar.h"
#include "lea.tab.hh"
extern yy::parser::semantic_type yylval;
%}

%%
<<EOF>>                 {
                            expects_push(yytext); _p_lex("[lex] >> : %s\n", yytext);
                            return yy::parser::token::token_kind_type::KW_EOF;}
[)]                     {
                            expects_push(yytext); _p_lex("[lex] PAREN_RIGHT : %s\n", yytext);
                            return yy::parser::token::token_kind_type::RPAREN;
                        }
[(]                     {
                            expects_push(yytext); _p_lex("[lex] PAREN_LEFT : %s\n", yytext);
                            return yy::parser::token::token_kind_type::LPAREN;
                        }
"{"                     {
                            expects_push(yytext); _p_lex("[lex] { : %s\n", yytext);
                            return yy::parser::token::token_kind_type::BLOCK_BEGIN; }
"}"                     {
                            expects_push(yytext); _p_lex("[lex] } : %s\n", yytext);
                            return yy::parser::token::token_kind_type::BLOCK_END; }
":"                     {
                            printf(">> 01");yylval.ycText = yytext;
                            expects_push(yytext); _p_lex("[lex] COLON : %s\n", yytext);
                            return yy::parser::token::token_kind_type::COLON;
                        }
";"                     {
                            expects_push(yytext); _p_lex("[lex] >> : %s\n", yytext);
                            return yy::parser::token::token_kind_type::SEMI;
                        }
","                     {
                            expects_push(yytext); _p_lex("[lex] COMMA : %s\n", yytext);
                            return yy::parser::token::token_kind_type::COMMA;
                        }
"."                     {
                            expects_push(yytext); _p_lex("[lex] >> : %s\n", yytext);
                            return yy::parser::token::token_kind_type::DOT;
                        }
"+"                     {
                            expects_push(yytext); _p_lex("[lex] + : %s\n", yytext);
                            return yy::parser::token::token_kind_type::OP_ADD;
                        }
"-"                     {
                            expects_push(yytext); _p_lex("[lex] - : %s\n", yytext);
                            return yy::parser::token::token_kind_type::OP_SUB;
                        }
"*"                     {
                            expects_push(yytext); _p_lex("[lex] * : %s\n", yytext);
                            return yy::parser::token::token_kind_type::OP_MUL;
                        }
"/"                     {
                            expects_push(yytext); _p_lex("[lex] >> : %s\n", yytext);
                            return yy::parser::token::token_kind_type::OP_DIV;
                        }
[ \t]                   {;}
\n                      {
                            expects_push(yytext); _p_lex("[lex] newline\n");
                            // _line_inc();
                            lealine++;
                            return yy::parser::token::token_kind_type::NEWLINE;
                        }
"->"                    {
                            expects_push(yytext); _p_lex("[lex] >> : %s\n", yytext);
                            return yy::parser::token::token_kind_type::ARROW;
                        }
"="                     {
                            expects_push(yytext); _p_lex("[lex] >> : %s\n", yytext);
                            return yy::parser::token::token_kind_type::ASSIGN;
                        }
"void"                  {
                            expects_push(yytext); _p_lex("[lex] >> : %s\n", yytext);
                            yylval.ycText = yytext;
                            return yy::parser::token::token_kind_type::KW_VOID;
                        }
"byte"                  {
                            expects_push(yytext); _p_lex("[lex] >> : %s\n", yytext);
                            yylval.ycText = yytext;
                            return yy::parser::token::token_kind_type::KW_BYTE;
                        }
"char"                  {
                            expects_push(yytext); _p_lex("[lex] >> : %s\n", yytext);
                            yylval.ycText = yytext;
                            return yy::parser::token::token_kind_type::KW_CHAR;
                        }
"int"                   {
                            expects_push(yytext); _p_lex("[lex] >> : %s\n", yytext);
                            yylval.ycText = yytext;
                            return yy::parser::token::token_kind_type::KW_INT;
                        }
"bool"                  {
                            expects_push(yytext); _p_lex("[lex] >> : %s\n", yytext);
                            yylval.ycText = yytext;
                            return yy::parser::token::token_kind_type::KW_BOOL;
                        }
"true"                  {
                            // yylval.ycValueBool = 1;
                            yylval.ycText = yytext;
                            expects_push(yytext); _p_lex("[lex] TRUE : %s\n", yytext);
                            return yy::parser::token::token_kind_type::KW_TRUE;
                        }
"false"                 {
                            expects_push(yytext); _p_lex("[lex] >> : %s\n", yytext);
                            yylval.ycText = yytext;
                            ; yylval.ycValueBool = 0;
                            return yy::parser::token::token_kind_type::KW_FALSE;
                        }
"double"                {
                            expects_push(yytext); _p_lex("[lex] >> : %s\n", yytext);
                            yylval.ycText = yytext;
                            return yy::parser::token::token_kind_type::KW_DOUBLE;
                        }
"string"                {
                            expects_push(yytext); _p_lex("[lex] >> : %s\n", yytext);
                            expects_push(yytext); _p_lex("[lex] KW_STRING : %s\n", yytext);
                            yylval.ycText = yytext;
                            return yy::parser::token::token_kind_type::KW_STRING;
                        }
"&&"                    {
                            expects_push(yytext); _p_lex("[lex] >> : %s\n", yytext);
                            return yy::parser::token::token_kind_type::AND;
                        }
"||"                    {
                            expects_push(yytext); _p_lex("[lex] >> : %s\n", yytext);
                            return yy::parser::token::token_kind_type::OR;
                        }
"=="                    {
                            expects_push(yytext); _p_lex("[lex] >> : %s\n", yytext);
                            return yy::parser::token::token_kind_type::EQ;
                        }
"!="                    {
                            expects_push(yytext); _p_lex("[lex] >> : %s\n", yytext);
                            return yy::parser::token::token_kind_type::NE;
                        }
">="                    {
                            expects_push(yytext); _p_lex("[lex] >> : %s\n", yytext);
                            return yy::parser::token::token_kind_type::GE;
                        }
"<="                    {
                            expects_push(yytext); _p_lex("[lex] >> : %s\n", yytext);
                            return yy::parser::token::token_kind_type::LE;
                        }
">"                     {
                            expects_push(yytext); _p_lex("[lex] >> : %s\n", yytext);
                            return yy::parser::token::token_kind_type::GT;
                        }
"<"                     {
                            expects_push(yytext); _p_lex("[lex] >> : %s\n", yytext);
                            return yy::parser::token::token_kind_type::LT;
                        }
"!"                     {
                            expects_push(yytext); _p_lex("[lex] >> : %s\n", yytext);
                            return yy::parser::token::token_kind_type::NOT;
                        }
"def"                   {
                            expects_push(yytext); _p_lex("[lex] >> : %s\n", yytext);
                            yylval.ycText = yytext;
                            return yy::parser::token::token_kind_type::KW_DEF;
                        }
"return"                   {
                            expects_push(yytext); _p_lex("[lex] >> : %s\n", yytext);
                            yylval.ycText = yytext;
                            return yy::parser::token::token_kind_type::KW_RETURN;
                        }
"class"                 {
                            expects_push(yytext); _p_lex("[lex] else : %s\n", yytext);
                            return yy::parser::token::token_kind_type::KW_CLASS;
                        }
"struct"                {
                            expects_push(yytext); _p_lex("[lex] else : %s\n", yytext);
                            return yy::parser::token::token_kind_type::KW_STRUCT;
                        }
"if"                    {
	                        expects_push(yytext); _p_lex("[lex] if : %s\n", yytext);
                            return yy::parser::token::token_kind_type::KW_IF;
                        }
"else"                  {
                            expects_push(yytext); _p_lex("[lex] else : %s\n", yytext);
                            return yy::parser::token::token_kind_type::KW_ELSE;
                        }
"for"                   {
                            expects_push(yytext); _p_lex("[lex] for : %s\n", yytext);
                            return yy::parser::token::token_kind_type::KW_FOR;
                        }
"while"                 {
                            expects_push(yytext); _p_lex("[lex] >> : %s\n", yytext);
                            return yy::parser::token::token_kind_type::KW_WHILE;
                        }
"match"                 {
                            expects_push(yytext); _p_lex("[lex] >> : %s\n", yytext);
                            return yy::parser::token::token_kind_type::KW_MATCH;
                        }
"case"                  {
                            expects_push(yytext); _p_lex("[lex] >> : %s\n", yytext);
                            return yy::parser::token::token_kind_type::KW_CASE;
                        }
"_"                     {
                            expects_push(yytext); _p_lex("[lex] >> : %s\n", yytext);
                            return yy::parser::token::token_kind_type::KW__;
                        }
(')(.|\n|\r)(')         {
                            yylval.ycText = yytext;
                            expects_push(yytext); _p_lex("[lex] CHAR : %s\n", yytext);
                            return yy::parser::token::token_kind_type::CHAR;
                        }
"\""([^"\""\\]|\\"\""|(\\[nr]))*"\""         {
                            yylval.ycText = yytext;
                            expects_push(yytext); _p_lex("[lex] STRING : %s\n", yytext);
                            return yy::parser::token::token_kind_type::STRING;
                        }
[0-9]+                  {
                            yylval.ycText = yytext;
                            expects_push(yytext); _p_lex("[lex] POS_INT : %s\n", yytext);
                            return yy::parser::token::token_kind_type::INTEGER;
                        }
[0-9]+"."[0-9]+         {
                            yylval.ycText = yytext;
                            expects_push(yytext); _p_lex("[lex] DOUBLE : %s\n", yytext);
                            return yy::parser::token::token_kind_type::DOUBLE;
                        }
[a-zA-Z_][0-9a-zA-Z_]*  {
                            yylval.ycText = yytext;
                            printf("lexer: %s\n", yytext);
                            expects_push(yytext); _p_lex("[lex] FIELD : %s\n", yytext);
                            return yy::parser::token::token_kind_type::FIELD;
                        }

%%
int yyFlexLexer::yywrap()
{
    return 1;
}
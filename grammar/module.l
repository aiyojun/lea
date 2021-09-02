%{
#include <cstdlib>
#include <vector>
#include <string>
#include <iostream>
bool openSemi = false;
bool openEnter = false;
bool openNewline = false;
bool openRaw = false;
bool openImp = false;
std::string gtoken;
std::string gtoken_0;
std::string gtoken_1;
void set_raw_mode() {openNewline=false;openSemi=true;openEnter=true;openImp=true;}
void ll_println(char* msg) {gtoken_1=gtoken_0;gtoken_0=gtoken;gtoken=std::string(msg==0?"":msg);gtoken=gtoken=="\n"?"\\n":gtoken;}// {std::cout << "[ll] " << msg << "\n";}
#include "module.tab.hh"
extern yy::parser::semantic_type yylval;
bool braceOpen = false;
std::vector<std::string> implements;
%}

%%

[ \t]       {yylval.ycText=yytext;if(openRaw)return yy::parser::token::token_kind_type::GAP;}
\n 			{yylval.ycText=yytext;ll_println(yytext);if(openNewline) return yy::parser::token::token_kind_type::NEWLINE;if(openEnter) return yy::parser::token::token_kind_type::SB_ENTER;}
"import"	{yylval.ycText=yytext;ll_println(yytext);return yy::parser::token::token_kind_type::KW_IMPORT;}
"var"		{yylval.ycText=yytext;ll_println(yytext);return yy::parser::token::token_kind_type::KW_VAR;}
"val"		{yylval.ycText=yytext;ll_println(yytext);return yy::parser::token::token_kind_type::KW_VAL;}
"def"		{yylval.ycText=yytext;ll_println(yytext);return yy::parser::token::token_kind_type::KW_DEF;}
"class"		{yylval.ycText=yytext;ll_println(yytext);return yy::parser::token::token_kind_type::KW_CLASS;}
"pub"		{yylval.ycText=yytext;ll_println(yytext);return yy::parser::token::token_kind_type::KW_PUB;}
"void"		{yylval.ycText=yytext;ll_println(yytext);return yy::parser::token::token_kind_type::KW_VOID;}
"int"		{yylval.ycText=yytext;ll_println(yytext);return yy::parser::token::token_kind_type::KW_INT;}
"long"		{yylval.ycText=yytext;ll_println(yytext);return yy::parser::token::token_kind_type::KW_LONG;}
"double"	{yylval.ycText=yytext;ll_println(yytext);return yy::parser::token::token_kind_type::KW_DOUBLE;}
"char"		{yylval.ycText=yytext;ll_println(yytext);return yy::parser::token::token_kind_type::KW_CHAR;}
"string"	{yylval.ycText=yytext;ll_println(yytext);return yy::parser::token::token_kind_type::KW_STRING;}
"bool"		{yylval.ycText=yytext;ll_println(yytext);return yy::parser::token::token_kind_type::KW_BOOL;}
"true"		{yylval.ycText=yytext;ll_println(yytext);return yy::parser::token::token_kind_type::KW_TRUE;}
"false"		{yylval.ycText=yytext;ll_println(yytext);return yy::parser::token::token_kind_type::KW_FALSE;}
"if"		{yylval.ycText=yytext;ll_println(yytext);return yy::parser::token::token_kind_type::KW_IF;}
"else"		{yylval.ycText=yytext;ll_println(yytext);return yy::parser::token::token_kind_type::KW_ELSE;}
"match"		{yylval.ycText=yytext;ll_println(yytext);return yy::parser::token::token_kind_type::KW_MATCH;}
"case"		{yylval.ycText=yytext;ll_println(yytext);return yy::parser::token::token_kind_type::KW_CASE;}
"while"		{yylval.ycText=yytext;ll_println(yytext);return yy::parser::token::token_kind_type::KW_WHILE;}
"for"		{yylval.ycText=yytext;ll_println(yytext);return yy::parser::token::token_kind_type::KW_FOR;}
"continue"	{yylval.ycText=yytext;ll_println(yytext);return yy::parser::token::token_kind_type::KW_CONTINUE;}
"break"		{yylval.ycText=yytext;ll_println(yytext);return yy::parser::token::token_kind_type::KW_BREAK;}
"return"	{yylval.ycText=yytext;ll_println(yytext);return yy::parser::token::token_kind_type::KW_RETURN;}
[(]			{yylval.ycText=yytext;ll_println(yytext);return yy::parser::token::token_kind_type::SB_LPAREN;}
[)]			{yylval.ycText=yytext;ll_println(yytext);return yy::parser::token::token_kind_type::SB_RPAREN;}
"{"			{yylval.ycText=yytext;ll_println(yytext);return yy::parser::token::token_kind_type::SB_LBRACE;}
"}"			{yylval.ycText=yytext;ll_println(yytext);return yy::parser::token::token_kind_type::SB_RBRACE;}
"["			{yylval.ycText=yytext;ll_println(yytext);return yy::parser::token::token_kind_type::SB_LSQBRACE;}
"]"			{yylval.ycText=yytext;ll_println(yytext);return yy::parser::token::token_kind_type::SB_RSQBRACE;}
"."			{yylval.ycText=yytext;ll_println(yytext);return yy::parser::token::token_kind_type::SB_DOT;}
":"			{yylval.ycText=yytext;ll_println(yytext);return yy::parser::token::token_kind_type::SB_COLON;}
";"			{yylval.ycText=yytext;ll_println(yytext);if(openNewline) return yy::parser::token::token_kind_type::NEWLINE;if(openSemi) return yy::parser::token::token_kind_type::SB_SEMI;}
","			{yylval.ycText=yytext;ll_println(yytext);return yy::parser::token::token_kind_type::SB_COMMA;}
"->"		{yylval.ycText=yytext;ll_println(yytext);return yy::parser::token::token_kind_type::SB_ARROW;}
"="			{yylval.ycText=yytext;ll_println(yytext);return yy::parser::token::token_kind_type::SB_ASSIGN;}
"+"			{yylval.ycText=yytext;ll_println(yytext);return yy::parser::token::token_kind_type::SB_ADD;}
"-"			{yylval.ycText=yytext;ll_println(yytext);return yy::parser::token::token_kind_type::SB_SUB;}
"*"			{yylval.ycText=yytext;ll_println(yytext);return yy::parser::token::token_kind_type::SB_MUL;}
"/"			{yylval.ycText=yytext;ll_println(yytext);return yy::parser::token::token_kind_type::SB_DIV;}
"%"			{yylval.ycText=yytext;ll_println(yytext);return yy::parser::token::token_kind_type::SB_MOD;}
">"			{yylval.ycText=yytext;ll_println(yytext);return yy::parser::token::token_kind_type::SB_GT;}
"<"			{yylval.ycText=yytext;ll_println(yytext);return yy::parser::token::token_kind_type::SB_LT;}
">="		{yylval.ycText=yytext;ll_println(yytext);return yy::parser::token::token_kind_type::SB_GE;}
"<="		{yylval.ycText=yytext;ll_println(yytext);return yy::parser::token::token_kind_type::SB_LE;}
"!="		{yylval.ycText=yytext;ll_println(yytext);return yy::parser::token::token_kind_type::SB_NE;}
"=="		{yylval.ycText=yytext;ll_println(yytext);return yy::parser::token::token_kind_type::SB_EQ;}
"!"			{yylval.ycText=yytext;ll_println(yytext);return yy::parser::token::token_kind_type::SB_NOT;}
"&&"		{yylval.ycText=yytext;ll_println(yytext);return yy::parser::token::token_kind_type::SB_AND;}
"||"		{yylval.ycText=yytext;ll_println(yytext);return yy::parser::token::token_kind_type::SB_OR;}
(')(.|\n|\r)(') 	{yylval.ycText = yytext;ll_println(yytext);return yy::parser::token::token_kind_type::VA_CHAR;}
"\""([^"\""\\]|\\"\""|(\\[nr]))*"\"" {yylval.ycText = yytext;ll_println(yytext);return yy::parser::token::token_kind_type::VA_STRING;}
[0-9]+ 				{yylval.ycText = yytext;ll_println(yytext);return yy::parser::token::token_kind_type::VA_INT;}
[0-9]+"."[0-9]+ 	{yylval.ycText = yytext;ll_println(yytext);return yy::parser::token::token_kind_type::VA_DOUBLE;}
[a-zA-Z_][0-9a-zA-Z_]* 	{yylval.ycText = yytext;ll_println(yytext);return yy::parser::token::token_kind_type::VA_ID;}

%%

FlexLexer* lexer = new yyFlexLexer;

int yyFlexLexer::yywrap()
{
    return 1;
}

int yylex(yy::parser::semantic_type* value) {
	if (!openImp && braceOpen) {
		openNewline=false;openSemi=true;openEnter=true;openRaw=true;
		std::string segment;
		int lbrace_count = 1;
		while (braceOpen) {
			int token = lexer->yylex();
			if (token == 0) return 0;
			if (token == yy::parser::token::token_kind_type::SB_RBRACE) {
				lbrace_count--;
				if (lbrace_count == 0) {
					braceOpen = false;
					implements.emplace_back(segment);
					std::cout << "segment : " << segment << std::endl;
					openSemi=false;openEnter=false;openRaw=false;
					value->ycText = yylval.ycText;
					return yy::parser::token::token_kind_type::SB_RBRACE;
				}
				segment+=std::string(yylval.ycText);
			} else if (token == yy::parser::token::token_kind_type::SB_LBRACE) {
				lbrace_count++;
				segment+=std::string(yylval.ycText);
			} else {
				segment+=std::string(yylval.ycText);
			}
		}
	}
	int _r = lexer->yylex();
	value->ycText = yylval.ycText;
    return _r;
}


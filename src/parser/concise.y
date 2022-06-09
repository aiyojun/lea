%{
#include "rv.yacc.hh"
extern int yylex(yy::parser::semantic_type* value);
#include "../core.h"
%}

%union {
    char* ycText;
};

%token SEMI COLON COMMA DOT
%token LP RP LSP RSP LBP RBP
%token MUL DIV MOD ADD SUB SADD SSUB
%token XOR ANTI BAND BOR LSHIFT RSHIFT
%token ARROW ASSIGN
%token EQ NE GE LE GT LT AND OR NOT
%token TRUE FALSE
%token ENDING
%token CLASS IMPORT
%token FOR IF ELSE RETURN
%token <ycText> PRIVATE
%token <ycText> STATIC
%token <ycText> DEF
%token <ycText> TYPE
%token <ycText> ID
%token <ycText> STR
%token <ycText> CHAR
%token <ycText> NUM

%left OR
%left AND
%left BOR
%left XOR
%left BAND
%left EQ NE
%left GT GE LT LE
%left LSHIFT RSHIFT
%left ADD SUB
%left MUL DIV MOD
%right CAST
%right NOT SADD SSUB ANTI
%right UMINUS
%left LP LSP DOT

%%

start: 
  multiImport ENDING           {
  importer->GMergeDependency(importer->dependencies.GReset());
  context->print();
  return 0;
}
| multiImport multiLine ENDING {
  importer->GMergeDependency(importer->dependencies.GReset());
  symbolCollector->GPrint("Symbol Loop Up");
  typeHelper->GPrint("Type System");
  rVal->GPrint("Right Value");
  context->print();
  return 0;
}
| multiLine ENDING             {
  symbolCollector->GPrint("Symbol Loop Up");
  typeHelper->GPrint("Type System");
  rVal->GPrint("Right Value");
  context->print();
  return 0;
}
;

multiImport:
  TermImport multiImport
| TermImport
;

TermImport:
  IMPORT {
  importer->dependencies.GOnce();
  importer->oneDepth.GInit();
} package SEMI {
  importer->GMergePackage(importer->oneDepth.GReset());
}
;

package:
  ID DOT package {
  importer->GPush("LEVEL", $1);
  importer->oneDepth.GOnce();
}
| ID {
  importer->GPush("LEVEL", $1);
  importer->oneDepth.GOnce();
}
;

define:
  QualifierDefine
| QualifierDefine COLON multiType
| QualifierDefine ArgsTypeList
| QualifierDefine ArgsTypeList COLON multiType
;

QualifierDefine:
  DEF ID           {
  symbolCollector->GPush("DEF", $1);
  symbolCollector->GPush("ID" , $2);
  symbolCollector->GMerge("SYMBOL");
  symbolCollector->GOnce();
}
| qualifier DEF ID {
  symbolCollector->GPush("DEF", $2);
  symbolCollector->GPush("ID" , $3);
  symbolCollector->GMerge("SYMBOL", 3);
  symbolCollector->GOnce();
}
;

qualifier:
  STATIC         {
  symbolCollector->GPush("PREFIX", "static");
  symbolCollector->GMerge("QUALIFIER", 1);
}
| PRIVATE        {
  symbolCollector->GPush("PREFIX", "private");
  symbolCollector->GMerge("QUALIFIER", 1);
}
| STATIC PRIVATE {
  symbolCollector->GPush("PREFIX", "static");
  symbolCollector->GPush("PREFIX", "private");
  symbolCollector->GMerge("QUALIFIER");
}
;

assign:
  block
| ASSIGN block
| ASSIGN rv SEMI
;

block:
  LBP RBP
| LBP {
  symbolCollector->GInit();
} multiLine RBP {
  symbolCollector->GMerge("GROUP", symbolCollector->GReset());
  symbolCollector->GMerge("SCOPE", 2);
}
;

if:
  IF LP rv RP block
| IF LP rv RP block else
;
else:
  ELSE block
| ELSE if
;

for: FOR LP VarList COLON rv RP block;
VarList: ID COMMA VarList | ID;

return: RETURN rv SEMI;

multiLine:
  TermLine multiLine
| TermLine
;

TermLine:
  define SEMI
| define assign
| if
| for
| return
| ID assign
| rv SEMI
| SEMI
;

multiType:
  TYPE       {typeHelper->GPush("TYPE", $1);}
| lambdaType
;

lambdaType:
  ARROW multiType {
  typeHelper->GMergeReturn();
  typeHelper->GMergeLambda(1);
}
| LP RP ARROW multiType {
  typeHelper->GMergeReturn();
  typeHelper->GMergeLambda(1);
}
| LP {
  typeHelper->GInit();
} TypeList RP {
  typeHelper->GMergeTypeList(typeHelper->GReset());
} ARROW multiType {
  typeHelper->GMergeReturn();
  typeHelper->GMergeLambda(2);
}
;

TypeList:
  multiType COMMA TypeList {typeHelper->GOnce();}
| multiType                {typeHelper->GOnce();}
;

ArgsTypeList: LP RP | LP param RP;
param: paramOne COMMA param | paramOne;
paramOne: ID COLON multiType;

rv:
  rv OR rv                  {rVal->GMerge("OR");}
| rv AND rv                 {rVal->GMerge("AND");}
| rv BOR rv                 {rVal->GMerge("BOR");}
| rv XOR rv                 {rVal->GMerge("XOR");}
| rv BAND rv                {rVal->GMerge("BAND");}
| rv EQ rv                  {rVal->GMerge("EQ");}
| rv NE rv                  {rVal->GMerge("NE");}
| rv GT rv                  {rVal->GMerge("GT");}
| rv GE rv                  {rVal->GMerge("GE");}
| rv LT rv                  {rVal->GMerge("LT");}
| rv LE rv                  {rVal->GMerge("LE");}
| rv LSHIFT rv              {rVal->GMerge("LSHIFT");}
| rv RSHIFT rv              {rVal->GMerge("RSHIFT");}
| rv ADD rv                 {rVal->GMerge("ADD");}
| rv SUB rv                 {rVal->GMerge("SUB");}
| rv MUL rv                 {rVal->GMerge("MUL");}
| rv DIV rv                 {rVal->GMerge("DIV");}
| rv MOD rv                 {rVal->GMerge("MOD");}
| ADD rv %prec UMINUS       {rVal->GMerge("ADD", 1);}
| SUB rv %prec UMINUS       {rVal->GMerge("SUB", 1);}
| NOT rv                    {rVal->GMerge("NOT", 1);}
| SADD rv                   {rVal->GMerge("SADD", 1);}
| SSUB rv                   {rVal->GMerge("SSUB", 1);}
| ANTI rv                   {rVal->GMerge("ANTI", 1);}
| rv LP {rVal->newArgsSpace();} RP          {rVal->GMerge("INVOKE", 1);rVal->releaseArgsSpace();}
| rv LP {rVal->newArgsSpace();} ArgsList RP {rVal->GMerge("INVOKE", 1 + rVal->releaseArgsSpace());}
| rv LSP rv RSP            {rVal->GMerge("ARRAY");}
| rv DOT rv                {rVal->GMerge("DOT");}
| LP TYPE {rVal->GPush("TYPE", $2);} RP rv %prec CAST {rVal->GMerge("CAST");}
| atom
;

ArgsList:
  rv COMMA ArgsList         {rVal->addOneArg();}
| rv                        {rVal->addOneArg();}
;

lambda:
  ARROW lambdaReturn
| LP ArgsTypeList RP ARROW lambdaReturn
;

lambdaReturn:
  rv SEMI
| block
;

atom:
  ID       {rVal->GPush("ID", $1);}
| STR      {rVal->GPush("STR", $1);}
| CHAR     {rVal->GPush("CHAR", $1);}
| NUM      {rVal->GPush("NUM", $1);}
| TRUE     {rVal->GPush("BOOL", "true");}
| FALSE    {rVal->GPush("BOOL", "false");}
| LP rv RP {rVal->GMerge("PAREN", 1);}
| lambda   
;


%%

void yy::parser::error(const std::string& msg)
{
  std::cout << "\033[31;1m[yy] " <<"parse error : " << join(seq, ", ") << "\033[0m\n";
}

yy::parser* leaParser = new yy::parser;
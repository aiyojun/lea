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
  MO->GMergeDependency(MO->dependencies.GReset());
  CT->GPrint();
  return 0;
}
| multiImport multiLine ENDING {
  MO->GMergeDependency(MO->dependencies.GReset());
  SM->GPrint("Symbol Loop Up");
  TP->GPrint("Type System");
  VA->GPrint("Right Value");
  EX->GPrint("Execution");
  CT->GPrint();
  return 0;
}
| multiLine ENDING             {
  SM->GPrint("Symbol Loop Up");
  TP->GPrint("Type System");
  VA->GPrint("Right Value");
  EX->GPrint("Execution");
  CT->GPrint();
  return 0;
}
;

multiImport:
  TermImport multiImport
| TermImport
;

TermImport:
  IMPORT {
  MO->dependencies.GOnce();
  MO->oneDepth.GInit();
} package SEMI {
  MO->GMergePackage(MO->oneDepth.GReset());
}
;

package:
  ID DOT package {
  MO->GPush("LEVEL", $1);
  MO->oneDepth.GOnce();
}
| ID {
  MO->GPush("LEVEL", $1);
  MO->oneDepth.GOnce();
}
;

/* symbol system */

define:
  QualifierDefine {
  SM->argsList.GReset();
}
| QualifierDefine COLON multiType {
  SM->GCheckVariableWithType();
  SM->argsList.GReset();
}
| QualifierDefine ArgsTypeList {
  SM->GCheckMethod(SM->argsList.GGet(), 0);
  SM->argsList.GReset();
}
| QualifierDefine ArgsTypeList COLON multiType {
  SM->GCheckMethod(SM->argsList.GGet(), 1);
  SM->argsList.GReset();
}
;

QualifierDefine:
  DEF ID           {
  SP->GEnter($1, $2);

  SM->argsList.GInit();
  SM->GPush("DEF", $1);
  SM->GPush("ID" , $2);
  SM->GMergeSymbol(2);
  SM->GOnce();
}
| qualifier DEF ID {
  SP->GEnter($2, $3);

  SM->argsList.GInit();
  SM->GPush("DEF", $2);
  SM->GPush("ID" , $3);
  SM->GMergeSymbol(3);
  SM->GOnce();
}
;

qualifier:
  STATIC         {
  SM->GPush("PREFIX", "static");
  SM->GMerge("QUALIFIER", 1);
}
| PRIVATE        {
  SM->GPush("PREFIX", "private");
  SM->GMerge("QUALIFIER", 1);
}
| STATIC PRIVATE {
  SM->GPush("PREFIX", "static");
  SM->GPush("PREFIX", "private");
  SM->GMerge("QUALIFIER");
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
  SM->GInit();
} multiLine RBP {
  SM->GMerge("GROUP", SM->GReset());
  SM->GMerge("SCOPE", 2);
}
;

if:
  TermIf                  
| TermIf else             {EX->GMerge("if-group");}
;
TermIf: IF LP rv RP block {EX->GPush("if", "");};

else:
  ELSE block              {EX->GPush("else", "");}
| ELSE if                 {EX->GReplace("else-if", "");}
;

for: FOR LP VarList COLON rv RP block;
VarList: ID COMMA VarList | ID;

return: RETURN rv SEMI;

/* code context */

multiLine:
  TermLine multiLine
| TermLine
;

TermLine:
  define SEMI   {SP->GExit();/*EX->GPush("define", "");*/}
| define assign {SP->GExit();/*EX->GPush("define:assign", "");*/}
| if
| for
| return
| ID assign
| rv SEMI
| SEMI
;

/* type system */

multiType:
  TYPE       {TP->GPush("TYPE", $1);}
| lambdaType
;

lambdaType:
  ARROW multiType {
  TP->GMergeReturn();
  TP->GMergeLambda(1);
}
| LP RP ARROW multiType {
  TP->GMergeReturn();
  TP->GMergeLambda(1);
}
| LP {
  TP->GInit();
} TypeList RP {
  TP->GMergeTypeList(TP->GReset());
} ARROW multiType {
  TP->GMergeReturn();
  TP->GMergeLambda(2);
}
;

TypeList:
  multiType COMMA TypeList {TP->GOnce();}
| multiType                {TP->GOnce();}
;

ArgsTypeList:
  LP RP
| LP param RP
;

param: 
  paramOne COMMA param 
| paramOne             
;
paramOne: ID COLON multiType {SM->argsList.GOnce();};

/* right value */

rv:
  rv OR rv                  {VA->GMerge("OR");}
| rv AND rv                 {VA->GMerge("AND");}
| rv BOR rv                 {VA->GMerge("BOR");}
| rv XOR rv                 {VA->GMerge("XOR");}
| rv BAND rv                {VA->GMerge("BAND");}
| rv EQ rv                  {VA->GMerge("EQ");}
| rv NE rv                  {VA->GMerge("NE");}
| rv GT rv                  {VA->GMerge("GT");}
| rv GE rv                  {VA->GMerge("GE");}
| rv LT rv                  {VA->GMerge("LT");}
| rv LE rv                  {VA->GMerge("LE");}
| rv LSHIFT rv              {VA->GMerge("LSHIFT");}
| rv RSHIFT rv              {VA->GMerge("RSHIFT");}
| rv ADD rv                 {VA->GMerge("ADD");}
| rv SUB rv                 {VA->GMerge("SUB");}
| rv MUL rv                 {VA->GMerge("MUL");}
| rv DIV rv                 {VA->GMerge("DIV");}
| rv MOD rv                 {VA->GMerge("MOD");}
| ADD rv %prec UMINUS       {VA->GMerge("ADD", 1);}
| SUB rv %prec UMINUS       {VA->GMerge("SUB", 1);}
| NOT rv                    {VA->GMerge("NOT", 1);}
| SADD rv                   {VA->GMerge("SADD", 1);}
| SSUB rv                   {VA->GMerge("SSUB", 1);}
| ANTI rv                   {VA->GMerge("ANTI", 1);}
| rv LP {VA->newArgsSpace();} RP          {VA->GMerge("INVOKE", 1);VA->releaseArgsSpace();}
| rv LP {VA->newArgsSpace();} ArgsList RP {VA->GMerge("INVOKE", 1 + VA->releaseArgsSpace());}
| rv LSP rv RSP            {VA->GMerge("ARRAY");}
| rv DOT rv                {VA->GMerge("DOT");}
| LP TYPE {VA->GPush("TYPE", $2);} RP rv %prec CAST {VA->GMerge("CAST");}
| atom
;

ArgsList:
  rv COMMA ArgsList         {VA->addOneArg();}
| rv                        {VA->addOneArg();}
;

lambda:
  ARROW lambdaReturn
| ArgsTypeList ARROW lambdaReturn
;

lambdaReturn:
  rv SEMI
| block
;

atom:
  ID       {VA->GPush("ID", $1);}
| STR      {VA->GPush("STR", $1);}
| CHAR     {VA->GPush("CHAR", $1);}
| NUM      {VA->GPush("NUM", $1);}
| TRUE     {VA->GPush("BOOL", "true");}
| FALSE    {VA->GPush("BOOL", "false");}
| LP rv RP {VA->GMerge("PAREN", 1);}
| lambda   
;


%%

void yy::parser::error(const std::string& msg)
{
  std::cout << "\033[31;1m[yy] " <<"parse error : " << join(seq, ", ") << "\033[0m\n";
}

yy::parser* leaParser = new yy::parser;
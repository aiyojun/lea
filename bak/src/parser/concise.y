%{
#include "rv.yacc.hh"
extern int yylex(yy::parser::semantic_type* value);
//#include "../core.h"
extern long __LEA_LINE__;
extern long __LEA_CHAR__;
#include "../lea.h"
using namespace lea;
%}

%union {
  char* ycText;
};

%token SEMI COLON COMMA DOT LINE_COMMENT COMMENT_BEGIN COMMENT_END NEWLINE
%token LP RP LSP RSP LBP RBP
%token MUL DIV MOD ADD SUB SADD SSUB
%token XOR ANTI BAND BOR LSHIFT RSHIFT
%token ARROW ASSIGN
%token EQ NE GE LE GT LT AND OR NOT
%token TRUE FALSE
%token ENDING
%token CLASS IMPORT
%token FOR IF ELSE RETURN NEW
%token <ycText> PRIVATE
%token <ycText> STATIC
%token <ycText> DEF
%token <ycText> TYPE
%token <ycText> ID
%token <ycText> STR
%token <ycText> CHAR
%token <ycText> NUM
%token <ycText> FLOAT
%token <ycText> INT

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
  //MO->GMergeDependency(MO->dependencies.GReset());
  //CT->GPrint();
  return 0;
}
| multiImport multiLine ENDING {
  //MO->GMergeDependency(MO->dependencies.GReset());
  //SM->GPrint("Symbol Loop Up");
  TP->GPrint("Type System");
  //VA->GPrint("Right Value");
  //EX->GPrint("Execution");
  //CX->GPrint("Context execution");
  //CT->GPrint();
  //RV->GPrint("Right value");
  LSymbol::printTable();
  return 0;
}
| multiLine ENDING             {
  //SM->GPrint("Symbol Loop Up");
  TP->GPrint("Type System");
  //VA->GPrint("Right Value");
  //EX->GPrint("Execution");
  //CX->GPrint("Context execution");
  //CT->GPrint();
  //RV->GPrint("Right value");
  LSymbol::printTable();
  return 0;
}
;

multiImport:
  TermImport multiImport
| TermImport
;

TermImport:
  IMPORT {
  //MO->dependencies.GOnce();
  //MO->oneDepth.GInit();
} package SEMI {
  //MO->GMergePackage(MO->oneDepth.GReset());
}
;

package:
  ID DOT package {
  //MO->GPush("LEVEL", $1);
  //MO->oneDepth.GOnce();
}
| ID {
  //MO->GPush("LEVEL", $1);
  //MO->oneDepth.GOnce();
}
;

/* symbol system */

define:
  QualifierDefine {
  //SM->argsList.GReset();
}
| QualifierDefine COLON multiType {
  //SM->GCheckVariableWithType();
  //SM->argsList.GReset();
}
| QualifierDefine ArgsTypeList {
  //SM->GCheckMethod(SM->argsList.GGet(), 0);
  //SM->argsList.GReset();
}
| QualifierDefine ArgsTypeList COLON multiType {
  //SM->GCheckMethod(SM->argsList.GGet(), 1);
  //SM->argsList.GReset();
}
;

QualifierDefine:
  DEF ID           {
  SP->GEnter($2);

  //SM->argsList.GInit();
  //SM->GPush("DEF", $1);
  //SM->GPush("ID" , $2);
  //SM->GMergeSymbol(2);
  //SM->GOnce();
}
| qualifier DEF ID {
  SP->GEnter($3);

  //SM->argsList.GInit();
  //SM->GPush("DEF", $2);
  //SM->GPush("ID" , $3);
  //SM->GMergeSymbol(3);
  //SM->GOnce();
}
;

qualifier:
  STATIC         {
  //SM->GPush("PREFIX", "static");
  //SM->GMerge("QUALIFIER", 1);
}
| PRIVATE        {
  //SM->GPush("PREFIX", "private");
  //SM->GMerge("QUALIFIER", 1);
}
| STATIC PRIVATE {
  //SM->GPush("PREFIX", "static");
  //SM->GPush("PREFIX", "private");
  //SM->GMerge("QUALIFIER");
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
  //SM->GInit();
} multiLine RBP {
  //SM->GMerge("GROUP", SM->GReset());
  //SM->GMerge("SCOPE", 2);
}
;

if:
  TermIf                  
| TermIf else             {/*EX->GMerge("if-group");*/}
;
TermIf: IF {} LP rv RP {SP->GEnter("if");} block {SP->GExit();/*EX->GPush("if", "");*/};

else:
  ELSE {
  SP->GEnter("else");
} block {
  SP->GExit();
  //EX->GPush("else", "");
}
| ELSE {
  SP->GEnter("else");
} if {
  SP->GExit();
  //EX->GReplace("else-if", "");
}
;

for: FOR LP VarList COLON rv RP block;
VarList: ID COMMA VarList | ID;

return: 
  RETURN    {
  //CX->GPush(SP->GGet() + "::return:empty");
}
| RETURN rv {
  //CX->GPush(SP->GGet() + "::return:value");
}
;

new:
  NEW ID LP RP
| NEW ID LP ArgsList RP
;

/* code context */

multiLine:
  TermLine multiLine
| TermLine
;

TermLine:
  define SEMI   {
  //CX->GPush(SP->GGet() + "::define");
  SP->GExit();
  /*EX->GPush("define", "");*/
}
| define assign {
  //CX->GPush(SP->GGet() + "::define:assign");
  SP->GExit();
  /*EX->GPush("define:assign", "");*/
}
| if
| for
| new SEMI
| return SEMI
| ID assign {
  //CX->GPush(SP->GGet() + "::assign");
}
| rv SEMI   {
  //CX->GPush(SP->GGet() + "::value");
}
| SEMI
;

/* type system */

multiType:
  TYPE       {
  TP->GPush(LType::build($1));
}
| lambdaType
;

lambdaType:
  ARROW multiType {
  TP->GLambda();
}
| LP RP ARROW multiType {
  TP->GLambda();
}
| LP {
  TP->GInit();
} TypeList RP {
} ARROW multiType {
  TP->GLambda(TP->GReset());
}
;

TypeList:
  multiType COMMA TypeList {
  TP->GOnce();
}
| multiType                {
  TP->GOnce();
}
;

ArgsTypeList:
  LP RP
| LP param RP
;

param: 
  paramOne COMMA param 
| paramOne             
;
paramOne: ID COLON multiType {/*SM->argsList.GOnce();*/};

/* right value */

rv:
  rv OR rv                  {RV->GOr();}
| rv AND rv                 {RV->GAnd();}
| rv BOR rv                 {RV->GBor();}
| rv XOR rv                 {RV->GXor();}
| rv BAND rv                {RV->GBand();}
| rv EQ rv                  {RV->GEq();}
| rv NE rv                  {RV->GNe();}
| rv GT rv                  {RV->GGt();}
| rv GE rv                  {RV->GGe();}
| rv LT rv                  {RV->GLt();}
| rv LE rv                  {RV->GLe();}
| rv LSHIFT rv              {RV->GLshift();}
| rv RSHIFT rv              {RV->GRshift();}
| rv ADD rv                 {RV->GAdd();}
| rv SUB rv                 {RV->GSub();}
| rv MUL rv                 {RV->GMul();}
| rv DIV rv                 {RV->GDiv();}
| rv MOD rv                 {RV->GMod();}
| ADD rv %prec UMINUS       {}
| SUB rv %prec UMINUS       {}
| NOT rv                    {RV->GNot();}
| SADD rv                   {RV->GSadd();}
| SSUB rv                   {RV->GSsub();}
| ANTI rv                   {RV->GAnti();}
| rv LP {RV->newArgsSpace();} RP          {RV->GInvoke();RV->releaseArgsSpace();}
| rv LP {RV->newArgsSpace();} ArgsList RP {RV->GInvoke(RV->releaseArgsSpace());}
| rv LSP rv RSP            {RV->GArray();}
| rv DOT rv                {RV->GAccess();}
| LP TYPE {} RP rv %prec CAST {RV->GCast();}
| atom
;

ArgsList:
  rv COMMA ArgsList         {RV->addOneArg();}
| rv                        {RV->addOneArg();}
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
  ID       {RV->GPush(LValue::buildSymbol(std::string($1), SP->GGet()));}
| STR      {RV->GPush(LValue::build(TString, std::string($1)));}
| CHAR     {RV->GPush(LValue::build(TChar, std::string($1)));}
| INT      {RV->GPush(LValue::build(TInt, std::string($1)));}
| FLOAT    {RV->GPush(LValue::build(TFloat, std::string($1)));}
| TRUE     {RV->GPush(LValue::build(TBool, "true"));}
| FALSE    {RV->GPush(LValue::build(TBool, "false"));}
| LP rv RP {}
| lambda   
;


%%

void yy::parser::error(const std::string& msg)
{
  std::cout << "\033[31;1m[yy] " << __LEA_LINE__ << ":" << __LEA_CHAR__ << "\033[0m\n";
}

yy::parser* leaParser = new yy::parser;
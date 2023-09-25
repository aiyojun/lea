%{
#include "rv.yacc.hh"
extern int yylex(yy::parser::semantic_type* value);
//#include "../core.h"
extern long __LEA_LINE__;
extern long __LEA_CHAR__;
extern std::string iLine;
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
  return 0;
}
| multiImport multiGlobalDefine ENDING {
  TP->GPrint("Type System");
  LType::printTable();
  LSymbol::printTable();
  return 0;
}
| multiGlobalDefine ENDING             {
  //TP->GPrint("Type System");
  LType::printTable();
  LSymbol::printTable();
  return 0;
}
;

multiImport:
  TermImport multiImport
| TermImport
;

TermImport:
  IMPORT {} package SEMI {}
;

package:
  ID DOT package {}
| ID {}
;

/* global define */
multiGlobalDefine: globalDefine multiGlobalDefine | globalDefine;
globalDefine: symbolDefine | newType;


/* symbol system */

define: 
  QualifierDefine {SA->GOver();}
| QualifierDefine COLON multiType {SA->GType(TP->GBack()->getValue());SA->GOver();}
| QualifierDefine ArgsTypeList {TP->GFunction(TP->GReset(), false);SA->GType(TP->GBack()->getValue());SA->GOver();}
| QualifierDefine ArgsTypeList COLON multiType {TP->GFunction(TP->GReset());SA->GType(TP->GBack()->getValue());SA->GOver();}
;

QualifierDefine:
  DEF ID           {SA->GClear();SA->GDef($1, $2);SA->GScope(SP->GGet());SP->GEnter($2);}
| qualifier DEF ID {SA->GDef($2, $3);SA->GScope(SP->GGet());SP->GEnter($3);}
;

qualifier:
  STATIC         {SA->GClear();SA->GQualifier("static");}
| PRIVATE        {SA->GClear();SA->GQualifier("private");}
| STATIC PRIVATE {SA->GClear();SA->GQualifier("public");}
;

assign:
  block
| ASSIGN block {}
| ASSIGN rv SEMI
;

block:
  LBP RBP
| LBP {} multiLine RBP {}
;

if:
  TermIf                  
| TermIf else             {}
;
TermIf: IF {} LP rv RP {} block {};

else:
  ELSE {} block {}
| ELSE {} if {}
;

return: 
  RETURN    {}
| RETURN rv {}
;

/* code context */

newType: enterNewType typeScope {SP->GExit();};

enterNewType: 
  CLASS TYPE {ClassType::build($2);SP->GEnter($2);}
| PRIVATE CLASS TYPE {ClassType::build($3);SP->GEnter($3);}
;

typeScope: 
  LBP RBP
| LBP multiSymbolDefine RBP
;

multiSymbolDefine: 
  symbolDefine multiSymbolDefine
| symbolDefine
;

symbolDefine: 
  define SEMI {SP->GExit();}
| define assign {SP->GExit();}
| SEMI
;

multiLine:
  TermLine multiLine
| TermLine
;

TermLine:
  symbolDefine
| if
| return SEMI
| ID assign {}
| rv SEMI   {}
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
  LP RP {TP->GInit();}
| LP param RP {}
;

param: 
  paramOne COMMA param {TP->GOnce();}
| paramOne             {TP->GInit();TP->GOnce();}
;
paramOne: ID COLON multiType {};

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
| NEW TYPE LP RP
| NEW TYPE LP ArgsList RP
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
| lambda   {std::cout << "\r-- lambda " <<__LEA_LINE__<<":"<< __LEA_CHAR__<<"\n";}
;


%%

void yy::parser::error(const std::string& msg)
{
  //\033[31;1m \033[0m
  std::cout << "" << __LEA_LINE__ << ":" << __LEA_CHAR__ << ": error: \n" << iLine << "\n";
}

yy::parser* leaParser = new yy::parser;
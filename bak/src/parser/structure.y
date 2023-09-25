%{

// Parser header
#include "rv.yacc.hh"
extern int yylex(yy::parser::semantic_type* value);

// Dependencies of stdlib
#include <iostream>
#include <deque>
#include <string>
typedef const std::string& cstring;
#include <vector>

// Json
#include "../json.hpp"

// Declaration of Tree
#include "../core.h"


// All of declarations:
extern std::deque<std::string> seq;

// Implement
void print(const char* s)
{
  std::cout << s;
}
void println(cstring s)
{
  std::cout << s << std::endl;
}
void println(const char* s)
{
  std::cout << s << std::endl;
}

%}

%union {
    char* ycText;
};

%token SEMI
%token COLON
%token COMMA
%token LBP
%token RBP
%token TRUE
%token FALSE
%token LP
%token RP
%token LSP
%token RSP
%token <ycText> TYPE
%token <ycText> ID
%token <ycText> STR
%token <ycText> CHAR
%token <ycText> NUM
%token DOT
%token MUL
%token DIV
%token MOD
%token SADD
%token ADD
%token SSUB
%token SUB
%token XOR
%token ARROW
%token EQ
%token ASSIGN
%token GE
%token LE
%token LSHIFT
%token RSHIFT
%token GT
%token LT
%token AND
%token BAND
%token OR
%token BOR
%token NEQ
%token NOT
%token ANTI

%token ENDING
%token FOR
%token IF
%token ELSE
%token RETURN
%token <ycText> DEF
%token CLASS
%token IMPORT
%token PRIVATE

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

%type <ycText> multiSymbol
%type <ycText> symbol

%%

start:
  memberLoop ENDING {
  int globalNumber = symbolCollector->releaseScope();
  symbolCollector->GMergeGlobalSymbol(globalNumber);
  symbolCollector->GPrint("Symbol");
  typeHelper->GPrint("TypeHelper");
  context->print();
  return 0;
}
| dependencies {
  importer->GMergeDependency(importer->dependencies.GReset());
  importer->GPrint("Importer");
} 
  memberLoop ENDING {
  int globalNumber = symbolCollector->releaseScope();
  symbolCollector->GMergeGlobalSymbol(globalNumber);
  symbolCollector->GPrint("Symbol");
  typeHelper->GPrint("TypeHelper");
  context->print();
  return 0;
}
| ENDING {
  //astTree->print();
  symbolCollector->GPrint("Symbol");
  return 0;
}
;

memberLoop: member memberLoop | member;
member: clazz | symbol;

dependencies: dependency dependencies | dependency;
dependency: 
  IMPORT {
  importer->dependencies.GOnce();
  importer->oneDepth.GInit();

} 
  package SEMI {
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

symbol:
  DEF multiSymbol COLON types SEMI  {
  $$=$2;

  symbolCollector->GPush("DEF", $1);
  symbolCollector->GPush("ID", $2);
  symbolCollector->GMerge("SYMBOL");
  symbolCollector->addOne();
}
| DEF multiSymbol block             {
  $$=$2;

  symbolCollector->GPush("DEF", $1);
  symbolCollector->GPush("ID", $2);
  symbolCollector->GMerge("SYMBOL");
  symbolCollector->addOne();
}
| DEF multiSymbol COLON types block {
  $$=$2;
  symbolCollector->GPush("DEF", $1);
  symbolCollector->GPush("ID", $2);
  symbolCollector->GMerge("SYMBOL");
  symbolCollector->addOne();
}
;

multiSymbol: 
  ID             {$$ = $1;}
| ID parameters  {$$ = $1;}
;

parameters: LP RP | LP param RP;
param: paramOne COMMA param | paramOne;
paramOne: ID COLON types;

clazz: 
  CLASS ID SEMI 
| CLASS ID LBP RBP
| CLASS ID LBP {
  symbolCollector->GEnterClazz($2);
  symbolCollector->addOne();
  symbolCollector->newScope();
} multiDefine RBP {
  int memberNumber = symbolCollector->releaseScope();
  symbolCollector->GExitClazz(memberNumber);
}
;

multiDefine: prefixSymbol multiDefine | prefixSymbol;
prefixSymbol: 
  PRIVATE symbol {
  symbolCollector->GMergeClazzSymbol("private");
}
| symbol         {
  symbolCollector->GMergeClazzSymbol("public");
}
;

types: 
  TYPE       {typeHelper->GPush("TYPE", $1);}
| lambdaType
;

lambdaType:
  ARROW types {
  typeHelper->GMergeReturn();
  typeHelper->GMergeLambda(1);
}
| LP RP ARROW types {
  typeHelper->GMergeReturn();
  typeHelper->GMergeLambda(1);
}
| LP {
  typeHelper->GInit();
} typeList RP {
  typeHelper->GMergeTypeList(typeHelper->GReset());
} ARROW types {
  typeHelper->GMergeReturn();
  typeHelper->GMergeLambda(2);
}
;

typeList:
  types COMMA typeList {typeHelper->GOnce();}
| types                {typeHelper->GOnce();}
;

block: 
  LBP RBP
;

%%

void yy::parser::error(const std::string& msg)
{
  std::string _r;
  int i = 0;
  for (auto& s : seq)
  {
    _r += (i == 0 ? "" : ", ") + s;
    i++;
  }
  std::cout << "\033[31;1m[yy] " <<"parse error : " << _r << "\033[0m\n";
}

yy::parser* leaParser = new yy::parser;
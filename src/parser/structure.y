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
  memberLoop ENDING  {symbolCollector->merge("GLOBAL", symbolCollector->releaseScope());astTree->print();symbolCollector->print();return 0;}
| dependencies   {astTree->merge("IMPORT", importer->resetAll());} 
  memberLoop ENDING  {symbolCollector->merge("GLOBAL", symbolCollector->releaseScope());astTree->print();symbolCollector->print();return 0;}
| ENDING         {astTree->print();symbolCollector->print();return 0;}
;

memberLoop: member memberLoop | member;
member: clazz | symbol;

dependencies: dependency dependencies | dependency;
dependency: 
  IMPORT         {importer->recordOne();importer->initDepth();} 
  package SEMI   {astTree->merge("PACKAGE", importer->resetDepth());astTree->merge("PACKAGE", 1);}
;
package:
  ID DOT package {astTree->pushStack("PKG", $1);importer->addDepth();}
| ID             {astTree->pushStack("PKG", $1);importer->addDepth();}
;

symbol:
  DEF multiSymbol COLON types SEMI  {
  $$=$2;
  println($2);
  symbolCollector->pushStack("DEF", $1);
  symbolCollector->addOne();
  symbolCollector->pushStack("ID", $2);
  symbolCollector->merge("SYMBOL");
}
| DEF multiSymbol block             {
  $$=$2;
  println($2);
  symbolCollector->pushStack("DEF", $1);
  symbolCollector->addOne();
  symbolCollector->pushStack("ID", $2);
  symbolCollector->merge("SYMBOL");
}
| DEF multiSymbol COLON types block {
  $$=$2;
  println($2);
  symbolCollector->pushStack("DEF", $1);
  symbolCollector->addOne();
  symbolCollector->pushStack("ID", $2);
  symbolCollector->merge("SYMBOL");
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
| CLASS ID LBP {symbolCollector->addOne();symbolCollector->newScope();} multiDefine RBP {
  symbolCollector->merge(std::string("CLASS:") + std::string($2), symbolCollector->releaseScope());
}
;


multiDefine: prefixSymbol multiDefine | prefixSymbol;
prefixSymbol: 
  PRIVATE symbol {symbolCollector->merge("PREFIX_SYMBOL:private", 1);}
| symbol         {symbolCollector->merge("PREFIX_SYMBOL:public" , 1);}
;

types: TYPE | lambdaType;

lambdaType:
  ARROW types
| LP RP ARROW types
| LP typeList RP ARROW types
;

typeList: types COMMA typeList | types;

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
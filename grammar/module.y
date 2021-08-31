%{
#include <string>
#include <iostream>
typedef const std::string& cstring;
#include "module.tab.hh"
extern std::string gtoken_1;
extern std::string gtoken_0;
extern std::string gtoken;
extern bool braceOpen;
extern int yylex(yy::parser::semantic_type* value);
void println(const char* msg) {std::cout << "[yy] " << msg << "\n";}
void println(cstring msg) {std::cout << "[yy] " << msg << std::endl;}
%}

%union {
    char* ycText;
}

%token KW_IMPORT
%token KW_VAR
%token KW_VAL
%token KW_DEF
%token KW_CLASS
%token KW_PUB
%token KW_VOID
%token KW_INT
%token KW_LONG
%token KW_DOUBLE
%token KW_CHAR
%token KW_STRING
%token KW_BOOL
%token KW_TRUE
%token KW_FALSE
%token KW_IF
%token KW_ELSE
%token KW_MATCH
%token KW_CASE
%token KW_WHILE
%token KW_FOR
%token KW_CONTINUE
%token KW_BREAK
%token KW_RETURN
%token SB_LBRACE
%token SB_RBRACE
%token SB_LPAREN
%token SB_RPAREN
%token SB_DOT
%token SB_COLON
%token SB_SEMI
%token SB_COMMA
%token SB_ARROW
%token SB_ASSIGN
%token SB_ADD
%token SB_SUB
%token SB_MUL
%token SB_DIV
%token SB_MOD
%token SB_GT
%token SB_LT
%token SB_GE
%token SB_LE
%token SB_NE
%token SB_EQ
%token SB_NOT
%token SB_AND
%token SB_OR
%token SB_ENTER
%token <ycText> VA_CHAR
%token <ycText> VA_STRING
%token <ycText> VA_INT
%token <ycText> VA_DOUBLE
%token <ycText> VA_ID

%start root

%%

root: globalLoop;

globalLoop: globalLoop globalStatement | globalStatement;

globalStatement:
  import {println("import");}
| globalVariableDeclare {println("variable declare");}
| globalFunctionDefine {println("function define");}
| classDefine {println("class define");}
;

import: KW_IMPORT VA_ID;

globalVariableDeclare:
  KW_VAR VA_ID SB_COLON globalVariableBasicType
| KW_VAR VA_ID SB_COLON globalVariableBasicType SB_ASSIGN globalVariableBasicValue
| KW_VAL VA_ID SB_COLON globalVariableBasicType SB_ASSIGN globalVariableBasicValue
;
globalVariableBasicType:
  KW_VOID
| KW_INT
| KW_LONG
| KW_DOUBLE
| KW_CHAR
| KW_STRING
| KW_BOOL
;
globalVariableBasicValue:
  VA_CHAR
| VA_STRING
| VA_INT
| VA_DOUBLE
;

classDefine: KW_CLASS VA_ID SB_LBRACE classMember SB_RBRACE;
classMember:
  classMember classMemberAtom
| classMemberAtom
;
classMemberAtom:
  globalVariableDeclare {println("private member variable declare");}
| globalFunctionDefine {println("private member function define");}
| KW_PUB globalVariableDeclare {println("public variable declare");}
| KW_PUB globalFunctionDefine {println("public function define");}
;

globalFunctionDefine:
  KW_DEF VA_ID globalFunctionDefineBody
| KW_DEF VA_ID SB_LPAREN SB_RPAREN globalFunctionDefineBody
| KW_DEF VA_ID SB_LPAREN globalFunctionDefineArgsList SB_RPAREN globalFunctionDefineBody
| KW_DEF VA_ID SB_COLON globalVariableBasicType globalFunctionDefineBody
| KW_DEF VA_ID SB_LPAREN SB_RPAREN SB_COLON globalVariableBasicType globalFunctionDefineBody
| KW_DEF VA_ID SB_LPAREN globalFunctionDefineArgsList SB_RPAREN SB_COLON globalVariableBasicType globalFunctionDefineBody
;

globalFunctionDefineArgsList:
  globalFunctionDefineArgsList SB_COMMA VA_ID SB_COLON globalFunctionDefineArgsType
| VA_ID SB_COLON globalFunctionDefineArgsType
;

globalFunctionDefineArgsType:
  globalVariableBasicType
| SB_ARROW globalVariableBasicType
| SB_LPAREN SB_RPAREN SB_ARROW globalVariableBasicType
| SB_LPAREN typeList SB_RPAREN SB_ARROW globalVariableBasicType
;

typeList:
  typeList SB_COMMA globalVariableBasicType
| globalVariableBasicType
;

globalFunctionDefineBody:
  SB_ARROW globalVariableBasicValue
| lbrace SB_RBRACE
| lbrace functionBody SB_RBRACE
;

lbrace: SB_LBRACE {braceOpen=true;}
;

functionBody:
  functionBody functionBodyAtom
| functionBodyAtom
;

functionBodyAtom:
  rightValue
| stateIf
| stateReturn
;

stateIf:
  stateIfWithElif
| stateIfWithElif KW_ELSE SB_LBRACE functionBodyAtom SB_RBRACE
;

stateIfWithElif:
  stateIfWithElif KW_ELSE stateIfAtom
| stateIfAtom
;

stateIfAtom:
  KW_IF SB_LPAREN rightValue SB_RPAREN SB_LBRACE functionBodyAtom SB_RBRACE
;

stateReturn: 
  KW_RETURN
| KW_RETURN rightValue
;


//---------------------------------------------------------------
// right value
//---------------------------------------------------------------
rightValue: booOrValue;

booOrValue:
  booOrValue SB_OR booAndValue
| booAndValue
;

booAndValue:
  booAndValue SB_AND compareValue
| compareValue
;

compareValue:
  calculateValue
| calculateValue SB_GT calculateValue
| calculateValue SB_LT calculateValue
| calculateValue SB_GE calculateValue
| calculateValue SB_LE calculateValue
| calculateValue SB_NE calculateValue
| calculateValue SB_EQ calculateValue
;

calculateValue:
  calculateProValue
| calculateValue SB_ADD calculateProValue
| calculateValue SB_SUB calculateProValue
;

calculateProValue:
  atomValue
| calculateProValue SB_MUL atomValue
| calculateProValue SB_DIV atomValue
| calculateProValue SB_MOD atomValue
;

atomValue:
  SB_LPAREN booOrValue SB_RPAREN
| SB_NOT booOrValue
| SB_SUB VA_INT
| SB_SUB VA_DOUBLE
| VA_INT
| VA_DOUBLE
| VA_CHAR
| VA_STRING
| KW_TRUE
| KW_FALSE
| chainAccess
;

invokingArgsList:
  invokingArgsList SB_COMMA booOrValue
| booOrValue
;

chainAccess:
  chainAccess SB_DOT accessTarget
| accessTarget
;

accessTarget:
  VA_ID
| VA_ID SB_LPAREN SB_RPAREN
| VA_ID SB_LPAREN invokingArgsList SB_RPAREN
;


%%

void yy::parser::error(const std::string& msg) {
    if (gtoken_0 == "\n") gtoken_0 = "\\n";
    std::cout << "[yy] ('" << gtoken_1 << "', '" << gtoken_0 << "', '" << gtoken << "') parse error : " << msg << std::endl;
}

yy::parser::semantic_type yylval;
yy::parser* moduleParser = new yy::parser;

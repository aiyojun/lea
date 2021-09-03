%{
#include <string>
typedef const std::string& cstring;
#include <vector>
#include <map>
#include <iostream>
#include "basic_ds.h"
#include "AST.h"
#include "syntax.tab.hh"
#include "type.h"

lea_var leaVar;
lea_fun leaFun;
lea_cls leaCls;
lea_ctx leaCtx;

std::map<std::string, lea_cls> *ptr_class_type;

extern std::string gtoken_1;
extern std::string gtoken_0;
extern std::string gtoken;
extern bool braceOpen;
extern int yylex(yy::parser::semantic_type* value);

void println(const char* msg) {std::cout << "[yy] " << msg << "\n";}
void println(cstring msg) {std::cout << "[yy] " << msg << std::endl;}
void println(lea_var _lv) {
  std::cout << _lv.lea_var_type << " " << _lv.name << ": " << _lv.type << (_lv.assigned ? " (assigned)" : "") << std::endl;
}
void println(lea_fun _lf) {
  std::cout << (_lf.scene.empty()?"":_lf.scene+" ") 
            << "def " << _lf.name << "(" << join(",", _lf.args_type) << "): "
            << _lf.return_type << (_lf.implemented ? " (implement)" : "") << std::endl;
}
void println(lea_cls _lc) {
  std::cout<<"class "<<_lc.name<<"\n";
  for (auto& _lv: _lc.memberVariables) {
    std::cout<<"  "<<(_lv.prefix==""?"":_lv.prefix+" ")<<_lv.lea_var_type << " " << _lv.name << ": " << _lv.type << (_lv.assigned ? " (assigned)" : "") << std::endl;
  }
  for (auto& _lf: _lc.memberFunctions) {
    std::cout<<"  "<<(_lf.prefix==""?"":_lf.prefix+" ")<<"def " << _lf.name << "(" << join(",", _lf.args_type) << "): " << _lf.return_type << (_lf.implemented ? " (implement)" : "") << std::endl;
  }
}
void println(lea_ctx _ctx) {
  std::cout << "\033[32;1mCONTEXT:\033[0m" << std::endl;
  std::cout << "import " << join(",", _ctx.globalImports) << std::endl;
  std::cout << "-----------------------------" << std::endl;
  std::cout << "\033[32;1mGlobal variables:\033[0m" << std::endl;
  std::cout << "-----------------------------" << std::endl;
  for (auto& _lv : _ctx.globalVariables) {
    println(_lv);
  }
  std::cout << "-----------------------------" << std::endl;
  std::cout << "\033[32;1mGlobal functions:\033[0m" << std::endl;
  std::cout << "-----------------------------" << std::endl;
  for (auto& _lf : _ctx.globalFunctions) {
    println(_lf);
  }
  std::cout << "-----------------------------" << std::endl;
  std::cout << "\033[32;1mGlobal class:\033[0m" << std::endl;
  std::cout << "-----------------------------" << std::endl;
  for (auto& _cls : _ctx.globalClasses) {
    println(_cls);
  }
  std::cout << "-----------------------------" << std::endl;
}

std::vector<std::string> scopeStack;
std::string pre_op;
std::string tempString;
std::vector<std::string> tempVectorString;

void debug_println() {
  println(leaCtx);
}
%}

%union {
    char* ycText;
}
%token <ycText> GAP
%token <ycText> NEWLINE
%token <ycText> KW_IMPORT
%token <ycText> KW_VAR
%token <ycText> KW_VAL
%token <ycText> KW_DEF
%token <ycText> KW_CLASS
%token <ycText> KW_PUB
%token <ycText> KW_VOID
%token <ycText> KW_INT
%token <ycText> KW_LONG
%token <ycText> KW_DOUBLE
%token <ycText> KW_CHAR
%token <ycText> KW_STRING
%token <ycText> KW_BOOL
%token <ycText> KW_TRUE
%token <ycText> KW_FALSE
%token <ycText> KW_IF
%token <ycText> KW_ELSE
%token <ycText> KW_MATCH
%token <ycText> KW_CASE
%token <ycText> KW_WHILE
%token <ycText> KW_FOR
%token <ycText> KW_CONTINUE
%token <ycText> KW_BREAK
%token <ycText> KW_RETURN
%token <ycText> SB_LBRACE
%token <ycText> SB_RBRACE
%token <ycText> SB_LPAREN
%token <ycText> SB_RPAREN
%token <ycText> SB_LSQBRACE
%token <ycText> SB_RSQBRACE
%token <ycText> SB_DOT
%token <ycText> SB_COLON
%token <ycText> SB_SEMI
%token <ycText> SB_COMMA
%token <ycText> SB_ARROW
%token <ycText> SB_ASSIGN
%token <ycText> SB_ADD
%token <ycText> SB_SUB
%token <ycText> SB_MUL
%token <ycText> SB_DIV
%token <ycText> SB_MOD
%token <ycText> SB_GT
%token <ycText> SB_LT
%token <ycText> SB_GE
%token <ycText> SB_LE
%token <ycText> SB_NE
%token <ycText> SB_EQ
%token <ycText> SB_NOT
%token <ycText> SB_AND
%token <ycText> SB_OR
%token <ycText> SB_ENTER
%token <ycText> VA_CHAR
%token <ycText> VA_STRING
%token <ycText> VA_INT
%token <ycText> VA_DOUBLE
%token <ycText> VA_ID

%left KW_RETURN
//%nonassoc KW_TRUE KW_FALSE
%left SB_OR
%left SB_AND
%left SB_LT SB_LE SB_GT SB_GE SB_EQ SB_NE
%left SB_SUB SB_ADD
%left SB_MUL SB_DIV SB_MOD
%left SB_NOT
//%nonassoc VA_ID VA_INT VA_DOUBLE VA_CHAR VA_STRING

%type <ycText> globalVariableBasicType
%type <ycText> globalVariableName
%type <ycText> atomValue

%start root

%%

root: globalLoop {};

globalLoop: globalLoop globalStatement | globalStatement;

globalStatement:
  import
| globalVariableDeclare {leaCtx.globalVariables.emplace_back(leaVar);leaVar.clear();}
| globalFunctionDefine  {leaCtx.globalFunctions.emplace_back(leaFun);leaFun.clear();}
| classDefine {leaCtx.globalClasses.emplace_back(leaCls);leaCls.clear();leaVar.clear();leaFun.clear();}
;

import: KW_IMPORT VA_ID {leaCtx.globalImports.emplace_back($2);};

globalVariableDeclare:
  KW_VAR globalVariableName SB_COLON globalVariableBasicType {leaVar.type=tempString;leaVar.lea_var_type = "var"; leaVar.assigned = false;}
| KW_VAR globalVariableName SB_COLON globalVariableBasicType SB_ASSIGN rightValue {leaVar.type=tempString;leaVar.lea_var_type = "val"; leaVar.assigned = true;}
| KW_VAL globalVariableName SB_COLON globalVariableBasicType SB_ASSIGN rightValue {leaVar.type=tempString;leaVar.lea_var_type = "val"; leaVar.assigned = true;}
;
globalVariableName: VA_ID {$$=$1;leaVar.name=std::string($1);leaVar.scope=join(".",scopeStack);}
;
globalVariableBasicType:
  KW_VOID   {$$=$1;tempString=std::string($1);}
| KW_INT    {$$=$1;tempString=std::string($1);}
| KW_LONG   {$$=$1;tempString=std::string($1);}
| KW_DOUBLE {$$=$1;tempString=std::string($1);}
| KW_CHAR   {$$=$1;tempString=std::string($1);}
| KW_STRING {$$=$1;tempString=std::string($1);}
| KW_BOOL   {$$=$1;tempString=std::string($1);}
| VA_ID     {$$=$1;tempString=std::string($1);}
;
globalVariableBasicValue:
  VA_CHAR
| VA_STRING
| VA_INT
| VA_DOUBLE
;

classDefine: KW_CLASS className SB_LBRACE classMember SB_RBRACE {scopeStack.pop_back();}
;
className: VA_ID {leaCls.name=std::string($1);scopeStack.emplace_back(leaCls.name);}
;
classMember:
  classMember classMemberAtom
| classMemberAtom
;
classMemberAtom:
  globalVariableDeclare {leaVar.scope=join(".",scopeStack);leaVar.prefix="private";leaCls.memberVariables.emplace_back(leaVar);}
| globalFunctionDefine  {leaFun.scope=join(".",scopeStack);leaFun.prefix="private";leaCls.memberFunctions.emplace_back(leaFun);}
| KW_PUB globalVariableDeclare {leaVar.scope=join(".",scopeStack);leaVar.prefix="public";leaCls.memberVariables.emplace_back(leaVar);}
| KW_PUB globalFunctionDefine  {leaFun.scope=join(".",scopeStack);leaFun.prefix="public";leaCls.memberFunctions.emplace_back(leaFun);}
;

globalFunctionDefine:
  KW_DEF globalFunctionName globalFunctionDefineBody {leaFun.return_type="void";leaFun.implemented=true;}
| KW_DEF globalFunctionName SB_LPAREN SB_RPAREN globalFunctionDefineBody {leaFun.return_type="void";leaFun.implemented=true;}
| KW_DEF globalFunctionName SB_LPAREN globalFunctionDefineArgsList SB_RPAREN globalFunctionDefineBody {leaFun.return_type="void";leaFun.implemented=true;}
| KW_DEF globalFunctionName SB_COLON globalFunctionReturnType globalFunctionDefineBody {leaFun.implemented=true;}
| KW_DEF globalFunctionName SB_LPAREN SB_RPAREN SB_COLON globalFunctionReturnType globalFunctionDefineBody {leaFun.implemented=true;}
| KW_DEF globalFunctionName SB_LPAREN globalFunctionDefineArgsList SB_RPAREN SB_COLON globalFunctionReturnType globalFunctionDefineBody {leaFun.implemented=true;}
;

globalFunctionName: VA_ID {leaFun.name = std::string($1);leaFun.scope=join(".",scopeStack);}
;
globalFunctionReturnType: globalVariableBasicType {leaFun.return_type = std::string($1);}
;

globalFunctionDefineArgsList:
  globalFunctionDefineArgsList SB_COMMA VA_ID SB_COLON globalFunctionDefineArgsType {}
| VA_ID SB_COLON globalFunctionDefineArgsType
;

globalFunctionDefineArgsType:
  globalVariableBasicType {leaFun.args_type.emplace_back(std::string($1));}
//| SB_ARROW globalVariableBasicType {leaFun.args_type.emplace_back("()->" + std::string($2));}
//| SB_LPAREN SB_RPAREN SB_ARROW globalVariableBasicType {leaFun.args_type.emplace_back("()->" + std::string($4));}
//| SB_LPAREN typeList SB_RPAREN SB_ARROW globalVariableBasicType {leaFun.args_type.emplace_back("("+join(",", tempVectorString) + ")->" + std::string($5));tempVectorString.clear();}
;

//typeList:
//  typeList SB_COMMA globalVariableBasicType {tempVectorString.emplace_back(std::string($3));}
//| globalVariableBasicType {tempVectorString.emplace_back(std::string($1));}
//;

globalFunctionDefineBody:
  SB_ARROW globalVariableBasicValue
| lbrace SB_RBRACE {scopeStack.pop_back();}
| lbrace functionBody SB_RBRACE {scopeStack.pop_back();}
;

lbrace: SB_LBRACE {braceOpen=true;scopeStack.emplace_back(leaFun.name);}
;

functionBody:
  functionBody functionBodyAtom
| functionBodyAtom
;

functionBodyAtom:
  rightValue
| globalVariableDeclare
| stateIf
| stateReturn
;

stateIf:
  stateIfWithElif
| stateIfWithElif KW_ELSE stateElseLbrace SB_RBRACE {scopeStack.pop_back();}
| stateIfWithElif KW_ELSE stateElseLbrace functionBody SB_RBRACE {scopeStack.pop_back();}
;

stateElseLbrace: SB_LBRACE {scopeStack.emplace_back("else");}
;

stateIfWithElif:
  stateIfWithElif KW_ELSE stateIfAtom
| stateIfAtom
;

stateIfAtom:
  KW_IF SB_LPAREN rightValue SB_RPAREN stateIfLbrace SB_RBRACE {scopeStack.pop_back();}
| KW_IF SB_LPAREN rightValue SB_RPAREN stateIfLbrace functionBody SB_RBRACE {scopeStack.pop_back();}
;

stateIfLbrace: SB_LBRACE {scopeStack.emplace_back("if");}
;

stateReturn: 
  KW_RETURN
| KW_RETURN rightValue
;


//---------------------------------------------------------------
// right value
//---------------------------------------------------------------
rightValue: booOrValue {println("\033[31;1mLEA right value\033[0m");AST::self.print();AST::self.clear();}
;

booOrValue:
  booOrValue SB_OR booAndValue    {AST::self.link_node("||");}
| booAndValue
;

booAndValue:
  booAndValue SB_AND compareValue {AST::self.link_node("&&");}
| compareValue
;

compareValue:
  calculateValue
| calculateValue SB_GT calculateValue {AST::self.link_node(">");}
| calculateValue SB_LT calculateValue {AST::self.link_node("<");}
| calculateValue SB_GE calculateValue {AST::self.link_node(">=");}
| calculateValue SB_LE calculateValue {AST::self.link_node("<=");}
| calculateValue SB_NE calculateValue {AST::self.link_node("!=");}
| calculateValue SB_EQ calculateValue {AST::self.link_node("==");}
;

calculateValue:
  calculateProValue
| calculateValue SB_ADD calculateProValue {AST::self.link_node("+");}
| calculateValue SB_SUB calculateProValue {AST::self.link_node("-");}
;

calculateProValue:
  oneOpValue
| calculateProValue SB_MUL oneOpValue {AST::self.link_node("*");}
| calculateProValue SB_DIV oneOpValue {AST::self.link_node("/");}
| calculateProValue SB_MOD oneOpValue {AST::self.link_node("%");}
;

oneOpValue:
  topOpValue
| SB_NOT topOpValue {AST::self.link_node("!");}
| SB_SUB topOpValue {AST::self.link_node("-_");}
| SB_ADD topOpValue {AST::self.link_node("+_");}
;

topOpValue:
  atomValue
| chainAccessValue
;

chainAccessValue:
  chainAccessValue SB_DOT xxArrValue  {AST::self.link_node(".");}
| arrValue SB_DOT xxArrValue          {AST::self.link_node(".");}
| arrValue
;

arrValue:
  xValue
| xValue SB_LSQBRACE booOrValue SB_RSQBRACE   {AST::self.link_node("[]");}
| arrValue SB_LSQBRACE booOrValue SB_RSQBRACE {AST::self.link_node("[]");}
;

xxArrValue:
  xxValue
| xxValue SB_LSQBRACE booOrValue SB_RSQBRACE    {AST::self.link_node("[]");}
| xxArrValue SB_LSQBRACE booOrValue SB_RSQBRACE {AST::self.link_node("[]");}
;

xValue:
  SB_LPAREN booOrValue SB_RPAREN
| xxValue
;

xxValue:
  accessName {auto ptr=AST::self.create_node(tempString);ptr->type=4;}
| accessName accessLparen SB_RPAREN {AST::self.exit_inode();}
| accessName accessLparen invokingArgsList SB_RPAREN {AST::self.link_inode();AST::self.exit_inode();}
;

accessName: VA_ID {tempString=std::string($1);}
;

accessLparen: SB_LPAREN {auto ptr=AST::self.create_node(tempString);ptr->type=3;AST::self.enter_inode();}
;

atomValue:
  VA_INT            {$$=$1;auto ptr=AST::self.create_node($1);ptr->type=2;ptr->sign_type="int";}
| VA_DOUBLE         {$$=$1;auto ptr=AST::self.create_node($1);ptr->type=2;ptr->sign_type="double";}
| VA_CHAR           {$$=$1;auto ptr=AST::self.create_node($1);ptr->type=2;ptr->sign_type="char";}
| VA_STRING         {$$=$1;auto ptr=AST::self.create_node($1);ptr->type=2;ptr->sign_type="string";}
| KW_TRUE           {$$=$1;auto ptr=AST::self.create_node($1);ptr->type=2;ptr->sign_type="bool";}
| KW_FALSE          {$$=$1;auto ptr=AST::self.create_node($1);ptr->type=2;ptr->sign_type="bool";}
;

invokingArgsList:
  invokingArgsList SB_COMMA booOrValue
| booOrValue
;

%%

void yy::parser::error(const std::string& msg) {
    if (gtoken_0 == "\n") gtoken_0 = "\\n";
    std::cout << "\033[31;1m[yy] ('" << gtoken_1 << "', '" << gtoken_0 << "', '" << gtoken << "') parse error : " << msg << "\033[0m\n";
}

yy::parser::semantic_type yylval;
yy::parser* moduleParser = new yy::parser;

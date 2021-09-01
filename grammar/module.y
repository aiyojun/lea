%{
#include <string>
typedef const std::string& cstring;
#include <vector>
#include <map>
#include <iostream>
typedef const std::string& cstring;
std::string join(cstring c, const std::vector<std::string>& v)
{std::string _r;for(int i=0;i<v.size();i++){_r+=v[i];if(i!=v.size()-1)_r+=c;}return _r;}
class lea_var {public: std::string prefix; std::string name; std::string type; std::string lea_var_type; bool assigned = false; void clear() {prefix="";name="";type="";lea_var_type="";assigned=false;}};
lea_var leaVar;
class lea_fun {public: std::string prefix; std::string name; std::string return_type; std::vector<std::string> args_type; bool implemented = false; std::string scene;void clear(){prefix="";name="";return_type="";args_type.clear(); implemented=false;scene="";}};
lea_fun leaFun;
class lea_cls {
public:
std::string name;
std::vector<lea_var> memberVariables;
std::vector<lea_fun> memberFunctions;
void clear() {name="";memberVariables.clear();memberFunctions.clear();}
};
lea_cls leaCls;
class lea_ctx {
public:
std::vector<std::string> globalImports;
std::vector<lea_var> globalVariables;
std::vector<lea_fun> globalFunctions;
std::vector<lea_cls> globalClasses;
};
lea_ctx leaCtx;
#include "module.tab.hh"
extern std::string gtoken_1;
extern std::string gtoken_0;
extern std::string gtoken;
extern bool braceOpen;
extern int yylex(yy::parser::semantic_type* value);
void println(const char* msg) {std::cout << "[yy] " << msg << "\n";}
void println(cstring msg) {std::cout << "[yy] " << msg << std::endl;}
void println(lea_var _lv) {std::cout << _lv.lea_var_type << " " << _lv.name << ": " << _lv.type << (_lv.assigned ? " (assigned)" : "") << std::endl;}
void println(lea_fun _lf) {std::cout <<(_lf.scene.empty()?"":_lf.scene+" ")<<"def " << _lf.name << "(" << join(",", _lf.args_type) << "): " << _lf.return_type << (_lf.implemented ? " (implement)" : "") << std::endl;}
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
std::string tempString;
std::vector<std::string> tempVectorString;
void debug_println() {
  println(leaCtx);
}
%}

%union {
    char* ycText;
}

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

%type <ycText> globalVariableBasicType
%type <ycText> globalVariableName

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
| KW_VAR globalVariableName SB_COLON globalVariableBasicType SB_ASSIGN globalVariableBasicValue {leaVar.type=tempString;leaVar.lea_var_type = "val"; leaVar.assigned = true;}
| KW_VAL globalVariableName SB_COLON globalVariableBasicType SB_ASSIGN globalVariableBasicValue {leaVar.type=tempString;leaVar.lea_var_type = "val"; leaVar.assigned = true;}
;
globalVariableName: VA_ID {$$=$1;leaVar.name=std::string($1);}
;
globalVariableBasicType:
  KW_VOID   {$$=$1;tempString=std::string($1);}
| KW_INT    {$$=$1;tempString=std::string($1);}
| KW_LONG   {$$=$1;tempString=std::string($1);}
| KW_DOUBLE {$$=$1;tempString=std::string($1);}
| KW_CHAR   {$$=$1;tempString=std::string($1);}
| KW_STRING {$$=$1;tempString=std::string($1);}
| KW_BOOL   {$$=$1;tempString=std::string($1);}
;
globalVariableBasicValue:
  VA_CHAR
| VA_STRING
| VA_INT
| VA_DOUBLE
;

classDefine: KW_CLASS className SB_LBRACE classMember SB_RBRACE {}
;
className: VA_ID {leaCls.name=std::string($1);}
;
classMember:
  classMember classMemberAtom
| classMemberAtom
;
classMemberAtom:
  globalVariableDeclare {leaVar.prefix="private";leaCls.memberVariables.emplace_back(leaVar);}
| globalFunctionDefine  {leaFun.prefix="private";leaCls.memberFunctions.emplace_back(leaFun);}
| KW_PUB globalVariableDeclare {leaVar.prefix="public";leaCls.memberVariables.emplace_back(leaVar);}
| KW_PUB globalFunctionDefine  {leaFun.prefix="public";leaCls.memberFunctions.emplace_back(leaFun);}
;

globalFunctionDefine:
  KW_DEF globalFunctionName globalFunctionDefineBody {leaFun.return_type="void";leaFun.implemented=true;}
| KW_DEF globalFunctionName SB_LPAREN SB_RPAREN globalFunctionDefineBody {leaFun.return_type="void";leaFun.implemented=true;}
| KW_DEF globalFunctionName SB_LPAREN globalFunctionDefineArgsList SB_RPAREN globalFunctionDefineBody {leaFun.return_type="void";leaFun.implemented=true;}
| KW_DEF globalFunctionName SB_COLON globalFunctionReturnType globalFunctionDefineBody {leaFun.implemented=true;}
| KW_DEF globalFunctionName SB_LPAREN SB_RPAREN SB_COLON globalFunctionReturnType globalFunctionDefineBody {leaFun.implemented=true;}
| KW_DEF globalFunctionName SB_LPAREN globalFunctionDefineArgsList SB_RPAREN SB_COLON globalFunctionReturnType globalFunctionDefineBody {leaFun.implemented=true;}
;

globalFunctionName: VA_ID {leaFun.name = std::string($1);}
;
globalFunctionReturnType: globalVariableBasicType {leaFun.return_type = std::string($1);}
;

globalFunctionDefineArgsList:
  globalFunctionDefineArgsList SB_COMMA VA_ID SB_COLON globalFunctionDefineArgsType {}
| VA_ID SB_COLON globalFunctionDefineArgsType
;

globalFunctionDefineArgsType:
  globalVariableBasicType {leaFun.args_type.emplace_back(std::string($1));}
| SB_ARROW globalVariableBasicType {leaFun.args_type.emplace_back("()->" + std::string($2));}
| SB_LPAREN SB_RPAREN SB_ARROW globalVariableBasicType {leaFun.args_type.emplace_back("()->" + std::string($4));}
| SB_LPAREN typeList SB_RPAREN SB_ARROW globalVariableBasicType {leaFun.args_type.emplace_back("("+join(",", tempVectorString) + ")->" + std::string($5));tempVectorString.clear();}
;

typeList:
  typeList SB_COMMA globalVariableBasicType {tempVectorString.emplace_back(std::string($3));}
| globalVariableBasicType {tempVectorString.emplace_back(std::string($1));}
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

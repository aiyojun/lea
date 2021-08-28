#include "scope.h"

#include <vector>
#include <string>
#include "basic_ds.h"
#include "value.h"

std::vector<std::string> scopeStack{"global"};
/** Prepared for yacc */
void enter_scope() {scopeStack.emplace_back(function.name);}
void enter_scope_of(char* name) {scopeStack.emplace_back(std::string(name));}
void exit_scope() {scopeStack.pop_back();}
/** Prepared for C++ */
std::string getScope() {return join(".", scopeStack);}
std::string getScopeBack() {return scopeStack.back();}



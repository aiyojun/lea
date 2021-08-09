//
// Created by Mr.Jun on 2021/8/7.
//
#include "grammar.h"
#include <stdio.h>
#include <vector>

#include "SymbolTable.h"

SymbolTable symbolTable;

using namespace std;

void declare(const char* _identifier) {
    printf("[%-6s]\n", _identifier);
}

void declare(const char* _identifier, const char* context) {
    printf("[%-6s] %s\n", _identifier, context);
}

char _stack[512];

void _push(char *s) {
    sprintf(_stack, "%s", s);
}

void _pull(char *s) {
    sprintf(s, "%s", _stack);
}

unsigned int _openMultiComment = 0;

void _open_mc() {
    _openMultiComment = 1;
}

void _close_mc() {
    _openMultiComment = 0;
}

void _if() {
    declare("if");
}

void _elif() {
    declare("elif");
}

void _else() {
    declare("else");
}

void _def(char* fun_name) {
//    char var[512]; _pull(var);
//    printf("_def : %s\n", fun_name);
    declare("def", fun_name);
    symbolTable.addFunc(fun_name, FunctionAction::Def);
}

void _block() {
    declare("block{");
}

void _block_() {
    declare("block}");
}

vector<int> call_args;

void _add_arg() {
    call_args.emplace_back(1);
}

void _call(int args) {
    if (_openMultiComment) return;
    char buf[8];
    sprintf(buf, "call-%zu", call_args.size());
    call_args.clear();
    char var[512]; _pull(var);
    declare(buf, var);
    symbolTable.addFunc(var, FunctionAction::Call);
}

void _var_def(char* var_name) {
    char var[512]; _pull(var);
    declare("var:", var);
    symbolTable.addSymbol(var, SymbolType::Variable);
}

void _var_ass(char* var_name) {
    char var[512]; _pull(var);
    declare("var=", var);
    symbolTable.addSymbol(var, SymbolType::Variable);
}

void _var_def_ass(char* var_name) {
    char var[512]; _pull(var);
    declare("var:=", var);
    symbolTable.addSymbol(var, SymbolType::Variable);
}

void _for() {
    declare("for");
}

void _match() {
    declare("match");
}

void _case() {
    declare("case");
}

void printf_empty(const char *__restrict __format, ...) {}

void clean() {

}

void complete() {
    symbolTable.show();
}
//
// Created by Mr.Jun on 2021/8/7.
//
#include "lang/grammar.h"
#include <stdio.h>
#include <string.h>
#include <vector>
#include <mutex>

#include "lang/SymbolTable.h"
#include "gen/CodeAction.h"

SymbolTable symbolTable;
long lea_line = 0;
std::mutex line_mutex;
std::vector<std::string> _scopes;
char output_file[100];

using namespace std;

std::string getScope() {
    if (_scopes.empty()) return std::string("global");
    return _scopes.back();
}

void declare(const char* _identifier) {
    printf("[%-6s]\n", _identifier);
}

void declare(const char* _identifier, const char* context) {
    printf("[%-6s] %s\n", _identifier, context);
}

char _lea_file[512];

void _lea(char *name) {
    strcpy(name, name);
    _scopes.clear();
    CodeAction::codeAction.output = std::string(output_file);
}

void _line_inc() {
    line_mutex.lock();
    lea_line++;
    line_mutex.unlock();
}

char _stack[128];

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

void _scope_ano(long line) {
    _scopes.emplace_back(std::string("anonymous::" + std::to_string(line)));
}

void _scope_begin(char *scope) {
    _scopes.emplace_back(std::string(scope));
}

void _scope_end(char *scope) {
    std::cout << "scopes : ";
    for (const auto& s : _scopes) {
        std::cout << s << " ";
    }
    std::cout << std::endl;
    std::string back = _scopes.back();
    if (scope != nullptr && strcmp(back.c_str(), scope) != 0) {
        std::cerr << "[scope] try to close (" << std::string(scope) << "), expect (" << back << ")." << endl;
        exit(1);
    }
    _scopes.pop_back();
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

std::string funcNameNow;

void _def(char* fun_name) {
//    char var[512]; _pull(var);
//    printf("_def : %s\n", fun_name);
    declare("def", fun_name);
    symbolTable.addFunc(lea_line, getScope(), fun_name, FunctionAction::Def);
    funcNameNow = std::string(fun_name);
    if (funcNameNow == "main") {
        CodeAction::codeAction.M_Def();
    }
}

void _def_() {
    if (funcNameNow == "main") {
        CodeAction::codeAction.M_Ret(0);
    }
    funcNameNow = "";
}

void _block() {
    declare("block{");

}

void _block_() {
    declare("block}");

}

vector<int> call_args;
vector<string> call_args_str;

void _add_arg() {
    call_args.emplace_back(1);
}
void _add_arg_str(char* s) {
    call_args_str.emplace_back(string(s));
}
void _call(int args) {
    if (_openMultiComment) return;
    char buf[8];
    sprintf(buf, "call-%zu", call_args.size());
    char var[512]; _pull(var);
    declare(buf, var);
    symbolTable.addFunc(lea_line, getScope(), var, FunctionAction::Call);


    CodeAction::codeAction.D_Def("msg", call_args_str.back());
    std::string func(var);
    if (func == "printf") {
        std::vector<std::string> argv{"msg"};
        CodeAction::codeAction.F_Call(argv, func);
    }

    CodeAction::codeAction.M_Ret(0);

    call_args.clear();
    call_args_str.clear();
}

void _var_def(char* var_name) {
    char var[512]; _pull(var);
    declare("var:", var);
    symbolTable.addVar(lea_line, getScope(), var, "");
}

void _var_ass(char* var_name) {
    char var[512]; _pull(var);
    declare("var=", var);
    symbolTable.addVar(lea_line, getScope(), var, "");
}

void _var_def_ass(char* var_name) {
    char var[512]; _pull(var);
    declare("var:=", var);
    symbolTable.addVar(lea_line, getScope(), var, "");
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
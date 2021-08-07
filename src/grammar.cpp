//
// Created by Mr.Jun on 2021/8/7.
//
#include "grammar.h"
#include <stdio.h>
#include <stdarg.h>

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
}

void _block() {
    declare("block{");
}

void _block_() {
    declare("block}");
}

void _call(int args) {
    char buf[8];
    sprintf(buf, "call-%d", args);
    declare(buf);
}

void _var_def(char* var_name) {
    char var[512]; _pull(var);
    declare("var:", var);
}

void _var_ass(char* var_name) {
    char var[512]; _pull(var);
    declare("var=", var);
}

void _var_def_ass(char* var_name) {
    char var[512]; _pull(var);
    declare("var:=", var);
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
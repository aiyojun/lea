//
// Created by Mr.Jun on 2021/8/7.
//
#include "grammar.h"
#include <stdio.h>
#include <stdarg.h>

void declare(const char* _identifier) {
    printf("[%-6s]\n", _identifier);
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

void _def() {
    declare("def");
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

void _var_def() {
    declare("var:");
}

void _var_ass() {
    declare("var=");
}

void _var_def_ass() {
    declare("var:=");
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
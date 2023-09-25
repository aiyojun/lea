//
// Created by Mr.Jun on 2021/8/23.
//
#include "grammar.h"
#include <string.h>

int runtime::size_of_expect = 10;
std::deque<std::string> runtime::expects;

void expects_push(char* token) {
    if (runtime::expects.size() + 1 > runtime::size_of_expect) {
        runtime::expects.pop_front();
    }
    runtime::expects.emplace_back(std::string(token));
}

runtime::exp_q get_expects() {
    return runtime::expects;
}

void get_expects_back(int i, char buf[]) {
    strcpy(buf, runtime::expects[runtime::expects.size() - 1 - i].c_str());
}
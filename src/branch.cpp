#include "grammar.h"

#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
#include <vector>
#include <map>

class branch {
public:
    static int global_branch_i;
    static int branch_deep;
    static std::map<int, std::vector<std::string>> branch_stack;
//    static std::vector<std::string> branch_stack;
//    static std::vector<std::string> branch_inner_stack;
};

int branch::global_branch_i = 0;
int branch::branch_deep = 0;
std::map<int, std::vector<std::string>> branch::branch_stack;
//std::vector<std::string> branch::branch_stack;
//std::vector<std::string> branch::branch_inner_stack;

void branch_clear() {
    branch::global_branch_i = 0;
    branch::branch_stack.clear();
//    branch::branch_inner_stack.clear();
}
std::string branch_new_inner() {
    std::string _r = ".L"+std::to_string(branch::global_branch_i++);
//    branch::branch_inner_stack.emplace_back(_r);
    return _r;
}
std::string branch_new() {
    std::string _r = ".L"+std::to_string(branch::global_branch_i++);
//    branch::branch_stack.emplace_back(_r);
    return _r;
}


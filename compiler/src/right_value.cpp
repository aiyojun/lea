//
// Created by Mr.Jun on 2021/8/11.
//

#include "../include/lang/grammar.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <string.h>

int deep = 0;
int n_pro = 0;
int n_com = 0;

std::vector<RV_ARG> rv_arg;

__export_c void add_deep() {deep++;}
__export_c void rv_enter() {
    deep = 0;
    add_deep();
    std::cout << "[rv] enter" << std::endl;

}
__export_c void rv_exit() {
    rv_arg.clear();
    std::cout << "[rv] exit, deep : " << deep << std::endl;
}

__export_c void rv_mul() {

}
__export_c void rv_div() {

}
__export_c void rv_add() {

}
__export_c void rv_sub() {

}




__export_c void rv_arg_add(char* val, char* type) {
    RV_ARG arg;
    strcpy(arg.raw, val);
    strcpy(arg.type, type);
    rv_arg.emplace_back(arg);
//    arg.raw = std::string(val);
//    arg.type = std::string(type);
}

__export_c void rv_boo() {
    std::string stacks;
//    std::cout << std::setw(15) << std::left << "arg.raw" << std::setw(15) << std::left << "arg.type" << std::endl;
    for (const auto& arg : rv_arg) {
        stacks.append(arg.raw);
        stacks.append(" ");
//        std::cout << std::setw(15) << std::left << arg.raw << std::setw(15) << std::left << arg.type << std::endl;
    }
    std::cout << "stacks : " << stacks << std::endl;
}

__export_c void rv_boo_ops(char* op) {
    printf("[rv] boo ops : %s\n", op);
    if (strcmp(op, "==") == 0) {

    } else if (strcmp(op, "!=") == 0) {

    }
}

__export_c void rv_cal_com() {
//    printf("[rv] cal n_com : %d\n", n_com);
    if (n_com > 1) {
        std::string stacks;
        std::string types;
        for (const auto& arg : rv_arg) {
            stacks.append(arg.raw);
            stacks.append(" ");
            types.append(arg.type);
            types.append(" ");
        }
        std::cout << "stacks : " << stacks << std::endl;
        std::cout << " types : " <<  types << std::endl;

        for (int i = stacks.size() - (n_com * 2 - 1); i < stacks.size(); i++) {

        }
    }
}

__export_c void rv_cal_pro() {
//    printf("[rv] cal n_pro : %d\n", n_pro);

}
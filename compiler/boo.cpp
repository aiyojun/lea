//
// Created by root on 2021/8/19.
//
#include "syntax.h"
#include <vector>
#include <string>
#include <stdio.h>
#include <map>
#include <iostream>

class Atom {
public:
    int type; // 0->left 1->middle_op 3->right
    std::string data;
    std::string data_type;
};

class boo_node {
public:
    int deep;
    int type; // 0->leaf 1->and 2->or
    std::string alias;
    std::vector<boo_node*> children;
    std::vector<Atom> expr;
    static int global_deep;
};

int boo_node::global_deep = 0;

void bo_deep_inc() {
    boo_node::global_deep++;
}

void bo_deep_dec() {
    boo_node::global_deep--;
}





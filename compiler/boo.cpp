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
    int type; // -1->root 0->leaf 1->and 2->or 3->?
    unsigned int no;
    std::string alias;
    boo_node* parent;
    std::vector<boo_node*> children;
    std::vector<Atom> expr;
    static int global_deep;
    static boo_node* ptr;
    static boo_node* root;
    static bool paren_open;
};
boo_node* boo_node::ptr  = nullptr;
boo_node* boo_node::root = nullptr;
int boo_node::global_deep = 0;
bool boo_node::paren_open = false;

void tree_init() {
    printf("tree init\n");
    boo_node::root = new boo_node();
    boo_node::root->type = 0;
    boo_node::root->deep = 0;
    boo_node::root->no = 0;
    boo_node::ptr = boo_node::root;
}

void tree_release() {
    printf("tree release\n");
}

void tree_append_wrapper() {
//    boo_node::global_deep++;

}

void tree_append(int t) {
    if (boo_node::paren_open) {boo_node::paren_open = false; return;}
    if (t == 5 && boo_node::ptr->deep-1 > boo_node::global_deep) {printf("++ out\n");return;}
    t = t == 5 ? 4 : t;
    if (t == 6 && boo_node::global_deep != 0) {return;}
    printf("++ %d\n", t);
    t = t == 6 ? 4 : t;
    if (t != 3 && t != 4) throw std::runtime_error("type error");
    boo_node* ptr = new boo_node;
    ptr->type = t;
    if (boo_node::ptr->deep-1 > boo_node::global_deep) {
        int times = boo_node::ptr->deep - 1 - boo_node::global_deep;
        boo_node* pa = boo_node::ptr->parent;
        while (times > 0) {
            times--;
            pa = pa->parent;
        }
        ptr->parent = pa;
        ptr->deep = ptr->parent->deep + 1;
        ptr->no = ptr->parent->children.size();
        ptr->parent->children.emplace_back(ptr);
    } else if (boo_node::ptr->type == 0) {
        ptr->deep = 1;
        ptr->parent = boo_node::ptr;
        ptr->no = ptr->parent->children.size();
        ptr->parent->children.emplace_back(ptr);
    } else if (boo_node::ptr->type == 4) {
        ptr->deep = boo_node::ptr->deep;
        ptr->parent = boo_node::ptr->parent;
        ptr->no = ptr->parent->children.size();
        ptr->parent->children.emplace_back(ptr);
    } else if (boo_node::ptr->type == 3) {
        ptr->deep = boo_node::ptr->deep + 1;
        ptr->parent = boo_node::ptr;
        ptr->no = ptr->parent->children.size();
        ptr->parent->children.emplace_back(ptr);
    } else {
        throw std::runtime_error("wrapper error");
    }
    boo_node::ptr = ptr;
}

void tree_append_occupy() {
    boo_node* ptr_occupy = new boo_node();
    ptr_occupy->type = 3;
    ptr_occupy->deep = boo_node::global_deep;
    if (boo_node::global_deep == boo_node::ptr->deep) { // todo: error branch
        ptr_occupy->parent = boo_node::ptr->parent;
        ptr_occupy->no = ptr_occupy->parent->children.size();
        ptr_occupy->parent->children.emplace_back(ptr_occupy);
        boo_node::ptr = ptr_occupy;
    } else if (boo_node::global_deep > boo_node::ptr->deep) {
        ptr_occupy->parent = boo_node::ptr;
        ptr_occupy->no = ptr_occupy->parent->children.size();
        ptr_occupy->parent->children.emplace_back(ptr_occupy);
        boo_node::ptr = ptr_occupy;
    } else {
        throw std::runtime_error("occupy error");
    }
    boo_node::global_deep++;
}

void tree_append_brother() {
    boo_node* ptr_brother = new boo_node();
    ptr_brother->type = 4;
//        printf("xxx-00.1 %d\n", boo_node::ptr== nullptr ? 0 : 1);
    ptr_brother->deep = boo_node::global_deep;//boo_node::ptr->deep;
    if (boo_node::ptr == boo_node::root) {
//        printf("xxx-01\n");
        ptr_brother->parent = boo_node::root;
        ptr_brother->no = ptr_brother->parent->children.size();
        ptr_brother->parent->children.emplace_back(ptr_brother);
    } else if (boo_node::global_deep < boo_node::ptr->deep) {
        if (boo_node::ptr->parent == nullptr) {
            throw std::runtime_error("no parent");
        }
        int times = boo_node::ptr->deep - boo_node::global_deep;
        boo_node* pa = boo_node::ptr->parent;
        while (times > 0) {
            times--;
            pa = pa->parent;
        }
        ptr_brother->parent = pa;
//        ptr_brother->parent = boo_node::ptr->parent->parent;
        ptr_brother->no = ptr_brother->parent->children.size();
        ptr_brother->parent->children.emplace_back(ptr_brother);
    } else if (boo_node::global_deep == boo_node::ptr->deep) {
//        printf("xxx-00\n");
        if (boo_node::ptr->type == 3) {
            ptr_brother->parent = boo_node::ptr;
            ptr_brother->no = ptr_brother->parent->children.size();
            ptr_brother->parent->children.emplace_back(ptr_brother);
        } else {
            ptr_brother->parent = boo_node::ptr->parent;
            ptr_brother->no = ptr_brother->parent->children.size();
            ptr_brother->parent->children.emplace_back(ptr_brother);
        }
    } else {
        printf("- %d - %d - %d\n", boo_node::global_deep, boo_node::ptr->deep, boo_node::ptr->type);
        throw std::runtime_error("impossible branch");
    }
    boo_node::ptr = ptr_brother;
}
//std::map<boo_node*, int> printed;
void _print(boo_node* ptr) {
    printf(" | deep:%d-type:%d-bro:%d", ptr->deep, ptr->type, ptr->no);
    printf("\n");
    if (!ptr->children.empty()) {
        for (auto& p : ptr->children) {
            _print(p);
        }
    }
}

void tree_print() {
    printf("begin print\n");
    _print(boo_node::root);
    printf("over print\n");
}

void bo_deep_inc() {
    boo_node::global_deep++;
}

void bo_deep_dec() {
    boo_node::global_deep--;
    boo_node::paren_open = true;
}





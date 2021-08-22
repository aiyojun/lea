//
// Created by Mr.Jun on 2021/8/19.
//
#include "grammar.h"
#include <vector>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <map>
#include <iostream>

//bool find(const std::vector<std::string>& vec, cstring s) {
////    std::find_if(vec.begin(), vec.end(), s);
//    for (cstring ss : vec) {
//        if (ss == s) return true;
//    }
//    return false;
//}

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
    std::vector<std::string> stack;
    boo_node* parent;
    std::vector<boo_node*> children;
    std::vector<Atom> expr;
    static int global_deep;
    static boo_node* ptr;
    static boo_node* root;
    static bool paren_open;
    static bool paren_is_boo;

    static int paren_just_deep;
    static std::map<int, std::vector<std::string>> paren_stacks;
};
boo_node* boo_node::ptr  = nullptr;
boo_node* boo_node::root = nullptr;
int boo_node::global_deep = 0;
bool boo_node::paren_open = false;
bool boo_node::paren_is_boo = false;
int boo_node::paren_just_deep = 0;
std::map<int, std::vector<std::string>> boo_node::paren_stacks;

void paren_deep_inc() {debug_printf("paren_deep_inc\n");boo_node::paren_just_deep++;}
void paren_deep_dec() {debug_printf("paren_deep_dec\n");
    printf("has"); for (auto& ps : boo_node::paren_stacks) { printf(" ; %d", ps.first);} printf("\n");
    if (boo_node::paren_stacks.find(boo_node::paren_just_deep) != boo_node::paren_stacks.end()) {
        printf("%d => ", boo_node::paren_just_deep);
        for (cstring ss : boo_node::paren_stacks[boo_node::paren_just_deep]) {
            printf(" ; %s", ss.c_str());
        }
        printf("\n");
        boo_node::paren_stacks[boo_node::paren_just_deep].clear();
    }
    boo_node::paren_just_deep--;
}
void paren_push(char* prefix, char* value, char* type) {debug_printf("paren_push\n");
    if (boo_node::paren_just_deep <= 0) {return;}
    if (boo_node::paren_stacks.find(boo_node::paren_just_deep) == boo_node::paren_stacks.end()) {
        boo_node::paren_stacks[boo_node::paren_just_deep] = std::vector<std::string>();
        boo_node::paren_stacks[boo_node::paren_just_deep].emplace_back(std::string(prefix) + value);
    } else {
        boo_node::paren_stacks[boo_node::paren_just_deep].emplace_back(std::string(prefix) + value);
    }
}
void paren_pop() {debug_printf("paren_pop\n");
    if (boo_node::paren_just_deep == 0) {return;}
    std::vector<std::string>& stack = boo_node::paren_stacks[boo_node::paren_just_deep];
    if (std::find(stack.begin(), stack.end(), "&&") == stack.end() &&
        std::find(stack.begin(), stack.end(), "||") == stack.end()) {
        boo_node* ptr = boo_node::ptr;
        if (ptr->type == 3) {
            boo_node::ptr = boo_node::ptr->parent;
            boo_node::ptr->children.pop_back();
            printf(">> delete ptr; node type [ %d ]; child : [ %zu ]\n", ptr->type, ptr->parent->children.size());
            delete ptr;
        } else if (ptr->type == 4) {
            if (ptr->parent->type == 3) {
                boo_node* ptr_t = ptr->parent; // need to delete
                ptr->parent = ptr_t->parent;
                ptr->deep = ptr->parent->deep + 1;
                ptr->parent->children.pop_back();
                ptr->parent->children.emplace_back(ptr);
                delete ptr_t;
            } else {
                throw std::runtime_error("impossible branch, paren pop error");
            }
        } else {
            throw std::runtime_error("paren pop error");
        }

    }
}

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

void tree_node_append(int t) {debug_printf("tree_node_append\n");
    tree_append(t);
}

void tree_append(int t) {debug_printf("tree_append\n");
    if (boo_node::paren_open) {boo_node::paren_open = false; debug_printf("tree_append 01\n");return;}
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
    debug_printf("tree_append end\n");
}
//std::map<boo_node*, int> printed;
void _print(boo_node* ptr) {
    std::string s = join("", ptr->stack);
    printf(" | deep:%d-type:%d-bro:%d-stack:%s", ptr->deep, ptr->type, ptr->no, s.c_str());
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

void tree_node_stack_push(char* prefix, char* element, char* type) {
    paren_push(prefix, element, type);
//    if (boo_node::ptr->type == 3) throw std::runtime_error("??? app : " + std::string(prefix) + element);
//    boo_node::ptr->stack.emplace_back(std::string(prefix)+element);
}


char framebuffer[800][600];
std::vector<boo_node*> all_nodes;
int y_node_max_n = 0;
int x_node_max_n = 0;
int y_len = 5;
int x_len = 15;
int x_gap = 5;
int y_gap = 5;
void collect_node_info() {
    std::map<int, int> x_collect;
    for (auto& ptr : all_nodes) {
        int deep = ptr->deep;
        if (x_collect.find(deep) == x_collect.end()) {
            x_collect[deep] = 1;
        } else {
            x_collect[deep]++;
        }
        y_node_max_n = deep > y_node_max_n ? deep : y_node_max_n;
    }
    for (auto& kv : x_collect) {
        x_node_max_n = kv.second > x_node_max_n ? kv.second : x_node_max_n;
    }
}

void write_into_block(char ptr[5][15], cstring data) {
    for (int i = 0; i < 15; i++) {
        if (i > 0 && i < 4) {
            ptr[i][0] = '|'; ptr[i][14] = '|';
        }
        ptr[0][i] = '-'; ptr[4][i] = '-';
    }
    unsigned int begin = 0;
    int rest = data.size();
    int j = 1;
    while (rest > 0) {
        std::string s;
        if (rest > 13) {
            s = data.substr(begin, 13);
            strcpy(ptr[j], s.c_str());
            begin = begin + 13;
            rest = rest - 13;
            j++;
            if (j == 4) break;
        } else {
            s = data.substr(begin, rest);
            strcpy(ptr[j], s.c_str());
            break;
        }
    }
}

void out_into_frame() {
    if (x_node_max_n * x_len + (x_node_max_n - 1) * x_gap > 800) throw std::runtime_error("[frame] x > edge");
    if (y_node_max_n * y_len + (y_node_max_n - 1) * y_gap > 800) throw std::runtime_error("[frame] y > edge");



}






#include "tree_node.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <tuple>
#include "basic_ds.h"

int tree_node::uuid = 0;

AST AST::self;

tree_node* AST::create_node(cstring value) {
	ivk_stack[ivk_depth].emplace_back(new tree_node());
	ivk_stack[ivk_depth].back()->data = value;
	return ivk_stack[ivk_depth].back();
}

void AST::link_node(cstring ops) {
    std::vector<tree_node*>& stack = ivk_stack[ivk_depth];
    auto ptr = new tree_node();
    ptr->type = 1; ptr->data = ops;
    std::set<std::string> op_single {"()", "!", "-_", "+_"};
    std::set<std::string> op_double {
    	"+", "-", "*", "/", "%",
    	">", ">=", "<", "<=", "==", "!=",
    	"&&", "||",
    	"[]", "."
    };
    if (contains(op_single, ops)) {
        tree_node* p0 = stack[stack.size() - 1];
        if (ops == "()" && p0->data == "()") return;
        p0->parent = ptr;
        ptr->children.emplace_back(p0);
        stack.pop_back(); stack.emplace_back(ptr);
    } else if (contains(op_double, ops)) {
        tree_node* p0 = stack[stack.size() - 2];
        tree_node* p1 = stack[stack.size() - 1];
        p0->parent = ptr; p1->parent = ptr;
        ptr->children.emplace_back(p0); ptr->children.emplace_back(p1);
        stack.pop_back(); stack.pop_back(); stack.emplace_back(ptr);
    } else {
        throw std::runtime_error("tree node link error");
    }
}

void AST::link_inode() {
    std::vector<tree_node*>& i_stack = ivk_stack[ivk_depth];
    auto invoking_node = ivk_stack[ivk_depth - 1].back();
    for (int i = 0; i < i_stack.size(); i++) {
        tree_node* ptr = i_stack[i];
        ptr->parent = invoking_node;
        invoking_node->children.emplace_back(ptr);
    }
    i_stack.clear();
}

void AST::refresh(tree_node* node, int depth, int& max_deep) {
    node->deep = depth;
    if (node->deep > max_deep) max_deep = node->deep;
    if (node->children.empty()) return;
    int i = 0;
    for (auto child : node->children) {
        child->no = i;
        refresh(child, depth + 1, max_deep);
        i++;
    }
}

void AST::capture(std::vector<tree_node*>& vec, tree_node* node, int deep, int& max_deep) {
    if (deep > max_deep) max_deep = deep;
    node->deep = deep;
    vec.emplace_back(node);
    if (!node->children.empty()) {
        for (auto& ptr : node->children) {
            capture(vec, ptr, deep + 1, max_deep);
        }
    }
}

void AST::subtree_print(tree_node* subtree) {
    std::vector<tree_node*> nodes;
    int max_deep = 0;
    capture(nodes, subtree, 0, max_deep);
    for (int dp = 0; dp <= max_deep; dp++) {
        printf("%2d ", dp);
        if (dp == 0) {
            tree_node* ptr = subtree;
            printf(" | %d:%d:%s\n", ptr->id, 0, ptr->data.c_str());
            continue;
        } else {
            for (auto& ptr : nodes) {
                if (ptr->deep == dp) {
                    printf(" | [%d] %d:%d:%s", ptr->parent->id, ptr->id, ptr->no, ptr->data.c_str());
                }
            }
        }
        printf("\n");
    }
}

void AST::print() {
    auto root = AST::self.ivk_stack[0][0];
    int max_deep = 0;
    std::vector<tree_node*> nodes;
    capture(nodes, root, 0, max_deep);
// #define _print_stack 
#ifdef _print_stack
    printf(">> Stack print\n");
    printf("---------------\n");
    for (auto stack_kv : AST::self.ivk_stack) {
    	std::vector<std::string> line;
    	for (auto node : stack_kv.second) line.emplace_back(node->data);
    	printf("%d | %s\n", stack_kv.first, join(", ", line).c_str());
    }
    printf("---------------\n");
#endif
	printf(">> Tree print\n");
    printf("---------------\n");
    for (int dp = 0; dp <= max_deep; dp++) {
        printf("%2d ", dp);
        if (dp == 0) {
            tree_node* ptr = root;
            printf(" |      %2d:%2d:%-5s\n", ptr->id, 0, ptr->data.c_str());
            continue;
        } else {
            for (auto& ptr : nodes) {
                if (ptr->deep == dp) {
                    printf(" | [%2d] %2d:%2d:%-5s", ptr->parent->id, ptr->id, ptr->no, ptr->data.c_str());
                }
            }
        }
        printf("\n");
    }
    printf("---------------\n");
}
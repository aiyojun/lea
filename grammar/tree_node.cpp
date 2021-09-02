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
int tree_node::max_deep = 0;
tree_node* tree_node::root;

int tree_node::invoking_deep = 0;
std::map<int, std::vector<tree_node*>> tree_node::invoking_stack;
std::string tree_node::heap_register_name;

void tree_clear() {
    tree_node::uuid = 0;
    tree_node::max_deep = 0;
    tree_node::root = nullptr;
    tree_node::invoking_deep = 0;
    tree_node::invoking_stack.clear();
    tree_node::heap_register_name = "";
}

void invoking_deep_inc() {tree_node::invoking_deep++;}
void invoking_deep_dec() {tree_node::invoking_deep--;}
void heap_register(const char* fun) {tree_node::heap_register_name = std::string(fun);}
void heap_variable() {
    std::vector<tree_node*>& node_stack = tree_node::invoking_stack[tree_node::invoking_deep];
    auto* ptr = new tree_node();
    std::string val = tree_node::heap_register_name;
    ptr->data = val;
    ptr->type = 4;
    node_stack.emplace_back(ptr);
}
void heap_invoking() {
    std::vector<tree_node*>& node_stack = tree_node::invoking_stack[tree_node::invoking_deep];
    auto* ptr = new tree_node();
    std::string val = tree_node::heap_register_name;
    ptr->data = val;
    ptr->type = 3;
    node_stack.emplace_back(ptr);
}

// void heap_variable_v2() {
//     std::vector<tree_node*>& node_stack = tree_node::invoking_stack[tree_node::invoking_deep];
//     auto* ptr = new tree_node();
//     std::string val = tree_node::heap_register_name;
//     ptr->data = val;
//     ptr->type = 4;
//     if (!contains(tree_node::invoking_chain, tree_node::invoking_deep)) {
//     	invoking_chain[tree_node::invoking_deep] = std::vector<tree_node*>();
//     	invoking_chain[tree_node::invoking_deep].emplace_back(ptr);
//     } else {
//     	ptr.children.emplace_back(invoking_chain[tree_node::invoking_deep].back());
//     	invoking_chain[tree_node::invoking_deep].emplace_back(ptr);
//     }
// }
// void heap_invoking_v2() {
// 	std::vector<tree_node*>& node_stack = tree_node::invoking_stack[tree_node::invoking_deep];
//     auto* ptr = new tree_node();
//     std::string val = tree_node::heap_register_name;
//     ptr->data = val;
//     ptr->type = 3;
//     if (!contains(tree_node::invoking_chain, tree_node::invoking_deep)) {
//     	invoking_chain[tree_node::invoking_deep] = std::vector<tree_node*>();
//     	invoking_chain[tree_node::invoking_deep].emplace_back(ptr);
//     } else {
//     	ptr.children.emplace_back(invoking_chain[tree_node::invoking_deep].back());
//     	invoking_chain[tree_node::invoking_deep].emplace_back(ptr);
//     }
// }
// void heap_chain_v3() {
// 	std::vector<tree_node*>& node_stack = tree_node::invoking_chain[tree_node::invoking_deep];
// }



void heap_invoking_args_link() {
    std::vector<tree_node*>& node_stack = tree_node::invoking_stack[tree_node::invoking_deep];
    tree_node* invoking_node = tree_node::invoking_stack[tree_node::invoking_deep - 1].back();
    for (int i = 0; i < node_stack.size(); i++) {
        tree_node* ptr = node_stack[i];
        ptr->parent = invoking_node;
        invoking_node->children.emplace_back(ptr);
    }
    node_stack.clear();
}

void tree_node_create(const char* prefix, const char* value, const char* type) {
    std::vector<tree_node*>& node_stack = tree_node::invoking_stack[tree_node::invoking_deep];
    auto* ptr = new tree_node();
    std::string val = std::string(prefix) + value;
    ptr->type = 2; ptr->data = val; ptr->sign_type = std::string(type);
    node_stack.emplace_back(ptr); //TODO: consider invoking deep
}

void tree_node_chain() {
	std::vector<tree_node*>& stack = tree_node::invoking_stack[tree_node::invoking_deep];
	auto* ptr = new tree_node();
	ptr->type = 5; ptr->data = "chain";
	int len = 0;
	for (unsigned int i = 0; i < stack.size(); i++) {
		auto& node = stack[stack.size() - 1 - i];
		if (node->type == 3 || node->type == 4) {
			len++;
		} else {
			break;
		}
	}
	// std::cout << "len: " << len << "\n";
	for (int i = 0; i < len; i++) {
		auto& node = stack[stack.size() - len + i];
		node->parent = ptr;
		ptr->children.emplace_back(node);
	}
	for (int i = 0; i < len; i++) {
		stack.pop_back();
	}
	stack.emplace_back(ptr);
}

void tree_node_link(const char* op) {
    std::vector<tree_node*>& stack = tree_node::invoking_stack[tree_node::invoking_deep];
    std::string ops(op); auto* ptr = new tree_node();
    std::map<std::string, int> mapping{
        {"+", 1}, {"-", 2}, {"*", 3}, {"/", 4}, {"%", 5},
        {">", 6}, {">=", 7}, {"<", 8}, {"<=", 9}, {"==", 10}, {"!=", 11},
        {"!", 12}, {"&&", 13}, {"||", 14}, 
        {".", 15}
    };
    ptr->type = 1; ptr->data = ops;
    if (ops == "()" || ops == "!" || ops == "[]") {
        tree_node* p0 = stack[stack.size() - 1];
        if (ops == "()" && p0->data == "()") {return;}
        p0->parent = ptr;
        ptr->children.emplace_back(p0);
        stack.pop_back(); stack.emplace_back(ptr);
    } else if (contains(mapping, ops)) {
        tree_node* p0 = stack[stack.size() - 2];
        tree_node* p1 = stack[stack.size() - 1];
        p0->parent = ptr; p1->parent = ptr;
        ptr->children.emplace_back(p0); ptr->children.emplace_back(p1);
        stack.pop_back(); stack.pop_back(); stack.emplace_back(ptr);
    } else {
        throw std::runtime_error("tree node link error");
    }
}

void recursion_deep(tree_node* node, int depth) {
    node->deep = depth;
    if (node->deep > tree_node::max_deep) {
        tree_node::max_deep = node->deep;
        if (tree_node::max_deep > 20) {
            printf("node deep : %d\n", node->deep);
        }
    }
    if (node->children.empty()) {return;}
    int i = 0;
    for (auto& child : node->children) {
        child->no = i;
        recursion_deep(child, depth + 1);
        i++;
    }
}

void tree_node_deep_assign() {
    tree_node::root = new tree_node();
    tree_node::root->type = 0;
    tree_node::root->data = "root";
    tree_node::root->deep = 0;
    tree_node::root->parent = nullptr;
    tree_node::root->children.emplace_back(tree_node::invoking_stack[0][0]);
    tree_node::invoking_stack[0][0]->parent = tree_node::root;
    recursion_deep(tree_node::root, 0);
}

void rotate_boo(tree_node* node) {
    if (node->data == "&&" || node->data == "||") {
        rotate_subtree_boo(node, node->data);
    }
    if (!node->children.empty()) {
        for (auto& child : node->children) {
            rotate_boo(child);
        }
    }
}

void rotate_subtree_boo(tree_node* node, cstring ops) {
    while (!without_boo(node->children, ops)) {
        std::vector<tree_node*> tmp;
        for (int i = 0; i < node->children.size(); i++) {
            tree_node* child = node->children[i];
            if (child->data == ops) {
                for (tree_node* child_of_child : child->children) {
                    tmp.emplace_back(child_of_child);
                }
            } else {
                tmp.emplace_back(child);
            }
        }
        node->children.clear();
        for (auto& pp : tmp) {
            pp->parent = node;
            node->children.emplace_back(pp);
        }
    }
}
bool without_boo(const std::vector<tree_node*>& vec, cstring sym) {
    for (auto& ptr : vec) {if (ptr->data == sym) return false;}
    return true;
}

void tree_node_collect_v2(std::vector<tree_node*>& vec, tree_node* node, int deep, int& max_deep) {
    if (deep > max_deep) max_deep = deep;
    node->deep = deep;
    vec.emplace_back(node);
    if (!node->children.empty()) {
        for (auto& ptr : node->children) {
            tree_node_collect_v2(vec, ptr, deep + 1, max_deep);
        }
    }
}

void subtree_print(tree_node* subtree) {
    std::vector<tree_node*> allNodes;
    int max_deep = 0;
    tree_node_collect_v2(allNodes, subtree, 0, max_deep);
    for (int dp = 0; dp <= max_deep; dp++) {
        printf("%2d ", dp);
        if (dp == 0) {
            tree_node* ptr = subtree;
            printf(" | %d:%d:%s\n", ptr->id, 0, ptr->data.c_str());
            continue;
        } else {
            for (auto& ptr : allNodes) {
                if (ptr->deep == dp) {
                    printf(" | [%d] %d:%d:%s", ptr->parent->id, ptr->id, ptr->no, ptr->data.c_str());
                }
            }
        }
        printf("\n");
    }
}

void tree_node_print() {
    printf(">> Tree print\n");
    printf("---------------\n");
//    printf("tree_node_print max_deep : %d\n", tree_node::max_deep);
//    for (auto& p : tree_node::invoking_stack) {
//        printf(">>>> invoking stack - %d ; size : %d\n", p.first, (int) p.second.size());
//        for (auto& pp : p.second) {
//            printf(" | %s", pp->data.c_str());
//        }
//        printf("\n");
//    }
    std::vector<tree_node*> allNodes;
//    tree_node_collect(allNodes, tree_node::root);
    int max_deep = 0;
    tree_node_collect_v2(allNodes, tree_node::root, 0, max_deep);
//    printf("collected size : %d\n", (int) allNodes.size());
//    for (auto& child : allNodes) {
//        printf("id : %d, deep : %d, data ; %s\n", child->id, child->deep, child->data.c_str());
//    }
    if (max_deep > 50) {throw std::runtime_error("take care, overflow upper limit");}
    for (int dp = 0; dp <= max_deep; dp++) {
        printf("%2d ", dp);
        if (dp == 0) {
            tree_node* ptr = tree_node::root;
            printf(" | %d:%d:%s\n", ptr->id, 0, ptr->data.c_str());
            continue;
        } else {
            for (auto& ptr : allNodes) {
                if (ptr->deep == dp) {
                    printf(" | [%d] %d:%d:%s", ptr->parent->id, ptr->id, ptr->no, ptr->data.c_str());
                }
            }
        }
        printf("\n");
    }
    printf("---------------\n");
}

// TODO: analysis right side
// TODO: analysis left side, scenes as following:
//       1. : type = x
//       2. = x
//       3. if (x)
//       4. return x
//       5. fun()
void tree_analysis(int usage) {
    rotate_boo(tree_node::root);
    recursion_deep(tree_node::root, 0);
    printf("// After rotate boo\n");
    // reduce_clc(tree_node::root, new calculate_modifier);
    // printf("// After reduce clc\n");
    tree_node_print();
    // reduce_cmp(tree_node::root, new compare_modifier);
    // printf("// After reduce cmp\n");
    // tree_node_print();
    // reduce_boo(tree_node::root, new boo_modifier);
    // printf("// After reduce boo\n");
    // tree_node_print();
    // std::set<tree_node*> recording;
    // forecast_boo(0, recording, tree_node::root->children[0], tree_node::root->children[0]);
    // printf("// After forecast boo\n");
    //     tree_node_print();
    // if (usage == 3) {
    //     printf("// After gen\n");
    //     subtree_remove_paren(0, tree_node::root);
    //     tree_node_print();
    //     lea_if::gen_boo(tree_node::root);
    //     lea_if::gen_boo_print();

    //     // lea_if::allocate_label();
    //     // do_compare();
    // } else if (usage == 1) {
    //     do_assign(usage);
    // } else if (usage == 2) {

    // } else if (usage == 4) {

    // }
}
#include "grammar.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>

class tree_node {
public:
    tree_node() {id = ++id_count;if (id_count > 100) { printf("id count error\n");}}
    static int id_count;
    int id = 0;
    int no = 0;
    int deep;
    tree_node *parent;
    std::vector<tree_node*> children;

    int type;
    std::string data;
    std::vector<std::string> stack_data;

    static int max_deep;
    static tree_node* root;
    static std::vector<tree_node*> node_stack;
    static std::vector<tree_node*> node_stack_trunk;
    static std::vector<tree_node*> node_stack_leaves;
    static std::vector<tree_node*> nodes;

    static int invoking_deep;
    static std::map<int, tree_node*> invoking_stack_query;
    static std::map<int, std::vector<tree_node*>> invoking_stack;
    static std::string heap_register_name;
    static std::vector<tree_node*> all_nodes;
};

int tree_node::id_count = 0;
int tree_node::max_deep = 0;
tree_node* tree_node::root;
std::vector<tree_node*> tree_node::node_stack;
std::vector<tree_node*> tree_node::node_stack_trunk;
std::vector<tree_node*> tree_node::node_stack_leaves;
std::vector<tree_node*> tree_node::nodes;

int tree_node::invoking_deep = 0;
std::map<int, std::vector<tree_node*>> tree_node::invoking_stack;
std::string tree_node::heap_register_name;
std::vector<tree_node*> tree_node::all_nodes;

void invoking_deep_inc() {tree_node::invoking_deep++;}
void invoking_deep_dec() {tree_node::invoking_deep--;}
void heap_register(char* fun) {tree_node::heap_register_name = std::string(fun);}
void heap_variable() {
    std::vector<tree_node*>& node_stack = tree_node::invoking_stack[tree_node::invoking_deep];
    tree_node* ptr = new tree_node();
    std::string val = tree_node::heap_register_name;
    ptr->data = val;
    ptr->type = 4;
//    tree_node::node_stack.emplace_back(ptr);
    //TODO: consider invoking deep
    node_stack.emplace_back(ptr);
    //TODO: end
    tree_node::all_nodes.emplace_back(ptr);
}
void heap_invoking() {
    std::vector<tree_node*>& node_stack = tree_node::invoking_stack[tree_node::invoking_deep];
    tree_node* ptr = new tree_node();
    std::string val = tree_node::heap_register_name;
    ptr->data = val;
    ptr->type = 3;
    //TODO: consider invoking deep
    node_stack.emplace_back(ptr);
    //TODO: end
    tree_node::all_nodes.emplace_back(ptr);
}

void heap_invoking_args_link() {
    std::vector<tree_node*>& node_stack = tree_node::invoking_stack[tree_node::invoking_deep];
    tree_node* invoking_node = tree_node::invoking_stack[tree_node::invoking_deep - 1].back();
    for (int i = 0; i < node_stack.size(); i++) {
        tree_node* ptr = node_stack[i];
        ptr->parent = invoking_node;
        invoking_node->children.emplace_back(ptr);
        node_stack.pop_back();
    }
}

void tree_node_create(char* prefix, char* value, char* type) {
    std::vector<tree_node*>& node_stack = tree_node::invoking_stack[tree_node::invoking_deep];

    printf("tree_node_create %s\n", value);
    tree_node* ptr = new tree_node();
    std::string val = std::string(prefix) + value;
    ptr->data = val;
    ptr->type = 2;
//    tree_node::node_stack.emplace_back(ptr);

    //TODO: consider invoking deep
    node_stack.emplace_back(ptr);
    //TODO: end

//    tree_node::node_stack_leaves.emplace_back(ptr);
//    tree_node::nodes.emplace_back(ptr);
    tree_node::all_nodes.emplace_back(ptr);
}

void tree_node_link(char* op) {
    std::vector<tree_node*>& stack = tree_node::invoking_stack[tree_node::invoking_deep];

//    std::vector<tree_node*>& stack = tree_node::node_stack;

    std::string ops(op);
    tree_node* ptr = new tree_node();

    std::map<std::string, int> mapping{
        {"+", 1}, {"-", 2}, {"*", 3}, {"/", 4}, {"%", 5},
        {">", 6}, {">=", 7}, {"<", 8}, {"<=", 9}, {"==", 10}, {"!=", 11},
        {"!", 12}, {"&&", 13}, {"||", 14}
    };

    if (ops == ")" || ops == "()") {
        ptr->type = 1;
        ptr->data = "()";

        tree_node* p0 = stack[stack.size() - 1];
        p0->parent = ptr;
        ptr->children.emplace_back(p0);
        stack.pop_back(); stack.emplace_back(ptr);
    } else if (ops == "!") {
        ptr->type = 1;
        ptr->data = ops;

        tree_node* p0 = stack[stack.size() - 1];
        p0->parent = ptr;
        ptr->children.emplace_back(p0);
        stack.pop_back(); stack.emplace_back(ptr);
    } else if (mapping.find(ops) != mapping.end()) {
        ptr->type = 1;
        ptr->data = ops;

        tree_node* p0 = stack[stack.size() - 2];
        tree_node* p1 = stack[stack.size() - 1];
        p0->parent = ptr; p1->parent = ptr;
        ptr->children.emplace_back(p0); ptr->children.emplace_back(p1);
        stack.pop_back(); stack.pop_back(); stack.emplace_back(ptr);
    } else {
        throw std::runtime_error("tree node link error");
    }

//    tree_node::node_stack_trunk.emplace_back(ptr);
//    tree_node::nodes.emplace_back(ptr);
    tree_node::all_nodes.emplace_back(ptr);
}

void recursion_deep(tree_node* node, int depth) {
    printf("recursion_deep\n");
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
    printf("tree_node_deep_assign\n");
    tree_node::root = new tree_node();
    tree_node::root->type = 0;
    tree_node::root->data = "root";
    tree_node::root->deep = 0;
    tree_node::root->parent = nullptr;
    tree_node::root->children.emplace_back(tree_node::invoking_stack[0][0]);
    tree_node::invoking_stack[0][0]->parent = tree_node::root;
//    tree_node::root->children.emplace_back(tree_node::node_stack.back());
//    tree_node::node_stack.back()->parent = tree_node::root;
//    tree_node::nodes.emplace_back(tree_node::root);

    recursion_deep(tree_node::root, 0);
}

void tree_node_print() {
    printf("tree_node_print max_deep : %d\n", tree_node::max_deep);
    if (tree_node::max_deep > 20) {
        exit(3);
    }
    for (int dp = 0; dp <= tree_node::max_deep; dp++) {
        printf("%2d ", dp);
        if (dp == 0) {
            tree_node* ptr = tree_node::root;
            printf(" | %d:%d:%s", ptr->id, 0, ptr->data.c_str());
            continue;
            if (tree_node::nodes.back()->deep == 0) {
                tree_node* ptr = tree_node::nodes.back();
                printf(" | %d:%d:%s", ptr->id, 0, ptr->data.c_str());
            } else if (tree_node::nodes[0]->deep == 0) {
                tree_node* ptr = tree_node::nodes[0];
                printf(" | %d:%d:%s", ptr->id, 0, ptr->data.c_str());
            } else {
                throw std::runtime_error("tree node print error");
//                for (auto& ptr : tree_node::nodes) {
//                    printf("#01 | %d:%d:%s", ptr->id, 0, ptr->data.c_str());
//                }
            }
        } else {
            for (auto& ptr : tree_node::all_nodes) {
//            for (auto& ptr : tree_node::nodes) {
                if (ptr->deep == dp) {
//                    printf(" | [%d:%d:%s] %d:%d:%s", ptr->parent->id, ptr->parent->no, ptr->parent->data.c_str(), ptr->id, ptr->no, ptr->data.c_str());
                    printf(" | [%d] %d:%d:%s", ptr->parent->id, ptr->id, ptr->no, ptr->data.c_str());
                }
            }
        }
        printf("\n");
    }
}

bool hasBool = true;

bool without_boo(const std::vector<tree_node*>& vec, cstring sym) {
    for (auto& ptr : vec) {
        if (ptr->data == sym) {
            return false;
        }
    }
    return true;
}

tree_node* pick_not_paren(tree_node* paren_node) {
    tree_node* ptr = paren_node;
    while (ptr->data != "()") {
        if (ptr->children.size() > 1) {
            throw std::runtime_error("paren node must have one child");
        }
        ptr = ptr->children[0];
    }
    return ptr;
}

void modify_child(tree_node* node, cstring ops) {
    while (!without_boo(node->children, ops)) {
        std::vector<tree_node*> tmp;
        for (int i = 0; i < node->children.size(); i++) {
            tree_node* child = node->children[i];
            if (child->data == ops) {
                for (tree_node* child_of_child : child->children) {
                    tmp.emplace_back(child_of_child);
                }
//                delete child;
            } else {
                tmp.emplace_back(child);
            }
        }
        node->children.clear();
        for (auto& pp : tmp) node->children.emplace_back(pp);
    }
}

void recursion_modify(tree_node* node) {
//    tree_node::nodes.emplace_back(node);
    if (node->data == "&&" || node->data == "||") {
        modify_child(node, node->data);
    }
    if (!node->children.empty()) {
        for (auto& child : node->children) {
            recursion_modify(child);
        }
    }
}

void tree_node_collect(tree_node* node) {
    tree_node::nodes.emplace_back(node);
    if (!node->children.empty()) {
        for (auto& ptr : node->children) {
            tree_node_collect(ptr);
        }
    }
}

void tree_node_modify() {
    printf("tree_node_modify\n");
    recursion_modify(tree_node::root);
    tree_node::nodes.clear();
    tree_node_collect(tree_node::root);
    tree_node::max_deep = 0;
    recursion_deep(tree_node::root, 0);
    printf("tree_node_modify over max deep : %d\n", tree_node::max_deep);
//    exit(1);
}




#include "grammar.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>

class tree_node {
public:
    tree_node() {id = ++uuid;if (uuid > 100) { printf("id count error\n");}}
    static int uuid;

    /** member of tree node */
    int id = 0;
    int no = 0;
    int deep;
    tree_node *parent;
    std::vector<tree_node*> children;

    /** right value information */
    int type;
    std::string data;
    std::string sign_type;
    std::vector<std::string> stack_data;

    /** tree management */
    static int max_deep;
    static tree_node* root;

    /** prepared for nest invoking */
    static int invoking_deep;
//    static std::map<int, tree_node*> invoking_stack_query;
    static std::map<int, std::vector<tree_node*>> invoking_stack;
    static std::string heap_register_name;
};

int tree_node::uuid = 0;
int tree_node::max_deep = 0;
tree_node* tree_node::root;

int tree_node::invoking_deep = 0;
std::map<int, std::vector<tree_node*>> tree_node::invoking_stack;
std::string tree_node::heap_register_name;

void tree_clear() {
    printf("tree_clear\n");
    tree_node::uuid = 0;
    tree_node::max_deep = 0;
    tree_node::root = nullptr;
    tree_node::invoking_deep = 0;
    tree_node::invoking_stack.clear();
    tree_node::heap_register_name = "";
    printf("tree_clear over , invoking_deep size : %d\n", (int) tree_node::invoking_stack.size());
}

void invoking_deep_inc() {tree_node::invoking_deep++;}
void invoking_deep_dec() {tree_node::invoking_deep--;}
void heap_register(char* fun) {tree_node::heap_register_name = std::string(fun);}
void heap_variable() {
    std::vector<tree_node*>& node_stack = tree_node::invoking_stack[tree_node::invoking_deep];
    auto* ptr = new tree_node();
    std::string val = tree_node::heap_register_name;
    ptr->data = val;
    ptr->type = 4;
    //TODO: consider invoking deep
    node_stack.emplace_back(ptr);
}
void heap_invoking() {
    std::vector<tree_node*>& node_stack = tree_node::invoking_stack[tree_node::invoking_deep];
    auto* ptr = new tree_node();
    std::string val = tree_node::heap_register_name;
    ptr->data = val;
    ptr->type = 3;
    //TODO: consider invoking deep
    node_stack.emplace_back(ptr);
}

void heap_invoking_args_link() {
    std::vector<tree_node*>& node_stack = tree_node::invoking_stack[tree_node::invoking_deep];
    tree_node* invoking_node = tree_node::invoking_stack[tree_node::invoking_deep - 1].back();
    for (int i = 0; i < node_stack.size(); i++) {
        tree_node* ptr = node_stack[i];
        ptr->parent = invoking_node;
        invoking_node->children.emplace_back(ptr);
    }
    for (int i = 0; i < node_stack.size(); i++) {
        node_stack.pop_back();
    }
}

void tree_node_create(char* prefix, char* value, char* type) {
    std::vector<tree_node*>& node_stack = tree_node::invoking_stack[tree_node::invoking_deep];
//    printf("tree_node_create %s\n", value);
    auto* ptr = new tree_node();
    std::string val = std::string(prefix) + value;
    ptr->type = 2; ptr->data = val; ptr->sign_type = std::string(type);
    node_stack.emplace_back(ptr); //TODO: consider invoking deep
}

void tree_node_link(char* op) {
    std::vector<tree_node*>& stack = tree_node::invoking_stack[tree_node::invoking_deep];
    std::string ops(op); auto* ptr = new tree_node();
    std::map<std::string, int> mapping{
        {"+", 1}, {"-", 2}, {"*", 3}, {"/", 4}, {"%", 5},
        {">", 6}, {">=", 7}, {"<", 8}, {"<=", 9}, {"==", 10}, {"!=", 11},
        {"!", 12}, {"&&", 13}, {"||", 14}
    };
    ptr->type = 1; ptr->data = ops;
    if (ops == "()" || ops == "!") {
        tree_node* p0 = stack[stack.size() - 1];
        if (ops == "()" && p0->data == "()") {return;}
        p0->parent = ptr;
        ptr->children.emplace_back(p0);
        stack.pop_back(); stack.emplace_back(ptr);
    } else if (mapping.find(ops) != mapping.end()) {
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
//    printf("recursion_deep\n");
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
    recursion_deep(tree_node::root, 0);
    printf("tree_node_deep_assign over\n");
}



bool without_boo(const std::vector<tree_node*>& vec, cstring sym) {
    for (auto& ptr : vec) {
        if (ptr->data == sym) {
            return false;
        }
    }
    return true;
}

//tree_node* pick_not_paren(tree_node* paren_node) {
//    tree_node* ptr = paren_node;
//    while (ptr->data != "()") {
//        if (ptr->children.size() > 1) {
//            throw std::runtime_error("paren node must have one child");
//        }
//        ptr = ptr->children[0];
//    }
//    return ptr;
//}

void tree_modify_boo(tree_node* node, cstring ops) {
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

void tree_recursion_boo(tree_node* node) {
    if (node->data == "&&" || node->data == "||") {
        tree_modify_boo(node, node->data);
    }
    if (!node->children.empty()) {
        for (auto& child : node->children) {
            tree_recursion_boo(child);
        }
    }
}

void tree_node_collect(std::vector<tree_node*>& vec, tree_node* node) {
    vec.emplace_back(node);
    if (!node->children.empty()) {
        for (auto& ptr : node->children) {
            tree_node_collect(vec, ptr);
        }
    }
}

void tree_node_modify() {
    printf("tree_node_modify\n");
    tree_recursion_boo(tree_node::root);
    std::vector<tree_node*> allNodes;
    tree_node_collect(allNodes, tree_node::root);
    tree_node::max_deep = 0;
    recursion_deep(tree_node::root, 0);
    printf("tree_node_modify over max deep : %d\n", tree_node::max_deep);
}

void tree_node_print() {
    printf("tree_node_print max_deep : %d\n", tree_node::max_deep);
    for (auto& p : tree_node::invoking_stack) {
        printf(">>>> invoking stack - %d ; size : %d\n", p.first, (int) p.second.size());
        for (auto& pp : p.second) {
            printf(" | %s", pp->data.c_str());
        }
        printf("\n");
    }
    std::vector<tree_node*> allNodes;
    tree_node_collect(allNodes, tree_node::root);
    if (tree_node::max_deep > 50) {throw std::runtime_error("take care, overflow upper limit");}
    for (int dp = 0; dp <= tree_node::max_deep; dp++) {
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
}

std::string analysis_type_op;
std::vector<std::string> analysis_invoking;
std::vector<std::string> analysis_variable;

void tree_recursion_anl(tree_node* node) {
    if (node->type == 3) {
        analysis_invoking.emplace_back(node->data);
        return;
    }
    if (node->type == 4) {
        analysis_variable.emplace_back(node->data);
        return;
    }
    if (!node->children.empty()) {
        for (auto& ptr : node->children) {
            tree_recursion_anl(ptr);
        }
    }
}

// TODO: analysis right side
// TODO: analysis left side, scenes as following:
//       1. : type = x
//       2. = x
//       3. if (x)
//       4. return x
//       5. fun()
void tree_analysis(int usage) {
//    tree_node_print();
    printf("tree_analysis %d\n", usage);
    tree_node* node_op_r = tree_node::root->children[0];
    if (node_op_r->data == "()")
        node_op_r = node_op_r->children[0];
    std::string ops = node_op_r->data;
    int type = node_op_r->type;
    if (type == 3) { // TODO: invoking
        if (usage == 1) {

        } else if (usage == 2) {

        } else if (usage == 3) {

        } else if (usage == 4) {

        } else if (usage == 5) {
            printf(">> invoking deep : %d\n", tree_node::invoking_deep);
            if (tree_node::invoking_deep == 0) {
                args_clear();
                for (int i = 0; i < node_op_r->children.size(); i++) {
                    std::string value_r = node_op_r->children[i]->data;
                    std::string value_type = node_op_r->children[i]->sign_type;
                    if (value_type == "int") {
                        mov4byte2arg(rt(atoi(value_r.c_str())));
                    } else if (value_type == "double") {
                        mov2xmm(ptr_ip(declare_ro_data("double", value_r)));
                    } else if (value_type == "char") {
                        mov4byte2arg(rt((int) value_r[1]));
                    } else if (value_type == "string") {
                        mov8byte2arg(ptr(declare_ro_data("string", value_r)));
                    } else
                        yyerror("args type error");
                }
                function_call(ops);
            } else
                yyerror("unimplemented branch");
        } else
            yyerror("unknown right value usage 5");

        return;
    }
    if (type == 4) { // TODO: variable
//        if (usage == 1) {
//            std::string variable_name = give_variable().name;
//            std::string variable_type = give_variable().type;
//
//        } else {
//            yyerror("unknown right value usage");
//        }
        return;
    }
    if (type == 2) { // TODO: number
        std::string valueType = node_op_r->sign_type;
        if (usage == 1) { // absolute in stack
            std::string variable_name = give_variable().name;
            std::string variable_type = give_variable().type;
            if (variable_type == "int" && valueType == "int") {
                stack4bytes(variable_name, rt(atoi(ops.c_str())));
            } else if (variable_type == "double" && variable_type == "int") {
                stack_double(variable_name, declare_ro_data("double", ops));
            } else if (variable_type == "double" && variable_type == "double") {
                stack_double(variable_name, declare_ro_data("double", ops));
            } else if (variable_type == "char" && variable_type == "char") {
                printf("stack4bytes char : %c\n", ops[1]);
                stack4bytes(variable_name, rt((int) ops[1]));
            } else if (variable_type == "string" && variable_type == "string") {
                stack8bytes(variable_name, ptr(declare_ro_data("string", ops)));
            } else
                yyerror(("error value type of "+variable_name).c_str());
        } else if (usage == 2) {
            std::string variable_name = give_variable().name;
            const smb& variable = query_smb(variable_name);
            std::string variable_type = variable.type;
            if (variable.scope == "global") {
                if (variable_type == "int" && valueType == "int") {
                    mov4byte(rt(atoi(ops.c_str())), ptr_ip(variable_name));
                } else if (variable_type == "double" && variable_type == "int") {
                    mov2xmm0(ptr_ip(declare_ro_data("double", ops)));
                    xmm0mov(ptr_ip(variable_name));
                } else if (variable_type == "double" && variable_type == "double") {
                    mov2xmm0(ptr_ip(declare_ro_data("double", ops)));
                    xmm0mov(ptr_ip(variable_name));
                } else if (variable_type == "char" && variable_type == "char") {
                    printf("stack4bytes char : %c\n", ops[1]);
                    mov4byte(rt((int) ops[1]), ptr_ip(variable_name));
                } else if (variable_type == "string" && variable_type == "string") {
                    mov8byte(ptr(declare_ro_data("string", ops)), ptr_ip(variable_name));
                } else
                    yyerror(("error value type of "+variable_name).c_str());
            } else {
                int offset_bp = g_stack_address(variable_name);
                if (variable_type == "int" && valueType == "int") {
                    int2stack(atoi(ops.c_str()), offset_bp);
                } else if (variable_type == "double" && variable_type == "int") {
                    double2stack(ptr_ip(declare_ro_data("double", ops)), offset_bp);
                } else if (variable_type == "double" && variable_type == "double") {
                    double2stack(ptr_ip(declare_ro_data("double", ops)), offset_bp);
                } else if (variable_type == "char" && variable_type == "char") {
                    printf("stack4bytes char : %c\n", ops[1]);
                    int2stack((int) ops[1], offset_bp);
                } else if (variable_type == "string" && variable_type == "string") {
                    ptr2stack(ptr(declare_ro_data("string", ops)), offset_bp);
                } else
                    yyerror(("error value type of "+variable_name).c_str());
            }
        } else if (usage == 3) {

        } else if (usage == 4) {
            std::string function_name(getScopeBack());
            const smb& function_g = query_smb(function_name);
            std::string function_type = function_g.type;
//            printf(">> function name : %s\n", give_function().name.c_str());
            if (function_type == "int" && valueType == "int") {
                mov4byte(rt(atoi(ops.c_str())), r4("a"));
            } else if (function_type == "double" && valueType == "double") {
                mov2xmm0(ptr_ip(declare_ro_data("double", ops)));
            } else if (function_type == "char" && valueType == "char") {
                mov4byte(rt((int) ops[1]), r4("a"));
            } else if (function_type == "string" && valueType == "string") {
                mov8byte(ptr(declare_ro_data("string", ops)), r8("a"));
            } else {
                yyerror(("return " + function_type + ", but received " + ops + " [" + valueType + "]").c_str());
            }
        } else {
            yyerror("unknown right value usage type 2");
        }
        return;
    }
    //
    if (type != 1) {throw std::runtime_error("unknown tree node");}
    std::map<std::string, int> op_cal{{"*", 1}, {"/", 2}, {"+", 3}, {"-", 4}};
    std::map<std::string, int> op_jud{{">", 6}, {">=", 7}, {"<", 8}, {"<=", 9}, {"==", 10}, {"!=", 11}};
    std::map<std::string, int> op_boo{{"!", 12}, {"&&", 13}, {"||", 14}};
    // TODO: operator
    if (op_cal.find(ops) != op_cal.end()) {

        return;
    }
    if (op_jud.find(ops) != op_jud.end()) {

        return;
    }
    if (op_boo.find(ops) != op_boo.end()) {

        return;
    }

    throw std::runtime_error("nobody (processing) here");
}
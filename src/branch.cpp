#include "grammar.h"
#include "tree.h"
#include "basic_ds.h"

#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
#include <vector>
#include <map>

class branch {
public:
    static int global_branch_i;
    static int global_branch_inner_i;
    static int branch_deep;
    static std::map<int, std::vector<std::string>> branch_stack;
//    static std::vector<std::string> branch_stack;
//    static std::vector<std::string> branch_inner_stack;
};

int branch::global_branch_i = 0;
int branch::global_branch_inner_i = 0;
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
    std::string _r = ".Lx"+std::to_string(branch::branch_deep)+"."+std::to_string(branch::global_branch_inner_i++);
//    branch::branch_inner_stack.emplace_back(_r);
    return _r;
}
std::string branch_new() {
    std::string _r = ".L"+std::to_string(branch::branch_deep)+"."+std::to_string(branch::global_branch_i++);
//    branch::branch_stack.emplace_back(_r);
    return _r;
}

namespace lea_if {
    std::map<int, std::string> branch_labels;

    void allocate_label() {
        branch_labels[-1] = branch_new();
        branch_labels[-2] = branch_new();
        for (int i = 1; i < lea_if::back_seq_cmp.size(); i++) {
            int id = lea_if::back_seq_cmp[i];
            branch_labels[id] = branch_new_inner();
        }
    }
}

void subtree_compare(tree_node* subtree) {
    std::string ops = subtree->data;
    tree_node* left  = subtree->children[0];
    tree_node* right = subtree->children[1];
    if (ops == ">" && left->type == 4 && right->type == 2) { // variable + basic type
        std::string variable_name = left->data;
        const smb& variable_g = query_smb(variable_name);
        std::string variable_type = variable_g.type;
        std::string variable_address(variable_g.scope == "global" ? left->data : st(g_stack_address(left->data)));
        if (variable_type == "int" && right->sign_type == "int") {
            mov4byte(rt(atoi(right->data.c_str())), r4("a"));
            gas_cmp4bytes(variable_address, r4("a"));
        } else if (variable_type == "int" && right->sign_type == "double") {

        } else if (variable_type == "double" && right->sign_type == "int") {

        } else if (variable_type == "double" && right->sign_type == "double") {

        } else if (variable_type == "char" && right->sign_type == "char") {

        } else if (variable_type == "string" && right->sign_type == "string") {

        } else {
            yyerror("compare type error");
        }
    } else {
        yyerror(("unimplemented compare operation between " + left->data + " and " + right->data).c_str());
    }
}



void do_compare() {
    // TODO: generate gas code from comparing expression one by one
    //       This process is linear.
    //       Action: query from lea_if::compare_nodes by node id
    //////////////////////////////////////////////////////////////////////////////////
    std::vector<std::string> temp_gas;
    for (int i = 0; i < lea_if::back_seq_cmp.size(); i++) {
        int node_id = lea_if::back_seq_cmp[i];
        if (i != 0) {
            if (!contains(lea_if::branch_labels, node_id))
                throw std::runtime_error("no node id in branch label map");
            gas_cmd(lea_if::branch_labels[node_id] + ":");
        }
        if (!contains(lea_if::compare_nodes, node_id)) {yyerror("lack of node id");}
        subtree_compare(lea_if::compare_nodes[node_id]);
    }
}


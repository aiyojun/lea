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
//    std::string _r = ".Lx"+std::to_string(branch::branch_deep)+"."+std::to_string(branch::global_branch_inner_i++);
    std::string _r = ".L"+std::to_string(branch::global_branch_i++);
//    branch::branch_inner_stack.emplace_back(_r);
    return _r;
}
std::string branch_new() {
//    std::string _r = ".L"+std::to_string(branch::branch_deep)+"."+std::to_string(branch::global_branch_i++);
    std::string _r = ".L"+std::to_string(branch::global_branch_i++);
//    branch::branch_stack.emplace_back(_r);
    return _r;
}

namespace lea_if {
    std::map<int, std::string> branch_labels;

    void allocate_label() {
        branch_labels[-1] = branch_new();
        branch_labels[-2] = branch_new();
        for (unsigned int i = 1; i < lea_if::back_seq_cmp.size() - 2; i++) {
            int id = lea_if::back_seq_cmp[i];
            if (contains(lea_if::ref_node_id, id))
                branch_labels[id] = branch_new_inner();
        }
        std::string s_out;
        for (auto& pp : branch_labels) {
            s_out += "   " + pp.second + ":" + std::to_string(pp.first);
        }
        std::cout << "label : " << s_out << std::endl;
    }
}

void case_var_gt_num(tree_node* left, tree_node* right, std::tuple<int, int, int>& group, int next_node_id) {
    std::string variable_name = left->data;
    const smb& variable_g = query_smb(variable_name);
    std::string variable_type = variable_g.type;
    std::string variable_address(variable_g.scope == "global" ? left->data : st(g_stack_address(left->data)));
    if (variable_type == "int" && right->sign_type == "int") {
        mov4byte(rt(atoi(right->data.c_str())), r4("a"));
        gas_cmp4bytes(variable_address, r4("a"));
        if (next_node_id == -1) {
            if (std::get<1>(group) == -1) {
                gas_cmd("jg "+lea_if::branch_labels[std::get<2>(group)]);
            } else if (std::get<2>(group) == -1) {
                gas_cmd("jle "+lea_if::branch_labels[std::get<1>(group)]);
            } else {
                yyerror("discover and add the case");
            }
        } else {
            auto& next_group = lea_if::following[lea_if::compare_nodes[next_node_id]];
            if (std::get<1>(group) == std::get<0>(next_group)) {
                gas_cmd("jg "+lea_if::branch_labels[std::get<2>(group)]);
            } else if (std::get<2>(group) == std::get<0>(next_group)) {
                gas_cmd("jle "+lea_if::branch_labels[std::get<1>(group)]);
            } else {
                yyerror("discover and add the case");
            }
        }
    } else if (variable_type == "int" && right->sign_type == "double") {

    } else if (variable_type == "double" && right->sign_type == "int") {

    } else if (variable_type == "double" && right->sign_type == "double") {

    } else if (variable_type == "char" && right->sign_type == "char") {

    } else if (variable_type == "string" && right->sign_type == "string") {

    } else {
        yyerror("compare type error");
    }
}

void subtree_compare(int node_id, int next_node_id) {
    auto subtree = lea_if::compare_nodes[node_id];
    auto& group = lea_if::following[subtree];
    std::string ops = subtree->data;
    tree_node* left  = subtree->children[0];
    tree_node* right = subtree->children[1];
    if (ops == ">" && left->type == 4 && right->type == 2) { // variable + basic type
        case_var_gt_num(left, right, group, next_node_id);
    } else if (ops == "<" && left->type == 2 && right->type == 4) {
        case_var_gt_num(right, left, group, next_node_id);
    } else {
        yyerror(("unimplemented compare operation between " + left->data + " and " + right->data).c_str());
    }
}



void do_compare() {
    ////////////////////////////////////////////////////////////////
    /// TODO: generate gas code from comparing expression one by one
    ///       This process is linear.
    ///       Action: query from lea_if::compare_nodes by node id
    ////////////////////////////////////////////////////////////////
    std::vector<std::string> temp_gas;
    for (unsigned int i = 0; i < lea_if::back_seq_cmp.size() - 2; i++) {
        int node_id = lea_if::back_seq_cmp[i];
        int next_node_id = lea_if::back_seq_cmp[i+1];
        if (i != 0 && contains(lea_if::ref_node_id, node_id)) {
            if (!contains(lea_if::branch_labels, node_id))
                throw std::runtime_error("no node id in branch label map");
            gas_cmd(lea_if::branch_labels[node_id] + ":");
        }
        std::string s_out = "";
        for (auto & node : lea_if::compare_nodes) {
            s_out += " | " +  std::to_string(node.first);
        }
//        if (node_id != -1 && node_id != -2) {
        printf("s_out: %s ; %d\n", s_out.c_str(), node_id);
        if (!contains(lea_if::compare_nodes, node_id)) {
            yyerror("lack of node id");
        }
        if (i == lea_if::back_seq_cmp.size() - 3) {
            subtree_compare(node_id, -1);
        } else {
            subtree_compare(node_id, next_node_id);
        }
//        }
    }
    gas_cmd(lea_if::branch_labels[-1] + ":");
    gas_cmd(lea_if::branch_labels[-2] + ":");
}


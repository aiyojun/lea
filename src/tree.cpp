#include "grammar.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <tuple>
#include "tree.h"
#include "basic_ds.h"
#include "branch.h"

int tree_node::uuid = 0;
int tree_node::max_deep = 0;
tree_node* tree_node::root;

int tree_node::invoking_deep = 0;
std::map<int, std::vector<tree_node*>> tree_node::invoking_stack;
std::string tree_node::heap_register_name;

void tree_clear() {
//    printf("tree_clear\n");
    tree_node::uuid = 0;
    tree_node::max_deep = 0;
    tree_node::root = nullptr;
    tree_node::invoking_deep = 0;
    tree_node::invoking_stack.clear();
    tree_node::heap_register_name = "";
//    printf("tree_clear over , invoking_deep size : %d\n", (int) tree_node::invoking_stack.size());
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
//    printf("tree_node_deep_assign\n");
    tree_node::root = new tree_node();
    tree_node::root->type = 0;
    tree_node::root->data = "root";
    tree_node::root->deep = 0;
    tree_node::root->parent = nullptr;
    tree_node::root->children.emplace_back(tree_node::invoking_stack[0][0]);
    tree_node::invoking_stack[0][0]->parent = tree_node::root;
    recursion_deep(tree_node::root, 0);
//    printf("tree_node_deep_assign over\n");
}


//
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
                //                delete child;
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

std::map<std::string, int> calculation_operators{
    {"+", 1}, {"-", 2}, {"*", 3}, {"/", 4}
};

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

void tree_node_collect(std::vector<tree_node*>& vec, tree_node* node) {
    vec.emplace_back(node);
    if (!node->children.empty()) {
        for (auto& ptr : node->children) {
            tree_node_collect(vec, ptr);
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

namespace lea_if {
    std::set<int> ref_node_id;
    std::vector<int> back_seq;
    std::vector<int> back_seq_cmp;
    std::map<tree_node *, std::tuple<int, int, int>> following;
    std::map<tree_node *, int> back_point_s;
    std::map<tree_node *, int> back_point_f;
    std::map<int, tree_node *> compare_nodes;
    std::set<std::string> compare_op;
    std::set<std::string> boo_op;
    void on_create() {
        compare_op = {">", "<", ">=", "<=", "!=", "=="};
        boo_op = {"&&", "||", "!"};
        back_point_f.clear();
        back_point_s.clear();
        following.clear();
        back_seq.clear();
        back_seq_cmp.clear();
        compare_nodes.clear();
    }
    void generate_modifier::enter(tree_node *node) {
        if (node->type != 1) return;
        std::string ops = node->data;
        if (contains(boo_op, ops)) {
            back_seq.emplace_back(node->id);
            if (ops == "&&") {
                if (contains(back_point_s, node)) {
                } else if (contains(back_point_s, node->parent) && node->parent->type == 1 && node->parent->data == "||") {
                    back_point_s[node] = back_point_s[node->parent];
                    if (node->no + 1 < node->parent->children.size()) {
                        back_point_f[node] = node->parent->children[node->no + 1]->id;
                    } else {
                        back_point_f[node] = back_point_f[node->parent];
                    }
                } else {
                    printf("node parent %d %s\n", node->parent->id, node->parent->data.c_str());
                    yyerror("????");
                }
                for (int child_index = 0; child_index < node->children.size(); child_index++) {
                    auto child = node->children[child_index];
                    if (contains(compare_op, child->data)) {
                        if (child_index + 1 < node->children.size()) {
                            following[child] = std::tuple<int, int, int>(
                                    child->id, back_point_f[node], node->children[child_index + 1]->id);
                        } else if (child_index == node->children.size() - 1) {
                            following[child] = std::tuple<int, int, int>(
                                    child->id, back_point_f[node], back_point_s[node] );
                        }
                    }
                }
            } else if (ops == "||") {
                if (contains(back_point_s, node)) {
                } else if (contains(back_point_s, node->parent) && node->parent->type == 1 && node->parent->data == "&&") {
                    back_point_f[node] = back_point_f[node->parent];
                    if (node->no + 1 < node->parent->children.size()) {
                        back_point_s[node] = node->parent->children[node->no + 1]->id;
                    } else {
                        back_point_s[node] = back_point_s[node->parent];
                    }
                } else {
                    printf("node parent %d %s\n", node->parent->id, node->parent->data.c_str());
                    yyerror("????");
                }
                for (int child_index = 0; child_index < node->children.size(); child_index++) {
                    auto child = node->children[child_index];
                    if (contains(compare_op, child->data)) {
                        if (child_index + 1 < node->children.size()) {
                            following[child] = std::tuple<int, int, int>(
                                    child->id, node->children[child_index + 1]->id, back_point_s[node]);
                        } else if (child_index == node->children.size() - 1) {
                            following[child] = std::tuple<int, int, int>(
                                    child->id, back_point_f[node], back_point_s[node]);
                        }
                    }
                }
            }
        } else if (contains(compare_op, ops)) {
            back_seq.emplace_back(node->id);
            back_seq_cmp.emplace_back(node->id);
            compare_nodes[node->id] = node;
            std::cout << "compare node add " << node->id << std::endl;
        }
    }

    int find_from(const std::vector<int>& ok_v, const std::vector<int>& v, unsigned int i) {
        for (unsigned int j = i; j < v.size(); j++) {
            int id = v[j];
            if (contains(ok_v, id)) {
                return id;
            }
        }
        throw std::runtime_error("find from " + std::to_string(i) + " error");
    }

    int find_next(const std::vector<int>& ok_v, int id) {
        for (unsigned int i = 0; i < ok_v.size(); i++) {
            if (ok_v[i] == id) return ok_v[i + 1];
        }
        return -1;
    }

    void on_update() {
        std::map<int, int> replace_node_id;
        lea_if::back_seq.emplace_back(-1);
        lea_if::back_seq.emplace_back(-2);
        lea_if::back_seq_cmp.emplace_back(-1);
        lea_if::back_seq_cmp.emplace_back(-2);
        for (int i = 0; i < lea_if::back_seq.size(); i++) {
            int id = lea_if::back_seq[i];
            if (!contains(lea_if::back_seq_cmp, id)) {
                int next_id = find_from(lea_if::back_seq_cmp, lea_if::back_seq, i);
                replace_node_id[id] = next_id;
            }
        }
        lea_if::gen_boo_print();
        std::cout << "replacing map : ";
        for (auto& kv_i : replace_node_id) {
            std::cout << kv_i.first << "->" << kv_i.second << "   ";
        }
        std::cout << std::endl;
        for (auto& node_kv : lea_if::following) {
            std::tuple<int, int, int>& group = node_kv.second;
            int& failed  = std::get<1>(group);
            int& success = std::get<2>(group);
            if (!contains(lea_if::back_seq_cmp, failed)) {
                if (!contains(replace_node_id, failed))
                    throw std::runtime_error("no node id in replacing map");
                failed = replace_node_id[failed];
            }
            if (!contains(lea_if::back_seq_cmp, success)) {
                printf("++ success\n");
                if (!contains(replace_node_id, success))
                    throw std::runtime_error("no node id in replacing map");
                success = replace_node_id[success];
            }
        }
        for (unsigned i = 0; i < lea_if::back_seq_cmp.size() - 3; i++) {
            int next_node_id = lea_if::back_seq_cmp[i + 1];
            std::tuple<int, int, int>& group = lea_if::following[lea_if::compare_nodes[lea_if::back_seq_cmp[i]]];
            int& failed  = std::get<1>(group);
            int& success = std::get<2>(group);
            std::cout << "C:" << std::get<0>(group) << "; F: " << failed << "; S: " << success << std::endl;
            if (failed!=-1 && failed!=-2 && contains(lea_if::back_seq_cmp, failed) && failed != next_node_id) {
                lea_if::ref_node_id.insert(failed);
            }
            if (success!=-1 && success!=-2 && contains(lea_if::back_seq_cmp, success) && success != next_node_id) {
                lea_if::ref_node_id.insert(success);
            }
        }
        std::string ss_out;
        for (auto& pp : lea_if::ref_node_id) {
            ss_out += "  " + std::to_string(pp);
        }
        std::cout << "ref node : " << ss_out << std::endl;
    }

    void gen_boo(tree_node* node) {
        on_create();
        auto ptr = node->children[0];
        if (ptr->type == 1 && (ptr->data == "&&" || ptr->data == "||")) {
            back_point_s[ptr] = -1; // self branch
            back_point_f[ptr] = -2; // next branch
        } else {
            yyerror("?002");
        }
        std::set<tree_node*> recording;
        reduce_subtree(0, recording, node->children[0], node->children[0], new generate_modifier());
        on_update();
    }

    void gen_boo_print() {
        std::cout << "** simu gas:" << std::endl;
        for (auto& kv : following) {
            std::cout
            << "cmp: o " << std::get<0>(kv.second) << std::endl
            << "->F: o " << std::get<1>(kv.second) << std::endl
            << "->S: o " << std::get<2>(kv.second) << std::endl
            ;
        }
        std::cout << "** -1 : self branch ; -2 : next branch." << std::endl;
        std::cout << "** node seq     : " << join(", ", to_vs(back_seq)) << std::endl;
        std::cout << "** node seq cmp : " << join(", ", to_vs(back_seq_cmp)) << std::endl;
    }
}

void do_simple_compare(tree_node* node) { // > < >= <= != ==
    if (node->type != 1) return;
    std::string ops = node->data;
    tree_node* p0 = node->children[0];
    tree_node* p1 = node->children[1];
    if (ops == ">") {

    }
//    gas_cmp4bytes();
    gas_cmd("sete al");
}

void do_multi_compare(tree_node* subtree) { // and or => if (...)

}

/** value tree parsing & evaluation & generating */
void evaluation() {
    // TODO: use tree left recursion with node exit-processing

}

std::map<tree_node*, std::tuple<std::string, std::string, std::string>> stored_result;
void add_variable_number(tree_node* op_node, tree_node* v_node, tree_node* n) {
    if (v_node->type == 4) {
        std::string label;
        std::string scope;
        std::string variable_type;
        expected_variable(v_node->data, variable_type, scope, label);
        if (variable_type == "int" && n->sign_type == "int") {
            mov4byte(rt(atoi(n->data.c_str())), r4("a"));
            gas_add4bytes(label, r4("a"));
            stored_result[op_node] = std::tuple<std::string, std::string, std::string>(r4("a"), "", "");
        } else if (variable_type == "int" && n->sign_type == "double") {

        }
    } else if (v_node->type == 1) {

    } else if (v_node->type == 3) {

    } else {
        yyerror("");
    }
}

/** Don't modify the tree structure */
// name,type,value
//std::vector<std::tuple<std::string, std::string, std::string>> evaluation_stack;
void evaluation_modifier::modify(tree_node *node) { // + - * /
    if (node->type == 3) {

    } else if (node->type == 1 && contains(std::vector<std::string>{"+","-","*","/"}, node->data)) {
        // + - * /

    }
}

/** prepare many helper functions to reduce code of operating */
void expected_variable(cstring name, std::string &type, std::string& scope, std::string& label) {
    const smb& variable_g = give_variable();
    type = variable_g.type;
    scope = variable_g.scope;
    if (g_stack_has(name))
        label = st(g_stack_address(name));
    else if (variable_g.scope == "global") {
        label = name;
    } else yyerror("");
}

void push_stack_variable(cstring name, cstring type, cstring gas_src) {
    if (type == "int") {
        stack4bytes(name, gas_src);
    } else if (type == "double") {
        stack8bytes(name, gas_src);
    } else if (type == "char") {
        stack4bytes(name, gas_src);
    } else if (type == "bool") {
        stack4bytes(name, gas_src);
    } else if (type == "string") {
        std::string _ptr = declare_ro_data("string", gas_src);
        stack8bytes(name, ptr(_ptr));
    } else {
        yyerror("unknown basic type");
    }
}

void do_assign(int usage) {
    const smb& variable_g = give_variable();
    std::string variable_type = variable_g.type;
    std::string variable_name = variable_g.name;
    // TODO: step 1. analysis variable's type
    //       step 2. analysis leaVal
    //       step 3. generate code
    recursion_deep(tree_node::root, 0);
    tree_node* leader = tree_node::root->children[0];
    if (tree_node::max_deep == 1 && leader->type == 2) {
        std::string imm = rt(atoi(leader->data.c_str()));
        if (variable_type == "int" && leader->sign_type == "int") {
            if (usage == 1) {
                stack4bytes(variable_name, imm);
            } else {
                if (g_stack_has(variable_name)) {
                    mov4byte(imm, st(g_stack_address(variable_name)));
                } else if (variable_g.scope == "global") {
                    mov4byte(imm, ptr_ip(variable_name));
                } else {
                    yyerror(("variable ["+variable_name+"] isn't in stack and global scope!").c_str());
                }
            }
        } else if (variable_type == "int" && leader->sign_type == "double") {

        } else if (variable_type == "double" && leader->sign_type == "int") {

        } else if (variable_type == "double" && leader->sign_type == "double") {

        } else if (variable_type == "char" && leader->sign_type == "char") {

        } else if (variable_type == "string" && leader->sign_type == "string") {

        } else {
            yyerror(("cannot assign " + leader->data + " to " + variable_g.name).c_str());
        }
    } else if (tree_node::max_deep == 1 && leader->type == 4) {

    } else if (tree_node::max_deep == 1 && leader->type == 3) {

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
    rotate_boo(tree_node::root);
    recursion_deep(tree_node::root, 0);
    printf("// After rotate boo\n");
    reduce_clc(tree_node::root, new calculate_modifier);
    printf("// After reduce clc\n");
    tree_node_print();
    reduce_cmp(tree_node::root, new compare_modifier);
    printf("// After reduce cmp\n");
    tree_node_print();
    reduce_boo(tree_node::root, new boo_modifier);
    printf("// After reduce boo\n");
    tree_node_print();
    std::set<tree_node*> recording;
    forecast_boo(0, recording, tree_node::root->children[0], tree_node::root->children[0]);
    printf("// After forecast boo\n");
        tree_node_print();
    if (usage == 3) {
        printf("// After gen\n");
        subtree_remove_paren(0, tree_node::root);
        tree_node_print();
        lea_if::gen_boo(tree_node::root);
        lea_if::gen_boo_print();

        lea_if::allocate_label();
        do_compare();
    } else if (usage == 1) {
        do_assign(usage);
    } else if (usage == 2) {

    } else if (usage == 4) {

    }
}
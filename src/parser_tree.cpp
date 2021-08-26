#include "grammar.h"
#include <stdio.h>
#include <string>
#include <vector>
#include <set>
// necessary functions
template<typename T>
bool contains(std::set<T> container, T key)
{return container.find(key) != container.end();}
// operator classify
namespace lea_op {
    std::set<std::string> boo {"&&", "||", "!", "()"};
    std::set<std::string> compare {">", "<", ">=", "<=", "!=", "==", "()"};
    std::set<std::string> calculate {"+", "-", "*", "/", "()"};
}
// data type classify
namespace lea_type {
    std::set<std::string> numberType {"int", "double"};
}

// TODO: core logic
//       1. make bool binary subtree been multi-subtree
//       2. reduce calculate subtree (binary tree)
//       3. reduce compare subtree (binary tree)
//       4. reduce bool subtree (multi-tree)
// Part 1. reduce tree - calculate rt number
void reduce_clc(tree_node* subtree, subtree_modifier* modifier_clc) {
    if (subtree->children.empty()) return;
    if (subtree_is_clc(subtree)) {
        std::set<tree_node*> recording;
        reduce_subtree(0, recording, subtree, subtree, modifier_clc);
        return;
    }
    for (tree_node* every : subtree->children) reduce_clc(every, modifier_clc);
}

void reduce_cmp(tree_node* subtree, subtree_modifier* modifier_cmp) {
    if (subtree->children.empty()) return;
    if (subtree_is_cmp(subtree)) {
        std::set<tree_node*> recording;
        reduce_subtree(0, recording, subtree, subtree, modifier_cmp);
        return;
    }
    for (tree_node* every : subtree->children) reduce_cmp(every, modifier_cmp);
}

void reduce_boo(tree_node* subtree, subtree_modifier* modifier_boo) {
    if (subtree->children.empty()) return;
    if (subtree_is_boo(subtree)) {
        std::set<tree_node*> recording;
        reduce_subtree(0, recording, subtree, subtree, modifier_boo);
        return;
    }
    for (tree_node* every : subtree->children) reduce_boo(every, modifier_boo);
}

void forecast_boo(int debug_deep, std::set<tree_node*>& recording, tree_node* node, tree_node* root) {
    if (recording.find(node) != recording.end()) {
        recording.erase(node);
        tree_node* node_parent;
        bool is_root = false;
        if (node == root) is_root = true; else node_parent = node->parent;

        if (node->type == 1) {
            std::string ops = node->data;
            if (ops == "&&" || ops == "||") {
                bool hasFalse = !(ops == "&&");
                std::set<int> true_v;
                int total = node->children.size();
                int true_number = 0;
                for (int i = 0; i < node->children.size(); i++) {
                    auto* ptr = node->children[i];
                    if (ptr->type == 2 && ptr->data == (ops == "&&" ? "false" : "true")) {
                        hasFalse = true;
                        break;
                    } else if (ptr->type == 2 && ptr->data == (ops == "&&" ? "true" : "false")) {
                        true_v.insert(i);
                        true_number++;
                    }
                }
                if (hasFalse) {
                    node->type = 2;
                    node->data = ops == "&&" ? "false" : "true";
                    for (auto& child : node->children) {child->parent = nullptr;}
                    node->children.clear();
                } else if (total == true_number) {
                    node->type = 2;
                    node->data = ops == "&&" ? "true" : "false";
                    for (auto& child : node->children) {child->parent = nullptr;}
                    node->children.clear();
                } else if (!true_v.empty()) {
                    std::vector<tree_node*> tmp;
                    for (int i = 0; i < node->children.size(); i++) {
                        if (true_v.find(i) == true_v.end()) {
                            auto& child = node->children[i];
                            tmp.emplace_back(child);
                            child->no = tmp.size() - 1;
                        }
                    }
                    node->children.swap(tmp);
                }

            } else if (ops == "()") {
                tree_node* p0 = node->children[0];
                p0->parent = node->parent;
                p0->no = node->no;
                p0->deep = p0->parent->deep + 1;
                p0->parent->children[node->no] = p0;
                node->parent = nullptr;
            }
        }
        if (!is_root) forecast_boo(debug_deep - 1, recording, node_parent, root);
        return;
    }
    recording.insert(node);
    if (node->type == 1) {
        forecast_boo(debug_deep+1, recording, node->children[0], root);
    } else if (node == root) {
        recording.erase(node);
    } else if (node->no + 1 < node->parent->children.size()) {
        recording.erase(node);
        forecast_boo(debug_deep, recording, node->parent->children[node->no + 1], root);
    } else if (node->no + 1 >= node->parent->children.size()) {
        recording.erase(node);
        forecast_boo(debug_deep - 1, recording, node->parent, root);
    }
}


/**
 * inner implement
 */
__TopTree bool subtree_is_clc(tree_node* subtree) {
    if (subtree->children.empty()) {
        return subtree->type == 2 && contains(lea_type::numberType, subtree->sign_type);
    }
    if (contains(lea_op::calculate, subtree->data)) {
        for (auto& child : subtree->children) {
            if (!subtree_is_clc(child)) return false;
        }
        return true;
    }
    return false;
}
__TopTree bool subtree_is_cmp(tree_node* subtree) {
    if (subtree->children.empty()) return subtree->type == 2;
    if (contains(lea_op::compare, subtree->data)) {
        for (auto& child : subtree->children) {
            if (!subtree_is_cmp(child)) return false;
        }
        return true;
    }
    return false;
}
__TopTree bool subtree_is_boo(tree_node* subtree) {
    if (subtree->children.empty()) return subtree->type == 2;
    if (contains(lea_op::boo, subtree->data)) {
        for (auto& child : subtree->children) {
            if (!subtree_is_boo(child)) return false;
        }
        return true;
    }
    return false;
}

void reduce_subtree(
        int debug_deep, std::set<tree_node*>& recording,
        tree_node* root, tree_node* node,
        subtree_modifier* modifier) {
    if (recording.find(node) != recording.end()) {  // exit node
        recording.erase(node);
        bool is_root = false;
        tree_node* node_parent;
        if (node == root) is_root = true; else node_parent = node->parent;

        modifier->modify(node);  // TODO: core logic

        if (!is_root) {reduce_subtree(debug_deep+1, recording, root, node_parent, modifier);}
        return;
    }
    recording.insert(node);  // entry node
    if (!node->children.empty()) {
        reduce_subtree(debug_deep+1, recording, root, node->children[0], modifier);
    } else if (node->children.empty() && node->parent == root) {  // root exit
        recording.erase(node);
    } else if (node->children.empty() && node->no + 1 < node->parent->children.size()) { // && node->parent != root
        recording.erase(node); reduce_subtree(debug_deep+1, recording, root, node->parent->children[node->no + 1], modifier);
    } else if (node->children.empty() && node->no + 1 >= node->parent->children.size()) { //&& node->parent != root
        recording.erase(node); reduce_subtree(debug_deep+1, recording, root, node->parent, modifier);
    }
}

void calculate_modifier::modify(tree_node* node) {
    std::string ops = node->data;
    if (contains(lea_op::calculate, ops) && ops != "()") {
        tree_node* p0 = node->children[0];
        tree_node* p1 = node->children[1];
        auto ptr = new tree_node();
        ptr->type = 2;
        ptr->deep = node->deep + 1;
        ptr->parent = node->parent;
        ptr->no = node->no;
        ptr->parent->children[ptr->no] = ptr;
        if (ops == "+" && p0->sign_type == "int" && p1->sign_type == "int") {
            ptr->sign_type = "int";
            ptr->data = std::to_string(atoi(p0->data.c_str()) + atoi(p1->data.c_str()));
        } else if (ops == "+" && p0->sign_type == "int" && p1->sign_type == "double") {
            ptr->sign_type = "double";
            ptr->data = std::to_string(atoi(p0->data.c_str()) + atof(p1->data.c_str()));
        } else if (ops == "+" && p0->sign_type == "double" && p1->sign_type == "int") {
            ptr->sign_type = "double";
            ptr->data = std::to_string(atof(p0->data.c_str()) + atoi(p1->data.c_str()));
        } else if (ops == "+" && p0->sign_type == "double" && p1->sign_type == "double") {
            ptr->sign_type = "double";
            ptr->data = std::to_string(atof(p0->data.c_str()) + atof(p1->data.c_str()));
        } else if (ops == "-" && p0->sign_type == "int" && p1->sign_type == "int") {
            ptr->sign_type = "int";
            ptr->data = std::to_string(atoi(p0->data.c_str()) - atoi(p1->data.c_str()));
        } else if (ops == "-" && p0->sign_type == "int" && p1->sign_type == "double") {
            ptr->sign_type = "double";
            ptr->data = std::to_string(atof(p0->data.c_str()) - atof(p1->data.c_str()));
        } else if (ops == "-" && p0->sign_type == "double" && p1->sign_type == "int") {
            ptr->sign_type = "double";
            ptr->data = std::to_string(atof(p0->data.c_str()) - atoi(p1->data.c_str()));
        } else if (ops == "-" && p0->sign_type == "double" && p1->sign_type == "double") {
            ptr->sign_type = "double";
            ptr->data = std::to_string(atof(p0->data.c_str()) - atof(p1->data.c_str()));
        } else if (ops == "*" && p0->sign_type == "int" && p1->sign_type == "int") {
            ptr->sign_type = "int";
            ptr->data = std::to_string(atoi(p0->data.c_str()) * atoi(p1->data.c_str()));
        } else if (ops == "*" && p0->sign_type == "int" && p1->sign_type == "double") {
            ptr->sign_type = "double";
            ptr->data = std::to_string(atof(p0->data.c_str()) * atof(p1->data.c_str()));
        } else if (ops == "*" && p0->sign_type == "double" && p1->sign_type == "int") {
            ptr->sign_type = "double";
            ptr->data = std::to_string(atof(p0->data.c_str()) * atoi(p1->data.c_str()));
        } else if (ops == "*" && p0->sign_type == "double" && p1->sign_type == "double") {
            ptr->sign_type = "double";
            ptr->data = std::to_string(atof(p0->data.c_str()) * atof(p1->data.c_str()));
        }  else if (ops == "/" && p0->sign_type == "int" && p1->sign_type == "int") {
            ptr->sign_type = "int";
            ptr->data = std::to_string(atoi(p0->data.c_str()) / atoi(p1->data.c_str()));
        } else if (ops == "/" && p0->sign_type == "int" && p1->sign_type == "double") {
            ptr->sign_type = "double";
            ptr->data = std::to_string(atof(p0->data.c_str()) / atof(p1->data.c_str()));
        } else if (ops == "/" && p0->sign_type == "double" && p1->sign_type == "int") {
            ptr->sign_type = "double";
            ptr->data = std::to_string(atof(p0->data.c_str()) / atoi(p1->data.c_str()));
        } else if (ops == "/" && p0->sign_type == "double" && p1->sign_type == "double") {
            ptr->sign_type = "double";
            ptr->data = std::to_string(atof(p0->data.c_str()) / atof(p1->data.c_str()));
        } else
            yyerror("??? 01");
    } else if (ops == "()") {
        tree_node* p0 = node->children[0];
        p0->parent = node->parent;
        p0->no = node->no;
        p0->deep = p0->parent->deep + 1;
        p0->parent->children[node->no] = p0;
        node->parent = nullptr;
    } else
        yyerror(("??? impossible branch " + ops).c_str());
}

void compare_modifier::modify(tree_node *node) {

    std::string ops = node->data;
    if (contains(lea_op::compare, ops) && ops != "()") {
        tree_node* p0 = node->children[0];
        tree_node* p1 = node->children[1];
        auto ptr = new tree_node();
        ptr->type = 2;
        ptr->sign_type = "bool";
        ptr->parent = node->parent;
        ptr->deep = node->parent->deep + 1;
        ptr->no = node->no;
        ptr->parent->children[ptr->no] = ptr;
        node->parent = nullptr;
        if (ops == ">") {
            if (p0->sign_type == "int" || p1->sign_type == "int") {
                ptr->data = (atoi(p0->data.c_str()) > atoi(p1->data.c_str())) ? "true" : "false";
            } else if (p0->sign_type == "int" || p1->sign_type == "double") {
                ptr->data = (atoi(p0->data.c_str()) > atof(p1->data.c_str())) ? "true" : "false";
            } else if (p0->sign_type == "double" || p1->sign_type == "int") {
                ptr->data = (atof(p0->data.c_str()) > atoi(p1->data.c_str())) ? "true" : "false";
            } else if (p0->sign_type == "double" || p1->sign_type == "double") {
                ptr->data = (atof(p0->data.c_str()) > atof(p1->data.c_str())) ? "true" : "false";
            } else {
                yyerror("compare type error >");
            }
        } else if (ops == ">=") {
            if (p0->sign_type == "int" || p1->sign_type == "int") {
                ptr->data = (atoi(p0->data.c_str()) >= atoi(p1->data.c_str())) ? "true" : "false";
            } else if (p0->sign_type == "int" || p1->sign_type == "double") {
                ptr->data = (atoi(p0->data.c_str()) >= atof(p1->data.c_str())) ? "true" : "false";
            } else if (p0->sign_type == "double" || p1->sign_type == "int") {
                ptr->data = (atof(p0->data.c_str()) >= atoi(p1->data.c_str())) ? "true" : "false";
            } else if (p0->sign_type == "double" || p1->sign_type == "double") {
                ptr->data = (atof(p0->data.c_str()) >= atof(p1->data.c_str())) ? "true" : "false";
            } else {
                yyerror("compare type error >=");
            }
        } else if (ops == "<") {
            if (p0->sign_type == "int" || p1->sign_type == "int") {
                ptr->data = (atoi(p0->data.c_str()) < atoi(p1->data.c_str())) ? "true" : "false";
            } else if (p0->sign_type == "int" || p1->sign_type == "double") {
                ptr->data = (atoi(p0->data.c_str()) < atof(p1->data.c_str())) ? "true" : "false";
            } else if (p0->sign_type == "double" || p1->sign_type == "int") {
                ptr->data = (atof(p0->data.c_str()) < atoi(p1->data.c_str())) ? "true" : "false";
            } else if (p0->sign_type == "double" || p1->sign_type == "double") {
                ptr->data = (atof(p0->data.c_str()) < atof(p1->data.c_str())) ? "true" : "false";
            } else {
                yyerror("compare type error <");
            }
        } else if (ops == "<=") {
            if (p0->sign_type == "int" || p1->sign_type == "int") {
                ptr->data = (atoi(p0->data.c_str()) <= atoi(p1->data.c_str())) ? "true" : "false";
            } else if (p0->sign_type == "int" || p1->sign_type == "double") {
                ptr->data = (atoi(p0->data.c_str()) <= atof(p1->data.c_str())) ? "true" : "false";
            } else if (p0->sign_type == "double" || p1->sign_type == "int") {
                ptr->data = (atof(p0->data.c_str()) <= atoi(p1->data.c_str())) ? "true" : "false";
            } else if (p0->sign_type == "double" || p1->sign_type == "double") {
                ptr->data = (atof(p0->data.c_str()) <= atof(p1->data.c_str())) ? "true" : "false";
            } else {
                yyerror("compare type error <=");
            }
        } else if (ops == "!=") {
            if (p0->sign_type == "int" || p1->sign_type == "int") {
                ptr->data = (atoi(p0->data.c_str()) != atoi(p1->data.c_str())) ? "true" : "false";
            } else if (p0->sign_type == "int" || p1->sign_type == "double") {
                ptr->data = (atoi(p0->data.c_str()) != atof(p1->data.c_str())) ? "true" : "false";
            } else if (p0->sign_type == "double" || p1->sign_type == "int") {
                ptr->data = (atof(p0->data.c_str()) != atoi(p1->data.c_str())) ? "true" : "false";
            } else if (p0->sign_type == "double" || p1->sign_type == "double") {
                ptr->data = (atof(p0->data.c_str()) != atof(p1->data.c_str())) ? "true" : "false";
            } else if (p0->sign_type == "string" || p1->sign_type == "string") {
                ptr->data = (p0->data != p1->data) ? "true" : "false";
            } else if (p0->sign_type == "char" || p1->sign_type == "char") {
                ptr->data = (p0->data != p1->data) ? "true" : "false";
            } else if (p0->sign_type == "bool" || p1->sign_type == "bool") {
                ptr->data = (p0->data != p1->data) ? "true" : "false";
            } else {
                yyerror("compare type error !=");
            }
        } else if (ops == "==") {
            if (p0->sign_type == "int" || p1->sign_type == "int") {
                ptr->data = (atoi(p0->data.c_str()) == atoi(p1->data.c_str())) ? "true" : "false";
            } else if (p0->sign_type == "int" || p1->sign_type == "double") {
                ptr->data = (atoi(p0->data.c_str()) == atof(p1->data.c_str())) ? "true" : "false";
            } else if (p0->sign_type == "double" || p1->sign_type == "int") {
                ptr->data = (atof(p0->data.c_str()) == atoi(p1->data.c_str())) ? "true" : "false";
            } else if (p0->sign_type == "double" || p1->sign_type == "double") {
                ptr->data = (atof(p0->data.c_str()) == atof(p1->data.c_str())) ? "true" : "false";
            } else if (p0->sign_type == "string" || p1->sign_type == "string") {
                ptr->data = (p0->data == p1->data) ? "true" : "false";
            } else if (p0->sign_type == "char" || p1->sign_type == "char") {
                ptr->data = (p0->data == p1->data) ? "true" : "false";
            } else if (p0->sign_type == "bool" || p1->sign_type == "bool") {
                ptr->data = (p0->data == p1->data) ? "true" : "false";
            } else {
                yyerror("compare type error !=");
            }
        }
    } else if (ops == "()") {
        tree_node* p0 = node->children[0];
        p0->parent = node->parent;
        p0->no = node->no;
        p0->deep = p0->parent->deep + 1;
        p0->parent->children[node->no] = p0;
        node->parent = nullptr;
    } else {
        yyerror(("??? impossible compare branch " + ops).c_str());
    }
}

void boo_modifier::modify(tree_node *node) {
    std::string ops = node->data;
    if (ops == "&&") {
        auto ptr = new tree_node();
        ptr->type = 2;
        ptr->sign_type = "bool";
        ptr->no = node->no;
        ptr->parent = node->parent;
        ptr->deep = ptr->parent->deep + 1;
        ptr->parent->children[ptr->no] = ptr;
        bool result = true;
        for (auto& child : node->children) {
            if (child->data == "false" || child->data != "true") {
                result = false; break;
            }
        }
        ptr->data = result ? "true" : "false";
    } else if (ops == "||") {
        auto ptr = new tree_node();
        ptr->type = 2;
        ptr->sign_type = "bool";
        ptr->no = node->no;
        ptr->parent = node->parent;
        ptr->deep = ptr->parent->deep + 1;
        ptr->parent->children[ptr->no] = ptr;
        bool result = false;
        for (auto& child : node->children) {
            if (child->data == "true") {
                result = true; break;
            }
        }
        ptr->data = result ? "true" : "false";
    } else if (ops == "!") {
        yyerror("not implement operator");
    } else if (ops == "()") {
        tree_node* p0 = node->children[0];
        p0->parent = node->parent;
        p0->no = node->no;
        p0->deep = p0->parent->deep + 1;
        p0->parent->children[node->no] = p0;
        node->parent = nullptr;
    } else {
        yyerror(("??? impossible boo branch " + ops).c_str());
    }
}

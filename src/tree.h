#ifndef __tree_h__
#define __tree_h__

typedef const std::string& cstring;

#include <vector>
#include <string>
#include <map>
#include <set>

// tree
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

    /** 8.25.2021 for invoking */
    std::string expect_type;

    /** tree management */
    static int max_deep;
    static tree_node* root;

    /** prepared for nest invoking */
    static int invoking_deep;
    //    static std::map<int, tree_node*> invoking_stack_query;
    static std::map<int, std::vector<tree_node*>> invoking_stack;
    static std::string heap_register_name;
};

// tree processing
void recursion_deep(tree_node* node, int depth);
// processing bool expression
bool without_boo(const std::vector<tree_node*>& vec, cstring sym);
void rotate_subtree_boo(tree_node* node, cstring ops);
void rotate_boo(tree_node* node);
//void tree_modify_boo(tree_node* node, cstring ops);
//void tree_recursion_boo(tree_node* node);
// recollect nodes of the tree
void tree_node_collect(std::vector<tree_node*>& vec, tree_node* node);

void subtree_print(tree_node* subtree);

//
// parser_tree.cpp
#define __TopTree

__TopTree bool subtree_is_clc(tree_node* subtree);
__TopTree bool subtree_is_cmp(tree_node* subtree);
__TopTree bool subtree_is_boo(tree_node* subtree);
__TopTree void subtree_remove_paren(int depth, tree_node* subtree);

class subtree_modifier {
public:
    virtual void enter(tree_node*) = 0;
    virtual void modify(tree_node*) = 0;
};
class calculate_modifier : public subtree_modifier {
public:
    void enter(tree_node *) override {};
    void modify(tree_node* node) override;
};
class compare_modifier : public subtree_modifier {
public:
    void enter(tree_node *) override {};
    void modify(tree_node* node) override;
};
class boo_modifier : public subtree_modifier {
public:
    void enter(tree_node *) override {};
    void modify(tree_node* node) override;
};

namespace lea_if {
    extern std::vector<int> back_seq;
    extern std::vector<int> back_seq_cmp;
    extern std::map<tree_node *, std::tuple<int, int, int>> following;
    extern std::map<tree_node *, int> back_point_s;
    extern std::map<tree_node *, int> back_point_f;
    extern std::map<int, tree_node *> compare_nodes;
    extern std::set<std::string> compare_op;
    extern std::set<std::string> boo_op;
    class generate_modifier : public subtree_modifier {
    public:
        void enter(tree_node *) override;
        void modify(tree_node *) override {};
    };
}

void reduce_subtree(
        int debug_deep, std::set<tree_node*>& recording,
        tree_node* root, tree_node* node,
        subtree_modifier* modifier);

void reduce_clc(tree_node* subtree, subtree_modifier* modifier_clc);
void reduce_cmp(tree_node* subtree, subtree_modifier* modifier_cmp);
void reduce_boo(tree_node* subtree, subtree_modifier* modifier_boo);

void forecast_boo(
        int debug_deep, std::set<tree_node*>& recording, tree_node* node, tree_node* root);


#endif//__tree_h__
#ifndef __tree_node_h__
#define __tree_node_h__

#include <vector>
#include <string>
typedef const std::string& cstring;
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
    // static std::map<int, std::vector<tree_node*>> invoking_chain;
};

class tree {
public:
	// void clear();
	// void invoking_deep_inc();
	// void invoking_deep_dec();
	// void heap_register(const char* id);
};

void tree_clear();
void invoking_deep_inc();
void invoking_deep_dec();
void heap_register(const char* fun);
void heap_variable();
void heap_invoking();
void heap_invoking_args_link();
void tree_node_create(const char* prefix, const char* value, const char* type);
void tree_node_link(const char* op);
void tree_node_chain();
void tree_node_deep_assign();
void tree_node_print();
void tree_analysis(int usage);

// tree processing
void recursion_deep(tree_node* node, int depth);
// processing bool expression
bool without_boo(const std::vector<tree_node*>& vec, cstring sym);
void rotate_subtree_boo(tree_node* node, cstring ops);
void rotate_boo(tree_node* node);
//void tree_modify_boo(tree_node* node, cstring ops);
//void tree_recursion_boo(tree_node* node);
// recollect nodes of the tree
// void tree_node_collect(std::vector<tree_node*>& vec, tree_node* node);
void tree_node_collect_v2(std::vector<tree_node*>& vec, tree_node* node, int deep, int& max_deep);

void subtree_print(tree_node* subtree);

#endif//__tree_node_h__
#ifndef __ast_h__
#define __ast_h__

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
};

class AST {
public:
	static AST self;
	tree_node* create_node(cstring);
	void link_node(cstring);
	void link_inode();
	inline void clear() {ivk_depth = 0;ivk_stack.clear();};
	inline void enter_inode() {ivk_depth++;};
	inline void exit_inode() {ivk_depth--;};
	static void refresh(tree_node*, int, int&);
	static void capture(std::vector<tree_node*>&, tree_node*, int, int&);
	static void subtree_print(tree_node*);
	void print();

	int ivk_depth = 0;
	std::map<int, std::vector<tree_node*>> ivk_stack;
};

#endif//__ast_h__
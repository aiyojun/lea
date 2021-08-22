#include "grammar.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>

class tree_node {
public:
    int deep;
    tree_node *parent;
    std::vector<tree_node*> children;

    int type;
    std::string data;
    std::vector<std::string> stack_data;
};


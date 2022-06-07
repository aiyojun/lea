#ifndef __core_h__
#define __core_h__

#include <iostream>
#include <deque>
#include <string>
typedef const std::string& cstring;
#include <vector>
#include "json.hpp"

class AstNode {
public:
    std::string type;
    std::string text;
    AstNode* parent;
    std::vector<AstNode*> children;

    void assign(cstring type, cstring text, AstNode* parent);
    void append(AstNode* child);
};

class AstTree {
public:
    AstNode *root;
    AstNode *ptr;
    std::vector<AstNode*> stack;

    AstTree();
    void init();
    void merge(cstring nodeSign, int n=2);
    void pushStack(cstring type, cstring text);
    AstNode* popStack();

    void print();
    nlohmann::json loopUp(AstNode* node, int depth=0);
};

class TheImport {
public:
    int deps;
    int depth;

    void initDepth();
    void addDepth();
    int resetDepth();

    void init();
    void recordOne();
    int resetAll();
};

class RightValue {
public:
    std::vector<int> invokingArgs;
    void newArgsSpace();
    void addOneArg();
    int releaseArgsSpace();
};

extern AstTree* astTree;
extern RightValue *rightValue;
extern TheImport* importer;

void prepareCompiler();
void releaseCompiler();


#endif/*__core_h__*/
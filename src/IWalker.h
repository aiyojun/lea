#ifndef LEA_IWALKER_H
#define LEA_IWALKER_H

#include "antlr4-runtime.h"

using namespace antlr4;

class IWalker {
public:
    void setRoot(tree::ParseTree *node) { _root = node; }

    tree::ParseTree *root() { return _root; }

    virtual void onBeforeTree(tree::ParseTree *node) = 0;

    virtual void onAfterTree(tree::ParseTree *node) = 0;

    void walk(tree::ParseTree *node);

private:
    tree::ParseTree *_root;
};


#endif //LEA_IWALKER_H

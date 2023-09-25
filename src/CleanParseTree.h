#ifndef LEA_CLEANPARSETREE_H
#define LEA_CLEANPARSETREE_H

#include "IWalker.h"

class CleanParseTree : public IWalker {
public:
    virtual void onBeforeTree(tree::ParseTree *node) override;

    virtual void onAfterTree(tree::ParseTree *node) override;

    void clean();

private:
    std::vector<tree::ParseTree *> _newlines;
};


#endif //LEA_CLEANPARSETREE_H

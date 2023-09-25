#include "IWalker.h"

void IWalker::walk(tree::ParseTree *node) {
    if (node == nullptr) return;
    onBeforeTree(node);
    for (auto& child : node->children) walk(child);
    onAfterTree(node);
}
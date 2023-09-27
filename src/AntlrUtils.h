#ifndef LEA_ANTLRUTILS_H
#define LEA_ANTLRUTILS_H

#include "antlr4-runtime.h"

using namespace antlr4;

class AntlrUtils {
public:
    static bool isRule(tree::ParseTree *node, size_t index);
};


#endif //LEA_ANTLRUTILS_H

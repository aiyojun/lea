
#include "AntlrUtils.h"

bool AntlrUtils::isRule(tree::ParseTree *node, size_t index)
{ return RuleContext::is(node)
    && ((ParserRuleContext *) node)->getRuleIndex() == index; }

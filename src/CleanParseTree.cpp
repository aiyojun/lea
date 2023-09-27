#include "CleanParseTree.h"
#include "OnlyObjectOrientedParser.h"

void CleanParseTree::onBeforeTree(tree::ParseTree *node) {

    if (RuleContext::is(node) && (
            ((ParserRuleContext *) node)->getRuleIndex() == OnlyObjectOrientedParser::RuleNl ||
            ((ParserRuleContext *) node)->getRuleIndex() == OnlyObjectOrientedParser::RuleSemi
    )) {
        _newlines.emplace_back(node);
    }
}

void CleanParseTree::onAfterTree(tree::ParseTree *node) {

}

void CleanParseTree::clean() {
    walk(root());
}

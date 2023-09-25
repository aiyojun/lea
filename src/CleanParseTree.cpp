#include "CleanParseTree.h"
#include "OnlyObjectOrientedParser.h"

void CleanParseTree::onBeforeTree(tree::ParseTree *node) {

    if (RuleContext::is(node) && (
            ((ParserRuleContext *) node)->getRuleIndex() == OnlyObjectOrientedParser::RuleNl ||
            ((ParserRuleContext *) node)->getRuleIndex() == OnlyObjectOrientedParser::RuleSemi
    )) {
//        std::cout << "newline : " << node->getText() << std::endl;
        _newlines.emplace_back(node);
    }
//    std::cout << (typeid(node) == typeid(RuleContext *)) << RuleContext::is(node) << " " << node->getText()
//              << std::endl;
//    std::cout << (typeid(node) == typeid(OnlyObjectOrientedParser::NlContext *)) << std::endl;
//    if (((ParserRuleContext *) node)->getRuleIndex() == OnlyObjectOrientedParser::RuleNl ||
//        ((ParserRuleContext *) node)->getRuleIndex() == OnlyObjectOrientedParser::RuleSemi) {
//        _newlines.emplace_back(node);
//        std::cout << "newline : " << node->getText() << std::endl;
//    }
}

void CleanParseTree::onAfterTree(tree::ParseTree *node) {

}

void CleanParseTree::clean() {
    walk(root());
    std::cout << "useless node size : " << _newlines.size() << std::endl;
    for (auto* node : _newlines) {
//        std::remove_if(node->parent->children.begin(), node->parent->children.end(),
//                       [&node](tree::ParseTree *each) {return each == node;});
//        node->parent = nullptr;
//        delete node;
    }
}

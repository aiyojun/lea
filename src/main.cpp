#include <iostream>

#include "antlr4-runtime.h"
#include "OnlyObjectOrientedLexer.h"
#include "OnlyObjectOrientedParser.h"
#include "OnlyObjectOrientedBaseListener.h"
#include "CleanParseTree.h"

using namespace antlr4;


//void printNode(tree::ParseTree *node, int depth = 0) {
//    if (node == nullptr) return;
//    auto text = node->getText();
////    text.replace(text.begin(), text.end(), "");
//    if (node->children.empty()) {
//        std::cout << depth << "\t" << text << node. << std::endl;
//    }
//    for (int i = 0; i < node->children.size(); i++) {
//        printNode(node->children.at(i), depth + 1);
//    }
//}


int main(int argc, const char* argv[]) {
    std::cout << "-- antlr4-runtime" << std::endl;
    std::ifstream stream;
    stream.open(argv[1]);
    ANTLRInputStream input(stream);
    OnlyObjectOrientedLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    OnlyObjectOrientedParser parser(&tokens);


    tree::ParseTree *tree = parser.start();

//    printNode(tree);
//    OnlyObjectOrientedBaseListener listener;
//    tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);

    CleanParseTree cleaner;
    cleaner.setRoot(tree);
    cleaner.clean();

    std::cout << "clean complete.\n";

    std::cout << "Tree:\n" << tree->toStringTree(&parser, true)<< std::endl;

    return 0;
}
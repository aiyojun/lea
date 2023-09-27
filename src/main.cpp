#include <iostream>

#include "antlr4-runtime.h"
#include "OnlyObjectOrientedLexer.h"
#include "OnlyObjectOrientedParser.h"
#include "CleanParseTree.h"

using namespace antlr4;


class IRGenerator : public IWalker {
public:
    virtual void onBeforeTree(tree::ParseTree *node) override;
    virtual void onAfterTree(tree::ParseTree *node) override;
};

void IRGenerator::onBeforeTree(tree::ParseTree *node) {

}

void IRGenerator::onAfterTree(tree::ParseTree *node) {

}



int main(int argc, const char* argv[]) {
    std::cout << "-- antlr4-runtime" << std::endl;
    std::ifstream stream;
    stream.open(argv[1]);
    ANTLRInputStream input(stream);
    OnlyObjectOrientedLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    OnlyObjectOrientedParser parser(&tokens);


    tree::ParseTree *tree = parser.start();

    IRGenerator generator;
    generator.setRoot(tree);
    generator.walk(generator.root());

    std::cout << "clean complete.\n";

    std::cout << "Tree:\n" << tree->toStringTree(&parser, true)<< std::endl;

    return 0;
}
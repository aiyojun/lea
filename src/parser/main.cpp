#include <map>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <FlexLexer.h>
extern FlexLexer* lexer;
#include "build/rv.yacc.hh"
extern yy::parser* leaParser;
#include "core.h"


int main(int argc, char** argv)
{
    prepareCompiler();
    // std::stringstream bridge;
    // lexer->switch_streams(bridge, std::cout);
    leaParser->parse();
    std::cout << "Compiling is completed!\n";
    releaseCompiler();
    // delete lexer;
    // delete leaParser;
    
    return 0;
}
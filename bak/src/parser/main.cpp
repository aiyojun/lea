#include <map>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <FlexLexer.h>
extern FlexLexer* lexer;
#include "build/rv.yacc.hh"
extern yy::parser* leaParser;
// #include "core.h"
#include "lea.h"

extern long __LEA_LINE__;
extern long __LEA_CHAR__;


int main(int argc, char** argv)
{
    // prepareCompiler();
    // std::stringstream bridge;
    // lexer->switch_streams(bridge, std::cout);
    try {
        lea::LPrepare();
        leaParser->parse();
        std::cout << "Compiling is completed!\n";
    } catch (std::exception& e) {
        std::cout << std::to_string(__LEA_LINE__) + ":" + std::to_string(__LEA_CHAR__) + " " << e.what();
    }

    // releaseCompiler();
    // delete lexer;
    // delete leaParser;
    
    return 0;
}
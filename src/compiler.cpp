#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <fstream>
#include "grammar.h"
#include <FlexLexer.h>

FlexLexer* lexer = new yyFlexLexer;

#undef yyFlexLexer
#define yyFlexLexer ccFlexLexer
#include <FlexLexer.h>

FlexLexer* cc_lexer = new yyFlexLexer;

#include "lea.tab.hh"

yy::parser* yy_parser = new yy::parser;
int lealine = 1;
yy::parser::semantic_type yylval;

void yyerror(const char* s)
{
    char buf[512];
    get_expects_back(0, buf);
    printf("\033[31;1mGrammar error : %s; Token : %s; Line : %d.\033[0m\n", s, buf, lealine);
    exit(1);
}

void yy::parser::error(const std::string& msg) {
    yyerror(msg.c_str());
}

int yylex(yy::parser::semantic_type* value) {
    value->ycText = yylval.ycText;
    return lexer->yylex();
}

void printf_empty(const char *__restrict __format, ...) {}

int main(int argc, char **argv)
{
    std::stringstream bridge;
    std::ifstream istream;
    char output_file[512];
    if (argc >= 3){
        strcpy(output_file, argv[2]);
        file_writer::out = std::string(output_file);
        istream.open(argv[1]);
        cc_lexer->switch_streams(istream, bridge);
        lexer->switch_streams(bridge, std::cout);
//        yyin = fopen(argv[1], "r");
    } else if (argc == 2) {
        istream.open(argv[1]);
        cc_lexer->switch_streams(istream, bridge);
        lexer->switch_streams(bridge, std::cout);
//        yyin = fopen(argv[1], "r");
    }
    cc_lexer->yylex();
    std::cout << "cc lexer complete remove comments." << std::endl;
//    std::stringstream bridge;
//    cc_lexer->switch_streams();
//std::cout << "bridge: " << bridge.str() << std::endl;
    yy_parser->parse();
std::cout << "yy parser parse over" << std::endl;
//    yyparse();
//    fclose(yyin);
    istream.close();
    delete cc_lexer;
    delete lexer;
    delete yy_parser;
    return 0;
}
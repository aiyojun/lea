#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <FlexLexer.h>
extern bool openImp;
extern void set_raw_mode();
extern std::vector<std::string> implements;
extern FlexLexer* preLexer;
extern FlexLexer* lexer;
#include "module.tab.hh"
extern yy::parser* moduleParser;
extern void debug_println();

int main(int argc, char** argv)
{
	std::stringstream bridge;

	preLexer->switch_streams(std::cin, bridge);
	   lexer->switch_streams(bridge, std::cout);
	
	while (preLexer->yylex() != 0) {

	}

	// std::cout << "bridge : \n" << bridge.str() << std::endl;

	moduleParser->parse();

	debug_println();

	std::cout << "implements:" << std::endl;

	openImp = true;

	int index = 0;
	for (auto& implement : implements) {
		std::cout << "[IMP] " << index++ << "\n" << implement << std::endl;
		bridge.clear();
		bridge << "def func" << index << "{";
		bridge << implement;
		bridge << "}";
		moduleParser->parse();
		std::cout << "[IMP] over" << std::endl;
	}

	delete lexer;
	delete preLexer;
	delete moduleParser;
	
	return 0;
}
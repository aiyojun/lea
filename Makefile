LEX        =flex
YACC       =bison
CXX        =gcc
build_dir  =./build
option_inc =-I ./include

all: check_build clean lea.tab.o lex.yy.o grammar.o SymbolTable.o
	$(CXX) -o lea $(build_dir)/lea.tab.o $(build_dir)/lex.yy.o $(build_dir)/grammar.o $(build_dir)/SymbolTable.o -lstdc++

check_build:
	@if [ ! -d $(build_dir) ]; then mkdir -p $(build_dir); fi

lea.tab.o: lea.tab.c
	$(CXX) -o $(build_dir)/lea.tab.o -c $(build_dir)/lea.tab.c $(option_inc)

lex.yy.o: lex.yy.c
	$(CXX) -o $(build_dir)/lex.yy.o -c $(build_dir)/lex.yy.c $(option_inc)

grammar.o:
	$(CXX) -o $(build_dir)/grammar.o -c src/grammar.cpp $(option_inc)

SymbolTable.o:
	$(CXX) -o $(build_dir)/SymbolTable.o -c src/SymbolTable.cpp

lea.tab.c: lex.yy.c
	$(YACC) -o $(build_dir)/lea.tab.c -d grammar/lea.y -v

lex.yy.c:
	$(LEX) -o $(build_dir)/lex.yy.c grammar/lea.l

run:
	cat ./grammarSupport.lea | ./lea

clean:
	@rm -rf $(build_dir)/*


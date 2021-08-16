ASM        =as
LEX        =flex
YACC       =bison
CXX        =gcc
LEA        =./lea
build_dir  =./build
option_inc =-I .

all: check_build clean main.o lea.tab.o lex.yy.o syntax.o
	$(CXX) -o lea $(build_dir)/main.o $(build_dir)/lea.tab.o $(build_dir)/lex.yy.o $(build_dir)/syntax.o -lstdc++ -lc

check_build:
	@if [ ! -d $(build_dir) ]; then mkdir -p $(build_dir); fi

syntax.o:
	$(CXX) -o $(build_dir)/syntax.o -c syntax.cpp

main.o:
	$(CXX) -o $(build_dir)/main.o -c main.cpp

lea.tab.o: lea.tab.c
	$(CXX) -o $(build_dir)/lea.tab.o -c $(build_dir)/lea.tab.c $(option_inc)

lex.yy.o: lex.yy.c
	$(CXX) -o $(build_dir)/lex.yy.o -c $(build_dir)/lex.yy.c $(option_inc)

lea.tab.c: lex.yy.c
	$(YACC) -o $(build_dir)/lea.tab.c -d grammar/lea.y -v

lex.yy.c:
	$(LEX) -o $(build_dir)/lex.yy.c grammar/lea.l

clean:
	@rm -rf $(build_dir)/*

run:
	$(LEA) ../leapro/syntax.lea

main:
	@$(LEA) ../leapro/main.lea $(build_dir)/main.lea.asm >/dev/null
	$(ASM) -o $(build_dir)/main.lea.o $(build_dir)/main.lea.asm
	$(CXX) -o ../leapro/main.lea.run $(build_dir)/main.lea.o -lc -no-pie

# 	$(LEA) ../leapro/main.lea ../leapro/main.lea.as

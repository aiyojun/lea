LEX=flex
YACC=bison
CXX=gcc

all: clean lea.tab.o lex.yy.o

	$(CXX) -o lea lea.tab.o lex.yy.o

lea.tab.o: lea.tab.c
	$(CXX) -c lea.tab.c

lex.yy.o: lex.yy.c
	$(CXX) -c lex.yy.c

lea.tab.c: lex.yy.c
	$(YACC) -d lea.y

lex.yy.c:
	$(LEX) lea.l

clean:
	@rm -rf lea.tab.o lex.yy.o lea.tab.c lea.tab.h lex.yy.c


#!/bin/bash
mkdir -p test && cp *.cpp *.h ../../grammar/comment.l ../../grammar/syntax.l ../../grammar/syntax.y ../basic_ds.* test && cd test \
&& flex -+ -P mm -o comment.cc comment.l \
&& bison -L C++ -v -d syntax.y \
&& flex -+ syntax.l \
&& gcc ./lex.yy.cc ./syntax.tab.cc ./comment.cc ./main.cpp ./basic_ds.cpp ./AST.cpp -lstdc++ -lc -o parser
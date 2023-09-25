cmake_minimum_required(VERSION 3.0.0)

project(lea)

set(CMAKE_CXX_STANDARD 17)

include_directories(include include/antlr4-runtime gen)

#add_compile_options(-w)

add_executable(lea
        src/main.cpp
        src/IWalker.cpp
        gen/OnlyObjectOrientedLexer.cpp
        gen/OnlyObjectOrientedParser.cpp
        gen/OnlyObjectOrientedVisitor.cpp
        gen/OnlyObjectOrientedBaseVisitor.cpp
        gen/OnlyObjectOrientedListener.cpp
        gen/OnlyObjectOrientedBaseListener.cpp
        src/CleanParseTree.cpp
        src/CleanParseTree.h
        src/IR/lang.cpp
        src/IR/lang.h
)

target_link_libraries(lea C:/Users/jun.dai/Documents/GitHub/lea/lib/x64/antlr4-runtime.lib)


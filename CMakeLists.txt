cmake_minimum_required(VERSION 3.20)

project(lea)

set(CMAKE_CXX_STANDARD 11)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/)
set(BUILD_DIR ${EXECUTABLE_OUTPUT_PATH}/build)
set(LEA_COMPILER ${PROJECT_SOURCE_DIR}/lea)

add_compile_options(-Wall)

message("-- Preset lea compiler: ${LEA_COMPILER}")

execute_process(COMMAND mkdir -p ${BUILD_DIR})

add_custom_command(
        OUTPUT ${BUILD_DIR}/lex.yy.cc
        PRE_BUILD
        COMMAND flex -+ -o ${BUILD_DIR}/lex.yy.cc ${EXECUTABLE_OUTPUT_PATH}/grammar/lea.l
        COMMENT "Building lex lex.yy.c ccFlexLexer"
)

add_custom_command(
        OUTPUT ${BUILD_DIR}/lex.cc.cc
        PRE_BUILD
        COMMAND flex -+ -P cc -o ${BUILD_DIR}/lex.cc.cc ${EXECUTABLE_OUTPUT_PATH}/grammar/comment.l
        COMMENT "Building lex lex.yy.c ccFlexLexer"
)

add_custom_command(
        OUTPUT ${BUILD_DIR}/lea.tab.cc
        PRE_BUILD
        COMMAND bison -L C++ -o ${BUILD_DIR}/lea.tab.cc -d ${EXECUTABLE_OUTPUT_PATH}/grammar/lea.y -v
        COMMENT "Building yacc lea.tab.c"
)

add_custom_target(cleanCache)
add_custom_target(leapro)
add_custom_target(test)

add_custom_command(
        TARGET cleanCache
        COMMAND rm -rf ${BUILD_DIR}/*
        COMMENT "Clean lex & yacc cache"
)

add_custom_command(
        TARGET leapro
        COMMAND ${EXECUTABLE_OUTPUT_PATH}/lea leapro/main.lea ${BUILD_DIR}/main.lea.asm # ${BUILD_DIR}/main.lea.asm >/dev/null
        COMMAND as -o ${BUILD_DIR}/main.lea.o ${BUILD_DIR}/main.lea.asm
        COMMAND gcc -o main.lea.run ${BUILD_DIR}/main.lea.o -lc -no-pie
        COMMENT "Compiling leapro/main.lea"
)

add_custom_command(
        TARGET test
#        COMMAND ${EXECUTABLE_OUTPUT_PATH}/lea leapro/test.lea ${BUILD_DIR}/test.lea.asm # ${BUILD_DIR}/main.lea.asm >/dev/null
        COMMAND as -o ${BUILD_DIR}/test.lea.o ${BUILD_DIR}/test.lea.asm
        COMMAND gcc -o test.lea.run ${BUILD_DIR}/test.lea.o -lc -no-pie
        COMMENT "Compiling leapro/test.lea"
)

include_directories(${EXECUTABLE_OUTPUT_PATH}/src ${EXECUTABLE_OUTPUT_PATH}/build)

add_executable(
        lea
        build/lea.tab.cc
        build/lex.yy.cc
        build/lex.cc.cc
        src/compiler.cpp
        src/value.cpp
        src/gas.cpp
        src/tree.cpp
        src/parsing.cpp
        src/parser_tree.cpp
        src/branch.cpp
        src/basic_ds.cpp
        src/scope.cpp
)

target_link_libraries(lea c stdc++)
cmake_minimum_required(VERSION 3.20)

project(compiler)

set(CMAKE_CXX_STANDARD 11)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/)

execute_process(COMMAND mkdir -p ${EXECUTABLE_OUTPUT_PATH}/build)

add_custom_command(
        OUTPUT ${EXECUTABLE_OUTPUT_PATH}/build/lex.yy.c
        PRE_BUILD
        COMMAND flex -o ${EXECUTABLE_OUTPUT_PATH}/build/lex.yy.c ${EXECUTABLE_OUTPUT_PATH}/grammar/lea.l
        COMMENT "Building lex lex.yy.c"
)

add_custom_command(
        OUTPUT ${EXECUTABLE_OUTPUT_PATH}/build/lea.tab.c
        PRE_BUILD
        COMMAND bison -o ${EXECUTABLE_OUTPUT_PATH}/build/lea.tab.c -d ${EXECUTABLE_OUTPUT_PATH}/grammar/lea.y -v
        COMMENT "Building yacc lea.tab.c"
)

add_custom_target(cleanCache)

add_custom_command(
        TARGET cleanCache
        COMMAND rm -rf ${EXECUTABLE_OUTPUT_PATH}/build/*
        COMMENT "Clean lex & yacc cache"
)

include_directories(${EXECUTABLE_OUTPUT_PATH}/)

add_executable(
        lea
        main.cpp
        build/lea.tab.c
        build/lex.yy.c
        val.cpp
        gas.cpp
        boo.cpp
)

target_link_libraries(lea c stdc++)
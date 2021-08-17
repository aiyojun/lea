cmake_minimum_required(VERSION 3.20)
project(compiler)

set(CMAKE_CXX_STANDARD 11)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/)

execute_process(COMMAND mkdir -p ${EXECUTABLE_OUTPUT_PATH}/build)
execute_process(COMMAND flex -o ${EXECUTABLE_OUTPUT_PATH}/build/lex.yy.c ${EXECUTABLE_OUTPUT_PATH}/grammar/lea.l)
execute_process(COMMAND bison -o ${EXECUTABLE_OUTPUT_PATH}/build/lea.tab.c -d ${EXECUTABLE_OUTPUT_PATH}/grammar/lea.y -v)

include_directories(${EXECUTABLE_OUTPUT_PATH}/)

add_executable(lea
        main.cpp
        build/lea.tab.c
        build/lex.yy.c
        syntax.cpp
        )

target_link_libraries(lea c stdc++)


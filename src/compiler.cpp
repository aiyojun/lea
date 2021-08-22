#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grammar.h"

int lealine = 1;

void yyerror(const char* s)
{
    printf("\033[31;1mGrammar error : %s; line : %d.\033[0m\n", s, lealine);
    exit(1);
}

void printf_empty(const char *__restrict __format, ...) {}

int main(int argc, char **argv)
{
    char output_file[512];
    if (argc >= 3){
        strcpy(output_file, argv[2]);
        file_writer::out = std::string(output_file);
        yyin = fopen(argv[1], "r");
    } else if (argc == 2) {
        yyin = fopen(argv[1], "r");
    }
    yyparse();
    fclose(yyin);
    return 0;
}
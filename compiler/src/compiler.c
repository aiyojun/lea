#include "lang/grammar.h"
#include <stdio.h>

extern FILE *yyin;

int main(int argc, char **argv)
{
    if (argc >= 3)
    {
        strcpy(output_file, argv[2]);
        yyin = fopen(argv[1], "r");
    }
    yyparse();
    return 0;
}
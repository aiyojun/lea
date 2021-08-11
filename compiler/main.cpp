#include <stdio.h>
#include <string.h>
#include "syntax.h"

int main(int argc, char **argv)
{
    char output_file[512];
    if (argc >= 3){
        strcpy(output_file, argv[2]);
        yyin = fopen(argv[1], "r");
    } else if (argc == 2) {
        yyin = fopen(argv[1], "r");
    }
    yyparse();
    fclose(yyin);
    return 0;
}
#include "mm.h"
#include <stdio.h>
#include <stdlib.h>

void* leaMalloc(unsigned int size) {
    void *ptr = malloc(size);
    if (ptr == NULL) {
        printf("\033[31;1mlea malloc failed!\033[0m\n");
        exit(1);
    }
    return ptr;
}
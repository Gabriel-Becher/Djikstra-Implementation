#include <stdio.h>
#include <stdlib.h>
#include "../inc/parseFiles.h"
#include "../inc/ioStructs.h"

InputData* parseInput(char* filename) {
    FILE* file = fopen(filename, "r");
    fclose(file);
    return NULL;
}

OutputData* parseOutput(char* filename) {
    FILE* file = fopen(filename, "r");
    fclose(file);
    return NULL;
}

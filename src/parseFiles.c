#include <stdio.h>
#include <stdlib.h>
#include "../inc/parseFiles.h"
#include "../inc/ioStructs.h"

InputData* readInput(char* filename) {
    FILE* file = fopen(filename, "r");
    fclose(file);
    return NULL;
}

void writeOutput(OutputData* outputData, char* filename) {
    if (outputData == NULL) {
        return;
    }
    FILE* file = fopen(filename, "w");
    fclose(file);
}

#include <stdio.h>
#include <stdlib.h>
#include "../inc/ioStructs.h"
#include "../inc/parseFiles.h"

int main(int argc, char *argv[]) {

    if(argc != 3){
        exit(-1);
    }

    InputData* inputData = parseInput(argv[1]);
    OutputData* outputData = parseOutput(argv[2]);

    if(inputData == NULL || outputData == NULL){
        printf("Parse error");
    }

    printf("Parsed input and output files successfully.\n");
    printf("%s || %s\n", argv[1], argv[2]);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include "../inc/ioStructs.h"
#include "../inc/parseFiles.h"
#include "../inc/djikstra.h"

int main(int argc, char *argv[]) {
    if(argc != 3){
        exit(-1);
    }
    InputData* inputData = NULL;
    OutputData* outputData = NULL;
    /**
     * 1 - Lê arquivo de entrada e poe na struct
     * 2 - processa a struct de entrada que resulta na struct de saída
     * 3 - Escreve a struct de saída em um arquivo
     */
    inputData = readInput(argv[1]);
    if(inputData == NULL){
        printf("Erro de leitura\n");
        return -1;
    }
    
    outputData = djikstra(inputData);
    if(outputData == NULL){
        printf("Erro no processamento da matriz\n");
        return -1;
    }
    writeOutput(outputData, argv[2]);
    return 0;
}
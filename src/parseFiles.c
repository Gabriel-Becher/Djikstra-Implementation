#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/parseFiles.h"
#include "../inc/ioStructs.h"

InputData* readInput(char* filename) {
    FILE* file;
    char buffer[256], path[3], inicio, fim;
    file = fopen(filename, "r");
    int size = 0;
    int** matriz;
    if (!file) {
        return NULL;
    }

    fgets(buffer, sizeof(buffer), file); // Leio uma linha para ver quantos numeros tem
    
    for(int i = 0; buffer[i] != '\0'; i++) {
        if(buffer[i] != ' ' && buffer[i] != '\n' && buffer[i] != '\r' && buffer[i] != '\t') {
            size++; // contagem de caracteres de possiveis numeros
        }
    }

    matriz = (int**)malloc(size * sizeof(int*));
    for(int i = 0; i < size; i++) {
        matriz[i] = (int*)malloc(size * sizeof(int)); // alocação da matriz
    }
    for(int i = 0; i < size; i++){
        int j = 0;
        fgets(buffer, sizeof(buffer), file); // leio a linha
        char* token = strtok(buffer, " \t\n\r");
        while (token != NULL && j < size) {
            token = strtok(NULL, " \t\n\r");
            if(token[0] == '-'){
                matriz[i][j] = -1; // menos um vai indicar sem caminho
            }else{
                matriz[i][j] = atoi(token); // converto o token para inteiro e armazeno na matriz
            }
            j++;
        }
    }

   while (fgets(buffer, sizeof(buffer), file)) {
       if (sscanf(buffer, "%c %c", &inicio, &fim) == 2) {
           break;
       }
   }

    path[0] = inicio;
    path[1] = fim;

    InputData* inputData = (InputData*)malloc(sizeof(InputData));
    if(inputData == NULL) {
        for(int i = 0; i < size; i++) {
            free(matriz[i]);
        }
        free(matriz);
        fclose(file);//desalocamos tudo pra evitar memory leak caso de erro
        return NULL;
    }
    inputData->matrix = matriz;
    inputData->size = size;
    inputData->path = (char*)path;
    fclose(file);
    return inputData;
}

void writeOutput(OutputData* outputData, char* filename) {
    if (outputData == NULL) {
        return;
    }
    FILE* file = fopen(filename, "w");
    fclose(file);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/parseFiles.h"
#include "../inc/ioStructs.h"

InputData* readInput(char* filename) {
    FILE* file;
    char buffer[256], path[3];
    file = fopen(filename, "r");
    int size = 0;
    int** matriz;
    if (!file) {
        return NULL;
    }

    fgets(buffer, sizeof(buffer), file); // Leio uma linha para ver quantos numeros tem
    
    for(int i = 0; buffer[i] != '\0'; i++) {
        if(buffer[i] != ' ' && buffer[i] != '\n') {
            size++; // contagem de caracteres de possiveis numeros
        }
    }

    matriz = (int**)malloc(size * sizeof(int*));
    for(int i = 0; i < size; i++) {
        matriz[i] = (int*)malloc(size * sizeof(int)); // alocação da matriz
    }

    fseek(file, 0, SEEK_SET); // volto o ponteiro do arquivo para o inicio pra facilitar leitura
    for(int i = 0; i < size; i++){
        int j = 0;
        fgets(buffer, sizeof(buffer), file); // leio a linha
        char* token = strtok(buffer, " ");
        while (token != NULL && j < size) {
            matriz[i][j] = atoi(token); // converto o token para inteiro e armazeno na matriz
            token = strtok(NULL, " ");
            j++;
        }
    }

    fgets(buffer, sizeof(buffer), file); // leio a linha do caminho
    char* token = strtok(buffer, " ");
    int index = 0;    
    while (token != NULL && index < 2) {
    path[index] = token[0];
    if((int)path[index] < 65 || (int)path[index] > 90){ // verifica se é letra maiuscula
        return NULL;
    }
    token = strtok(NULL, " ");
    index++;
    }

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

#include "../inc/djikstra.h"
#include "../inc/ioStructs.h"
#include <stdio.h>
#include <stdlib.h>
#define INFINITO 2147483647

int todosVisitados(int* visitado, int size) {
    for (int i = 0; i < size; i++) {
        if (visitado[i] == 0) {
            return 0;
        }
    }
    return 1;
}


OutputData* djikstra(InputData* inputData) {
    if (inputData == NULL) {
        return NULL;
    }
    int size = inputData->size;
    int** matriz = inputData->matrix;
    int inicioIndex = (int)inputData->path[0] - 65;
    int fimIndex = (int)inputData->path[1] - 65;
    char* simbolos = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int* visitados = (int*)malloc(size * sizeof(int));
    int* custos = (int*)malloc(size * sizeof(int));
    int* caminho = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        visitados[i] = 0;
        custos[i] = INFINITO;
        caminho[i] = -1;
    }
    OutputData* outputData = (OutputData*)malloc(sizeof(OutputData));
    if (outputData == NULL) {
        return NULL;
    }

   /*  while (!todosVisitados(visitados, size))
    {

    } */
    


    //Roteamento por djikstra
    /*
        Passo 1 - começa em A até D
        Passo 2 - Visitas todos os nós adjacentes ao nó atual, atualizando os custos mínimos para chegar a cada nó
        Passo 3 - Marca o nó atual como visitado
        Passo 4 - Seleciona o nó não visitado com o menor custo acumulado como o próximo nó atual
        Passo 5 - Repete os passos 2-4 até que o nó destino seja alcançado ou todos os nós tenham sido visitados
    */
    




    return NULL;
}
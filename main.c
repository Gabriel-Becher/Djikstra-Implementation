#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INFINITO 2147483647 // valor maximo do int pra controlar os valores

// structs de entrada e saída
typedef struct {
    int** matriz;
    int tamanho;
    char* caminho;
} InputData;

typedef struct {
    char* caminho;
    int tamanho;
    int custo;
} OutputData;

// prototipos das minhas funções

InputData* readInput();
OutputData* djikstra(InputData* inputData);
void writeOutput(OutputData* outputData);
int pegaMenorCusto(int* custos, int* visitados, int tamanho);
int todosVisitados(int* visitados, int tamanho); 

int main() {
    InputData* inputData = NULL;
    OutputData* outputData = NULL;
    
    inputData = readInput();
    if(inputData == NULL){
        printf("Erro de leitura\n");
        return -1;
    }
    
    outputData = djikstra(inputData);

    if(outputData == NULL){
        printf("Erro no processamento da matriz\n");
        return -1;
    }
    writeOutput(outputData);
    return 0;
}

InputData* readInput() {
    char buffer[256], caminho[3], inicio = '-', fim = '-';
    int tamanho = 0;
    int** matriz;

    fgets(buffer, sizeof(buffer), stdin); // Leio uma linha para ver quantos numeros tem
    
    for(int i = 0; buffer[i] != '\0'; i++) {
        if(buffer[i] != ' ' && buffer[i] != '\n' && buffer[i] != '\r' && buffer[i] != '\t') {
            tamanho++; // contagem de caracteres de possiveis colunas
        }
    }

    matriz = (int**)malloc(tamanho * sizeof(int*));
    for(int i = 0; i < tamanho; i++) {
        matriz[i] = (int*)malloc(tamanho * sizeof(int)); // alocação da matriz
    }
    for(int i = 0; i < tamanho; i++){
        int j = 0;
        fgets(buffer, sizeof(buffer), stdin); // leio a linha
        char* token = strtok(buffer, " \t\n\r");
        while (token != NULL && j < tamanho) {
            token = strtok(NULL, " \t\n\r");
            if(token[0] == '-'){
                matriz[i][j] = -1; // menos um vai indicar sem caminho
            }else{
                matriz[i][j] = atoi(token); // converto o token para inteiro e armazeno na matriz
            }
            j++;
        }
    }

   while (fgets(buffer, sizeof(buffer), stdin)) {
       if (sscanf(buffer, "%c %c", &inicio, &fim) == 2) {
           break;
       }
   }
   if(inicio == '-' || fim == '-') {
       for(int i = 0; i < tamanho; i++) {
           free(matriz[i]);
       }
       free(matriz);
       return NULL; // em caso de erro de leitura para evitar memory leak
   }

    caminho[0] = inicio;
    caminho[1] = fim;

    InputData* inputData = (InputData*)malloc(sizeof(InputData));
    if(inputData == NULL) {
        for(int i = 0; i < tamanho; i++) {
            free(matriz[i]);
        }
        free(matriz);
        return NULL;
    }
    inputData->matriz = matriz;
    inputData->tamanho = tamanho;
    inputData->caminho = (char*)caminho;
    return inputData;
}

OutputData* djikstra(InputData* inputData) {
    if (inputData == NULL) {
        return NULL;
    }
    // extrair as infos da entrada  lida
    int** matriz = inputData->matriz;
    int tamanho = inputData->tamanho;
    int inicioIndex = (int)inputData->caminho[0] - 65; // converter 'A' para 0, mesmo pras outras letras, suponho que sempre vão estar em ordem :)
    int fimIndex = (int)inputData->caminho[1] - 65;
    int tamanhoCaminho = 0;

    // vetores auxiliares pro calculo(visitados, custos e caminho)

    int* visitados = (int*)malloc(tamanho * sizeof(int));
    int* custos = (int*)malloc(tamanho * sizeof(int));
    int* caminho = (int*)malloc(tamanho * sizeof(int));
    for (int i = 0; i < tamanho; i++) { // inigialização
        visitados[i] = 0;
        custos[i] = INFINITO;
        caminho[i] = -1; // menos um indica sem caminho
    }
    OutputData* outputData = (OutputData*)malloc(sizeof(OutputData));
    if (outputData == NULL) {
        free(visitados);
        free(custos);
        free(caminho);
        return NULL;
    }
    custos[inicioIndex] = 0;
    while(!todosVisitados(visitados, tamanho)) {
        int atual = pegaMenorCusto(custos, visitados, tamanho);
        if(atual == -1) {
            break;
        }
        for(int i = 0; i< tamanho; i++) {
            if(matriz[atual][i] != -1 && !visitados[i]) {
                int custoAcm = custos[atual] + matriz[atual][i];
                if(custoAcm < custos[i]) {
                    custos[i] = custoAcm;
                    caminho[i] = atual;
                }
            }
        }
        visitados[atual] = 1;
    }
    if(custos[fimIndex] == INFINITO) {
        free(visitados);
        free(custos);
        free(caminho);
        free(outputData);
        return NULL; // nao achou caminho
    }
    // reconstruir o caminho
    int indiceAtual = fimIndex;
    char* caminhoFinal = (char*)malloc(tamanho * sizeof(char));
    if(caminhoFinal == NULL) {
        free(visitados);
        free(custos);
        free(caminho);
        free(outputData);
        return NULL;
    }
    while(indiceAtual != -1) {
        caminhoFinal[tamanhoCaminho++] = (char)(indiceAtual + 65);
        indiceAtual = caminho[indiceAtual];
    }

    // inverter o caminho
    for(int i = 0; i < tamanhoCaminho / 2; i++) {
        char temp = caminhoFinal[i];
        caminhoFinal[i] = caminhoFinal[tamanhoCaminho - i - 1];
        caminhoFinal[tamanhoCaminho - i - 1] = temp;
    }
    outputData->caminho = caminhoFinal;
    outputData->tamanho = tamanhoCaminho;
    outputData->custo = custos[fimIndex];

    free(visitados);
    free(custos);
    free(caminho);
    return outputData;
}

// função pra escrever a resposta
void writeOutput(OutputData* outputData) {


    // formato de saida A -> B; B -> C; C -> D 6
    if (outputData == NULL) {
        return;
    }
    for(int i=0; i< outputData->tamanho-1; i++) {
        fprintf(stdout, "%c -> %c", outputData->caminho[i], outputData->caminho[i+1]);
        if(i < outputData->tamanho - 2) {
            fprintf(stdout, "; ");// aleluia
        }
    }
    fprintf(stdout, " %d", outputData->custo);
    fflush(stdout); 
}

// função auxiliar
int pegaMenorCusto(int* custos, int* visitados, int tamanho) {
    int menorCusto = INFINITO;
    int indiceMenor = -1;
    for (int i = 0; i < tamanho; i++) {
        if (!visitados[i] && custos[i] < menorCusto) {
            menorCusto = custos[i];
            indiceMenor = i;
        }
    }
    return indiceMenor;
}

// mais função auxiliar
int todosVisitados(int* visitados, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        if (!visitados[i]) {
            return 0; // continua
        }
    }
    return 1; // parar
}
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

InputData* readInput(char* filename);
OutputData* djikstra(InputData* inputData);
void writeOutput(OutputData* outputData, char* filename);

//função para ler a entrada do arquivo

int main(int argc, char *argv[]) {
    if(argc != 3){
        exit(-1);
    }
    InputData* inputData = NULL;
    OutputData* outputData = NULL;
    
    inputData = readInput(argv[1]);
    if(inputData == NULL){
        printf("Erro de leitura\n");
        return -1;
    }
    
    outputData = &(OutputData){
        .caminho = "ABCD",
        .tamanho = 4,
        .custo = 6
    };

    //outputData = djikstra(inputData);
    if(outputData == NULL){
        printf("Erro no processamento da matriz\n");
        return -1;
    }
    writeOutput(outputData, argv[2]);
    return 0;
}

InputData* readInput(char* filename) {
    FILE* file;
    char buffer[256], caminho[3], inicio = '-', fim = '-';
    file = fopen(filename, "r");
    int tamanho = 0;
    int** matriz;
    if (!file) {
        return NULL;
    }

    fgets(buffer, sizeof(buffer), file); // Leio uma linha para ver quantos numeros tem
    
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
        fgets(buffer, sizeof(buffer), file); // leio a linha
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

   while (fgets(buffer, sizeof(buffer), file)) {
       if (sscanf(buffer, "%c %c", &inicio, &fim) == 2) {
           break;
       }
   }
   if(inicio == '-' || fim == '-') {
       for(int i = 0; i < tamanho; i++) {
           free(matriz[i]);
       }
       free(matriz);
       fclose(file);
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
        fclose(file);//desalocamos tudo pra evitar memory leak caso de erro
        return NULL;
    }
    inputData->matriz = matriz;
    inputData->tamanho = tamanho;
    inputData->caminho = (char*)caminho;
    fclose(file);
    return inputData;
}

// função pra escrever a resposta

void writeOutput(OutputData* outputData, char* filename) {
    // formato de saida A -> B; B -> C; C -> D 6
    char setas[] = "%c -> %c";
    char pontoEspaco[] = "; ";
    if (outputData == NULL) {
        return;
    }
    FILE* file = fopen(filename, "w");
    if (!file) {
        exit(-1);
    }
    for(int i=0; i< outputData->tamanho-1; i++) {
        fprintf(file, setas, outputData->caminho[i], outputData->caminho[i+1]);
        if(i < outputData->tamanho - 2) {
            fprintf(file, pontoEspaco);// aleluia
        }
    }

    fprintf(file, " %d", outputData->custo);

    fclose(file);
}

//função pra calcular o caminho

OutputData* djikstra(InputData* inputData) {
    if (inputData == NULL) {
        return NULL;
    }
    int tamanho = inputData->tamanho;
    int** matriz = inputData->matriz;
    /* int inicioIndex = (int)inputData->caminho[0] - 65;
    int fimIndex = (int)inputData->caminho[1] - 65;
     */int* visitados = (int*)malloc(tamanho * sizeof(int));
    int* custos = (int*)malloc(tamanho * sizeof(int));
    int* caminho = (int*)malloc(tamanho * sizeof(int));
    for (int i = 0; i < tamanho; i++) {
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

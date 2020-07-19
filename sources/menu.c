#include <stdlib.h>
#include <stdio.h>

int* menu() {
    int *operation = (int*) malloc(sizeof(int));

    printf("*****************************************\n");
    printf("                   MENU                  \n\n");
    printf("    COMANDOS:                            \n\n");
    printf("    1 -> Inicializar grafo               \n");
    printf("    2 -> Pesquisar Kevin Bacon de um ator\n");
    printf("    3 -> Consultar média e desvio padrão \n");
    printf("    0 -> Finalizar programa              \n");
    printf("*****************************************\n\n");
    printf("Insira o comando: ");
    scanf("%d", operation);

    return operation;
}
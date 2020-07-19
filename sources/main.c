/*
* Nome: Henrique Gomes Zanin
* nUSP: 10441321
*
* Nome: Gabriel Guimarães Vilas Boas Marin
* nUSP: 11218521
*/
#include <stdio.h>
#include <stdlib.h>
#include <sixDegrees.h>
#include <graph.h>
#include <dictionary.h>
#include <utils.h>
#include <menu.h>

/*
* A Implementação está definida para um grafo não direcionado ponderado
*/

int main (int argc, char **argv) {
    int *operation = NULL;
    Error *err = newError();
    Dictionary *dict = createDictionary();
    GRAPH *grafo = createGraph();
    int KBNumber = 0;
    char *searchName = NULL;
    


    do {
        operation = menu();
        switch (*operation) {
        case 1:
            /* Inicializar */
            err = initializeGraph(grafo, grafo->graph, dict);
            if (hasError(err)) PrintError(err);
            break;
        case 2:
            /* Pesquisar ator e pegar seu numero de Kevin Bacon */
            printf("\nDigite o nome que deseja buscar !!\nExemplo: Thomsen, Ulrich\n-> ");
            searchName = (char*) malloc(100);
            scanf("\n%[^\n]s", searchName);
            printf("\n");
            err = getKevinBaconNumber(grafo->graph, dict, searchName, &KBNumber);
            if (hasError(err)) PrintError(err);
            break;
        case 3:
            /* Consulta média e desvio padrão de todos os números de Kevin Bacon do grafo */
            printf("Media Aritmética: %f\n", grafo->kevinBaconMedia);
            printf("Desvio Padrão: %f\n\n", grafo->kevinBaconStandardDeviation);
            break;
        case 0:
            /* Finaliza o programa */
            printf("\nAguarde, finalizando programa...");
            freeGraph(grafo->graph);
            freeError(err);
            freeDictionary(dict);
            break;
        default:
            ErrorFormat("Codigo invalido", err);
            PrintError(err);
            break;
        }
    } while (*operation != 0);

    return 0;
}
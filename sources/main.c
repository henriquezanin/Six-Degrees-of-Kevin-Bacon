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
    


    do {
        operation = menu();
        switch (*operation) {
        case 1:
            /* Inicializar */
            err = initializeGraph(grafo->graph, dict);
            if (hasError(err)) PrintError(err);
            break;
        case 2:
            /* Pesquisar ator e pegar seu numero de Kevin Bacon */
            err = getKevinBaconNumber(grafo->graph, dict, "Pope, Tony", &KBNumber);
            if (hasError(err)) PrintError(err);
            break;
        case 3:
            /* Consulta média e desvio padrão de todos os números de Kevin Bacon do grafo */
            // movie = readMovie(file);
            // if (movie == NULL) {
            //     printf("Arquvio todo já foi lido");
            // } else {
            //     printMovie(movie);
            // }
            printf("Media Aritmética: %d\n", grafo->kevinBaconMedia);
            printf("Desvio Padrão: %d\n", grafo->kevinBaconStandardDeviation);
            break;
        case 0:
            /* Finaliza o programa */
            break;
        default:
            ErrorFormat("Codigo invalido", err);
            PrintError(err);
            break;
        }
    } while (*operation != 0);

    return 0;
}
// int main(int argc, char *argv[]){
//     int i, size, *path;
//     Dictionary *dict = createDictionary();
//     /*addDictionary(Valor, Chave, Dicionario);*/
//     addDictionary("Minduca", 0,dict);
//     addDictionary("Marin", 1,dict);
//     addDictionary("Kel", 2,dict);
//     addDictionary("Marcola", 3,dict);
//     addDictionary("Castor", 4,dict);
//     addDictionary("Rock", 5,dict);
//     addDictionary("USP", 6,dict);
//     addDictionary("UNESP", 7,dict);
//     /*for(i=0;i<dict->size;i++){
//         printf("%s\n",dict->elements[i]->string);
//     }*/
//     Error *err;
//     Graph *graph = newGraph(8);
//     /*addUndirectedEdge(nó,nó,peso,grafo)*/
//     err = addUndirectedEdge(0, 6, 1, graph);
//     err = addUndirectedEdge(0, 7, 1, graph);
//     err = addUndirectedEdge(1, 6, 1, graph);
//     err = addUndirectedEdge(2, 6, 1, graph);
//     err = addUndirectedEdge(3, 6, 1, graph);
//     err = addUndirectedEdge(4, 7, 1, graph);
//     err = addUndirectedEdge(5, 7, 1, graph);
//     //Executa a busca em largura a partir do Marin
//     err = BreadthFirstSearch(graph, 1);
//     if(hasError(err)){
//         PrintError(err);
//         return -1;
//     }
//     //Constroi o caminho do Castor para o Marin
//     path = pathTo(4,1,graph,&size);
//     puts("Caminho:");
//     printf("[");
//     for(i=0;i<size;i++){
//         if(i < size - 1)
//             printf("%s -> ", getDictionaryValue(path[i], dict));
//         else
//             printf("%s]\n\n", getDictionaryValue(path[i], dict));
//     }
//     puts("Nó caminho para outro nó");
//     puts("No [Adjacente]");
//     for(i=0;i<graph->nNodes;i++){
//         printf("%s [%s]\n",getDictionaryValue(i, dict), getDictionaryValue(graph->edgeTo[i],dict));
//     }
//     //Libera a memória
//     freeGraph(graph);
//     return 0;
// }
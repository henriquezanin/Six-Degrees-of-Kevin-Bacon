/*
* Nome: Henrique Gomes Zanin
* nUSP: 10441321
*/
#include <stdio.h>
#include <stdlib.h>
#include <graph.h>

/*
* A Implementação está definida para um grafo direcionado ponderado
* OBS: Todas as buscas retornam o mesmo caminho devido ao tamanho do grafo
* e a casualidade da inserção ser ordenada.
* A lista insere sempre no começo.
*/
int main(int argc, char *argv[]){
    Error *err;
    Graph *graph = newGraph(6);
    int i;
    /*Adiciona os vertices para o problema do custo de carregamento
    * de computadores, proposto na primeira aula de grafos
    */
    for(i=0;i<5;i++){
        err = addEdge(i, i+1, 2100, graph);
        if(hasError(err)){
            PrintError(err);
            freeError(err);
            return 1;
        }
        printf("Weight(%d,%d):%d\n",i,i+1,getWeight(i,i+1,graph));
    }
    for(i=0;i<4;i++){
        err = addEdge(i, i+2, 3200, graph);
        if(hasError(err)){
            PrintError(err);
            freeError(err);
            return 1;
        }
        printf("Weight(%d,%d):%d\n",i,i+2,getWeight(i,i+2,graph));
    }
    for(i=0;i<3;i++){
        err = addEdge(i, i+3, 4200, graph);
        if(hasError(err)){
            PrintError(err);
            freeError(err);
            return 1;
        }
        printf("Weight(%d,%d):%d\n",i,i+3,getWeight(i,i+3,graph));
    }
    //Execução da busca em largura, preenche o vetor de ultimo caminho conhecido para o nó
    err = BreadthFirstSearch(graph, 0);
    if(hasError(err)){
        PrintError(err);
        return 1;
    }
    puts("BFS: Last vertex on know path, eg. [From] -> [to]");
    for(i=0;i<graph->nNodes;i++)
        printf("[%d]-> [%d]\t", graph->edgeTo[i], i);
    printf("\n");
    //Libera a memória
    freeGraph(graph);
    return 0;
}
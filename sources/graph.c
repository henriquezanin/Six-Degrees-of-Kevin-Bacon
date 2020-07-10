/*
* Nome: Henrique Gomes Zanin
* nUSP: 10441321
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <utils.h>
#include <queue.h>
#include <stack.h>
#include <linkedList.h>
#include <graph.h>

//Inicializa a lista e adjacências
Graph *newGraph(int nNodes){
    Graph *graph = (Graph*)calloc(1,sizeof(Graph));
    graph->nNodes = nNodes;
    int i;
    if(nNodes > 0){
        graph->list = (List**)calloc(nNodes,sizeof(List*));
        graph->edgeTo = (int*)malloc(nNodes*sizeof(int));
        memset(graph->edgeTo,-1,sizeof(int)*nNodes);
    }
    for(i=0;i<nNodes;i++){
        graph->list[i] = newList();
    }
    return graph;
}

//Instancia uma nova aresta e retorna o ponteiro para ser inserido na lista
Edge *_newEdge(int id, int weight){
    Edge *new = (Edge*)calloc(1, sizeof(Edge));
    new->node = id;
    new->weight = weight;
    return new;
}

//Adiciona um novo nó na lista de adjacências
Error *addNode(int id,Graph *graph){
    Error *err = newError();
    if(!graph){
        ErrorFormat("addNode: Null graph", err);
        return err;
    }
    if(id >= graph->nNodes){
        graph->list = (List**)realloc(graph->list, (id+1)*sizeof(List*));
        graph->list[id] = newList();
        graph->edgeTo = (int*)realloc(graph->edgeTo, (id+1)*sizeof(int));
        memset(&graph->edgeTo[graph->nNodes],-1,sizeof(int)*(id+1));
        graph->nNodes = id+1;
    }
    else
        ErrorFormat("addNode: Node already exists", err);
    return err;
}

//Adciona uma nova aresta entre dois nós
Error *addEdge(int from, int to, int weight, Graph *graph){
    Error *err = newError();
    if(!graph){
        ErrorFormat("addEdge: Null graph", err);
        return err;
    }
    if(from < 0 || to < 0){
        ErrorFormat("addEdge: Negative value to node or edge", err);
        return err;
    }
    if(from > graph->nNodes || to > graph->nNodes){
        ErrorFormat("addEdge: Impossible to create edge, nodes does not exists", err);
        return err;
    }
    if(!graph->list[from])
        graph->list[from] = newList();
    Edge *new = _newEdge(to, weight);
    err = addFirst(to, (void*)new, graph->list[from]);
    return err;
}

//Remove uma dada aresta
Error *removeEdge(int from, int to, Graph *graph){
    Error *err = newError();
    if(!graph){
        ErrorFormat("removeEdge: Null graph", err);
        return err;
    }
    if(from < 0 || to < 0){
        ErrorFormat("RemoveEdge: Negative value to node or edge", err);
        return err;
    }
    if(from > graph->nNodes || to > graph->nNodes){
        ErrorFormat("removeEdge: Impossible to remove edge, nodes does not exists", err);
        return err;
    }
    Edge *edge = removeElementById(to, graph->list[from]);
    if(!edge){
        ErrorFormat("removeEdge: Null list", err);
        return err;
    }
    free(edge);
    return err;
}

/*Remove um determinado nó de forma lógica
* A realocação é custosa por necessitar alterar o 
* indexador de todos os nós
*/
Error *removeNode(int id, Graph *graph){
    Error *err = newError();
    if(!graph){
        ErrorFormat("removeNode: Null graph", err);
        return err;
    }
    if(id >= graph->nNodes){
        ErrorFormat("removeNode: node out of range", err);
        return err;
    }
    int i;
    int nElements = graph->list[id]->nElements;
    void **elements = freeList(graph->list[id]);
    for(i=0;i<nElements;i++)
        free(elements[i]);
    free(elements);
    return err;
}

// Desaloca toda a memória ocupada pelo grafo
Error *freeGraph(Graph *graph){
    Error *err = newError();
    if(!graph){
        ErrorFormat("freeGraph: Null graph", err);
        return err;
    }
    int i,j, nElements;
    void **elements;
    for(i=0;i<graph->nNodes;i++){
        nElements = graph->list[i]->nElements;
        elements = freeList(graph->list[i]);
        for(j=0;j<nElements;j++){
            free(elements[j]);
        }
        if(elements)
            free(elements);
    }
    return err;
}

//Retorna o peso de uma determinada aresta
int getWeight(int from, int to, Graph *graph){
    if(!graph)
        return -1;
    if(from >= graph->nNodes || to >= graph->nNodes)
        return -1;
    Edge *edge = (Edge *)getElement(to,graph->list[from]);
    return edge->weight;
}

//Etapa recursiva da busca em profundidade
void _dfs(Graph *graph, int initial, unsigned char *marked){
    marked[initial] = 1;
    int nodeID;
    listElement *node = graph->list[initial]->first;
    while(node){
        nodeID = node->id;
        if(!marked[nodeID]){
            graph->edgeTo[nodeID] = initial;
            _dfs(graph, nodeID, marked);
        }
        node = node->next;
    }
}

/*Chama a busca em profundidade recursiva e reseta o vetor que permite reconstruir o caminho
para um dado nó */
Error *DepthFirstSearch(Graph *graph, int initial){
    Error *err = newError();
    if(!graph){
        ErrorFormat("dfs: Null graph", err);
        return err;
    }
    if(initial >= graph->nNodes || initial < 0){
        ErrorFormat("dfs: initial node doesn't exists", err);
        return err;
    }
    memset(graph->edgeTo,-1,sizeof(int)*graph->nNodes);
    unsigned char *marked = (unsigned char*) calloc(graph->nNodes, sizeof(unsigned char));
    _dfs(graph, initial, marked);
    free(marked);
    return err;
}

/*Executa a busca em largura e reseta o vetor que permite reconstruir o caminho
para um dado nó */
Error *BreadthFirstSearch(Graph *graph, int initial){
    Error *err = newError();
    if(!graph){
        ErrorFormat("bfs: Null graph", err);
        return err;
    }
    if(initial >= graph->nNodes || initial < 0){
        ErrorFormat("bfs: initial node doesn't exists", err);
        return err;
    }
    int node,i, nEdges;
    unsigned char *marked = (unsigned char*) calloc(graph->nNodes, sizeof(unsigned char));
    int *nodeEdges;
    memset(graph->edgeTo,-1,sizeof(int)*graph->nNodes);
    Queue *queue = newQueue();
    enqueue(initial, queue);
    while(!queueIsEmpty(queue)){
        node = dequeue(queue, err);
        if(hasError(err)){
            ErrorFormat("BreadthFirstSearch: failed to dequeue", err);
            return err;
        }
        nodeEdges = getAllIdElements(graph->list[node]);
        nEdges = getListSize(graph->list[node]);
        for(i=0;i<nEdges;i++){
            if(!marked[nodeEdges[i]]){
                marked[nodeEdges[i]] = 1;
                enqueue(nodeEdges[i], queue);
                graph->edgeTo[nodeEdges[i]] = node;
            }
        }
        free(nodeEdges);
    }
    free(marked);
    return err;
}
/*Opera da mesma forma que a busca em profundidade porém de forma não recursiva
*Reseta o vetor que permite reconstruir o caminho para um dado nó */
Error *DepthFirstSearchNonRecursive(Graph *graph, int initial){
    Error *err = newError();
    if(!graph){
        ErrorFormat("dfs: Null graph", err);
        return err;
    }
    if(initial >= graph->nNodes || initial < 0){
        ErrorFormat("dfs: initial node doesn't exists", err);
        return err;
    }
    memset(graph->edgeTo,-1,sizeof(int)*graph->nNodes);
    unsigned char *marked = (unsigned char*) calloc(graph->nNodes, sizeof(unsigned char));
    int node,i,nEdges;
    int *nodeEdges;
    Stack *stack = newStack();
    push(initial, stack);
    while(!stackIsEmpty(stack)){
        node = getStackTop(stack, err);
        if(hasError(err)){
            ErrorFormat("DepthFirstSearchNonRecusrive: Failed to get stack top", err);
            return err;
        }
        nodeEdges = getAllIdElements(graph->list[node]);
        nEdges = getListSize(graph->list[node]);
        for(i=0;i<nEdges && marked[nodeEdges[i]];i++);
        if(i != nEdges){
            graph->edgeTo[nodeEdges[i]] = node;
            marked[nodeEdges[i]] = 1;
            node = nodeEdges[i];
            err = push(node, stack);
            if(hasError(err)){
                ErrorFormat("DepthFirstSearchNonRecursive: Failed to push stack item", err);
                return err;
            }
        }
        else{
            node = pop(stack, err);
            if(hasError(err)){
                ErrorFormat("DepthFirstSearchNonRecursive: Failed to pop stack item", err);
                return err;
            }
        }
        free(nodeEdges);
    }
    free(marked);
    return err;
}
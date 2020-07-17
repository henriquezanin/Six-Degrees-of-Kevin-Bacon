#include <sixDegrees.h>
#include <dictionary.h>

GRAPH* createGraph() {
    GRAPH *grafo = (GRAPH*) calloc(1, sizeof(GRAPH));
    grafo->graph = newGraph(8);
    return grafo;
}

Error* initializeGraph(Graph *graph, Dictionary *dict) {
    Error *err = newError();
    if (!graph) {
        ErrorFormat("Grafo não foi criado", err);
        return err;
    } else if (!dict) {
        ErrorFormat("Dicionário não foi criado", err);
        return err;
    } 
    // else if (!fileName) {
    //     ErrorFormat("Nome do arquivo não foi passado", err);
    //     return err;
    // }
     else {
        // Fazer parser pro arquivo

        addDictionary("USP", dict->size, dict);
        addDictionary("Joao", dict->size, dict);
        addDictionary("Pedro Henrique", dict->size, dict);
        addUndirectedEdge(0, 1, 1, graph);
        addUndirectedEdge(0, 2, 1, graph);
    }
    

    return err;
}

Error* getKevinBaconNumber(Graph *graph, Dictionary *dict, char *actor, int *KBNumber) {
    Error *err = newError();
    if (graph->nNodes < 1) {
        ErrorFormat("Grafo não possui nenhum nó", err);
        return err;
    } else if (!actor) {
        ErrorFormat("Ator não foi referenciado", err);
        return err;
    } else if (dict->size < 1) {
        ErrorFormat("Ninguém foi adicionado no grafo", err);
        return err;
    }

    int key = 0, secondKey = 0;
    int *path = NULL, size;
    int i;

    key = getDictionaryKey("Joao", dict);
    secondKey = getDictionaryKey("Pedro Henrique", dict);
    err = BreadthFirstSearch(graph, secondKey);
    if(hasError(err)) {
        PrintError(err);
        return err;
    }
    path = pathTo(secondKey, key, graph, &size);
    for(i = 0; i < size; i++) {
        if(i < size - 1)
            printf("%s -> ", getDictionaryValue(path[i], dict));
        else
            printf("%s\n", getDictionaryValue(path[i], dict));
    }

    return err;
}
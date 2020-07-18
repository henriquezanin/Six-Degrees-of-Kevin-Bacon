#include <sixDegrees.h>
#include <dictionary.h>
#include <utils.h>

GRAPH* createGraph() {
    GRAPH *grafo = (GRAPH*) calloc(1, sizeof(GRAPH));
    grafo->graph = newGraph(0);
    return grafo;
}

Error* initializeGraph(Graph *graph, Dictionary *dict) {
    Error *err = newError();
    int i = 0, moviePos = 0, aux = 0;
    MOVIE *movie = (MOVIE*) calloc(1, sizeof(MOVIE));
    FILE *file = fopen("./assets/input-top-grossing.txt", "r+");

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
        while((movie = readMovie(file)) && movie != NULL) {
            // movieCounter++;
            // movies = (MOVIE**) realloc(movies, (movieCounter+1)*sizeof(MOVIE*));

            moviePos = addDictionary(movie->name, dict->size, dict);
            for (i = 0; i < movie->actorsCounter; i++) {
                printf("%d <--- %s\n\n\n\n", i+1, movie->actors[i]);
                aux = getDictionaryKey(movie->actors[i], dict);
                if (aux == -1) addUndirectedEdge(
                    moviePos,
                    addDictionary(movie->actors[i], dict->size, dict),
                    1,
                    graph
                );
                else addUndirectedEdge(
                    moviePos,
                    aux,
                    1,
                    graph
                );
            }
        }

        // addDictionary("USP", dict->size, dict);
        // addDictionary("Joao", dict->size, dict);
        // addDictionary("Pedro Henrique", dict->size, dict);
        // addUndirectedEdge(0, 1, 1, graph);
        // addUndirectedEdge(0, 2, 1, graph);
    }
    
    printf("Arquivo carregado !!\n");
    return err;
}

Error* getKevinBaconNumber(Graph *graph, Dictionary *dict, char *actor, int *KBNumber) {
    Error *err = newError();
    if (!actor) {
        ErrorFormat("Ator não foi referenciado", err);
        return err;
    } else if (dict->size < 1) {
        ErrorFormat("Ninguém foi adicionado no grafo", err);
        return err;
    }

    int key = 0, secondKey = 0;
    int *path = NULL, size;
    int i;

    printf("PROCURANDO POR: %s\n", actor);
    key = getDictionaryKey(actor, dict);
    secondKey = getDictionaryKey("Bacon, Kevin", dict);
    err = BreadthFirstSearch(graph, secondKey);
    if(hasError(err)) {
        PrintError(err);
        return err;
    }
    path = pathTo(key, secondKey, graph, &size);
    printf("Caminho: ");
    for(i = 0; i < size; i++) {
        if(i < size - 1)
            printf("%s -> ", getDictionaryValue(path[i], dict));
        else
            printf("%s\n", getDictionaryValue(path[i], dict));
    }
    printf("Kevin Bacon number: %d\n", (size-1)/2);

    return err;
}
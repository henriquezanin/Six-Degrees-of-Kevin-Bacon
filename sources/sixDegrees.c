#include <sixDegrees.h>
#include <dictionary.h>
#include <utils.h>
#include <math.h>

GRAPH* createGraph() {
    GRAPH *grafo = (GRAPH*) calloc(1, sizeof(GRAPH));
    grafo->graph = newGraph(0);
    return grafo;
}

/*
 Inicializa o grafo adicionando os filmes com seus atores 
 Calcula as médias do grafo carregado
*/
Error* initializeGraph(GRAPH *grafo, Graph *graph, Dictionary *dict) {
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
     else {

        while((movie = readMovie(file)) && movie != NULL) {

            /* Adiciona filmes e atores */
            moviePos = addDictionary(movie->name, dict->size, dict);
            err = addNode(moviePos, graph);
            printf("\n\nFILME: %s\n\n", movie->name);
            for (i = 0; i < movie->actorsCounter; i++) {
                printf("%d <--- %s\n", i+1, movie->actors[i]);
                aux = getDictionaryKey(movie->actors[i], dict);
                if (aux == -1) {
                    aux = addDictionary(movie->actors[i], dict->size, dict);
                    err = addNode(aux, graph);
                    addUndirectedEdge(
                        moviePos,
                        aux,
                        1,
                        graph
                    );
                } else addUndirectedEdge(
                    moviePos,
                    aux,
                    1,
                    graph
                );
            }
            freeMovie(movie);
        }

        /* Calcula as medias */
        aux = getDictionaryKey("Bacon, Kevin", dict);
        err = BreadthFirstSearch(graph, aux);

        grafo->kevinBaconMedia = calcMedia(graph, dict, aux);
        grafo->kevinBaconStandardDeviation = calcStandardDeviation(graph, dict, aux);

    }
    
    printf("Arquivo carregado !!\n");
    return err;
}

/* Busca o numero de Kevin Bacon do ator pesquisado */
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
    if (key == -1) {
        ErrorFormat("Ator não encontrado", err);
        return err;
    }
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
    printf("Kevin Bacon number: %d\n\n", (size-1)/2);

    return err;
}

/* Calcula media aritmética */
float calcMedia(Graph *graph, Dictionary *dict, int kevinBaconPos) {
    int i, size = 0, counter = 0;
    float sum = 0;
    for (i = 0; i < dict->size; i++) {
        pathTo(i, kevinBaconPos, graph, &size);
        if (size%2 == 1) { /* Filtra o caminho do ator para filmes, contando somente as rotas de ator para ator */
            sum += (size-1)/2;
            counter++;
        }
        size = 0;
    }
    return (sum/counter);
}

/* Calcula o desvio padrão */
float calcStandardDeviation(Graph *graph, Dictionary *dict, int kevinBaconPos) {
    int i, size = 0;
    int *kevinBaconNums = (int*) calloc(dict->size, sizeof(int));
    int counter = 0, m = 0;
    float sum = 0, sigma = 0, p = 0;
    for (i = 0; i < dict->size; i++) {
        pathTo(i, kevinBaconPos, graph, &size);
        if (size%2 == 1) { /* Filtra o caminho do ator para filmes, somando somente as rotas de ator para ator */
            kevinBaconNums[counter] = (size-1)/2;
            counter++;
        }
        size = 0;
    }

    for (i = 0; i < counter; i++) {
        m = m + kevinBaconNums[i];
    }
    sum = (float) m / counter;
    for (i = 0; i < counter; i++) {
        p = p + pow(kevinBaconNums[i] - sum,2);
    }
    sigma = sqrt(p/(counter-1));

    free(kevinBaconNums);
    return sigma;
}

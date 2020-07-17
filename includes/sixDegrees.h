#ifndef __SIXDEGREES__
#define __SIXDEGREES__

#include <graph.h>
#include <dictionary.h>
#include <stdlib.h>

struct graphHeader {
    Graph *graph;
    int kevinBaconMedia;
    int kevinBaconStandardDeviation;
    struct actorSearch *searchedActor;
};

struct actorSearch {
    char *searchedActor;
    int searchedKevinBacon;
};

typedef struct graphHeader GRAPH;
typedef struct actorSearch ACTOR;

GRAPH* createGraph();
Error* initializeGraph(Graph*, Dictionary*);
Error* getKevinBaconNumber(Graph*, Dictionary*, char*, int*);



#endif
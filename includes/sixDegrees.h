#ifndef __SIXDEGREES__
#define __SIXDEGREES__

#include <graph.h>
#include <dictionary.h>
#include <stdlib.h>

struct graphHeader {
    Graph *graph;
    float kevinBaconMedia;
    float kevinBaconStandardDeviation;
    struct actorSearch *searchedActor;
};

struct actorSearch {
    char *searchedActor;
    int searchedKevinBacon;
};

typedef struct graphHeader GRAPH;
typedef struct actorSearch ACTOR;

GRAPH* createGraph();
Error* initializeGraph(GRAPH*, Graph*, Dictionary*);
Error* getKevinBaconNumber(Graph*, Dictionary*, char*, int*);
float calcMedia(Graph*, Dictionary*, int);
float calcStandardDeviation(Graph*, Dictionary*, int);




#endif
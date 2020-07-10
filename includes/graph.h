#ifndef __ADJLIST__
#define __ADJLIST__

#include <linkedList.h>

typedef struct edge{
    int node;
    int weight;
} Edge;


typedef struct graph{
    List **list;
    int nNodes;
    int *edgeTo;
}Graph;

Graph *newGraph(int);
Error *addEdge(int,int,int, Graph *);
Error *addNode(int,Graph *);
Error *freeGraph(Graph *);
int getWeight(int, int, Graph *);
Error *DepthFirstSearch(Graph *, int);
Error *BreadthFirstSearch(Graph *, int);
Error *DepthFirstSearchNonRecursive(Graph *, int );

#endif
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
Error *addDirectedEdge(int,int,int, Graph *);
Error *removeDirectedEdge(int , int , Graph *);
Error *addUndirectedEdge(int,int,int, Graph *);
Error *removeUndirectedEdge(int , int , Graph *);
Error *addNode(int,Graph *);
Error *removeNode(int, Graph *);
Error *freeGraph(Graph *);
int getWeight(int, int, Graph *);
Error *BreadthFirstSearch(Graph *, int);
int *pathTo(int ,int , Graph *, int *);

#endif
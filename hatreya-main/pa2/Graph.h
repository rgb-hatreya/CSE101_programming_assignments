//____
//Hansa Atreya (hatreya)
//pa2
//___
_#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include "List.h"

#define NIL 0
#define INF -1

typedef struct GraphObj* Graph;

// Constructors-Destructors
Graph newGraph(int n);
void freeGraph(Graph* pG);

// Access functions
int getOrder(Graph G);
int getNumEdges(Graph G);
int getNumArcs(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
void getPath(List L, Graph G, int u);

// Manipulation procedures
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);

// Other operations
void printGraph(FILE* out, Graph G);

#endif


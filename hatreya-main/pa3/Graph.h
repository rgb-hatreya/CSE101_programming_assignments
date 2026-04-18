//-----------------------------------------------------------------------------
// Graph.h
// Header file for Graph ADT (DFS)
// pa3
// Hansa Atreya (hatreya)
//-----------------------------------------------------------------------------

#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <stdio.h>
#include "List.h"

//-----------------------------------------------------------------------------
// Definitions
//-----------------------------------------------------------------------------

// NIL represents an undefined vertex
#define NIL 0

// UNDEF represents undefined discover/finish times
#define UNDEF -1

//-----------------------------------------------------------------------------
// Exported type
//-----------------------------------------------------------------------------

// Graph
// Opaque reference to a GraphObj
typedef struct GraphObj* Graph;

//-----------------------------------------------------------------------------
// Constructors-Destructors
//-----------------------------------------------------------------------------

// newGraph()
// Returns a Graph with n vertices and no edges
Graph newGraph(int n);

// freeGraph()
// Frees all heap memory associated with *pG and sets *pG to NULL
void freeGraph(Graph* pG);

//-----------------------------------------------------------------------------
// Access functions
//-----------------------------------------------------------------------------

// getOrder()
// Returns the number of vertices in G
int getOrder(Graph G);

// getNumEdges()
// Returns the number of undirected edges in G
int getNumEdges(Graph G);

// getNumArcs()
// Returns the number of directed edges (arcs) in G
int getNumArcs(Graph G);

// getParent()
// Returns the parent of vertex u in the DFS forest
// Pre: 1 <= u <= getOrder(G)
int getParent(Graph G, int u);

// getDiscover()
// Returns the discovery time of vertex u
// Pre: 1 <= u <= getOrder(G)
int getDiscover(Graph G, int u);

// getFinish()
// Returns the finish time of vertex u
// Pre: 1 <= u <= getOrder(G)
int getFinish(Graph G, int u);

//-----------------------------------------------------------------------------
// Manipulation procedures
//-----------------------------------------------------------------------------

// makeNull()
// Deletes all edges of G
void makeNull(Graph G);

// addEdge()
// Inserts an undirected edge joining u and v
// Pre: 1 <= u, v <= getOrder(G)
void addEdge(Graph G, int u, int v);

// addArc()
// Inserts a directed edge from u to v
// Pre: 1 <= u, v <= getOrder(G)
void addArc(Graph G, int u, int v);

// DFS()
// Runs the Depth First Search algorithm on G.
// Input List S determines the order of vertices processed.
// On completion, S contains the vertices sorted by decreasing finish times.
// Pre: length(S) == getOrder(G)
void DFS(Graph G, List S);

//-----------------------------------------------------------------------------
// Other operations
//-----------------------------------------------------------------------------

// transpose()
// Returns a new Graph that is the transpose of G
Graph transpose(Graph G);

// copyGraph()
// Returns a deep copy of G
Graph copyGraph(Graph G);

// printGraph()
// Prints the adjacency list representation of G
void printGraph(FILE* out, Graph G);

#endif

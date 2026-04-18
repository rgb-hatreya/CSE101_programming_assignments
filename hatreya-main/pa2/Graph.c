//____
//Hansa Atreya (hatreya)
//pa2
//____
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

#define WHITE 0
#define GRAY  1
#define BLACK 2

typedef struct GraphObj {
    int order;
    int size;
    int arcs;
    int source;
    List* adj;
    int* color;
    int* parent;
    int* dist;
} GraphObj;

// Helper: insert in sorted order
static void sortedInsert(List L, int x) {
    moveFront(L);
    while(position(L) >= 0 && get(L) < x) {
        moveNext(L);
    }
    if(position(L) == -1) {
        append(L, x);
    } else {
        insertBefore(L, x);
    }
}

// Constructors-Destructors
Graph newGraph(int n) {
    Graph G = malloc(sizeof(GraphObj));
    G->order = n;
    G->size = 0;
    G->arcs = 0;
    G->source = NIL;

    G->adj = calloc(n+1, sizeof(List));
    G->color = calloc(n+1, sizeof(int));
    G->parent = calloc(n+1, sizeof(int));
    G->dist = calloc(n+1, sizeof(int));

    for(int i=1; i<=n; i++){
        G->adj[i] = newList();
        G->color[i] = WHITE;
        G->parent[i] = NIL;
        G->dist[i] = INF;
    }

    return G;
}

void freeGraph(Graph* pG) {
    if(pG && *pG) {
        Graph G = *pG;
        for(int i=1; i<=G->order; i++){
            freeList(&G->adj[i]);
        }
        free(G->adj);
        free(G->color);
        free(G->parent);
        free(G->dist);
        free(G);
        *pG = NULL;
    }
}

// Access functions
int getOrder(Graph G) { return G->order; }
int getNumEdges(Graph G) { return G->size; }
int getNumArcs(Graph G) { return G->arcs; }
int getSource(Graph G) { return G->source; }

int getParent(Graph G, int u) {
    return G->parent[u];
}

int getDist(Graph G, int u) {
    return G->dist[u];
}

// getPath
void getPath(List L, Graph G, int u) {
    if(G->source == NIL) return;

    if(u == G->source) {
        append(L, u);
    } else if(G->parent[u] == NIL) {
        append(L, NIL);
    } else {
        getPath(L, G, G->parent[u]);
        append(L, u);
    }
}

// Manipulation procedures
void makeNull(Graph G) {
    for(int i=1; i<=G->order; i++) {
        clear(G->adj[i]);
    }
    G->size = 0;
    G->arcs = 0;
}

void addEdge(Graph G, int u, int v) {
    sortedInsert(G->adj[u], v);
    sortedInsert(G->adj[v], u);
    G->size++;
}

void addArc(Graph G, int u, int v) {
    sortedInsert(G->adj[u], v);
    G->arcs++;
}

// BFS
void BFS(Graph G, int s) {
    for(int i=1; i<=G->order; i++) {
        G->color[i] = WHITE;
        G->parent[i] = NIL;
        G->dist[i] = INF;
    }

    G->source = s;
    G->color[s] = GRAY;
    G->dist[s] = 0;

    List Q = newList();
    append(Q, s);

    while(length(Q) > 0) {
        int u = front(Q);
        deleteFront(Q);

        moveFront(G->adj[u]);
        while(position(G->adj[u]) >= 0) {
            int v = get(G->adj[u]);
            if(G->color[v] == WHITE) {
                G->color[v] = GRAY;
                G->dist[v] = G->dist[u] + 1;
                G->parent[v] = u;
                append(Q, v);
            }
            moveNext(G->adj[u]);
        }
        G->color[u] = BLACK;
    }

    freeList(&Q);
}

// printGraph
void printGraph(FILE* out, Graph G) {
    for(int i=1; i<=G->order; i++) {
        fprintf(out, "%d: ", i);
        printList(out, G->adj[i]);
        fprintf(out, "\n");
    }
}


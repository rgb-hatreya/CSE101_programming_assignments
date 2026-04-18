//____
//Hansa Atreya (hatreya)
//pa3
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
    List* adj;
    int* color;
    int* parent;
    int* discover;
    int* finish;
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

    G->adj = calloc(n+1, sizeof(List));
    G->color = calloc(n+1, sizeof(int));
    G->parent = calloc(n+1, sizeof(int));
    G->discover = calloc(n+1, sizeof(int));
    G->finish = calloc(n+1, sizeof(int));

    for(int i=1; i<=n; i++){
        G->adj[i] = newList();
        G->color[i] = WHITE;
        G->parent[i] = NIL;
        G->discover[i] = UNDEF;
        G->finish[i] = UNDEF;
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
        free(G->discover);
        free(G->finish);
        free(G);
        *pG = NULL;
    }
}

// Access functions
int getOrder(Graph G) { return G->order; }
int getNumEdges(Graph G) { return G->size; }
int getNumArcs(Graph G) { return G->arcs; }
int getDiscover(Graph G, int u) { return G->discover[u]; }
int getFinish(Graph G, int u) { return G->finish[u]; }
int getParent(Graph G, int u) {
    return G->parent[u];
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


// printGraph
void printGraph(FILE* out, Graph G) {
    for(int i = 1; i <= G->order; i++) {
        fprintf(out, "%d: (", i);
        moveFront(G->adj[i]);
        while(position(G->adj[i]) >= 0) {
            fprintf(out, "%d", get(G->adj[i]));
            moveNext(G->adj[i]);
            if(position(G->adj[i]) >= 0) fprintf(out, ", ");
        }
        fprintf(out, ")\n");
    }
}

static void Visit(Graph G, int u, int* time, List S) {
    G->discover[u] = ++(*time);
    G->color[u] = GRAY;

    moveFront(G->adj[u]);
    while(position(G->adj[u]) >= 0) {
        int v = get(G->adj[u]);
        if(G->color[v] == WHITE) {
            G->parent[v] = u;
            Visit(G, v, time, S);
        }
        moveNext(G->adj[u]);
    }

    G->color[u] = BLACK;
    G->finish[u] = ++(*time);

    // push onto stack (front of S)
    prepend(S, u);
}

void DFS(Graph G, List S) {
    if(length(S) != G->order) {
        fprintf(stderr, "DFS error: length(S) != order\n");
        exit(EXIT_FAILURE);
    }

    for(int i=1; i<=G->order; i++) {
        G->color[i] = WHITE;
        G->parent[i] = NIL;
        G->discover[i] = UNDEF;
        G->finish[i] = UNDEF;
    }

    int time = 0;

    List order = copyList(S);
    clear(S);

    moveFront(order);
    while(position(order) >= 0) {
        int u = get(order);
        if(G->color[u] == WHITE) {
            Visit(G, u, &time, S);
        }
        moveNext(order);
    }

    freeList(&order);
}

Graph transpose(Graph G) {
    Graph T = newGraph(G->order);

    for(int u=1; u<=G->order; u++) {
        moveFront(G->adj[u]);
        while(position(G->adj[u]) >= 0) {
            int v = get(G->adj[u]);
            addArc(T, v, u);
            moveNext(G->adj[u]);
        }
    }
    return T;
}

Graph copyGraph(Graph G) {
    Graph C = newGraph(G->order);
    for(int u=1; u<=G->order; u++) {
        moveFront(G->adj[u]);
        while(position(G->adj[u]) >= 0) {
            int v = get(G->adj[u]);
            addArc(C, u, v); // copy the arc
            moveNext(G->adj[u]);
        }
    }
    return C;
}



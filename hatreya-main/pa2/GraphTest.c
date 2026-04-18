//____
//Hansa Atreya (hatreya)
//pa2
//____
#include <stdio.h>
#include "Graph.h"

int main() {
    Graph G = newGraph(6);

    addEdge(G,1,2);
    addEdge(G,1,3);
    addEdge(G,2,4);
    addEdge(G,2,5);
    addEdge(G,2,6);
    addEdge(G,3,4);
    addEdge(G,4,5);
    addEdge(G,5,6);

    printGraph(stdout, G);

    BFS(G, 1);

    List L = newList();
    getPath(L, G, 5);

    printf("Path 1 to 5: ");
    printList(stdout, L);
    printf("\n");

    freeList(&L);
    freeGraph(&G);
    return 0;
}


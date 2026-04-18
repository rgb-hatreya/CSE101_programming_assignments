// Hansa Atreya (hatreya)
// PA3 Graph SCC test

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

void printSCCs(Graph G) {
    int n = getOrder(G);

    // Step 1: DFS on original graph
    List S = newList();
    for(int i = 1; i <= n; i++) append(S, i);

    DFS(G, S);

    // Step 2: Transpose
    Graph GT = transpose(G);

    // Step 3: DFS on GT using decreasing finish times from S
    List SCCorder = copyList(S);
    clear(S); // reuse S to store each SCC tree
    DFS(GT, SCCorder);

    // Step 4: Extract SCCs
    printf("\nStrongly Connected Components (SCCs):\n");

    List currentSCC = newList();
    for(int i = 1; i <= n; i++) {
        int u = back(SCCorder); // back of list = decreasing finish time
        deleteBack(SCCorder);   // pop
        prepend(currentSCC, u);

        // If vertex has no parent in GT DFS, SCC is complete
        if(getParent(GT, u) == NIL) {
            printf("SCC: ");
            printList(stdout, currentSCC);
            clear(currentSCC);
        }
    }

    freeList(&S);
    freeList(&currentSCC);
    freeList(&SCCorder);
    freeGraph(&GT);
}

int main() {
    printf("=== Graph SCC Test ===\n");

    // Example graph from PA3 handout
    Graph G = newGraph(8);
    addArc(G, 1, 2);
    addArc(G, 2, 3);
    addArc(G, 3, 1);
    addArc(G, 3, 4);
    addArc(G, 4, 5);
    addArc(G, 5, 4);
    addArc(G, 6, 7);
    addArc(G, 7, 6);
    addArc(G, 8, 8);

    printf("\nOriginal graph adjacency list:\n");
    printGraph(stdout, G);

    printSCCs(G);

    freeGraph(&G);
    printf("\nTest complete.\n");
    return 0;
}


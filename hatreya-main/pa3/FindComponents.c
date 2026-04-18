// FindComponents.c
// Hansa Atreya (hatreya)
// PA3

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

int main(int argc, char *argv[]) {
    if(argc != 3) {
        fprintf(stderr, "Usage: %s infile outfile\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE *in = fopen(argv[1], "r");
    if(!in) {
        fprintf(stderr, "Unable to open input file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    FILE *out = fopen(argv[2], "w");
    if(!out) {
        fprintf(stderr, "Unable to open output file %s\n", argv[2]);
        exit(EXIT_FAILURE);
    }

    // Step 1: Read number of vertices
    int n;
    fscanf(in, "%d", &n);
    Graph G = newGraph(n);

    // Step 2: Read edges
    int u, v;
    while(fscanf(in, "%d %d", &u, &v) == 2) {
        if(u == 0 && v == 0) break;
        addArc(G, u, v);
    }
    fclose(in);

    // Step 3: Print adjacency list
    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, G);
    fprintf(out, "\n");

    // Step 4: DFS on G to get finish times
    List S = newList();
    for(int i = 1; i <= getOrder(G); i++) append(S, i);
    DFS(G, S);

    // Step 5: Transpose G and DFS on GT
    Graph GT = transpose(G);
    List ST = copyList(S);  // vertices in decreasing finish times from first DFS
    clear(S);               // reuse S if needed
    DFS(GT, ST);

    // Step 6: Count strongly connected components first
int compNum = 0;
moveFront(ST);
while(position(ST) >= 0) {
    int x = get(ST);
    if(getParent(GT, x) == NIL) compNum++;
    moveNext(ST);
}

// Print summary line BEFORE listing components
fprintf(out, "G contains %d strongly connected components:\n", compNum);

// Step 7: Print each strongly connected component
List component = newList();
compNum = 0;  // reset for numbering components
moveBack(ST); // iterate in decreasing finish times
while(position(ST) >= 0) {
    int x = get(ST);
    prepend(component, x);

    if(getParent(GT, x) == NIL) {
        compNum++;
        // Print component
        fprintf(out, "Component %d: (", compNum);
        moveFront(component);
        while(position(component) >= 0) {
            fprintf(out, "%d", get(component));
            moveNext(component);
            if(position(component) >= 0) fprintf(out, ", ");
        }
        fprintf(out, ")\n");
        clear(component);
    }
    movePrev(ST);
}
// Step 8: Cleanup
freeList(&S);
freeList(&ST);
freeList(&component);
freeGraph(&G);
freeGraph(&GT);
fclose(out);

return 0;
}

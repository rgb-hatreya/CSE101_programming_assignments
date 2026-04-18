//____
//Hansa Atreya (hatreya)
//pa2
//____
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main(int argc, char* argv[]) {
    if(argc != 3) {
        fprintf(stderr, "Usage: %s <input> <output>\n", argv[0]);
        return 1;
    }

    FILE* in = fopen(argv[1], "r");
    FILE* out = fopen(argv[2], "w");

    if(in == NULL) {
        fprintf(stderr, "Unable to open input file %s\n", argv[1]);
        return 1;
    }
    if(out == NULL) {
        fprintf(stderr, "Unable to open output file %s\n", argv[2]);
        return 1;
    }

    int n;
    fscanf(in, "%d", &n);

    Graph G = newGraph(n);

    int u, v;
    while(fscanf(in, "%d %d", &u, &v) == 2) {
        if(u == 0 && v == 0) break;
        addEdge(G, u, v);
    }

    printGraph(out, G);
    fprintf(out, "\n");

    while(fscanf(in, "%d %d", &u, &v) == 2) {
        if(u == 0 && v == 0) break;

        BFS(G, u);

        int d = getDist(G, v);
        if(d == INF) {
            fprintf(out, "The distance from %d to %d is infinity\n", u, v);
            fprintf(out, "No %d-%d path exists\n\n", u, v);
        } else {
            fprintf(out, "The distance from %d to %d is %d\n", u, v, d);
            List L = newList();
            getPath(L, G, v);
            fprintf(out, "A shortest %d-%d path is: ", u, v);
            printList(out, L);
            fprintf(out, "\n\n");
            freeList(&L);
        }
    }

    freeGraph(&G);
    fclose(in);
    fclose(out);
    return 0;
}


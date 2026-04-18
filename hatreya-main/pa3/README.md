#pa3, CSE 101
Hansa Atreya (hatreya)

pa3 includes the files:

Graph.h: header file for the Graph ADT, including DFS.
Graph.c: Implementation of Graph ADT, using adjacency lists and DFS.
FindComponent.c: Main client of pa3. Reads graph from input file, prints adjacency list, and computes the strongly connected components of the graph using DFS and transpose(). Outputs SCC count and each component. 
List.h: Modified List ADT header from pa1.
List.c: modified List ADT from pa1. Used for adjacency lists, DFS stacksing, SCC tracking.
Makefile: Compiles code and links them to create FindComponents. Includes error and memory leak checks.
README.md: This file. Describes the source files of pa3.

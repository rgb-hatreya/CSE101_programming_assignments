//___________________
// Words.c

//Reads an input text file, extracts all unique words (case-sensitive),
//then indirectly sorts them alphabetically using a List ADT that stores
//indices into the word array.

// Output format:
//  (list of indices)

//   word1
//   word2
//   ...

// A word is a maximal substring not containing any of the delimiter
// characters specified in the assignment.
//_________________________________

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "List.h"

// Delimiter string given in the assignment
#define DELIM " \t\n\r\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789"

// Maximum line length to read
#define MAX_LINE 1024

int main(int argc, char* argv[]) {

    FILE *in, *out;

    //_________________________________
    // 1. Check command line arguments
    //_________________________________
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Open input and output files
    in = fopen(argv[1], "r");
    if (in == NULL) {
        fprintf(stderr, "Unable to open input file %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    out = fopen(argv[2], "w");
    if (out == NULL) {
        fprintf(stderr, "Unable to open output file %s\n", argv[2]);
        fclose(in);
        return EXIT_FAILURE;
    }

    //_________________________________
    // 2. Read file, extract unique words into a dynamic array
    //_________________________________

    int capacity = 100;                  // initial capacity of word array
    int nWords = 0;                      // number of unique words
    char** words = malloc(capacity * sizeof(char*));

    char line[MAX_LINE];

    // Read file line by line
    while (fgets(line, MAX_LINE, in) != NULL) {

        // Tokenize the line using strtok
        char* token = strtok(line, DELIM);

        while (token != NULL) {

            // Check if token already exists in words array
            bool found = false;
            for (int i = 0; i < nWords; i++) {
                if (strcmp(token, words[i]) == 0) {
                    found = true;
                    break;
                }
            }

            // If not found, add it
            if (!found) {

                // Resize array if needed
                if (nWords == capacity) {
                    capacity *= 2;
                    words = realloc(words, capacity * sizeof(char*));
                }

                // Allocate space and copy the word
                words[nWords] = malloc(strlen(token) + 1);
                strcpy(words[nWords], token);
                nWords++;
            }

            // Get next token
            token = strtok(NULL, DELIM);
        }
    }

    //_________________________________
    // 3. Build List of indices in sorted (alphabetical) order
    //    (Indirect Insertion Sort using List ADT)
    //_________________________________

    List L = newList();

    for (int i = 0; i < nWords; i++) {

        // If list is empty, just append
        if (length(L) == 0) {
            append(L, i);
            continue;
        }

        // Otherwise, find correct position
        moveFront(L);
        while (position(L) >= 0) {
            int j = get(L);

            // Compare current word with word at index j
            if (strcmp(words[i], words[j]) < 0) {
                insertBefore(L, i);
                break;
            }

            moveNext(L);
        }

        // If we reached the end without inserting, append
        if (position(L) == -1) {
            append(L, i);
        }
    }

    //_________________________________
    // 4. Print output
    //_________________________________

    // Print the List of indices
    printList(out, L);
    fprintf(out, "\n\n");

    // Print the words in alphabetical order using the List
    moveFront(L);
    while (position(L) >= 0) {
        int idx = get(L);
        fprintf(out, "%s\n", words[idx]);
        moveNext(L);
    }

    //_________________________________
    // 5. Free memory
    //_________________________________

    for (int i = 0; i < nWords; i++) {
        free(words[i]);
    }
    free(words);

    freeList(&L);

    fclose(in);
    fclose(out);

    return EXIT_SUCCESS;
}


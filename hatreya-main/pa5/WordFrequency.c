//-----------------------------------------------------------------------------
// WordFrequency.c
// Hansa Atreya (hatreya)
// Counts word frequencies using Dictionary ADT
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Dictionary.h"

#define MAX_LINE 1024

// Convert string to lowercase in place
void toLowerCase(char* str){
    for(int i = 0; str[i]; i++)
        str[i] = tolower((unsigned char)str[i]);
}

// Check if character is a valid word character (letter or digit)
int isWordChar(char c){
    return isalpha((unsigned char)c);
}

// Process a line: extract words and insert into Dictionary
void processLine(Dictionary D, char* line){
    int len = strlen(line);
    char word[MAX_LINE];
    int idx = 0;

    for(int i = 0; i <= len; i++){
        char c = line[i];
        if(isWordChar(c)){
            word[idx++] = tolower((unsigned char)c);
        } else {
            if(idx > 0){
                word[idx] = '\0';
                // Increment word count
                if(contains(D, word)){
                    int val = getValue(D, word);
                    setValue(D, word, val + 1);
                } else {
                    setValue(D, word, 1);
                }
                idx = 0;
            }
        }
    }
}

int main(int argc, char* argv[]){
    if(argc != 3){
        fprintf(stderr, "Usage: %s <input> <output>\n", argv[0]);
        return 1;
    }

    FILE* inFile = fopen(argv[1], "r");
    if(!inFile){
        perror("Error opening input file");
        return 1;
    }

    FILE* outFile = fopen(argv[2], "w");
    if(!outFile){
        perror("Error opening output file");
        fclose(inFile);
        return 1;
    }

    Dictionary D = newDictionary();
    char line[MAX_LINE];

    while(fgets(line, MAX_LINE, inFile)){
        processLine(D, line);
    }

    // Print word frequencies using public ADT function
    printDictionary(outFile, D);

    // Clean up
    freeDictionary(&D);
    fclose(inFile);
    fclose(outFile);

    return 0;
}


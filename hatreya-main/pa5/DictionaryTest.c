//-----------------------------------------------------------------------------
// DictionaryTest.c
// Hansa Atreya (hatreya)
// Test client for Dictionary ADT (CSE101 PA5)
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Dictionary.h"

int main(void) {

    printf("Creating new Dictionary...\n");
    Dictionary D = newDictionary();

    printf("Initial size: %d\n", size(D));

    // Test setValue
    printf("\nInserting key-value pairs...\n");
    setValue(D, "apple", 1);
    setValue(D, "banana", 2);
    setValue(D, "orange", 3);

    printf("Size after inserts: %d\n", size(D));

    // Test printDictionary
    printf("\nDictionary contents:\n");
    printDictionary(stdout, D);

    // Test contains
    printf("\nTesting contains():\n");
    printf("Contains 'apple'? %s\n", contains(D, "apple") ? "true" : "false");
    printf("Contains 'grape'? %s\n", contains(D, "grape") ? "true" : "false");

    // Test getValue
    printf("\nTesting getValue():\n");
    printf("Value of 'banana': %d\n", getValue(D, "banana"));

    // Test overwrite
    printf("\nOverwriting 'banana' value...\n");
    setValue(D, "banana", 10);
    printf("Updated value of 'banana': %d\n", getValue(D, "banana"));

    // Test removeKey
    printf("\nRemoving 'apple'...\n");
    removeKey(D, "apple");
    printf("Size after removal: %d\n", size(D));

    printf("\nDictionary after removal:\n");
    printDictionary(stdout, D);

    // Test copy
    printf("\nTesting copy()...\n");
    Dictionary C = copy(D);
    printf("Copied dictionary:\n");
    printDictionary(stdout, C);

    // Test equals
    printf("\nTesting equals():\n");
    printf("D equals C? %s\n", equals(D, C) ? "true" : "false");

    printf("\nModifying copy...\n");
    setValue(C, "kiwi", 7);
    printf("D equals C? %s\n", equals(D, C) ? "true" : "false");

    // Clear dictionary
    printf("\nClearing original dictionary...\n");
    clear(D);
    printf("Size after clear: %d\n", size(D));

    // Free memory
    freeDictionary(&D);
    freeDictionary(&C);

    printf("\nAll tests completed successfully.\n");

    return 0;
}


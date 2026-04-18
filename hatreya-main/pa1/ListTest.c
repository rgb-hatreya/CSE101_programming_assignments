//___________________________________
// ListTest.c
// Test client for List ADT

//This program goes through all major operations (cursor movement,
//insertion, deletion, copying, etc).

//If List implementation is correct, this program should run without crashing
//and produce sensible output.
//___________________________________

#include <stdio.h>
#include <stdlib.h>
#include "List.h"

int main(void) {

    printf("=== Creating new List L ===\n");
    List L = newList();

    // Append some elements
    printf("Appending 10, 20, 30, 40, 50\n");
    append(L, 10);
    append(L, 20);
    append(L, 30);
    append(L, 40);
    append(L, 50);

    printf("L = ");
    printList(stdout, L);
    printf("\nLength = %d\n\n", length(L));

    // Test cursor movement
    printf("=== Testing cursor movement ===\n");
    moveFront(L);
    printf("Cursor at front: %d (pos=%d)\n", get(L), position(L));

    moveNext(L);
    printf("After moveNext: %d (pos=%d)\n", get(L), position(L));

    moveBack(L);
    printf("Cursor at back: %d (pos=%d)\n", get(L), position(L));

    movePrev(L);
    printf("After movePrev: %d (pos=%d)\n\n", get(L), position(L));

    // Test insertBefore and insertAfter
    printf("=== Testing insertBefore and insertAfter ===\n");
    moveFront(L);              // cursor at 10
    moveNext(L);               // cursor at 20
    insertBefore(L, 15);       // insert before 20
    insertAfter(L, 25);        // insert after 20

    printf("L = ");
    printList(stdout, L);
    printf("\n\n");

    // Test deleteFront and deleteBack
    printf("=== Testing deleteFront and deleteBack ===\n");
    deleteFront(L);
    deleteBack(L);

    printf("L = ");
    printList(stdout, L);
    printf("\nLength = %d\n\n", length(L));

    // Test delete (cursor deletion)
    printf("=== Testing delete (cursor) ===\n");
    moveFront(L);
    moveNext(L);   // move to some middle element
    printf("Deleting cursor element: %d\n", get(L));
    delete(L);

    printf("L = ");
    printList(stdout, L);
    printf("\nCursor position = %d (should be -1)\n\n", position(L));

    // Test copyList
    printf("=== Testing copyList ===\n");
    List C = copyList(L);
    printf("Original L = ");
    printList(stdout, L);
    printf("\nCopy C     = ");
    printList(stdout, C);
    printf("\nEquals(L, C) = %s\n\n", equals(L, C) ? "true" : "false");

    // Test join
    printf("=== Testing join ===\n");
    List J = join(L, C);
    printf("Joined J = ");
    printList(stdout, J);
    printf("\n\n");

    // Test split
    printf("=== Testing split ===\n");
    moveFront(J);
    moveNext(J);
    moveNext(J);   // move cursor a few steps in

    printf("J before split = ");
    printList(stdout, J);
    printf("\n");

    List S = split(J);

    printf("Returned S = ");
    printList(stdout, S);
    printf("\nRemaining J = ");
    printList(stdout, J);
    printf("\n\n");

    // Test clear
    printf("=== Testing clear ===\n");
    clear(L);
    printf("L after clear = ");
    printList(stdout, L);
    printf("\nLength = %d\n\n", length(L));

    // Free all Lists
    freeList(&L);
    freeList(&C);
    freeList(&J);
    freeList(&S);

    printf("=== All tests completed successfully ===\n");

    return 0;
}


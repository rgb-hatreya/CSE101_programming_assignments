//____
//Hansa Atreya (hatreya)
//pa2
//___
_#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "List.h"

//_______Priv Node type_______
// Each Node stores one ListElement and pointers to neighboring nodes

typedef struct Node {
    ListElement data;
    struct Node* next;
    struct Node* prev;
} Node;

// _______Priv ListObj______
// front  -> first node
// back   -> last node
// cursor -> current node (may be NULL = undefined)
// length -> number of nodes
// pos    -> index of cursor, or -1 if undefined

typedef struct ListObj {
    Node* front;
    Node* back;
    Node* cursor;
    int length;
    int pos;
} ListObj;

//______Node constructors___

// Creates a new Node containing data
Node* newNode(ListElement data) {
    Node* N = malloc(sizeof(Node));
    N->data = data;
    N->next = N->prev = NULL;
    return N;
}

// Frees a Node and sets pointer to NULL
void freeNode(Node** pN) {
    if(pN && *pN) {
        free(*pN);
        *pN = NULL;
    }
}

//______List constructors____

// Creates a new empty List
List newList(void) {
    List L = malloc(sizeof(ListObj));
    L->front = L->back = L->cursor = NULL;
    L->length = 0;
    L->pos = -1;
    return L;
}

// Frees all memory associated with List
void freeList(List* pL) {
    if(pL && *pL) {
        clear(*pL);
        free(*pL);
        *pL = NULL;
    }
}

//____Access functions__

int length(List L) { 
    return L->length; 
}

int position(List L) { 
    return L->pos; 
}

// Returns front element (precondition: length > 0)
ListElement front(List L) {
    assert(L->length > 0);
    return L->front->data;
}

// Returns back element (precondition: length > 0)
ListElement back(List L) {
    assert(L->length > 0);
    return L->back->data;
}

// Returns cursor element (precondition: cursor defined)
ListElement get(List L) {
    assert(L->length > 0 && L->pos >= 0);
    return L->cursor->data;
}

// Returns true if both lists contain the same sequence of data
bool equals(List A, List B) {
    if(length(A) != length(B)) return false;

    Node* a = A->front;
    Node* b = B->front;

    while(a && b) {
        if(a->data != b->data) return false;
        a = a->next;
        b = b->next;
    }
    return true;
}

//_____manipulation procedures

// Clears the list to empty state
void clear(List L) {
    Node* n = L->front;
    while(n) {
        Node* tmp = n;
        n = n->next;
        freeNode(&tmp);
    }
    L->front = L->back = L->cursor = NULL;
    L->length = 0;
    L->pos = -1;
}

// Overwrites cursor element
void set(List L, ListElement x) {
    assert(L->length > 0 && L->pos >= 0);
    L->cursor->data = x;
}

// Places cursor at front
void moveFront(List L) {
    if(L->length > 0) {
        L->cursor = L->front;
        L->pos = 0;
    }
}

// Places cursor at back
void moveBack(List L) {
    if(L->length > 0) {
        L->cursor = L->back;
        L->pos = L->length - 1;
    }
}

// Moves cursor one step toward front
void movePrev(List L) {
    if(L->cursor) {
        if(L->cursor == L->front) {
            L->cursor = NULL;
            L->pos = -1;
        } else {
            L->cursor = L->cursor->prev;
            L->pos--;
        }
    }
}

// Moves cursor one step toward back
void moveNext(List L) {
    if(L->cursor) {
        if(L->cursor == L->back) {
            L->cursor = NULL;
            L->pos = -1;
        } else {
            L->cursor = L->cursor->next;
            L->pos++;
        }
    }
}

// Inserts element at front
void prepend(List L, ListElement data) {
    Node* N = newNode(data);

    if(L->length == 0) {
        L->front = L->back = N;
    } else {
        N->next = L->front;
        L->front->prev = N;
        L->front = N;
        if(L->pos != -1) L->pos++; // cursor shifts right
    }
    L->length++;
}

// Inserts element at back
void append(List L, ListElement data) {
    Node* N = newNode(data);

    if(L->length == 0) {
        L->front = L->back = N;
    } else {
        L->back->next = N;
        N->prev = L->back;
        L->back = N;
    }
    L->length++;
}

// Inserts before cursor
void insertBefore(List L, ListElement data) {
    assert(L->length > 0 && L->pos >= 0);

    if(L->cursor == L->front) {
        prepend(L, data);
    } else {
        Node* N = newNode(data);
        Node* C = L->cursor;

        N->prev = C->prev;
        N->next = C;
        C->prev->next = N;
        C->prev = N;

        L->length++;
        L->pos++; // cursor shifts right
    }
}

// Inserts after cursor
void insertAfter(List L, ListElement data) {
    assert(L->length > 0 && L->pos >= 0);

    if(L->cursor == L->back) {
        append(L, data);
    } else {
        Node* N = newNode(data);
        Node* C = L->cursor;

        N->next = C->next;
        N->prev = C;
        C->next->prev = N;
        C->next = N;

        L->length++;
    }
}

// Deletes front element
void deleteFront(List L) {
    assert(L->length > 0);

    Node* N = L->front;

    if(L->length == 1) {
        L->front = L->back = NULL;
    } else {
        L->front = N->next;
        L->front->prev = NULL;
    }

    if(L->pos == 0) {
        L->cursor = NULL;
        L->pos = -1;
    } else if(L->pos != -1) {
        L->pos--;
    }

    L->length--;
    freeNode(&N);
}

// Deletes back element
void deleteBack(List L) {
    assert(L->length > 0);

    Node* N = L->back;

    if(L->length == 1) {
        L->front = L->back = NULL;
    } else {
        L->back = N->prev;
        L->back->next = NULL;
    }

    if(L->pos == L->length - 1) {
        L->cursor = NULL;
        L->pos = -1;
    }

    L->length--;
    freeNode(&N);
}

// Deletes cursor element
void delete(List L) {
    assert(L->length > 0 && L->pos >= 0);

    if(L->cursor == L->front) {
        deleteFront(L);
    } else if(L->cursor == L->back) {
        deleteBack(L);
    } else {
        Node* N = L->cursor;

        N->prev->next = N->next;
        N->next->prev = N->prev;

        freeNode(&N);

        L->length--;
        L->cursor = NULL;
        L->pos = -1;
    }
}

//_______other operations_____

// Prints list in format: (1, 2, 3)
void printList(FILE* out, List L) {
    Node* N = L->front;
    fprintf(out, "(");

    while(N) {
        fprintf(out, "%d", N->data);
        if(N->next) fprintf(out, ", ");
        N = N->next;
    }
    fprintf(out, ")");
}

// Returns a copy of L (cursor undefined)
List copyList(List L) {
    List C = newList();
    for(Node* N = L->front; N != NULL; N = N->next) {
        append(C, N->data);
    }
    return C;
}

// Returns concat of A followed by B
List join(List A, List B) {
    List J = newList();

    for(Node* n = A->front; n; n = n->next) append(J, n->data);
    for(Node* n = B->front; n; n = n->next) append(J, n->data);

    return J;
}

// Removes and returns all elements before cursor
List split(List L) {
    assert(L->length > 0 && L->pos >= 0);

    List S = newList();

    while(L->front != L->cursor) {
        append(S, front(L));
        deleteFront(L);
    }

    return S;
}


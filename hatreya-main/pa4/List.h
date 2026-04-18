//_______________
//List.h
// List ADT header file
// pa4
// Hansa Atreya (hatreya)
//_______________
#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include <stdbool.h>

//_______________
// Exported type
//_______________

// ListElement
// Type of elements stored in the list.
// Change this typedef to have a different element type.
typedef void* ListElement;
// List
// Opaque reference to a ListObj.
// The actual struct def is private and lives in List.c.
typedef struct ListObj* List;

//_______________
// Constructors-Destructors
//______________

// newList()
// Creates and returns a new empty list.
// The cursor is initially undefined.
List newList(void);

// freeList()
// Frees all of the heap memory associated with *pL, sets *pL to NULL.
void freeList(List* pL);

//_______________
// Access functions
//______________

// length()
// Returns the number of elements in L.
int length(List L);

// position()
// If the cursor is defined, returns the index of the cursor element,  otherwise returns -1.
int position(List L);

// front()
// Returns the front element of L.
// Precondition: length(L) > 0
ListElement front(List L);

// back()
// Returns the back element of L.
// Precondition: length(L) > 0
ListElement back(List L);

// get()
// Returns the cursor element.
// Precondition: length(L) > 0, position(L) >= 0
ListElement get(List L);

//_____________________
// Manipulation procedures
//______________________

// clear()
// Resets L to its original empty state.
void clear(List L);

// set()
// Overwrites the cursor element’s data with x.
// Precondition: length(L) > 0, position(L) >= 0
void set(List L, ListElement x);

// moveFront()
// If L is non-empty, places the cursor under the front element.
// Otherwise, does nothing.
void moveFront(List L);

// moveBack()
// If L is non-empty, places the cursor under the back element.
// Otherwise, does nothing.
void moveBack(List L);

// movePrev()
// If the cursor is defined and not at the front, moves the cursor one step toward the front of L.
// If the cursor is defined and at the front, the cursor becomes undefined.
// If the cursor is undefined, does nothing.
void movePrev(List L);

// moveNext()
// If the cursor is defined and not at the back, moves the cursor one step toward the back of L.
// If the cursor is defined and at the back, the cursor becomes undefined.
// If the cursor is undefined, does nothing.
void moveNext(List L);

// prepend()
// Inserts a new element into L.
// If L is non-empty, insertion takes place before the front element.
void prepend(List L, ListElement data);

// append()
// Inserts a new element into L.
// If L is non-empty, insertion takes place after the back element.
void append(List L, ListElement data);

// insertBefore()
// Inserts a new element before the cursor.
// Precondition: length(L) > 0, position(L) >= 0
void insertBefore(List L, ListElement data);

// insertAfter()
// Inserts a new element after the cursor.
// Precondition: length(L) > 0, position(L) >= 0
void insertAfter(List L, ListElement data);

// deleteFront()
// Deletes the front element.
// Precondition: length(L) > 0
void deleteFront(List L);

// deleteBack()
// Deletes the back element.
// Precondition: length(L) > 0
void deleteBack(List L);

// delete()
// Deletes the cursor element, making the cursor undefined.
// Precondition: length(L) > 0, position(L) >= 0
void delete(List L);

#endif


//-----------------------------------------------------------------------------
// Dictionary.h
// Hansa Atreya(hatreya)
// Header file for Dictionary ADT (CSE101 PA5)
//-----------------------------------------------------------------------------

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>
#include <stdio.h>

// Exported types -------------------------------------------------------------

typedef const char* keyType;   // string keys
typedef int valType;           // integer values

// Dictionary reference type
typedef struct DictionaryObj* Dictionary;


// Constructors-Destructors ---------------------------------------------------

// newDictionary()
// Returns a reference to a new empty Dictionary.
Dictionary newDictionary(void);

// freeDictionary()
// Frees all heap memory associated with *pD, and sets *pD to NULL.
void freeDictionary(Dictionary* pD);


// Access functions -----------------------------------------------------------

// size()
// Returns the number of key-value pairs in D.
int size(Dictionary D);

// contains()
// Returns true if D contains key k, false otherwise.
bool contains(Dictionary D, keyType k);

// getValue()
// Returns the value associated with key k.
// Pre: contains(D, k)
valType getValue(Dictionary D, keyType k);


// Manipulation procedures ----------------------------------------------------

// clear()
// Resets D to the empty state.
void clear(Dictionary D);

// setValue()
// If D contains key k, overwrite value with v.
// Otherwise insert new pair (k,v).
void setValue(Dictionary D, keyType k, valType v);

// removeKey()
// Deletes the pair with key k.
// Pre: contains(D, k)
void removeKey(Dictionary D, keyType k);


// Other operations -----------------------------------------------------------

// copy()
// Returns a new Dictionary with same key-value pairs as D.
Dictionary copy(Dictionary D);

// equals()
// Returns true if A and B contain identical pairs.
bool equals(Dictionary A, Dictionary B);

// printDictionary()
// Prints pairs in insertion order as:
// key : value
void printDictionary(FILE* out, Dictionary D);

// printDiagnostic()
// Prints internal table + data arrays for debugging.
void printDiagnostic(FILE* out, Dictionary D);

#endif


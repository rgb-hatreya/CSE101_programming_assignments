 //-----------------------------------------------------------------------------
// Dictionary.c
// Hansa Atreya (hatreya)
//-----------------------------------------------------------------------------

#include "Dictionary.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#define INITIAL_TABLE_SIZE 32
#define EMPTY   0
#define DELETED -1

// ---------------- Entry ----------------
typedef struct Entry {
    keyType key;
    valType val;
    unsigned long hash;
} Entry;

// ---------------- Dictionary ----------------
typedef struct DictionaryObj {
    Entry* data;       // dense array
    int dataSize;      // allocated size of data[]
    int dataNext;      // next insertion index

    int* table;        // sparse hash table
    int tableSize;

    int numPairs;
    int numDeleted;
} DictionaryObj;

// ---------------- Sentinel ----------------
static const char dummy[] = {255,0};   // deleted marker
static const keyType DataDeleted = dummy;
static const keyType DataEmpty   = NULL; // empty marker

// ---------------- Utilities ----------------
static char* my_strdup(const char* s){
    char* c = malloc(strlen(s)+1);
    assert(c);
    strcpy(c,s);
    return c;
}

// FNV-1a hash
static unsigned long hashFunc(const char* s){
    unsigned long hash = 14695981039346656037ULL;
    while(*s){
        hash ^= (unsigned long)(unsigned char)(*s++);
        hash *= 1099511628211ULL;
    }
    return hash;
}

// find slot for key in table
static int findSlot(Dictionary D, keyType k, unsigned long h){

    for(int j = 0; j < D->tableSize; j++){
        int i = (h + j) % D->tableSize;

        if(D->table[i] == EMPTY)
            return i;

        if(D->table[i] != DELETED){
            Entry e = D->data[D->table[i]];
            if(e.key != DataDeleted && strcmp(e.key, k) == 0)
                return i;
        }
    }
    return -1;   // table full
}


// ---------------- Table resizing ----------------
static void resizeTable(Dictionary D) {
    int oldSize = D->tableSize;
    int* oldTable = D->table;

    // double table size
    D->tableSize *= 2;
    D->table = calloc(D->tableSize, sizeof(int));
    assert(D->table);

    // rehash all active entries
    for (int i = 0; i < oldSize; i++) {
        if (oldTable[i] > 0) {  // active slot
            int idx = oldTable[i];
            Entry e = D->data[idx];
            unsigned long h = e.hash;
            int j;
            for (j = 0; j < D->tableSize; j++) {
                int slot = (h + j) % D->tableSize;
                if (D->table[slot] == EMPTY) {
                    D->table[slot] = idx;
                    break;
                }
            }
        }
    }

    free(oldTable);
    D->numDeleted = 0;
}

// ---------------- Data resizing ----------------
static void growData(Dictionary D){
    if(D->dataNext >= D->dataSize){
        D->dataSize *= 2;
        D->data = realloc(D->data, D->dataSize * sizeof(Entry));
        assert(D->data);
        for(int i=D->dataNext;i<D->dataSize;i++){
            D->data[i].key = NULL;
            D->data[i].val  = 0;
            D->data[i].hash = 0;
        }
    }
}

// ---------------- Constructors ----------------
Dictionary newDictionary(void){
    Dictionary D = malloc(sizeof(DictionaryObj));
    assert(D);

    D->dataSize = 12;
    D->dataNext = 1;
    D->data = malloc(D->dataSize * sizeof(Entry));
    assert(D->data);

    // first slot empty
    D->data[0].key  = NULL;
    D->data[0].val  = 0;
    D->data[0].hash = 0;

    // ALL UNUSED SLOTS = NULL
    for(int i=1;i<D->dataSize;i++){
        D->data[i].key  = NULL;
        D->data[i].val  = 0;
        D->data[i].hash = 0;
    }

    D->tableSize = INITIAL_TABLE_SIZE;
    D->table = calloc(D->tableSize,sizeof(int));
    assert(D->table);

    D->numPairs = 0;
    D->numDeleted = 0;
    return D;
}


void freeDictionary(Dictionary* pD){
    if(pD && *pD){
        Dictionary D = *pD;
        for(int i=1;i<D->dataNext;i++){
            if(D->data[i].key && D->data[i].key != DataDeleted)
                free((char*)D->data[i].key);
        }
        free(D->data);
        free(D->table);
        free(D);
        *pD = NULL;
    }
}

// ---------------- Access ----------------
int size(Dictionary D){ return D->numPairs; }

bool contains(Dictionary D, keyType k){
    unsigned long h = hashFunc(k);

    for(int j = 0; j < D->tableSize; j++){
        int i = (h + j) % D->tableSize;

        if(D->table[i] == EMPTY)
            return false;

        if(D->table[i] != DELETED){
            Entry e = D->data[D->table[i]];
            if(e.key != DataDeleted && strcmp(e.key,k)==0)
                return true;
        }
    }
    return false;
}

valType getValue(Dictionary D, keyType k){
    unsigned long h = hashFunc(k);
    int i = h % D->tableSize;
    while(D->table[i] != EMPTY){
        if(D->table[i] != DELETED){
            Entry e = D->data[D->table[i]];
            if(strcmp(e.key,k)==0) return e.val;
        }
        i = (i+1)%D->tableSize;
    }
    fprintf(stderr,"Dictionary Error: getValue() key not found\n");
    exit(1);
}

// ---------------- Manipulation ----------------
void clear(Dictionary D){
    for(int i=1;i<D->dataNext;i++){
        if(D->data[i].key && D->data[i].key != DataDeleted)
            free((char*)D->data[i].key);
    }
    for(int i=0;i<D->dataSize;i++){
        D->data[i].key  = (i==0 ? DataEmpty : DataDeleted);
        D->data[i].val  = 0;
        D->data[i].hash = 0;
    }
    memset(D->table,0,D->tableSize*sizeof(int));
    D->dataNext = 1;
    D->numPairs = 0;
    D->numDeleted = 0;
}

void setValue(Dictionary D, keyType k, valType v) {
    assert(D != NULL);
    assert(k != NULL);

   if ((D->numPairs + D->numDeleted) * 2 >= D->tableSize)
       resizeTable(D);

    unsigned long h = hashFunc(k);
    int i;
    // Find slot using linear probing
    for (i = 0; i < D->tableSize; i++) {
        int slot = (h + i) % D->tableSize;

        if (D->table[slot] == EMPTY || D->table[slot] == DELETED) {
            // Found free slot
            break;
        }

        int idx = D->table[slot];
        Entry e = D->data[idx];
        if (e.key != DataDeleted && strcmp(e.key, k) == 0) {
            // Key exists: update value
            D->data[idx].val = v;
            return;
        }
    }

    // Add new entry
    growData(D);
    int idx = D->dataNext++;
    D->data[idx].key = my_strdup(k);
    D->data[idx].val = v;
    D->data[idx].hash = h;

    D->table[(h + i) % D->tableSize] = idx;
    D->numPairs++;
}


void removeKey(Dictionary D, keyType k){
    assert(D != NULL);
    assert(k != NULL);

    unsigned long h = hashFunc(k);

    for(int j = 0; j < D->tableSize; j++){
        int i = (h + j) % D->tableSize;

        if(D->table[i] == EMPTY)
            break;

        if(D->table[i] != DELETED){
            int idx = D->table[i];
            Entry* e = &D->data[idx];

            if(e->key != DataDeleted && strcmp(e->key,k)==0){

                free((char*)e->key);
                e->key = DataDeleted;

                D->table[i] = DELETED;

                D->numPairs--;
                D->numDeleted++;
                return;
            }
        }
    }

    fprintf(stderr,"Dictionary Error: removeKey() key not found\n");
    exit(EXIT_FAILURE);
}

// ---------------- Other Ops ----------------
Dictionary copy(Dictionary D){
    Dictionary C = newDictionary();
    for(int i=1;i<D->dataNext;i++){
        if(D->data[i].key && D->data[i].key != DataDeleted)
            setValue(C,D->data[i].key,D->data[i].val);
    }
    return C;
}

bool equals(Dictionary A, Dictionary B){
    if(size(A)!=size(B)) return false;
    for(int i=1;i<A->dataNext;i++){
        if(A->data[i].key && A->data[i].key != DataDeleted){
            if(!contains(B,A->data[i].key)) return false;
            if(getValue(B,A->data[i].key) != A->data[i].val) return false;
        }
    }
    return true;
}

void printDictionary(FILE* out, Dictionary D){
    for(int i=1;i<D->dataNext;i++){
        if(D->data[i].key && D->data[i].key != DataDeleted)
            fprintf(out,"%s : %d\n",D->data[i].key,D->data[i].val);
    }
}

void printDiagnostic(FILE* out, Dictionary D){
    fprintf(out,"\nData: \n");
    for(int i=0;i<D->dataSize;i++){
        if(D->data[i].key == NULL)
            fprintf(out,"(null) : %d : %lu\n", D->data[i].val, D->data[i].hash);
        else if(D->data[i].key == DataDeleted)
            fprintf(out,"ÿ : %d : %lu\n", D->data[i].val, D->data[i].hash);
        else
            fprintf(out,"%s : %d : %lu\n", D->data[i].key, D->data[i].val, D->data[i].hash);
    }

    fprintf(out,"numPairs: %d\n",D->numPairs);
    fprintf(out,"numDeleted: %d\n",D->numDeleted);
    fprintf(out,"dataSize: %d\n",D->dataSize);
    fprintf(out,"dataNextIndex: %d\n",D->dataNext);

    double dataDensity = (D->dataNext>1) ? (double)D->numPairs/(D->dataNext-1) : 0.0;
    double tableLoad = (double)D->numPairs/D->tableSize;

    fprintf(out,"dataDensity: %.6f\n",dataDensity);

    fprintf(out,"\nTable: \n");
    for(int i=0;i<D->tableSize;i++)
        fprintf(out,"%d : %d\n",i,D->table[i]);

    fprintf(out,"tableSize: %d\n",D->tableSize);
    fprintf(out,"tableLoadFactor: %.6f\n",tableLoad);
}


// pa4, CSE101
// Hansa Atreya (hatreya)

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "Matrix.h"
#include "List.h"

// ==================== Private Structures ====================

typedef struct EntryObj {
    int col;
    double val;
} EntryObj;

typedef EntryObj* Entry;

typedef struct MatrixObj {
    int size;      // n x n
    int nnz;       // number of non-zero entries
    List* rows;    // array of Lists (1-based indexing)
} MatrixObj;


// ==================== Private Helpers ====================

static Entry newEntry(int c, double v) {
    Entry E = malloc(sizeof(EntryObj));
    E->col = c;
    E->val = v;
    return E;
}

static void freeEntry(Entry* pE) {
    if (pE && *pE) {
        free(*pE);
        *pE = NULL;
    }
}

static double vectorDot(List P, List Q) {
    double sum = 0.0;

    moveFront(P);
    moveFront(Q);

    while (position(P) >= 0 && position(Q) >= 0) {
        Entry E1 = (Entry)get(P);
        Entry E2 = (Entry)get(Q);

        if (E1->col == E2->col) {
            sum += E1->val * E2->val;
            moveNext(P);
            moveNext(Q);
        } else if (E1->col < E2->col) {
            moveNext(P);
        } else {
            moveNext(Q);
        }
    }

    return sum;
}


// ==================== Constructors / Destructors ====================

Matrix newMatrix(int n) {
    Matrix M = malloc(sizeof(MatrixObj));
    M->size = n;
    M->nnz = 0;

    M->rows = calloc(n + 1, sizeof(List));
    for (int i = 1; i <= n; i++) {
        M->rows[i] = newList();
    }

    return M;
}

void freeMatrix(Matrix* pM) {
    if (pM && *pM) {
        makeZero(*pM);
        free((*pM)->rows);
        free(*pM);
        *pM = NULL;
    }
}


// ==================== Access Functions ====================

int dimension(Matrix M) {
    return M->size;
}

int numNonZero(Matrix M) {
    return M->nnz;
}

bool equals(Matrix A, Matrix B) {
    if (A->size != B->size || A->nnz != B->nnz) return false;

    for (int i = 1; i <= A->size; i++) {
        List rowA = A->rows[i];
        List rowB = B->rows[i];

        if (length(rowA) != length(rowB)) return false;

        moveFront(rowA);
        moveFront(rowB);

        while (position(rowA) >= 0) {
            Entry E1 = (Entry)get(rowA);
            Entry E2 = (Entry)get(rowB);

            if (E1->col != E2->col || E1->val != E2->val)
                return false;

            moveNext(rowA);
            moveNext(rowB);
        }
    }

    return true;
}


// ==================== Manipulation ====================

void makeZero(Matrix M) {
    for (int i = 1; i <= M->size; i++) {
        List row = M->rows[i];
        moveFront(row);
        while (position(row) >= 0) {
            Entry E = (Entry)get(row);
            freeEntry(&E);
            moveNext(row);
        }
        clear(row);
    }
    M->nnz = 0;
}

void changeEntry(Matrix M, int i, int j, double x) {
    assert(1 <= i && i <= M->size);
    assert(1 <= j && j <= M->size);

    List row = M->rows[i];
    moveFront(row);

    while (position(row) >= 0) {
        Entry E = (Entry)get(row);

        if (E->col == j) {
            if (x == 0) {
                delete(row);
                freeEntry(&E);
                M->nnz--;
            } else {
                E->val = x;
            }
            return;
        }
        else if (E->col > j) {
            break;
        }

        moveNext(row);
    }

    if (x != 0) {
        Entry newE = newEntry(j, x);

        if (position(row) == -1) {
            append(row, newE);
        } else {
            insertBefore(row, newE);
        }

        M->nnz++;
    }
}


// ==================== Arithmetic ====================

Matrix copy(Matrix A) {
    Matrix C = newMatrix(A->size);

    for (int i = 1; i <= A->size; i++) {
        List row = A->rows[i];
        moveFront(row);
        while (position(row) >= 0) {
            Entry E = (Entry)get(row);
            changeEntry(C, i, E->col, E->val);
            moveNext(row);
        }
    }

    return C;
}

Matrix transpose(Matrix A) {
    Matrix T = newMatrix(A->size);

    for (int i = 1; i <= A->size; i++) {
        List row = A->rows[i];
        moveFront(row);
        while (position(row) >= 0) {
            Entry E = (Entry)get(row);
            changeEntry(T, E->col, i, E->val);
            moveNext(row);
        }
    }

    return T;
}

Matrix scalarMult(double x, Matrix A) {
    Matrix C = newMatrix(A->size);

    for (int i = 1; i <= A->size; i++) {
        List row = A->rows[i];
        moveFront(row);
        while (position(row) >= 0) {
            Entry E = (Entry)get(row);
            changeEntry(C, i, E->col, x * E->val);
            moveNext(row);
        }
    }

    return C;
}

Matrix sum(Matrix A, Matrix B) {
    assert(A != NULL && B != NULL);
    assert(A->size == B->size);

    if (A == B) {
        return scalarMult(2.0, A);
    }

    Matrix C = newMatrix(A->size);

    for (int i = 1; i <= A->size; i++) {

        List P = A->rows[i];
        List Q = B->rows[i];

        moveFront(P);
        moveFront(Q);

        while (position(P) >= 0 || position(Q) >= 0) {

            if (position(P) >= 0 && position(Q) >= 0) {

                Entry E1 = (Entry)get(P);
                Entry E2 = (Entry)get(Q);

                if (E1->col == E2->col) {
                    double v = E1->val + E2->val;
                    if (v != 0) {
                        changeEntry(C, i, E1->col, v);
                    }
                    moveNext(P);
                    moveNext(Q);
                }
                else if (E1->col < E2->col) {
                    changeEntry(C, i, E1->col, E1->val);
                    moveNext(P);
                }
                else {
                    changeEntry(C, i, E2->col, E2->val);
                    moveNext(Q);
                }
            }
            else if (position(P) >= 0) {
                Entry E1 = (Entry)get(P);
                changeEntry(C, i, E1->col, E1->val);
                moveNext(P);
            }
            else {
                Entry E2 = (Entry)get(Q);
                changeEntry(C, i, E2->col, E2->val);
                moveNext(Q);
            }
        }
    }

    return C;
}


Matrix diff(Matrix A, Matrix B) {
    Matrix negB = scalarMult(-1.0, B);
    Matrix C = sum(A, negB);
    freeMatrix(&negB);
    return C;
}

Matrix product(Matrix A, Matrix B) {
    assert(A->size == B->size);

    Matrix C = newMatrix(A->size);
    Matrix BT = transpose(B);

    for (int i = 1; i <= A->size; i++) {
        if (length(A->rows[i]) == 0) continue;

        for (int j = 1; j <= BT->size; j++) {
            if (length(BT->rows[j]) == 0) continue;

            double v = vectorDot(A->rows[i], BT->rows[j]);
            if (v != 0)
                changeEntry(C, i, j, v);
        }
    }

    freeMatrix(&BT);
    return C;
}


// ==================== Output ====================

void printMatrix(FILE* out, Matrix M) {
    for (int i = 1; i <= M->size; i++) {
        if (length(M->rows[i]) == 0) continue;

        fprintf(out, "%d: ", i);

        List row = M->rows[i];
        moveFront(row);

        while (position(row) >= 0) {
            Entry E = (Entry)get(row);
            fprintf(out, "(%d, %.1f) ", E->col, E->val);
            moveNext(row);
        }

        fprintf(out, "\n");
    }
}


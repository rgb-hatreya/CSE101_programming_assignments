//pa4, CSE101
// Hansa Atreya (hatreya)
#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"

int main(void) {

    int n = 3;
    Matrix A = newMatrix(n);
    Matrix B = newMatrix(n);

    changeEntry(A, 1, 1, 1.0);
    changeEntry(A, 1, 2, 2.0);
    changeEntry(A, 1, 3, 3.0);

    changeEntry(A, 2, 1, 4.0);
    changeEntry(A, 2, 2, 5.0);
    changeEntry(A, 2, 3, 6.0);

    changeEntry(A, 3, 1, 7.0);
    changeEntry(A, 3, 2, 8.0);
    changeEntry(A, 3, 3, 9.0);

    changeEntry(B, 1, 1, 1.0);
    changeEntry(B, 2, 2, 1.0);
    changeEntry(B, 3, 3, 1.0);

    printf("A has %d non-zero entries:\n", numNonZero(A));
    printMatrix(stdout, A);

    printf("\nB has %d non-zero entries:\n", numNonZero(B));
    printMatrix(stdout, B);

    Matrix C = scalarMult(2.0, A);
    printf("\n2*A has %d non-zero entries:\n", numNonZero(C));
    printMatrix(stdout, C);

    Matrix D = sum(A, B);
    printf("\nA+B has %d non-zero entries:\n", numNonZero(D));
    printMatrix(stdout, D);

    Matrix E = diff(A, B);
    printf("\nA-B has %d non-zero entries:\n", numNonZero(E));
    printMatrix(stdout, E);

    Matrix F = transpose(A);
    printf("\nTranspose(A) has %d non-zero entries:\n", numNonZero(F));
    printMatrix(stdout, F);

    Matrix G = product(A, B);
    printf("\nA*B has %d non-zero entries:\n", numNonZero(G));
    printMatrix(stdout, G);

    // Free all matrices
    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&C);
    freeMatrix(&D);
    freeMatrix(&E);
    freeMatrix(&F);
    freeMatrix(&G);

    return 0;
}


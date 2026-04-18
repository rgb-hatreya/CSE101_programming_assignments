//-----------------------------------------------------------------------------
// Sparse.c
// pa4
// Hansa Atreya (hatreya)
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"

int main(int argc, char* argv[]) {

    // Check command line arguments
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Open input file
    FILE* in = fopen(argv[1], "r");
    if (in == NULL) {
        fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    // Open output file
    FILE* out = fopen(argv[2], "w");
    if (out == NULL) {
        fprintf(stderr, "Unable to open file %s for writing\n", argv[2]);
        fclose(in);
        exit(EXIT_FAILURE);
    }

    int n, a, b;
    fscanf(in, "%d %d %d", &n, &a, &b);

    // Create matrices
    Matrix A = newMatrix(n);
    Matrix B = newMatrix(n);

    int i, j;
    double x;

    // Read entries for A
    for (int k = 0; k < a; k++) {
        fscanf(in, "%d %d %lf", &i, &j, &x);
        changeEntry(A, i, j, x);
    }

    // Read entries for B
    for (int k = 0; k < b; k++) {
        fscanf(in, "%d %d %lf", &i, &j, &x);
        changeEntry(B, i, j, x);
    }

    // Print A
    fprintf(out, "A has %d non-zero entries:\n", numNonZero(A));
    printMatrix(out, A);
    fprintf(out, "\n");

    // Print B
    fprintf(out, "B has %d non-zero entries:\n", numNonZero(B));
    printMatrix(out, B);
    fprintf(out, "\n");

    Matrix C;

    // (1.5)*A
    C = scalarMult(1.5, A);
    fprintf(out, "(1.5)*A =\n");
    printMatrix(out, C);
    fprintf(out, "\n");
    freeMatrix(&C);

    // A+B
    C = sum(A, B);
    fprintf(out, "A+B =\n");
    printMatrix(out, C);
    fprintf(out, "\n");
    freeMatrix(&C);

    // A+A
    C = sum(A, A);
    fprintf(out, "A+A =\n");
    printMatrix(out, C);
    fprintf(out, "\n");
    freeMatrix(&C);

    // B-A
    C = diff(B, A);
    fprintf(out, "B-A =\n");
    printMatrix(out, C);
    fprintf(out, "\n");
    freeMatrix(&C);

    // A-A
    C = diff(A, A);
    fprintf(out, "A-A =\n");
    printMatrix(out, C);
    fprintf(out, "\n");
    freeMatrix(&C);

    // Transpose(A)
    C = transpose(A);
    fprintf(out, "Transpose(A) =\n");
    printMatrix(out, C);
    fprintf(out, "\n");
    freeMatrix(&C);

    // A*B
    C = product(A, B);
    fprintf(out, "A*B =\n");
    printMatrix(out, C);
    fprintf(out, "\n");
    freeMatrix(&C);

    // B*B
    C = product(B, B);
    fprintf(out, "B*B =\n");
    printMatrix(out, C);
    freeMatrix(&C);

    // Free matrices
    freeMatrix(&A);
    freeMatrix(&B);

    // Close files
    fclose(in);
    fclose(out);

    return 0;
}


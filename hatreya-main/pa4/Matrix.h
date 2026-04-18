// Matrix.h
// pa4, CSE101
// Hansa Atreya (hatreya)

#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdbool.h>

// Opaque Matrix type
typedef struct MatrixObj* Matrix;

// Constructors-Destructors ---------------------------------------------------
Matrix newMatrix(int n);
void freeMatrix(Matrix* pM);

// Access functions -----------------------------------------------------------
int dimension(Matrix M);
int numNonZero(Matrix M);
bool equals(Matrix A, Matrix B);

// Manipulation procedures ----------------------------------------------------
void makeZero(Matrix M);
void changeEntry(Matrix M, int i, int j, double x);

// Matrix Arithmetic operations -----------------------------------------------
Matrix copy(Matrix A);
Matrix transpose(Matrix A);
Matrix scalarMult(double x, Matrix A);
Matrix sum(Matrix A, Matrix B);
Matrix diff(Matrix A, Matrix B);
Matrix product(Matrix A, Matrix B);

// Other operations -----------------------------------------------------------
void printMatrix(FILE* out, Matrix M);

#endif


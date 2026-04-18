 pa4, CSE101
Hansa Atreya (hatreya)

pa4 includes the files:

Sparse.c - The main client of pa4. Reads matrix data from an input file, constructs sparse matrices using the Matrix ADT, performs Matrix operations, and prints results in specifed format.
 
Matrix.c - Implementation of Matrix ADT using a Lists array.

Matrix.h - Matrix.c header file. Defines Matrix type and declares all public operations of Matrix.

MatrixTest.c - Test client for Matrix ADT. Verifies all the public operations before compilation into Sparse

List.c - Implementation of the modified List ADT (eliminates copyList() and equals())

List.h - The header file for the modified List ADT (stores void pointers instead of ints for the Matrix objs)

Makefile - Compiles the code in pa4 into the Sparse executable, and implements targets for building and cleaning.

README.md - This file, which describes the content and structure of the pa4 fileset.

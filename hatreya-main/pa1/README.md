README for pa1
Hansa Atreya (hatreya)
Jan 16 2026
pa1 includes:

List.h: List.h is the header file for the List ADT. It links all the code together, 
        defining the List type and all of the operators. It also indirectly points to the list struct.
List.c: List.c includes several different functions that are used to create a List ADT. It makes use of a doubly-linked list,
        and two structs: Node and ListObj. It implements the operators defined in the header file. 
ListTest.c: ListTest.c tests the List ADT, testing all of the functions in List.c, prints test outputs and verifies correct behavior.
Words.c: Words.c takes in two files, where the output will have lines of text, and the output will have the words from the 
         text arranged in alphabetical order. It indirectly sorts the array, discarding all characters excluded from the definition of "words". 
Makefile: Makefile makes the executables, builds ListTest through makeListTest, 
         and checks for memory leaks through makeWords and makeChecklist.
README.md: This file is the README.It summarizes all the files in the project, with any extra notes. 

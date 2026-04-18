# CSE101 Programming Assignment 6 – C++ List ADT
Hansa Atreya (hatreya)

Pa6 includes the files: 

- **List.cpp** – Implementation of the List ADT including cursor-based operations, concat(), cleanup(), copy constructor, destructor, and overloaded operators.
- **List.h** – Provided header file (not modified).
- **ListTest.cpp** – Test harness written to verify correctness of List operations, inspired by ListClient.cpp.
- **Shuffle.cpp** – Client program that uses the List ADT to simulate card shuffling.
- **Makefile** – Provided Makefile, slightly modified to compile ListTest instead of ListClient.
- **README.md** – This file.

//Pseudocode/notes for pa6

//List.cpp
// use std namespace
// https://stackoverflow.com/questions/1452721/whats-the-problem-with-using-namespace-std
// https://www.geeksforgeeks.org/cpp/why-it-is-important-to-write-using-namespace-std-in-cpp-program/

//Constructors/Destructors
// "doubly linked list of Node
// objects, with two dummy nodes at the front and the back. The empty state of the List will be represented
// by these two sentinel nodes, pointing to each other as next and prev, respectively. The value stored in the
// data fields of the dummy nodes can by anything you like, and will not be read from or written to. As you
//may be aware, dummy List nodes are useful for simplifying special cases that arise in the insertion and
// deletion operations." - pa6 doc

//length() its just num_elements(iterated in insert and erase functions)

// front() 
//https://www.reddit.com/r/learnprogramming/comments/173dd67/throwing_exception_in_c/
//https://en.cppreference.com/w/cpp/error/length_error.html#:~:text=class%20length_error;,Inheritance%20diagram
//return reference to front through the dummy node

// back() same as front(), but for back element

// position()  returns iterated pos_cursor (like length)

// peekNext()
// https://stackoverflow.com/questions/22978863/differences-between-out-of-range-range-error-and-over-underflow-error
//throw error if nothing in next position. Else, return the element at the next node

//peekPrev() same as peekNext, but with prev node.

//clear()
//Move to front. Iterate through list while erase next element

//moveFront() 
//move cursor to front dummy. Then move cursor  to the the node after frontdummy(real front). Set cursor position to 0

//moveBack()
//Same as moveFront but with backdummy. Set cursor position to number of elements

//moveNext()
//error if already at end. Set beforeCursor to current afterCursor value, then change pointer of Aftercursor to next. Iterate cursor position, return passed over 
// element

//movePrev()
//Reverse of moveNext

//insertAfter()
//allocate new node for new element. Set the position of the new node to the neighboring nodes of cursor. Make AfterCursor the new node so cursor is ahead of it. 
//Iterate num_elements

//insertBefore()
//Same as insertAfter, but swap the neighbors. Make BeforeCursor new node (to make new node position be ahead of cursor). Iterate num_elements and pos_cursor 
// because cursor pos changes by +1

//eraseAfter()
//Error if nothing after to be deleted. Set Node pointer to node to be deleted. Set Aftercursor to skip Node. set beforecursor next pointer to Aftercursor(skip) . 
//go back to aftercursor prev pointer, set it to beforecursor . now delete node is untethered. Delete Node. num_elements -1

//eraseBefore() 
//Error if nothing before to delete. Same as eraseAfter but instead of Aftercursor set to the skipped node, set BeforeCursor. Also pos_cursor -1(because node was 
//behind cursor so cursor -> left)

//findNext()
//while there are still elements ahead. check if next element matches. moveNext()                
// step over it return the new cursor position. If no match, moveNext again. If x not found return -1

//findNext()
//Reverse of findnext

//to_string()
//Start with string beginning “(“. end with adding “)” before returning string.
//start at first real node, iterate until back dummy append this node's value to string. add comma if not the last element 

//equals()
//First check if num_elements is equal for both
//Then: walk both from frontdummy to back. While A not at backdummy, check if the equivalent node on B is equal. If mismatch then false. Then keep going, return 
//true if full success. 

//Overloaded operators based on example file

//ostream& operator<<
//Converts list into string and then returns that. 

//operator==
//Check with equals()

//operator=
//No need if in x = x situation. 
//Make temp copy of list, switch all dummy and pointer values to be for the new list. Return ref too self like stack.cpp

//cleanup() 
//Outer loop — walk every node iteratively. Each value is used as reference to scan .
//Inner loop — start right after outer. for each outer node, scan everything after it, looking for nodes with data matching the outer node's data.

//If a duplicate is found. save pointer to node being deleted. advance inner BEFORE deleting temp node

//If deleted node was behind cursor, cursor shifts left to stay accurate

//If cursor's left pointer is being deleted, beforeCursor = beforeCursor->prev                
//If right, afterCursor = afterCursor->next

//Set prev and next to skip over temp node. Delete node, then num_elements -1

//If no duplicate node exists, just keep moving outer and inner forwards

//concat()
//Create new list. Copy 1st list into new one, then copy all of second. Move the cursor back to start before returning new list. 

//setAfter()
// same as beforeCursor but pos < length, and call afterCursor

// setbefore() 
// check that pos > 0, throw error if not
// call beforeCursor. overwrite node data with x

//Shuffle.cpp
//Logic: from pa6 assignment doc. riffle shuffle def: split deck into 1/2 then from each half(starting w/right) 
//insert 1 card until both hands empty. if an extra card, add to right


//Shuffle: 
//Init new deck(shuffled)
//Split list into halves. Assign each half into a new list. (extra card on right if existing)
// Starting with back half, insert 1st element. Then insert 1st element from front half. Continue to end of half lists. 

// Reset deck for rebuilding:
// For each list, check if there are still elements. Then Rebuild next element with moveNext and insertAfter, at end move cursor to front of deck. 

// main()
// To unshuffle deck: start with deck length
// Take new lsit and make a copy of its original state. Then call shuffle on it. For each shuffle , tally. Then, keep looping main until the shuffled deck and 
// original are equal 

//cout << n << " " << count << endl;  https://www.geeksforgeeks.org/cpp/cout-in-c/ , print deck size and shuffle count for table

//ListTest.cpp

//ListClient— insert function, concat, cleanup, operator==, copy, findnext, set

//planning:

//Init 2 Lists. 

//Insert:
//Use Insertafter to test inserting ints in a for loop (output: (6,7,8,9,10) ). Also use to make (2,4,6,8)

//Copy + equality:
//Copy a list, then use == operator to check if it copied correctly 

//Concat: 
//Simple concat cal to append L2 to L1

//Cleanup:
//Create new list with duplicate ints ({4,3,5,1,3,1,2,2,4}). Use insertAfter. Then run cleanup. Print pre/post cleanup for comparison

//Cursor/position:
//Start at front of a list. Move forward once. Return “should have move once” with position call

//Final correct output: 
//L1 = (6, 7, 8, 9, 10)
//copyL1 = (6, 7, 8, 9, 10)
//L1 == copyL1 ? true
//L2 = (8, 6, 4, 2)
//joined = L1.concat(L2) = (6, 7, 8, 9, 10, 8, 6, 4, 2)
//dup before cleanup = (4, 2, 2, 1, 3, 1, 5, 3, 4)
//dup after cleanup  = (4, 2, 1, 3, 5)
//Cursor moved once, position = 1

 




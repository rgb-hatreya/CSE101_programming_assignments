//-----------------------------------------------------------------------------
// ListTest.cpp
// cse101 pa6
// Hansa Atreya (hatreya)
// Alternate test harness for List ADT
//-----------------------------------------------------------------------------

#include <iostream>
#include "List.h"

using namespace std;

int main() {

    List L1, L2;

    // --- Build L1 using insertAfter ---
    for(int i=10; i>=6; i--){
        L1.insertAfter(i);
    }
    cout << "L1 = " << L1 << endl;

    // --- Test copy constructor ---
    List copyL1(L1);
    cout << "copyL1 = " << copyL1 << endl;

    // --- Equality check ---
    cout << "L1 == copyL1 ? "
         << (L1 == copyL1 ? "true" : "false") << endl;

    // --- Modify L2 differently ---
    for(int i=1; i<=4; i++){
        L2.insertAfter(i*2);   // 2,4,6,8
    }
    cout << "L2 = " << L2 << endl;

    // --- Test concat ---
    List joined = L1.concat(L2);
    cout << "joined = L1.concat(L2) = " << joined << endl;

    // --- Test cleanup with mixed duplicates ---
    List dup;
    int values[] = {4,3,5,1,3,1,2,2,4};
    for(int x : values){
        dup.insertAfter(x);
    }

    cout << "dup before cleanup = " << dup << endl;
    dup.cleanup();
    cout << "dup after cleanup  = " << dup << endl;

    // --- Extra cursor test ---
    dup.moveFront();
    dup.moveNext();
    cout << "Cursor moved once, position = "
         << dup.position() << endl;

    return 0;
}

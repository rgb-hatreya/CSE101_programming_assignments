//-----------------------------------------------------------------------------
// Shuffle.cpp
// Hansa Atreya (hatreya) 
// Top level client for PA6
//-----------------------------------------------------------------------------

#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

using namespace std;

// Performs one perfect shuffle of deck
void shuffle(List& deck){

    int n = deck.length();
    int splitPoint = n/2;

    List firstHalf, secondHalf;

    deck.moveFront();

    // --- split into halves ---
    for(int i = 0; i < n; i++){
        int value = deck.moveNext();

        if(i < splitPoint){
            firstHalf.insertAfter(value);
            firstHalf.moveNext();
        }else{
            secondHalf.insertAfter(value);
            secondHalf.moveNext();
        }
    }

    firstHalf.moveFront();
    secondHalf.moveFront();

    deck.clear();

    // --- interleave (secondHalf first) ---
    for(int i = 0; i < n; i++){

        if(secondHalf.position() < secondHalf.length()){
            deck.insertAfter(secondHalf.moveNext());
            deck.moveNext();
        }

        if(firstHalf.position() < firstHalf.length()){
            deck.insertAfter(firstHalf.moveNext());
            deck.moveNext();
        }
    }

    deck.moveFront();
}


// Main

int main(int argc, char* argv[]){

    if(argc != 2){
        throw invalid_argument("Usage: Shuffle <max deck size>");
    }

    int max = stoi(argv[1]);

    cout << "deck size shuffle count" << endl;
    cout << "------------------------------" << endl;

    for(int n = 1; n <= max; n++){

        List D;

        // build original deck
        for(int i = 0; i < n; i++){
            D.insertAfter(i);
            D.moveNext();
        }

        List original = D;  // copy
        int count = 0;

        do{
            shuffle(D);
            count++;
        }while(!(D == original));

        cout << n << " " << count << endl;
    }

    return 0;
}


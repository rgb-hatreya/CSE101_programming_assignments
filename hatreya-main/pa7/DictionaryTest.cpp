/***
* Hansa Atreya
* hatreya
* 2026 Winter CSE101 PA7
* DictionaryTest.cpp
* Wilson Xie 
* Test client for Dictionary.cpp, based on DictionaryClient.cpp
***/ 
#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

using namespace std;

int main(){

   string s;
   int x;
   string S[] =   {
                     "In",
                     "this",
                     "project",
                     "you",
                     "will",
                     "create",
                     "a",
                     "Dictionary",
                     "ADT",
                     "based",
                     "on",
                     "a",
                     "Binary",
                     "search",
                     "tree",
                     "this",
                     "time",
                     "in",
                     "C++",
                     "and",
                     "use",
                     "it",
                     "to",
                     "recreate",
                     "the",
                     "functionality",
                     "of",
                     "pa1",
                  };
   string T[] =   {
                     "Start",
                     "early",
                     "ask",
                     "plenty",
                     "of",
                     "questions",
                     "and",
                     "submit",
                     "your",
                     "project",
                     "by",
                     "the",
                     "due",
                     "date",      
                  };

   Dictionary A;
   Dictionary B;

   cout << endl;

   // insert new pairs into A, set A to size of array given
   int n = sizeof(S) / sizeof(S[0]);   // array size / element size
   for(int i=0; i<n; i++){
      A.setValue(S[i], i+1);
   }
   
   // call operator=()
   B = A;


   // copy Dictionary B
   Dictionary C = B;
   cout << "A.size() = " << B.size() << endl  << A << endl;
   cout << "B.size() = " << B.size() << endl  << B << endl;
   cout << "C.size() = " << C.size() << endl  << C << endl;

   // check contains()
   if( A.contains("a")){
        cout << "A contains " << A.getValue("a") << endl << endl;
   }
   else{
        cout << "A does not contain" << A.getValue("a")  << endl << endl;
   }

   // check operator==()
   cout << "A==B is " << (A==B?"true":"false") << endl;
   cout << "B==C is " << (B==C?"true":"false") << endl;
   cout << "C==A is " << (C==A?"true":"false") << endl << endl;

   // destroy A/B/C (will happen automatically at end of scope)


   // perform alterations on A
   cout << A.getValue("it") << endl;
   A.getValue("it") *= 7; // change the value associated with "it"
   cout << A.getValue("it") << endl << endl;

   // check state of A
   cout << "A.size() = " << A.size() << endl  << A << endl;
   cout << A.pre_string() << endl;

   // remove some pairs from A

   //for(int i=0; i<4; i++){
      //cout << "removing " << T[i] << " from Dictionary A" << endl; 
      //A.remove(T[i]);
   //}
   cout << "removing C++ from Dictionary A" << endl;
    A.remove("C++");

    cout << "removing Binary from Dictionary A" << endl;
    A.remove("Binary");

   cout << "after remove loop" << endl;

   // check state of A
   cout << "A.size() = " << A.size() << endl  << A << endl;
   cout << A.pre_string() << endl;

   // clear B and check its state
   cout << "before clearing, B.size() = " << B.size() << endl  << A << endl;
   B.clear();
   cout << "after clearing, B.size() = " << B.size() << endl  << A << endl;


   // Test forward iteration on A. simplified logic from DictionaryClient for forward and reverse
   cout << "Iterating A from smallest to largest:" << endl;
   for(A.begin(); A.hasCurrent(); A.next()){
      //s = A.currentKey();
      //x = A.currentVal();
      cout << "(" << A.currentKey() << ", " << A.currentVal() << ") ";
   }
   cout << endl << endl;

   // do reverse iteration on A
   cout << "Iterating A from largest to smallest:" << endl;
   for(A.end(); A.hasCurrent(); A.prev()){
      //s = A.currentKey();
      //x = A.currentVal();
      cout << "(" << A.currentKey() << ", " << A.currentVal() << ") ";
   }
   cout << endl << endl;


  

   return( EXIT_SUCCESS );
}

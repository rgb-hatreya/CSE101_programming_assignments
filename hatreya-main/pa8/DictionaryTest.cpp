/***
* Hansa Atreya
* hatreya
* 2026 Winter CSE101 PA8
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

   string S[] =   { // words to insert
                     "Who",
                     "are",
                     "you",
                     "What",
                     "are",
                     "you",
                     "doing",
                     "in",
                     "this",
                     "house",
                     "the",
                     "man",
                     "demands",
                     "somehow",
                     "managing",
                     "a",
                     "hiss",
                     "and",
                     "a",
                     "roar",
                     "at",
                     "the",
                     "same",
                     "time"
                  };
    string T[] =   {
                     "Who",
                     "are",
                     "you",
                     "What",
                     "doing",
                     "in",
                     "this",
                     "house",
                     "the",
                     "man",
                     "demands",
                     "somehow",
                     "managing",
                  };
 

   Dictionary A;
   Dictionary B;

   cout << endl;

   // insert some pairs into A
   for(int i=0; i<24; i++){
      A.setValue(S[i], i+1);
   }
   
   // call operator=()
   B = A;

   B.setValue("grabs", 101);
   B.setValue("eye", 102);
   B.setValue("him", 103);

   // call copy constructor
   Dictionary C = B;

   cout << "A.size() = " << A.size() << endl  << A << endl;
   cout << "B.size() = " << B.size() << endl  << B << endl;
   cout << "C.size() = " << C.size() << endl  << C << endl;

   // check copy constructor
   cout << "copy constructor creates identical trees: " << endl;
   cout << ((C.pre_string()==B.pre_string())?"true":"false") << endl;
   cout << endl;

   // check operator==()
   cout << "A==B is " << (A==B?"true":"false") << endl;
   cout << "B==C is " << (B==C?"true":"false") << endl;
   cout << "C==A is " << (C==A?"true":"false") << endl << endl;

   // perform alterations on A
   cout << "A.getValue(\"house\") = " << A.getValue("house") << endl;
   A.getValue("house") *= 4; // change the value associated with "hemiolia"
   cout << "A.getValue(\"house\") = " << A.getValue("house") << endl << endl;

   // check state of A
   cout << "A.size() = " << A.size() << endl  << A << endl;
   cout << "A pre-order: " << endl << A.pre_string() << endl;

   // remove some pairs from A
   //for(int i=0; i<13; i++){ 
   //   A.remove(T[i]);
   //}

   // check state of A
   //cout << "A.size() = " << A.size() << endl  << A << endl;
  // cout << "A pre-order: " << endl << A.pre_string() << endl;

   // do forward iteration on B
   cout << "forward iteration on B, changing values:" << endl;
   for(B.begin(); B.hasCurrent(); B.next()){
      cout << "("+B.currentKey()+", " << B.currentVal() << ") ";
      B.currentVal()++;  // change value
      cout << "("+B.currentKey()+", " << B.currentVal() << ")\n";
   }
   cout << endl;

   // do reverse iteration on C
   cout << "reverse iteration on C, changing values" << endl;
   for(C.end(); C.hasCurrent(); C.prev()){
      cout << "("+C.currentKey()+", " << C.currentVal() << ") ";
      C.currentVal()++;  // change value
      cout << "("+C.currentKey()+", " << C.currentVal() << ")\n";
   }
   cout << endl;
   
   // check exceptions
   cout << "test pre-condition errors:" << endl;
   try{
      A.getValue("blah");
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.remove("blah");
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.currentKey();
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.currentVal();
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }  
   try{
      A.next();
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.prev();
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   cout << endl;  

   //rbt tests

   // left + right rotate  then check if same 
{
Dictionary D1;
      D1.setValue("a", 1);
      D1.setValue("b", 2);
      D1.setValue("c", 3); // right-right -> LeftRotate("a")
 
      Dictionary D2;
      D2.setValue("c", 3);
      D2.setValue("b", 2);
      D2.setValue("a", 1); // left-left -> RightRotate("c")
 
      cout << "after LeftRotate: " << D1.pre_string();
      cout << "after RightRotate: " << D2.pre_string();
      cout << "Do the trees match?: " << (D1.pre_string()==D2.pre_string() ? "true" : "false") << endl << endl;
      
}
// insertfixup + insert logic in setvalue
// Part 1: insert logic: verify setValue function. insert "d","b","f" -> size 3, sorted order confirmed via to_string.
// overwrite "b" with a new value -> size still 3, value updated.
// Part 2: InsertFixUp: insert "a" whose uncle is "f" (red)  as a case 1 example:
// recolor b and f black, d red, root forced back to black. No rotation. confirm with pre_string.
{
    Dictionary D;
      D.setValue("d", 4);
      D.setValue("b", 2);
      D.setValue("f", 6);
 
      // insert 
      cout << "size after 3 inserts (expect 3): " << D.size() << endl;
      cout << "in-order (expect b d f):" << endl << D.to_string();
 
      
      D.setValue("b", 99);
      cout << "size after overwrite (expect 3): " << D.size() << endl;
      cout << "updated value of b (expect 99): " << D.getValue("b") << endl;
 
      // restore b then insert "a" to trigger InsertFixUp
      D.setValue("b", 2);
      D.setValue("a", 1); // uncle "f" is red -> recolor only, no rotate
      cout << "pre-order after InsertFixUp case 1:" << endl << D.pre_string();
      // out should be: d  b  a(RED)  f  (b and f black, no structural rotation)
   }
   cout << endl;

   // delete+deletefixup
   // Part 1: RB_Delete remove red leaf "c"
   // Part 2: RB_Delete + RB_DeleteFixUp now"a" is now a black leaf. Removing it creates a double black; sibling (nil) is black
   // with black children → DeleteFixUp case 2: recolor, push to root. Then confirm  with pre_string
   cout << "=== RB_Delete + RB_DeleteFixUp ===" << endl;
   {
      Dictionary D;
      D.setValue("b", 2);
      D.setValue("a", 1);
      D.setValue("c", 3);
      cout << "before: " << D.pre_string();
 
      D.remove("c"); // red leaf delete
      cout << "after removing red leaf 'c': " << D.pre_string();
 
      D.remove("a"); // black leaf RB_Delete triggers RB_DeleteFixUp
      cout << "after removing black leaf 'a': " << D.pre_string();
      cout << "size (expect 1): " << D.size() << endl << endl;
   }

   //transplant
   {
      Dictionary D;
      D.setValue("b", 2);
      D.setValue("a", 1);
      D.remove("b"); // root replaced by left child via RB_Transplant
      cout << "contains 'b' (expect 0): " << D.contains("b") << endl;
      cout << "contains 'a' (expect 1): " << D.contains("a") << endl << endl;
   }

   return( EXIT_SUCCESS );
}


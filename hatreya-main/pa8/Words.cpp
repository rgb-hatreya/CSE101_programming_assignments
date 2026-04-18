/***
* Hansa Atreya
* hatreya
* 2026 Winter CSE101 PA8 ( same as pa7)
* Words.cpp
* 
* 
* Top level client for Dictionary.cpp
***/ 
#include<iostream>
#include<fstream>
#include<string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Dictionary.h"

// No MAX_LENGTH 
using namespace std;

int main(int argc, char * argv[]){

   //int token_count, line_count;
   size_t start, end, length; //changed from begin and len for readability
   ifstream in;
   ofstream out;
   string line;
   string tokenBuffer;
   string token;
   //string delim = " "; only need one delim
   string delim = " \n\r\f\v\t\\\"\',<.>/?;:[{]}|`~!@#$^&*()-_=+0123456789"; // added \n\r\f\v to delim based on ED post

   // check command line for correct number of arguments
   if( argc != 3 ){
      cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
      return(EXIT_FAILURE);
   }

   // open files for reading and writing 
   in.open(argv[1]);
   if( !in.is_open() ){
      cerr << "Unable to open file " << argv[1] << " for reading" << endl;
      return(EXIT_FAILURE);
   }

   out.open(argv[2]);
   if( !out.is_open() ){
      cerr << "Unable to open file " << argv[2] << " for writing" << endl;
      return(EXIT_FAILURE);
   }

    Dictionary D; //declare Dictionary
    int counter = 0; // initialize unique words counter
   // read each line of input file, then count and print tokens 
  
    while (std::getline(in, line)){ // While there are lines in the input file + reads them in
        length = line.length();
        start = min(line.find_first_not_of(delim, 0), length); // start = 1st character not in delim
        end = start; 

        while (start < length){
            end = min(line.find_first_of(delim, start), length); // push end past all non-delimiter characters
            token = line.substr(start, end - start); //extract token 
            if( token.length() > 0 ){
                if( !D.contains(token) ){        // if D does not contain token
                D.setValue(token, counter);   // insert (token, counter)
                counter++;                    // counter = counter + 1
                }
            }
            //begin = min(line.find_first_not_of(delim, end), length); //extract next token, push begin past next delim characters
            start = std::min(line.find_first_not_of(delim, end), (size_t)length); // using size_t to keep same type https://en.cppreference.com/w/c/types/size_t.html
        }   //STILL NOT WORKING. get help tmw. I GOT IT WHEEEE it was begin instead of start. 
    }
      
    //start iterator at first key in dictionary
    //D.begin();
    //while (D.hasCurrent()){ //while dictionary has a current element
        //out << D.currentKey() << " " << D.currentVal() << "\n"; //write currentKey and currentVal to output file
        //D.next(); //move iterator to next element
    //}
    // print list of values
    out << "(";

    D.begin();
    while (D.hasCurrent()) {
        out << D.currentVal();
        D.next();
        if (D.hasCurrent()) {
            out << ", ";
        }
    }

    out << ")" << "\n\n";   // blank line before words

    // print words
    D.begin();
    while (D.hasCurrent()) {
        out << D.currentKey() << "\n";
        D.next();
    }
   // close files 
   in.close();
   out.close();

   return(EXIT_SUCCESS);
}



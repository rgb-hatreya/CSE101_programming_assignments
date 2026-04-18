/***
* Hansa Atreya
* hatreya
* 2026 Winter CSE101 PA8
* WordFrequency.cpp
* https://claude.ai/share/7e40369c-7545-42d6-9188-0782e574cfab
* Top Level Client for RBT Dictionary ADT. 
***/ 
#include<iostream>
#include<fstream>
#include<string>
#include "Dictionary.h"

// No MAX_LENGTH 
using namespace std;

int main(int argc, char* argv[]) { //main adapted from pa7 Words.cpp
    //int token_count, line_count;
   size_t start, end, length; 
   ifstream in;
   ofstream out;
   string line;
   string tokenBuffer;
   string token;
    string delim = " \t\n\r\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";  

    // check command line for correct number of arguments (taken from pa7)
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

    while (std::getline(in, line)){ // While there are lines in the input file + reads them in (loop adapted from Words.cpp)
        length = line.length();
        start = min(line.find_first_not_of(delim, 0), length); // start = 1st character not in delim
        end = start;
        while (start < length){
            end = min(line.find_first_of(delim, start), length); // push end past all non-delimiter characters
            token = line.substr(start, end - start); //extract token 

            for(int i = 0; i < (int)token.length(); i++){  //changed token loop to convert tolower and then use getvalue/setvalue to modify values
                token[i] = tolower(token[i]); //convert to lowercase
            }
            //count freq
            if (D.contains(token)){
                D.getValue(token)++; // add tally to reference 
            }
         
            else {
            D.setValue(token, 1);  // first occurrence
            }
        
            
            start = std::min(line.find_first_not_of(delim, end), (size_t)length); // using size_t to keep same type https://en.cppreference.com/w/c/types/size_t.html
        }   
    } 
    
    out << D << endl; //print Dictionary directly to outputfile 


    //parse indiv words on each line 
    //convert each word to all lower case characters
    //then place it (as key) in a Dictionary
    //check if word is there (contains())
    //each new occurence of unique word adds 1 to frequency (value) use getvalue
    //If it is a new word, add it using setValue()
    //use find_first_of() and find_first_not_of() to tokenize around string delim


}


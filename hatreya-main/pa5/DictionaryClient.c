//-----------------------------------------------------------------------------
// DictionaryClient.c
// Test client for the Dictionary ADT
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Dictionary.h"

#define MAX_LEN 180

int main(int argc, char* argv[]){

   Dictionary A = newDictionary();
   int i;
   int  value[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 
                   19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29};
   char* word[] = {"one","two","three","four","five","six","seven","eight",
                   "nine","ten","eleven","twelve","thirteen","fourteen",
                   "fifteen","sixteen","seventeen","eighteen","nineteen",
                   "twenty","twenty-one","twenty-two","twenty-three","twenty-four",
                   "twenty-five","twenty-six","twenty-seven","twenty-eight",
                   "twenty-nine"};


   for(i=0; i<10; i++){
      setValue(A, word[i], value[i]);
   }

   printf("\n");
   printf("***print diagnostic*************************\n");
   printDiagnostic(stdout, A);
   printf("********************************************\n");

   for(i=3; i<10; i++){
      removeKey(A, word[i]);
   }

   printf("\n");
   printf("***print diagnostic*************************\n");
   printDiagnostic(stdout, A);
   printf("********************************************\n");

   for(i=10; i<15; i++){
      setValue(A, word[i], value[i]);
   }

   printf("\n");
   printf("***print diagnostic*************************\n");
   printDiagnostic(stdout, A);
   printf("********************************************\n");

   for(i=15; i<29; i++){
      setValue(A, word[i], value[i]);
   }

   printf("\n");
   printf("***print diagnostic*************************\n");
   printDiagnostic(stdout, A);
   printf("********************************************\n");

   printf("\n");
   printf("***print dictionary*************************\n");
   printDictionary(stdout, A);
   printf("********************************************\n");
   printf("\n");

   freeDictionary(&A);

   return(EXIT_SUCCESS);
}

CSE 101 – Programming Assignment 7
Dictionary ADT using Binary Search Tree in C++ /***
* Hansa Atreya
* hatreya
* 2026 Winter CSE101 PA7
* README.md
* List of submitted files and other relevant information ***/
Files
1. README.md:  This file. Contains a list of submitted files with brief explanations and notes for the grader.
2. Makefile: Provided Makefile which builds the executables.
3. Dictionary.h: Provided header file defining the RBT Dictionary ADT interface. 
4. Dictionary.cpp: Written by me. Contains the main implementation of the Dictionary ADT, modified from pa7.
5. DictionaryTest.cpp: Written by me., based on example file and pa7. A test client used to verify the functionality and correctness of the Dictionary ADT.
6. Words.cpp:  Written by me. A client program (unchanged from pa7) that uses the Dictionary ADT.
7. WordFrequency.cpp Written by me. Based heavily off of Words.cpp. A client program that reads text input and uses the Dictionary ADT to compute and display word frequencies. Used Claude to help with conceptual breakdown and planning https://claude.ai/share/7e40369c-7545-42d6-9188-0782e574cfab


pa8 planning:

use pa7 files and make mods as said in doc.
take rbt psuedocode from examples


init color with 0/1 int as black, red. start with color = rdd because new node always red.

for RBT helper functions, use given pseudocode from /examples https://www.geeksforgeeks.org/dsa/introduction-to-red-black-tree/
LeftRotate(T, x)
   // set y
   y = x.right 
   
   // turn y's left subtree into x's right subtree
   x.right = y.left 
   if y.left != T.nil     // not necessary if using sentinal nil node
      y.left.parent = x
   
   // link y's parent to x
   y.parent = x.parent 
   if x.parent == T.nil
      T.root = y
   else if x == x.parent.left
      x.parent.left = y
   else 
      x.parent.right = y
   
   // put x on y's left
   y.left = x 
   x.parent = y

RightRotate(T, x)
   // set y
   y = x.left 
   
   // turn y's right subtree into x's left subtree
   x.left = y.right 
   if y.right != T.nil  // not necessary if using sentinal nil node
      y.right.parent = x
   
   // link y's parent to x
   y.parent = x.parent 
   if x.parent == T.nil
      T.root = y
   else if x == x.parent.right
      x.parent.right = y
   else 
      x.parent.left = y
   
   // put x on y's right
   y.right = x 
   x.parent = y   

RB_InsertFixUp(T, z)
   while z.parent.color == RED
      if z.parent == z.parent.parent.left
         y = z.parent.parent.right
         if y.color == RED
            z.parent.color = BLACK              // case 1
            y.color = BLACK                     // case 1
            z.parent.parent.color = RED         // case 1
            z = z.parent.parent                 // case 1
         else 
            if z == z.parent.right
               z = z.parent                     // case 2
               LeftRotate(T, z)                 // case 2
            z.parent.color = BLACK              // case 3
            z.parent.parent.color = RED         // case 3
            RightRotate(T, z.parent.parent)     // case 3
      else 
         y = z.parent.parent.left
         if y.color == RED
            z.parent.color = BLACK              // case 4
            y.color = BLACK                     // case 4
            z.parent.parent.color = RED         // case 4
            z = z.parent.parent                 // case 4
         else 
            if z == z.parent.left
               z = z.parent                     // case 5
               RightRotate(T, z)                // case 5
            z.parent.color = BLACK              // case 6
            z.parent.parent.color = RED         // case 6
            LeftRotate(T, z.parent.parent)      // case 6
   T.root.color = BLACK

RB_Insert(T, z)
   y = T.nil
   x = T.root
   while x != T.nil
      y = x
      if z.key < x.key
         x = x.left
      else 
         x = x.right
   z.parent = y
   if y == T.nil
      T.root = z
   else if z.key < y.key
      y.left = z
   else 
      y.right = z
   z.left = T.nil
   z.right = T.nil
   z.color = RED
   RB_InsertFixUp(T, z)

RB_Transplant(T, u, v)
   if u.parent == T.nil
      T.root = v
   else if u == u.parent.left
      u.parent.left = v
   else 
      u.parent.right = v
   v.parent = u.parent

RB_DeleteFixUp(T, x)
   while x != T.root and x.color == BLACK
      if x == x.parent.left
         w = x.parent.right
         if w.color == RED
            w.color = BLACK                        // case 1
            x.parent.color = RED                   // case 1
            LeftRotate(T, x.parent)                // case 1
            w = x.parent.right                     // case 1
         if w.left.color == BLACK and w.right.color == BLACK
            w.color = RED                          // case 2
            x = x.parent                           // case 2
         else 
            if w.right.color == BLACK
               w.left.color = BLACK                // case 3
               w.color = RED                       // case 3
               RightRotate(T, w)                   // case 3
               w = x.parent.right                  // case 3
            w.color = x.parent.color               // case 4
            x.parent.color = BLACK                 // case 4
            w.right.color = BLACK                  // case 4
            LeftRotate(T, x.parent)                // case 4
            x = T.root                             // case 4
      else 
         w = x.parent.left
         if w.color == RED
            w.color = BLACK                        // case 5
            x.parent.color = RED                   // case 5
            RightRotate(T, x.parent)               // case 5
            w = x.parent.left                      // case 5
         if w.right.color == BLACK and w.left.color == BLACK
            w.color = RED                          // case 6
            x = x.parent                           // case 6
         else 
            if w.left.color == BLACK
               w.right.color = BLACK               // case 7
               w.color = RED                       // case 7
               LeftRotate(T, w)                    // case 7
               w = x.parent.left                   // case 7
            w.color = x.parent.color               // case 8
            x.parent.color = BLACK                 // case 8
            w.left.color = BLACK                   // case 8
            RightRotate(T, x.parent)               // case 8
            x = T.root                             // case 8
   x.color = BLACK

RB_Delete(T, z)
   y = z
   y_original_color = y.color
   if z.left == T.nil
      x = z.right
      RB_Transplant(T, z, z.right)
   else if z.right == T.nil
      x = z.left
      RB_Transplant(T, z, z.left)
   else 
      y = TreeMinimum(z.right)
      y_original_color = y.color
      x = y.right
      if y.parent == z
         x.parent = y
      else 
         RB_Transplant(T, y, y.right)
         y.right = z.right
         y.right.parent = y
      RB_Transplant(T, z, y)
      y.left = z.left
      y.left.parent = y
      y.color = z.color
   if y_original_color == BLACK
      RB_DeleteFixUp(T, x)

modify functions: remove, setvalue, iterators, what else?. 

WordFrequency
It will read in each line of a file, parse the individual words on each line,
convert each word to all lower case characters, then place it (as key) in a Dictionary. The number of times
a given word is encountered (its frequency) will also be stored (as value) in the Dictionary. Thus, as your
program is reading in words, it should first check to see if the word (key) is already present, using
contains(). If it is a new word, add it using setValue(). If it already exists, increment the
corresponding value by calling getValue(). When studying the file Dictionary.h, you will note that the
getValue() function returns a reference to a value, which can then be used to alter that value. Use the
example FileIO.cpp posted in /Examples/C++/FileIO as the starting point for WordFrequency.cpp, since
much of what you need is already there. The program FileIO.cpp contains a string variable called delim,
which is initialized to be a single space.
string delim = " ";
This is the delimiter used by the string functions find_first_of() and find_first_not_of() to
determine which characters belong to tokens, and which do not. Thus FileIO.cpp tokenizes the file around
spaces. Your program WordFrequency.cpp will instead tokenize around a larger set of characters. The
words in our file will be substrings that contain only alphabetic characters. To accomplish this, you can
reset delim as follows.
string delim = " \t\n\r\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";
So, to parse the input file, remove all whitespace, punctuation and special characters. What's left are the
words to be placed in the Dictionary, along with their frequencies.
Once all the words from an input file are placed in the Dictionary, along with their frequences, your program
WordFrequency.cpp will print the Dictionary to the output file. 



claude: https://claude.ai/share/7e40369c-7545-42d6-9188-0782e574cfab
The outer while(getline) loop, the start/end/length variables, and the inner while(start < length) loop using find_first_not_of and find_first_of are all directly reusable as-is.
What changes — the token handling block:
In Words.cpp, once you have a token you check if its new and assign it an incrementing counter as its value. In WordFrequency.cpp, the logic flips to frequency counting:

First, lowercase the token (loop over characters converting each to lowercase) before doing anything else
Then, check if the word already exists in the Dictionary using contains()
If it does exist, retrieve the current count with getValue(), then overwrite it with setValue() using that count + 1
If it does not exist, insert it fresh with setValue() using 1 as the starting frequency.

Words.cpp uses the Dictionary value as an index (a unique ID per word). WordFrequency.cpp uses the value as a tally (how many times that word has appeared). The tokenizer doesn't care — it just hands you tokens, and you decide what to do with them.
Output is also simpler: since the Dictionary is already sorted by key (alphabetically), you just iterate from begin() to end, printing currentKey() and currentVal() — no need for the two-pass output that Words.cpp does.
The main function signature also needs fixing — int main should be int main(int argc, char* argv[]), and youll need to declare in, out, line, token, start, end, length the same way as in Words.cpp.

DictionaryTest: 
pull from DictionaryClient as in pa7. edit existing tests . add tests for RBT helpers

left + right rotate  then check if same 

insertfixup + insert logic in setvalue

transplant 

delete+deletefixup

// LeftRotate + RightRotate
insert a, b, c into D1         // will trigger LeftRotate
insert c, b, a into D2         // will trigger RightRotate
check D1.pre_string == D2.pre_string

// InsertFixUp + setValue insert logic
insert d, b, f into Dict
check size == 3
check to_string is sorted
overwrite b with 99, check size still 3, check getValue(b) == 99
restore b, insert a            // uncle f is red,  recolor only
check pre_string shows no rotation

// RB_Delete + RB_DeleteFixUp
insert b, a, c into D
remove c                       // red leaf, no fixup
remove a                       // black leaf, triggers DeleteFixUp
check size == 1

// RB_Transplant
insert b, a into D
remove b                       // left child a takes root via Transplant
check contains(b) == false
check contains(a) == true


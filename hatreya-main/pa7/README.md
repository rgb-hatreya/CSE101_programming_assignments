# CSE 101 – Programming Assignment 7  
Dictionary ADT using Binary Search Tree in C++
/***
* Hansa Atreya
* hatreya
* 2026 Winter CSE101 PA7
* README.md
* List of submitted files and other relevant information
***/ 

Files

1. README.md 
   This file. Contains a list of submitted files with brief explanations and notes for the grader.

2. Makefile  
   Provided Makefile which builds the executables. 

3. **Dictionary.h**  
   Header file defining the ADT. Contains the public interface, typedefs, and helper function declarations,
though not all helpers were used.

4. **Dictionary.cpp**  
   Implementation of the ADT using a Binary Search Tree. Includes all required operations and several helper functions.

5. **DictionaryTest.cpp**  
   Test client for the ADT based on DictionaryClient, checked by tutors/TAs in office hours. 

6. **Words.cpp**  
   Client program that reads an input file, inserts unique words into a Dictionary, and prints the results in insertion order, like the pa1 ADT. AI help was used to plan this client, under guidance of TA: https://claude.ai/share/e72dcf1e-a37d-44f0-8c37-2b3c45e284a5

planning, notes, psuedocode, etc:
pa7 notes

Dictionary.cpp

// Node Constructor
Node(k, v):
    key    = k
    val    = v
    parent = null
    left   = null
    right  = null

// Helper Functions ----------------------------------------------------
inorderstring:
check that R exists 
inOrderString(s, R->left)
    append to s: R.key
    s+ :
    append to s tostring(R.val) because val is int
    s+ newline 
    inOrderString(s, R->right)

preorderString:
make sure root exists
add to s (R key)
add newline
call recursively for left, right child

findMin:
    if R == nil: return nil
    while R.left != nil: R = R.left
    return R

findMax:
    if R == nil: return nil
    while R.right != nil: R = R.right
    return R

findNext:
    if N == nil: return nil
    if N has right child: return findMin(N.right)
    P = N.parent
    while P != nil and N == P.right:
        N = P
        P = P.parent
    return P

findPrev:
    if N == nil: return nil
    if N has left child: return findMax(N.left)
    P = N.parent
    while P != nil and N == P.left:
        N = P
        P = P.parent
    return P

// Recursively inserts a deep copy of the subtree rooted at R into this
// Dictionary. Recursion terminates at N.
preOrderCopy:
    if R == N: return
    insert R.key, R.val into this Dictionary (setvalue)
    if R has left child:  preOrderCopy(R.left, N)
    if R has right child: preOrderCopy(R.right, N)

// Deletes all Nodes in the subtree rooted at R.
postOrderDelete:
    if R == nil: return
    postOrderDelete(R.left)
    postOrderDelete(R.right)
    delete R

// Constructors/Destructors ----------------------------------------------------

// Creates new Dictionary in the empty state.
Dictionary():
    create nil node with dummy key/val
    nil.left = nil.right = nil.parent = nil
    root = nil
    current = nil
    num_pairs = 0

// Copy constructor
Dictionary(D):
    initialize empty Dictionary
    preOrderCopy(D.root, D.nil)

// Destructor
~Dictionary():
    clear()
    delete nil

// Access Functions ----------------------------------------------------

// Returns the size of this Dictionary.
size():
    return num_pairs

// Returns true if there exists a pair such that key==k, and returns false otherwise.
contains:
    cur = root
    while cur != nil:
        if k == cur.key: return true
        else if k < cur.key: cur = cur.left
        else: cur = cur.right
    return false

// Returns a reference to the value corresponding to key k.
getValue:
    cur = root
    while cur != nil:
        if k == cur.key: return cur.val
        else if k < cur.key: cur = cur.left
        else: cur = cur.right
    throw error "key not found"

// Returns true if the current iterator is defined, returns false otherwise.
hasCurrent():
    return current != nil

// Returns current key using hasCurrent
currentKey():
    if not hasCurrent(): throw error "current is undefined"
    return current.key

// Returns current value using hasCurrent
currentVal():
    if not hasCurrent(): throw error "current is undefined"
    return current.val

// Manipulation Procedures ----------------------------------------------------

// Resets D to the empty state using post order delete
clear():
    postOrderDelete(root)
    root = nil
    current = nil
    num_pairs = 0

// If D contains key k, overwrite value with v. Otherwise insert new pair (k,v).
setValue(k, v):
    cur = root, parent = nil
    while cur != nil:
        if k == cur.key: overwrite cur.val = v, return
        parent = cur
        if k < cur.key: cur = cur.left
        else: cur = cur.right
    create new node n with key k, val v
    n.left = n.right = nil, n.parent = parent
    if parent == nil: root = n
    else if k < parent.key: parent.left = n
    else: parent.right = n
    num_pairs++

// Deletes the pair where key==k. If it is current, then current becomes undefined.
// Uses contains() for checking key existence
remove(k):
    walk tree to find node n with key k
    if not contains(k): throw error "key not found"
    if current == n: current = nil

    if n has no left child:             // case 1: no left child
        child = n.right
        replace n with child in parent
        delete n

    else if n has no right child:       // case 2: no right child
        child = n.left
        replace n with child in parent
        delete n

    else:                               // case 3: two children
        successor = findMin(n.right)
        copy successor.key and successor.val into n
        replace successor with successor.right in parent
        delete successor

    num_pairs--

// If non-empty, places current iterator at the first pair (as defined by < on keys)
begin():
    if root != nil: current = findMin(root)

// If non-empty, places current iterator at the last pair (as defined by < on keys)
end():
    if root != nil: current = findMax(root)

// Advances current to the next pair, or makes current undefined if at last pair.
// Uses hasCurrent(). (as defined by < on keys)
next():
    if not hasCurrent(): throw error "current is undefined"
    current = findNext(current)

// Moves current to the previous pair, or makes current undefined if at first pair.
// Uses hasCurrent(). (as defined by < on keys)
prev():
    if not hasCurrent(): throw error "current is undefined"
    current = findPrev(current)

// Other Operations ----------------------------------------------------

// Returns a string representation of this Dictionary
to_string() OLD:
    s = ""
    for each node n in order from findMin to findMax:
        s += n.key + " : " + n.val + newline
    return s

to_string() NEW: 
s = ""
call inorderstring
return s

// Returns a string consisting of all keys in this Dictionary.
pre_string() OLD:
    s = ""
    if root != nil:
        push root onto stack
        while stack not empty:
            pop node n from stack
            append n.key + newline to s
            if n has right child: push n.right
            if n has left child:  push n.left
    return s


pre_string() ACTUAL:
    s = ""
    call preOrderString
    return s


// Returns true if both dictionaries have the same size and identical pairs.
equals(D):
    if num_pairs != D.num_pairs: return false
    return to_string() == D.to_string()

// Overloaded Operators, pull from pa6 ----------------------------------------------------

operator<<(stream, D):
    return stream + D.to_string()

operator==(A, B):
    return A.equals(B)

// Assignment operator
operator=(D):
    if this != D:
        clear()
        make temp copy of D
        swap nil, root, current, num_pairs with temp
    return this




Attempt 1: resolved by fixing missing semicolon on nil return in setvalue
Test Empty_size: FAILED: test 1
Test SetValue_size: FAILED: test 1
Test Remove_size: FAILED: test 1
Test Empty_traverse: FAILED: test 1
Test Empty_clear: PASSED
Test NonEmpty_clear: PASSED
Test Begin_value: FAILED: test 1
Test End_value: PASSED
Test Next_value: FAILED: test 1
Test Prev_value: FAILED: test 2
Test SetValue_value: PASSED
Test Remove_value: FAILED: test 1
Test GetValue_value: PASSED
Test Repeated_setValue: FAILED: test 1
Test Dictionary_equals: PASSED
Test ToString_equals: FAILED: test 1
Test PreString_equals: FAILED: test 1
Test Contains_value: PASSED

Attempt 2: checked to_string, in inorderstring inserting colon did not have spaces surrounding it
Test Empty_size: PASSED
Test SetValue_size: PASSED
Test Remove_size: PASSED
Test Empty_traverse: PASSED
Test Empty_clear: PASSED
Test NonEmpty_clear: PASSED
Test Begin_value: PASSED
Test End_value: PASSED
Test Next_value: PASSED
Test Prev_value: PASSED
Test SetValue_value: PASSED
Test Remove_value: PASSED
Test GetValue_value: PASSED
Test Repeated_setValue: PASSED
Test Dictionary_equals: PASSED
Test ToString_equals: FAILED: test 1
Test PreString_equals: PASSED
Test Contains_value: PASSED



Words.cpp
parse the input file into individual words, discarding
duplicate words. Instead of placing the unique words into an array though, it will insert them as keys into
a Dictionary. The value corresponding to a key will record that keys insertion order into the Dictionary,
starting with position 0. In other words, value is the array index at which key would have been placed by
Words.c from pa1. Once the Dictionary is constructed, the output file (identical to that of pa1) can be
constructed by iterating over it using the ADT operations begin(), hasCurrent(), next(), currentKey()
and currentVal(), 

from claude: https://claude.ai/share/e72dcf1e-a37d-44f0-8c37-2b3c45e284a5
Create a Dictionary object before the loop
Track an insertion counter (starting at 0)
For each token extracted, check if it already exists in the Dictionary (how does getValue vs setValue help you detect duplicates?)
If it's new, insert it with the current counter value, then increment the counter

What needs to change conceptually:
Your current loop does two things: extracts tokens AND immediately prints line summaries. You need to separate those into two distinct phases.
Phase 1 - Building the Dictionary:

Before the loop, what two things do you need to initialize?
Inside the token extraction loop (which you can mostly keep), instead of adding to tokenBuffer, what Dictionary operation do you call — and how do you decide whether to insert or skip?

Phase 2 - Writing output:

After the reading loop closes, how do you walk through a Dictionary in order?
For each entry, what two pieces of information do you need to print, and which iterator operations give you those?

Key question to resolve first:
Look at your Dictionary.h — what's the difference in behavior between setValue and checking with contains before inserting? Which approach naturally handles the "discard duplicates" requirement without extra logic?
Concrete first step:
Try just getting Phase 1 working — read the file, extract tokens, and insert unique ones into a Dictionary. Then print the Dictionary with begin()/hasCurrent()/next() to verify it's correct before worrying about output format.
What does your Dictionary.h say about how contains() and setValue() behave with duplicate keys?

pseudocode/planning:

int main(int argc, char * argv[]){
    //other main declarations

check command line input for arguments (should be <3)
open file 1 to read
open file 2 to write

Dictionary D; 
int counter = 0; 

part 1: use contains() to check if there is a duplicate. if not, use setValue() to insert (key,val)
while there are lines in the input file
    read line
    extract first token from line https://cplusplus.com/reference/string/string/
    while token is not empty
        if D does not contain token
            insert (token, counter) into D
            counter = counter + 1
        extract next token  begin = std::min(line.find_first_not_of(delim, end), (size_t)length); https://en.cppreference.com/w/c/types/size_t.html


part 2: use begin(), hasCurrent(), next(), currentKey(),  currentVal() // need to traverse dictionary twice for 
start iterator at first key in dictionary
D.begin()
while dictionary has a current element
    write currentKey and currentVal to output file
    move iterator to next element
    D.next()

}

part 2 modified:
// print list of values
out << "(";

D.begin();
while (D.hasCurrent()) {
    output current val;
    D.next();
    if (D.hasCurrent()) {
        out << ", ";
    }
}

out << ")" << "\n\n";   // newline before words

// print words
D.begin();
while (D.hasCurrent()) {
    output current key, plus << "\n";
    D.next();
}

DictionaryTest.cpp
use DictionaryClient as a starting point for some text examples. 
tests done in DictionaryClient: all public .h functions

// Class Constructors & Destructors ----------------------------------------
   
   // Creates new Dictionary in the empty state. 
   Dictionary();   DONE

   // Copy constructor.
   Dictionary(const Dictionary& D);  DONE

   // Destructor
   ~Dictionary();  DONE


   // Access functions --------------------------------------------------------

   // size() DONE 
   // Returns the size of this Dictionary.
   int size() const;

   // contains() TO DO . pull logic from Words.cpp
   // Returns true if there exists a pair such that key==k, and returns false
   // otherwise.
   bool contains(keyType k) const;

   // getValue() DONE
   // Returns a reference to the value corresponding to key k.
   // Pre: contains(k)
   valType& getValue(keyType k) const;

   // hasCurrent()      DONE
   // Returns true if the current iterator is defined, and returns false 
   // otherwise.
   bool hasCurrent() const;

   // currentKey() DONE
   // Returns the current key.
   // Pre: hasCurrent() 
   keyType currentKey() const;

   // currentVal() DONE
   // Returns a reference to the current value.
   // Pre: hasCurrent()
   valType& currentVal() const;


   // Manipulation procedures -------------------------------------------------

   // clear() DONE
   // Resets this Dictionary to the empty state, containing no pairs.
   void clear();

   // setValue() DONE
   // If a pair with key==k exists, overwrites the corresponding value with v, 
   // otherwise inserts the new pair (k, v).
   void setValue(keyType k, valType v);

   // remove() DONE
   // Deletes the pair for which key==k. If that pair is current, then current
   // becomes undefined.
   // Pre: contains(k).
   void remove(keyType k);

   // begin() DONE
   // If non-empty, places current iterator at the first (key, value) pair
   // (as defined by the order operator < on keys), otherwise does nothing. 
   void begin();

   // end() DONE
   // If non-empty, places current iterator at the last (key, value) pair
   // (as defined by the order operator < on keys), otherwise does nothing. 
   void end();

   // next() DONE
   // If the current iterator is not at the last pair, advances current 
   // to the next pair (as defined by the order operator < on keys). If 
   // the current iterator is at the last pair, makes current undefined.
   // Pre: hasCurrent()
   void next();

   // prev() DONE
   // If the current iterator is not at the first pair, moves current to  
   // the previous pair (as defined by the order operator < on keys). If 
   // the current iterator is at the first pair, makes current undefined.
   // Pre: hasCurrent()
   void prev();


   // Other Functions ---------------------------------------------------------

   // to_string()
   // Returns a string representation of this Dictionary. Consecutive (key, value)
   // pairs are separated by a newline "\n" character, and the items key and value 
   // are separated by the sequence space-colon-space " : ". The pairs are arranged 
   // in order, as defined by the order operator <.
   std::string to_string() const;

   // pre_string()
   // Returns a string consisting of all keys in this Dictionary. Consecutive
   // keys are separated by newline "\n" characters. The key order is given
   // by a pre-order tree walk.
   std::string pre_string() const;

   // equals()
   // Returns true if and only if this Dictionary contains the same (key, value)
   // pairs as Dictionary D.
   bool equals(const Dictionary& D) const;


   // Overloaded Operators ----------------------------------------------------
   
   // operator<<()
   // Inserts string representation of Dictionary D into stream, as defined by
   // member function to_string().
   friend std::ostream& operator<<( std::ostream& stream, Dictionary& D );

   // operator==()
   // Returns true if and only if Dictionary A equals Dictionary B, as defined
   // by member function equals(). 
   friend bool operator==( const Dictionary& A, const Dictionary& B );

   // operator=()
   // Overwrites the state of this Dictionary with state of D, and returns a
   // reference to this Dictionary.
   Dictionary& operator=( const Dictionary& D );

}

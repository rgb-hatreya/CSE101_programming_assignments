/***
* Hansa Atreya
* hatreya
* 2026 Winter CSE101 PA8
* Dictionary.cpp
advice from Raj on modifying functions 
advice from Wilson: pull insert logic in setValue
* Implementation for Dictionary ADT based on a Red Black Tree. 
***/ 

#include "Dictionary.h"
#include <stdbool.h>
#include <stdio.h>
#include <string>
#include <stdexcept>

// Node Constructor
Dictionary::Node::Node(keyType k, valType v) {
    key    = k;
    val    = v;
    parent = nullptr;
    left   = nullptr;
    right  = nullptr;
    color = 1; // zero for black, 1 for red . init with red bc new nodes are red
}

// Helper Functions  ----------------------------------------------------

// Appends a string representation of the tree rooted at R to string s. The string appended consists of:
// "key : value \n" for each key-value pair in tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Node* R) const{
    if (R == nil) return; //make sure that the root exists
    inOrderString(s, R->left); 
    s += (R->key); //append R.key
    s+= " : ";
    s += std::to_string(R->val); //append R.value
    s += "\n";
    inOrderString(s, R->right);
}

// Appends a string representation of the tree rooted at R to s. The appended string consists of keys only, 
// separated by "\n", with the order determined by a pre-order tree walk.
void Dictionary::preOrderString(std::string& s, Node* R) const {
    if (R == nil) return; //make sure that the root exists
    s += (R->key); //append R.key
    if (R->color == 1) s += " (RED)";  // added based on failure of test
    s += "\n";
    preOrderString(s, R->left);
    preOrderString(s, R->right);
}

Dictionary::Node* Dictionary::findMin(Node* R) {
    if (R == nil) return nil;
    while (R->left != nil) R = R->left;
    return R;
}

Dictionary::Node* Dictionary::findMax(Node* R) {
    if (R == nil) return nil;
    while (R->right != nil) R = R->right;
    return R;
}

Dictionary::Node* Dictionary::findNext(Node* N) {
    if (N == nil) return nil;
    if (N->right != nil) return findMin(N->right);
    Node* P = N->parent;
    while (P != nil && N == P->right) {
        N = P;
        P = P->parent;
    }
    return P;
}

Dictionary::Node* Dictionary::findPrev(Node* N) {
    if (N == nil) return nil;
    if (N->left != nil) return findMax(N->left);
    Node* P = N->parent;
    while (P != nil && N == P->left) {
        N = P;
        P = P->parent;
    }
    return P;
}

//Recursively inserts a deep copy of the subtree rooted at R into this 
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N){ 
    if (R ==N) return; // termination at N
    setValue(R->key, R->val); //insert pair with SetValue
    if (R->left != N) {
        preOrderCopy(R->left, N);
    }
    if (R->right != N) {
        preOrderCopy(R->right, N);
    }
}

//Deletes all Nodes in the subtree rooted at R.
void Dictionary::postOrderDelete(Node* R){
    if (R == nil) return; //nothign to delete
    postOrderDelete(R->left);   // delete left subtree first
    postOrderDelete(R->right);  // delete right subtree second
    delete R;                  // delete current node last
}

// RBT Helper Functions  -----------------------------------------
   
   // LeftRotate()
   void Dictionary::LeftRotate(Node* N){
    Node* y  = N->right;             // set y

    N->right = y->left;              // turn y's left subtree into N's right subtree
    if (y->left != nil)
        y->left->parent = N;

    y->parent = N->parent;           // link y's parent to N
    if (N->parent == nil)
        root = y;
    else if (N == N->parent->left)
        N->parent->left  = y;
    else
        N->parent->right = y;

    y->left   = N;                   // put N on y's left
    N->parent = y;
   }

   // RightRotate()
   void Dictionary::RightRotate(Node* N) {
    Node* y  = N->left;              // set y

    N->left  = y->right;             // turn y's right subtree into N's left subtree
    if (y->right != nil)
        y->right->parent = N;

    y->parent = N->parent;           // link y's parent to N
    if (N->parent == nil)
        root = y;
    else if (N == N->parent->right)
        N->parent->right = y;
    else
        N->parent->left  = y;

    y->right  = N;                   // put N on y's right
    N->parent = y;
}

   // RB_InsertFixUP()
   void Dictionary::RB_InsertFixUp(Node* N) {
    while (N->parent->color == 1) {                    // while parent is red
        if (N->parent == N->parent->parent->left) {
            Node* y = N->parent->parent->right;        // uncle
            if (y->color == 1) {                       // case 1: uncle is red
                N->parent->color         = 0;
                y->color                 = 0;
                N->parent->parent->color = 1;
                N = N->parent->parent;
            } else {
                if (N == N->parent->right) {           // case 2: uncle is black, N is right child
                    N = N->parent;
                    LeftRotate(N);
                }
                N->parent->color         = 0;          // case 3
                N->parent->parent->color = 1;
                RightRotate(N->parent->parent);
            }
        } else {
            Node* y = N->parent->parent->left;         // uncle
            if (y->color == 1) {                       // case 4: uncle is red
                N->parent->color         = 0;
                y->color                 = 0;
                N->parent->parent->color = 1;
                N = N->parent->parent;
            } else {
                if (N == N->parent->left) {            // case 5: uncle is black, N is left child
                    N = N->parent;
                    RightRotate(N);
                }
                N->parent->color         = 0;          // case 6
                N->parent->parent->color = 1;
                LeftRotate(N->parent->parent);
            }
        }
    }
    root->color = 0;                                   // root is always black
}

   // RB_Transplant()
   void Dictionary::RB_Transplant(Node* u, Node* v) {
    if (u->parent == nil)
        root = v;
    else if (u == u->parent->left)
        u->parent->left  = v;
    else
        u->parent->right = v;
    v->parent = u->parent;
}

   // RB_DeleteFixUp()
   void Dictionary::RB_DeleteFixUp(Node* N) {
    while (N != root && N->color == 0) {              // while N is not root and N is black
        if (N == N->parent->left) {
            Node* w = N->parent->right;               // 
            if (w->color == 1) {                      // case 1
                w->color         = 0;
                N->parent->color = 1;
                LeftRotate(N->parent);
                w = N->parent->right;
            }
            if (w->left->color == 0 && w->right->color == 0) {
                w->color = 1;                         // case 2
                N = N->parent;
            } else {
                if (w->right->color == 0) {           // case 3
                    w->left->color = 0;
                    w->color       = 1;
                    RightRotate(w);
                    w = N->parent->right;
                }
                w->color         = N->parent->color; // case 4
                N->parent->color = 0;
                w->right->color  = 0;
                LeftRotate(N->parent);
                N = root;
            }
        } else {
            Node* w = N->parent->left;               
            if (w->color == 1) {                     // case 5
                w->color         = 0;
                N->parent->color = 1;
                RightRotate(N->parent);
                w = N->parent->left;
            }
            if (w->right->color == 0 && w->left->color == 0) {
                w->color = 1;                        // case 6
                N = N->parent;
            } else {
                if (w->left->color == 0) {           // case 7
                    w->right->color = 0;
                    w->color        = 1;
                    LeftRotate(w);
                    w = N->parent->left;
                }
                w->color         = N->parent->color; // case 8
                N->parent->color = 0;
                w->left->color   = 0;
                RightRotate(N->parent);
                N = root;
            }
        }
    }
    N->color = 0;                                    // make sure that N is black
}

   // RB_Delete()
   void Dictionary::RB_Delete(Node* N) {
    Node* y = N;
    Node* x;
    int   y_original_color = y->color;

    if (N->left == nil) {
        x = N->right;
        RB_Transplant(N, N->right);
    } else if (N->right == nil) {
        x = N->left;
        RB_Transplant(N, N->left);
    } else {
        y               = findMin(N->right);         // successor 
        y_original_color = y->color;
        x               = y->right;
        if (y->parent == N) {
            x->parent = y;
        } else {
            RB_Transplant(y, y->right);
            y->right         = N->right;
            y->right->parent = y;
        }
        RB_Transplant(N, y);
        y->left         = N->left;
        y->left->parent = y;
        y->color        = N->color;
    }
    if (y_original_color == 0)                       // if removed node was black, call fixup
        RB_DeleteFixUp(x);
}


// Consctructors/ Deconstructors  ----------------------------------------------------

// Creates new Dictionary in the empty state. 
Dictionary::Dictionary() {
    nil          = new Node("\0", 0);
    nil->color   = 0;  //sentinel is always black
    nil->left    = nil;
    nil->right   = nil;
    nil->parent  = nil;
    root         = nil;
    current      = nil;
    num_pairs    = 0;

}

// Copy Constructor
Dictionary::Dictionary(const Dictionary& D) {
    nil          = new Node("\0", 0);
    nil->color   = 0;
    nil->left    = nil;
    nil->right   = nil;
    nil->parent  = nil;
    root         = nil;
    current      = nil;
    num_pairs    = 0;
    preOrderCopy(D.root, D.nil); 
}

// Destructor
Dictionary::~Dictionary() {
    clear();
    delete nil;
}

// Access fxns ----------------------------------------------------

// Returns the size of this Dictionary.
int Dictionary::size() const {
    return num_pairs;
}  

// Returns true if there exists a pair such that key==k, and returns false otherwise.
bool Dictionary::contains(keyType k) const {
    Node* cur = root;
    while (cur != nil) {
        if (k == cur->key) return true;
        else if (k  < cur->key) cur = cur->left;
        else                    cur = cur->right;
    }
    return false;
}

// Returns a reference to the value corresponding to key k.
valType& Dictionary::getValue(keyType k) const {
    Node* cur = root;
    while (cur != nil) {
        if (k == cur->key) return cur->val;
        else if (k < cur->key) cur = cur->left;
        else                   cur = cur->right;
    }
    throw std::logic_error("Dictionary: getValue(): key \"" + k + "\" does not exist");  //fixed error message to throw actual key
}

// Returns true if the current iterator is defined, returns false otherwise.
bool Dictionary::hasCurrent() const {
    return current != nil;
}

// Returns current key using hasCurrent
keyType Dictionary::currentKey() const{
    if (!hasCurrent()) throw std::logic_error("Dictionary: currentKey(): current undefined");
    return current->key;
}
// Returns current value using hasCurrent
valType& Dictionary::currentVal() const{
    if (!hasCurrent()) throw std::logic_error("Dictionary: currentVal(): current undefined");
    return current->val;
}
// Manipulation procedures ----------------------------------------------------



// Resets D to the empty state using post order delete.
void Dictionary::clear() {
    postOrderDelete(root);
    root      = nil;
    current   = nil;
    num_pairs = 0;
}

void Dictionary::setValue(keyType k, valType v) {
    // Walk tree  and overwrite if key already exists
    Node* cur    = root;
    Node* parent = nil;
    while (cur != nil) {
        if (k == cur->key) { cur->val = v; return; }
        parent = cur;
        if (k < cur->key) cur = cur->left;
        else              cur = cur->right;
    }

    // Build new red node
    Node* z   = new Node(k, v);
    z->left   = nil;
    z->right  = nil;
    z->color  = 1;           // RED
    z->parent = parent;

    // Standard BST link
    if (parent == nil)          root = z;
    else if (k < parent->key)   parent->left  = z;
    else                        parent->right = z;

    num_pairs++;
    RB_InsertFixUp(z);       // restore RB 
}

// Deletes the pair where key==k. If it is current, then current becomes undefined. Uses contains() for checking key existence
void Dictionary::remove(keyType k) {
    if (!contains(k))
        throw std::logic_error("Dictionary: remove(): key \"" + k + "\" does not exist"); // fixed throw error to include actual key

    // Find the node
    Node* n = root;
    while (n != nil && n->key != k) {
        if (k < n->key) n = n->left;
        else            n = n->right;
    }

    if (current == n) current = nil;
    RB_Delete(n);            // handles all cases + fixup instead of BST cases
    delete n;
    num_pairs--;
}
// If non-empty, places current iterator at the first pair. CHECK IF (as defined by the order operator < on keys)
void Dictionary::begin() {
    if (root != nil) current = findMin(root);
}
// If non-empty, places current iterator at the last (key, value) pair. CHECK (as defined by the order operator < on keys)
void Dictionary::end() {
    if (root != nil) current = findMax(root);
}

// If the current iterator is not at the last pair, advances current to the next pair. 
// If the current iterator is at the last pair, makes current undefined. uses hasCurrent(). CHECK (as defined by the order operator < on keys) 
void Dictionary::next() {
    if (!hasCurrent()) throw std::logic_error("Dictionary: next(): current undefined");
    current = findNext(current);
}

// If the current iterator is not at the first pair, moves current to the previous pair . 
// If  the current iterator is at the first pair, makes current undefined. uses hasCurrent(). CHECK  (as defined by the order operator < on keys) 
void Dictionary::prev() {
    if (!hasCurrent()) throw std::logic_error("Dictionary: prev(): current undefined");
    current = findPrev(current);
}

// Other operations -----------------------------------------------------------

// Returns a string representation of this Dictionary similarly to as in previous pa, using inOrderString helper call
std::string Dictionary::to_string() const {
    std::string s;
    inOrderString(s, root);
    return s;
}

//Returns a string consisting of all keys in this Dictionary. Uses preOrderString to process tree to simplify function
std::string Dictionary::pre_string() const {
    std::string s;
    preOrderString(s, root);
    return s;
}

// Returns true of both dictionaries have the same size and idential pairs.
bool Dictionary::equals(const Dictionary& D) const {
    if (num_pairs != D.num_pairs) return false;
    return to_string() == D.to_string();
}

// Overloaded Operators -----------------------------------------------------------
//std::ostream& operator<<(std::ostream& stream, const Dictionary& D) { removed const to match header 
std::ostream& operator<<(std::ostream& stream, Dictionary& D) { 
    return stream << D.to_string();
}

bool operator==( const Dictionary& A, const Dictionary& B ){
    return A.equals(B);
}

Dictionary& Dictionary:: operator=( const Dictionary& D ){ //make temp of dictionary like pa6
    if (this != &D) {
        //clear(); not needed with temp
        Dictionary temp = D;
        std::swap(nil, temp.nil);
        std::swap(root, temp.root);
        std::swap(current, temp.current);
        std::swap(num_pairs, temp.num_pairs);
    }
    return *this;
}


/***
* Hansa Atreya
* hatreya
* 2026 Winter CSE101 PA7
* Dictionary.cpp
* Avni, Ashton
* Implementation for Dictionary ADT based on a Binary Search Tree. 
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


// Consctructors/ Deconstructors  ----------------------------------------------------

// Creates new Dictionary in the empty state. 
Dictionary::Dictionary() {
    nil          = new Node("\0", 0);
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
        else cur = cur->right;
    }
    throw std::logic_error("Dictionary: getValue(): key \"blah\" does not exist"); 
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


// Resets D to the empty state using post order delete
void Dictionary::clear(){ 
    postOrderDelete(root);
    root = nil;
    current = nil;
    num_pairs = 0;
}


// If D contains key k, overwrite value with v.
// Otherwise insert new pair (k,v).
void Dictionary::setValue(keyType k, valType v) {
    Node* cur = root;
    Node* parent = nil;
    while (cur != nil) {
        if (k == cur->key) { cur->val = v; return; }
        parent = cur;
        if (k < cur->key) {
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }
    Node* n   = new Node(k, v);
    n->left   = nil;
    n->right  = nil;
    n->parent = parent;
    if (parent == nil) root = n;
    else if (k < parent->key) parent->left = n;
    else parent->right = n;
    num_pairs++;
}

// Deletes the pair where key==k. If it is current, then current becomes undefined. Uses contains() for checking key existence
void Dictionary::remove(keyType k) {
    // Find node by walking tree with iteration
    Node* n = root;
    while (n != nil && n->key != k) {
        if (k < n->key) {
            n = n->left;
            } 
            else {
                n = n->right;
            }
        }       
    if (!contains(k)) throw std::logic_error("Dictionary: remove(): key \"blah\" does not exist");
    if (current == n) current = nil;

    if (n->left == nil) {
        // Case 1: no left child
        Node* child = n->right;
        if (n->parent == nil) root = child;
        else if (n == n->parent->left) n->parent->left  = child;
        else n->parent->right = child;
        if (child != nil) child->parent = n->parent;
        delete n;

    } else if (n->right == nil) {
        // Case 2: no right child
        Node* child = n->left;
        if (n->parent == nil) root = child;
        else if (n == n->parent->left) n->parent->left  = child;
        else n->parent->right = child;
        if (child != nil) child->parent = n->parent;
        delete n;

    } else {
        // Case 3: two children — swap with successor
        Node* successor  = findMin(n->right);
        n->key      = successor->key;
        n->val      = successor->val;
        Node* child = successor->right;
        if (successor == successor->parent->left) successor->parent->left  = child;
        else successor->parent->right = child;
        if (child != nil) child->parent = successor->parent;
        delete successor;
    }
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


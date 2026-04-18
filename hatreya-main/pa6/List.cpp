//-----------------------------------------------------------------------------
// List.cpp
// Implementation file for List ADT
// Hansa Atreya (hatreya)
// cse 101, pa6
//-----------------------------------------------------------------------------

#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

using namespace std;

// Node constructor
List::Node::Node(ListElement x){
    data = x;
    next = nullptr;
    prev = nullptr;
}

// Constructor 

// Creates new empty List 
List::List(){
    frontDummy = new Node(0);
    backDummy  = new Node(0);

    frontDummy->next = backDummy;
    backDummy->prev  = frontDummy;

    beforeCursor = frontDummy;
    afterCursor  = backDummy;

    pos_cursor = 0;
    num_elements = 0;
}

// Copy constructor
List::List(const List& L):List(){
    Node* N = L.frontDummy->next;
    while(N != L.backDummy){
        insertAfter(N->data);
        moveNext();
        N = N->next;
    }
    moveFront();
}

// Destructor
List::~List(){
    clear();
    delete frontDummy;
    delete backDummy;
}

// Access

int List::length() const { return num_elements; }

ListElement List::front() const{
    if(num_elements == 0) throw length_error("List: front(): empty");
    return frontDummy->next->data;
}

ListElement List::back() const{
    if(num_elements == 0) throw length_error("List: back(): empty");
    return backDummy->prev->data;
}

int List::position() const { return pos_cursor; }

ListElement List::peekNext() const{
    if(pos_cursor >= num_elements)
        throw range_error("List: peekNext()");
    return afterCursor->data;
}

ListElement List::peekPrev() const{
    if(pos_cursor <= 0)
        throw range_error("List: peekPrev()");
    return beforeCursor->data;
}

// Manipulation 

void List::clear(){
    moveFront();
    while(num_elements > 0)
        eraseAfter();
}

void List::moveFront(){
    beforeCursor = frontDummy;
    afterCursor  = frontDummy->next;
    pos_cursor = 0;
}

void List::moveBack(){
    afterCursor  = backDummy;
    beforeCursor = backDummy->prev;
    pos_cursor = num_elements;
}

ListElement List::moveNext(){
    if(pos_cursor >= num_elements)
        throw range_error("List: moveNext()");
    beforeCursor = afterCursor;
    afterCursor  = afterCursor->next;
    pos_cursor++;
    return beforeCursor->data;
}

ListElement List::movePrev(){
    if(pos_cursor <= 0)
        throw range_error("List: movePrev()");
    afterCursor  = beforeCursor;
    beforeCursor = beforeCursor->prev;
    pos_cursor--;
    return afterCursor->data;
}

void List::insertAfter(ListElement x){
    Node* N = new Node(x);

    N->prev = beforeCursor;
    N->next = afterCursor;

    beforeCursor->next = N;
    afterCursor->prev  = N;

    afterCursor = N;
    num_elements++;
}

void List::insertBefore(ListElement x){
    Node* N = new Node(x);

    N->prev = beforeCursor;
    N->next = afterCursor;

    beforeCursor->next = N;
    afterCursor->prev  = N;

    beforeCursor = N;
    pos_cursor++;
    num_elements++;
}

void List::eraseAfter(){
    if(pos_cursor >= num_elements)
        throw range_error("List: eraseAfter()");

    Node* N = afterCursor;
    afterCursor = N->next;
    beforeCursor->next = afterCursor;
    afterCursor->prev  = beforeCursor;

    delete N;
    num_elements--;
}

void List::eraseBefore(){
    if(pos_cursor <= 0)
        throw range_error("List: eraseBefore()");

    Node* N = beforeCursor;
    beforeCursor = N->prev;
    beforeCursor->next = afterCursor;
    afterCursor->prev  = beforeCursor;

    delete N;
    pos_cursor--;
    num_elements--;
}

// Other Functions 

int List::findNext(ListElement x){
    while(pos_cursor < num_elements){
        if(peekNext() == x){
            moveNext();
            return pos_cursor;
        }
        moveNext();
    }
    return -1;
}

int List::findPrev(ListElement x){
    while(pos_cursor > 0){
        if(peekPrev() == x){
            movePrev();
            return pos_cursor;
        }
        movePrev();
    }
    return -1;
}

std::string List::to_string() const{
    string s = "(";
    Node* N = frontDummy->next;
    while(N != backDummy){
        s += std::to_string(N->data);
        if(N->next != backDummy) s += ", ";
        N = N->next;
    }
    s += ")";
    return s;
}

bool List::equals(const List& R) const{
    if(num_elements != R.num_elements) return false;

    Node* A = frontDummy->next;
    Node* B = R.frontDummy->next;

    while(A != backDummy){
        if(A->data != B->data) return false;
        A = A->next;
        B = B->next;
    }
    return true;
}

// Overloaded Ops

ostream& operator<<( ostream& stream, const List& L ){
    return stream << L.to_string();
}

bool operator==( const List& A, const List& B ){
    return A.equals(B);
}

List& List::operator=( const List& L ){
    if(this != &L){
        List temp = L;
        swap(frontDummy, temp.frontDummy);
        swap(backDummy, temp.backDummy);
        swap(beforeCursor, temp.beforeCursor);
        swap(afterCursor, temp.afterCursor);
        swap(pos_cursor, temp.pos_cursor);
        swap(num_elements, temp.num_elements);
    }
    return *this;
}

// Cleanup and Concat

void List::cleanup(){

    Node* outer = frontDummy->next;
    int outerIndex = 0;

    while(outer != backDummy){

        Node* inner = outer->next;
        int innerIndex = outerIndex + 1;

        while(inner != backDummy){

            if(inner->data == outer->data){

                Node* temp = inner;
                inner = inner->next;

                // If deleted node is before cursor, decrement position
                if(innerIndex < pos_cursor){
                    pos_cursor--;
                }

                // Fix cursor pointers if necessary
                if(temp == beforeCursor){
                    beforeCursor = beforeCursor->prev;
                }
                if(temp == afterCursor){
                    afterCursor = afterCursor->next;
                }

                // Remove node
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;

                delete temp;
                num_elements--;

            } else {
                inner = inner->next;
                innerIndex++;
            }
        }

        outer = outer->next;
        outerIndex++;
    }
}

List List::concat(const List& L) const{

    List result;

    // copy this list
    Node* N = frontDummy->next;
    while(N != backDummy){
        result.insertAfter(N->data);
        result.moveNext();
        N = N->next;
    }

    // copy L
    N = L.frontDummy->next;
    while(N != L.backDummy){
        result.insertAfter(N->data);
        result.moveNext();
        N = N->next;
    }

    result.moveFront(); // cursor at position 0
    return result;
}


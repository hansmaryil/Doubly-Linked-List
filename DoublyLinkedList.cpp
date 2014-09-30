#include "DoublyLinkedList.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

DoublyLinkedList::Node::Node(DataType data)
{
    value = data;
    prev = NULL;
    next = NULL;
}

DoublyLinkedList::DoublyLinkedList()
{
    head_ = NULL;
    tail_ = NULL;
    size_ = 0;
}

DoublyLinkedList::~DoublyLinkedList()
{
    while(size_ > 0){
        remove_back();
    }
}

bool DoublyLinkedList::empty() const
{
    return (size_ == 0);
}

unsigned int DoublyLinkedList::size() const
{
    return size_;
}

void DoublyLinkedList::print() const
{
    Node *ptr = head_;
    
    cout << "[";
    
    while (ptr != NULL){
        cout << ptr -> value;
        ptr = ptr -> next;
        if (ptr != NULL){
            cout << ", ";
        }
    }
    cout << "]" << endl;
    
}

bool DoublyLinkedList::insert_front(DataType value)
{
    if (full()){
        return false;
    }
    
    Node *newNode = new Node(value);
    
    if (head_ == NULL){
        head_ = newNode;
        tail_ = newNode;
    }
    else{
        head_ -> prev = newNode;
        newNode -> next = head_;
        head_ = newNode;
    }
    
    size_++;
    return true;
}

bool DoublyLinkedList::remove_front()
{
    if (head_ != NULL){
        if (head_ == tail_){
            delete(head_);
            head_ = NULL;
            tail_ = NULL;
        }
        else{
            Node *nextNode = head_ -> next;
            nextNode -> prev = NULL;
            delete(head_);
            head_ = nextNode;
        }
        size_--;
        return true;
    }
    return false;
}

bool DoublyLinkedList::insert_back(DataType value)
{
    if (full()){
        return false;
    }
    
    Node *newNode = new Node(value);
    
    if (tail_ == NULL){
        head_ = newNode;
        tail_ = newNode;
    }
    else{
        tail_ -> next = newNode;
        newNode -> prev = tail_;
        tail_ = newNode;
    }
    
    size_++;
    return true;
}

bool DoublyLinkedList::remove_back()
{
    if (tail_ != NULL){
        if (tail_ == head_){
            delete(tail_);
            tail_ = NULL;
            head_ = NULL;
        }
        else{
            Node *prevNode = tail_ -> prev;
            prevNode -> next = NULL;
            delete(tail_);
            tail_ = prevNode;
        }
        size_--;
        return true;
    }
    return false;
}

bool DoublyLinkedList::insert(DataType value, unsigned int pos)
{
    if (pos > size_){
        return false;
    }
    if (pos == 0){
        return insert_front(value);
    }
    if (pos == size_){
        return insert_back(value);
    }

    Node *newNode = new Node(value), *posNode = getNode(pos - 1);
    newNode -> next = posNode -> next;
    newNode -> prev = posNode;
    posNode -> next -> prev = newNode;
    posNode -> next = newNode;
    size_++;
    return true;
}

bool DoublyLinkedList::remove(unsigned int pos)
{
    if (pos >= size_){
        return false;
    }
    if (pos == 0){
        return remove_front();
    }
    if (pos == size_ - 1){
        return remove_back();
    }
    
    Node *deleteNode = getNode(pos);
    Node *posNode = deleteNode -> prev;
    
    deleteNode -> next -> prev = posNode;
    posNode -> next = deleteNode -> next;
    delete(deleteNode);
    size_--;
    return true;    
}
    
unsigned int DoublyLinkedList::search(DataType value) const
{
    
    Node *ptr = head_;
    int index = 0;
    
    while (ptr != NULL){
        if (ptr -> value == value){
            return index;
        }
        index++;
        ptr = ptr -> next;
    }
    
    return size_;
}

DoublyLinkedList::DataType DoublyLinkedList::select(unsigned int pos) const
{
    
    if (size_ == 0){
        return NULL;
    }
    if (pos >= size_){
        return tail_ -> value; //WTF
    }
    Node *node = getNode(pos);
    return node -> value;
}

bool DoublyLinkedList::replace(unsigned int pos, DataType value)
{
    Node *node = getNode(pos);
    if (node == NULL){
        return false;
    }
    
    node -> value = value;
    return true;
}

DoublyLinkedList::Node* DoublyLinkedList::getNode(unsigned int pos) const
{
    if (pos >= size_){
        return NULL;
    }
    Node *ptr = head_;
    for (int i = 0; i < pos; i++){
        ptr = ptr -> next;
    }
    
    return ptr;
}
bool DoublyLinkedList::full() const
{
    return size_ == CAPACITY;
}

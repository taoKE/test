#pragma once

#include <iostream>

using namespace std;

template<class T>
class LinkedListNode {
    private: 
        LinkedListNode<T> * next;
        T value;

    public:
        LinkedListNode(T _v) : value(_v), next(NULL){}
        void setNext(T * _next) {
            next = _next;
        }

        LinkedListNode<T>* getNext(){
            return next;
        }

        T getValue(){
            return value;
        }

        LinkedListNode<T> * setNext(LinkedListNode<T>* n) {
            next = n;
        }

        void setValue(T s) {
            value = s;

        }
};

template<class T>
class LinkedList{
    private:
        LinkedListNode<T> * head;
        int size;

    public:
        LinkedList(LinkedListNode<T> * _h):head(_h){
            if(head != NULL) size = 1;
            else size = 0;
        }

        int getSize() {
            return size;
        }

        void append(LinkedListNode<T> * _next) {
            LinkedListNode<T> * current = head;
            if(current == NULL) {
                current = _next;
                head = _next;
            } else {
                while(current->getNext() != NULL){
                    current = current->getNext();
                }
                current->setNext( _next);
                size++;
            }
        }

        void headAppend(LinkedListNode<T> * newHead){
            newHead->setNext(head);
            head = newHead;
        }

        LinkedListNode<T> * getHead() {
            return head;
        }

        void setHead(LinkedListNode<T> * h) {
            head = h;
        }

        void printList() {
            LinkedListNode<T> * temp = head;
            while(temp != NULL) {
                cout<<temp->getValue()<< " ";
                temp = temp->getNext();
            }
        }

        ~LinkedList(){
            LinkedListNode<T> * current = head;
            while(current->getNext() != NULL){
                LinkedListNode<T> * temp = current;
                current = current->getNext();
                delete temp;
            }
        }

};

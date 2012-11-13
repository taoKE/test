#pragma once

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
};

template<class T>
class LinkedList{
    private:
        LinkedListNode<T> * head;

    public:
        LinkedList(LinkedListNode<T> * _h):head(_h){}

        void append(LinkedListNode<T> * _next) {
            LinkedListNode<T> * current = head;
            while(current->getNext() != NULL){
                current = current->getNext();
            }
            current->setNext( _next);
        }

        LinkedListNode<T> * getHead() {
            return head;
        }

        void setHead(LinkedListNode<T> * h) {
            head = h;
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

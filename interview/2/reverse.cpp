#include <iostream>
#include <string>
#include "linkedList.h"

using namespace std;

int main(){
    LinkedList<int> list(new LinkedListNode<int>(0));
    
    for(int i = 1 ; i < 10; i++){
        list.append(new LinkedListNode<int>(i));
    }

    LinkedListNode<int> * head = list.getHead();

    cout<<"the original list is "<<endl;
    while(head->getNext() != NULL){
        cout<<head->getValue()<<" ";
        head = head->getNext();
    }
    cout<< head->getValue() <<endl;

    head = list.getHead();
    LinkedListNode<int> * current = head;
    LinkedListNode<int> * prev = NULL;
    cout<<"the reversed list is "<<endl;
    while(current->getNext() != NULL) {
        LinkedListNode<int> * temp = current->getNext();
        current->setNext(prev);
        prev = current;
        current = temp;
    }
    current->setNext(prev);

    list.setHead(current);

    head = list.getHead();
    while(head->getNext() != NULL){
        cout<<head->getValue()<<" ";
        head = head->getNext();
    }
    cout<<head->getValue()<<endl;

    return 0;
    
}

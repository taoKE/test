#include <iostream>
#include "linkedList.h"

using namespace std;

void deleteNIter(LinkedList<int> & list, int n) {
    LinkedListNode<int> * first = list.getHead();
    LinkedListNode<int> * second = list.getHead();

    if(n > list.getSize() ){
        cout<<" error:n is bigger than the size of list"<<endl;
        return ;
    }

    for(int i = 0;  i < n ; i++){
        second = second->getNext();
    }
    while(second->getNext() != NULL) {
        first = first->getNext();
        second = second->getNext();
    }

    LinkedListNode<int> * temp = first->getNext();
    cout<<"tem value is "<<temp->getValue()<<endl;
    first->setValue(temp->getValue());
    first->setNext(temp->getNext());
    delete temp;
}

LinkedListNode<int> *  recu(LinkedListNode<int> * head, int n, int & found) {
    if(head->getNext() == NULL) {
        found = 1;
        return head;
    }

    LinkedListNode<int> * ret = recu(head->getNext(), n, found);
    if(found == n) {
        ret = head;
    }
     found++;
    
    return ret;
}

void deleteNIRecur(LinkedList<int> & list, int n){
    int found = 0;
    LinkedListNode<int> * node = recu(list.getHead(), n, found);

    LinkedListNode<int> * temp = node->getNext();
    node->setValue(temp->getValue());
    node->setNext(temp->getNext());
    delete temp;
}


int main() {
    LinkedList<int> list(new LinkedListNode<int> (0));

    for(int i = 0;i < 20 ; i++){
        list.append(new LinkedListNode<int>(i));
    }

    LinkedListNode<int> * head = list.getHead();

    cout<<"the original list is : "<<endl;
    list.printList();
    deleteNIter(list, 3);

    cout<<endl;

    list.printList();

    cout<<endl;
    deleteNIRecur(list, 3);
    list.printList();
    cout<<endl;
    return 0;
}

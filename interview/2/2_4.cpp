#include <iostream>
#include "linkedList.h"

LinkedList<int> * makeListFromInt(int a) {
    LinkedListNode<int> * head = new LinkedListNode<int>(a % 10);
    LinkedList<int> * res = new LinkedList<int>(head);
    
    a /= 10;

    while(a > 0) {
        res->append(new LinkedListNode<int> (a % 10));
        a /= 10;
    }

    //add one more bit for place holder
    res->append(new LinkedListNode<int> (0));

    return res;
}

/*
 * l2: linked list to be lengthened
 * add: # of new notes to be added 
 */
void normalize( LinkedList<int> * l2, int add) {
    for(int i = 0; i < add; i++){
        l2->append(new LinkedListNode<int>(0));
    }
}

LinkedList<int> * addition(LinkedList<int> * a, LinkedList<int> *b){
    LinkedListNode<int> * ahead = a->getHead();
    LinkedListNode<int> * bhead = b->getHead();

    LinkedList<int> * res = new LinkedList<int>(NULL);

    int carry = 0;
    while(ahead != NULL) {
        int c = ahead->getValue() + bhead->getValue() + carry;
        carry = c / 10;
        c %= 10;
        res->append(new LinkedListNode<int>(c));
        ahead = ahead->getNext();
        bhead = bhead->getNext();
    }

    return res;
}

int main() {
    int a, b;
    cin >> a;
    cin >> b;

    LinkedList<int> * al = makeListFromInt(a);
    LinkedList<int> * bl = makeListFromInt(b);

    int as = al->getSize();
    int bs = bl->getSize();
    if(as > bs) {
        normalize(bl,as - bs);
    } else {
        normalize(al, bs - as);
    }

    al->printList();
    cout<<endl;
    bl->printList();

    LinkedList<int> * res = addition(al,bl);

    cout<<endl;
    res->printList();

    delete al;
    delete bl;
    delete res;
}

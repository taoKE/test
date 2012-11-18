#pragma once

template <class T>
class Stack {
    private:
        T * a; //array to store the stack
        int top;

    pubblic:
        Stack(T * _a) : a(_a){}

        T pop() {
            if(top >= 0) {
                T temp = a[top];
                top--;

                return temp;
            }
            return NULL;
        }

        void push(T b) {
            a[++top] = b;
        }
};

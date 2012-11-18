#include <stack.h>
#include <iostream>
#include <string>

using namespace std;

int main() {
    int * array = new int[10];
    Stack stack(array);

    for(int i = 0; i < 10; i++) stack.push(i);

    int temp = stack.pop();
    while(temp != NULL) {
        cout<<temp<< " ";
        temp = stack.pop();
    }

    delete [] array;

    return 0;
}

#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int main() {
    //b is 128 bit
    int  b[4];
    memset( b,0, sizeof(b));

    string input;
    cin>>input;

    int size = input.size();

    for(int i = 0; i < size; i++){
        int ascii = (int) input[i];

        int index = ascii /32;
        int offset = ascii % 32;

            b[index] |= (1 << offset);
    }

    cout<<"The input string has unique characters:"<<endl;
    int temp = 1;
    for(int i = 0; i < 4; i++){
        int offset = i * 32;
        for(int j = 0; j < 32; j++) {
            int temp = offset + j;
            //cout<<"Offset is "<<offset<<endl;
            if(b[i] & (1 << j)) cout<<(char)(temp);
        }
    }

    return 0;
}


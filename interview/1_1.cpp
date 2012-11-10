#include <iostream>
#include <string>

using namespace std;

//This is for solution without any additional data structure

bool check(string input) {
   string already = "";

    int size = input.length();
    cout<<"size = "<<size<<endl;
    for(int  i  =0; i < size; i ++){
        if(already.find(input[i]) != string::npos){
            cout<<"right now: already is :"<<already<<";i= "<<i<<" char is "<<input[i]<<endl;
            return false;
        }
        else{
            char temp = input[i];
            already.append(&temp);
        }
    }
    return true;
}

int main() {
    string input;
    cout<<"Please input the string to see if they have unique char"<<endl;
    cin>>input;

    if(check(input)) cout<<"THis string has UNIQUE characters" << endl;
    else cout<<"THis string has same chars"<<endl;

    return 0;

}

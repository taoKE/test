#include <iostream>
#include <string>

using namespace std;

void normalizer(string input1, string input2, string & norm1, string &norm2){
        //Adding one more in 
        char zero = '0';
        norm1.append("0");
        norm1.append(input1);
        norm2 = "";
        int diff = input1.size() - input2.size();
        for(int i = 0; i <= diff; i++) {
            norm2.append("0");
        }
        norm2.append(input2);
}

string add(string norm1, string norm2) {
    int size = norm1.size();
    string res = norm1;
    int carry = 0;
    for(int i = size -1; i >= 0; i--){
        int first = norm1[i] - '0';
        int second = norm2[i] - '0';
        int _res = first + second + carry;
        carry = _res / 10;
        _res %= 10;
        res[i] = (char)(_res + '0');
    }
    return res;
}

int main() {
    string input1, input2;
    cin>>input1;
    cin>>input2;

    string norm1, norm2;

    int s1 = input1.size(), s2 = input2.size();

    if(s1 > s2){
        normalizer(input1, input2, norm1, norm2);
    }
    else {
        normalizer(input2, input1, norm2, norm1);
    }

    cout<<"norm1 is "<<norm1 << "; norm2 is "<<norm2<<endl;

    string res = add(norm1, norm2);

    cout << "result is "<<res <<endl;
    
    return 0;

}

#include <iostream>
#include <algorithm>

using namespace std;

bool isGoodPalinom(string str){
    int flag = str[0] - '0';
    for(int i = 0;i<(str.size()+1) / 2;i++){
        if (str[i] != str[str.size() - i - 1]){
            return 0;/// not even a polinom
        }

        if (str[i] < flag ){
            return 0;
        }
        flag = str[i];


    }

    return 1;
}

string to_bin(int a){
    if (a == 0){return "0";}
    string ret = "";
    while(a != 0){
        ret += (a%2) + '0';
        a/= 2;
    }
    reverse(ret.begin(),ret.end());
    return ret;
}

string arr[10000];

void rec(string s = "") {
    if (s.size() > 10)
        return;

    int sz = s.size();
    int how_much = 0;
    for(int l = 0;l<sz;l++){
        for(int r = l;r<sz;r++){
            ///cout << s.substr(l,r-l+1) << " ";
            how_much += isGoodPalinom(s.substr(l,r-l+1));
        }
    }
    if (arr[how_much] == "-1"){
        arr[how_much] = s;
    }

    rec(s + '0');
    rec(s + '1');
}

int main()
{


    for(int i = 0;i<100;i++){
        arr[i] = "-1";
    }

    rec();

    for(int i = 0;i<100;i++){
        string s = to_bin(i);



        cout << s << endl;


    }



    cout << endl << endl;

    for(int i = 0;i<100;i++){
        cout << i << " : " << arr[i] << endl;
    }


    cout << "Hello world!" << endl;
    return 0;
}

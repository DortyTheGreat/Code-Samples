#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    ifstream fin("input.txt");

    string str;

    fin >> str;
    ///cout << str << endl;
    int ans = -1;
    int cou = 1;

    for(int i =1;i<str.size();i++){
        if (str[i]%2 == str[i-1]%2){
            cou++;
        }else{
            ans = max(ans,cou);
            cou = 1;
        }
    }


    ans = max(ans,cou);
    cou = 1;

    cout << ans << endl;
    //cout << "Hello world!" << endl;
    return 0;
}

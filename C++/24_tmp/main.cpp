#include <iostream>
#include <fstream>
#include <map>
using namespace std;

int main()
{
    map<char,int> mp;

    ifstream fin("in.txt");
    string str;
    fin >> str;
    BigUnsigned test;

    BigUnsigned e2(test);

    for(int i =0 ;i< str.size();i++){
        mp[str[i]]++;
    }

    int max_ = -10;
    int mini = 100000000;

    for(auto elem : mp){
        max_ = max(max_, elem.second);
        mini = min(mini, elem.second);
        cout << elem.first << " " << elem.second << endl;
    }

    cout << mini << endl << max_ << endl;
    cout << "Hello world!" << endl;
    return 0;
}

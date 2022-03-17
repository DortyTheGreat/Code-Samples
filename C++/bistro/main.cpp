#include <iostream>
#include <fstream>
#include <map>
using namespace std;

int main()
{
    map<char,int> mp;
    ifstream fin("input.txt");
    string str;
    fin >> str;



    for(int i =2;i<str.size();i++){
        if (str[i-1] == str[i-2]){
            mp[str[i]]++;
        }
    }

    for (auto i : mp) cout << i.first << ' ' << i.second << '\n';

    //cout << "Hello world!" << endl;
    return 0;
}

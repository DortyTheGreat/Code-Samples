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

    for(int i = 1;i<str.size() - 1;i++){
        if (str[i-1] == 'A' && str[i+1] == 'C'){
            mp[str[i]]++;
        }
    }

    for(auto i : mp){
        cout << i.first << " " << i.second << endl;
    }

    ///cout << "Hello world!" << endl;
    return 0;
}

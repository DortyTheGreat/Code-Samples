/// https://codeforces.com/gym/374545/problem/E

#include <map>
#include <iostream>
using namespace std;

int main()
{
    int t;
    cin >> t;
    while(t--){
        string a;
        map<char,bool> ans;
        cin >> a;
        int cou = 1;
        char last = a[0];
        for(int i = 1;i< a.size();++i){
            if (a[i] != last){
                if(cou % 2){ans[last] = 1;}
                last = a[i];
                cou = 1;
            }else{
                cou++;
            }
        }

        if(cou % 2){ans[last] = 1;}

        for(auto elem : ans){
            cout << elem.first;
        }
        cout << endl;
    }
    return 0;
}

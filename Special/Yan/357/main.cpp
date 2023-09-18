#include <iostream>
#include <map>
#include <set>
using namespace std;

int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    map<string,int> mp;
    set<string> alp;
    int n;
    cin >> n;
    for(int i = 0; i < n; ++i){
        string s;
        cin >> s;
        for(int j = 0; j < s.size() - 3; ++j){
            string k = string(1,s[j]) + s[j+1]+s[j+2]+" " + s[j+1]+s[j+2]+s[j+3];
            alp.insert(string(1,s[j]) + s[j+1]+s[j+2]);
            alp.insert(string(1,s[j+1]) + s[j+2]+s[j+3]);
            mp[ k ]++;
        }
    }

    cout << alp.size() << endl;
    cout << mp.size() << endl;
    for(const auto& p : mp){
        cout << p.first << " " << p.second << '\n';
    }

    return 0;
}

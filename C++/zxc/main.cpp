#include <iostream>
#include <vector>
#include <utility>
using namespace std;

int main()
{
    string s;
    cin >> s;

    vector<pair<int,char>> abobus;
    if (s[0] != '?'){
        abobus.push_back({0,'?'});
    }
    int amount = 1;
    for(int i = 1;i<s.size();i++){
        if (s[i-1] == s[i]){
            amount++;
        }else{
            abobus.push_back({amount,s[i-1]});
            amount = 1;
        }
    }

    abobus.push_back({amount,s[s.size() - 1]});
    if (s[s.size() - 1] != '?'){
        abobus.push_back({0,'?'});
    }

    int l_q = -1;
    int r_q = abobus[0].first;

    char symbol = abobus[1].second;
    int symbol_len = abobus[1].first;

    for(int i = 2;i<abobus.size();i++){
        if (abobus[i].second == '?'){
            l_q = r_q;
            r_q = abobus[i].first;
        }else{
            if (abobus[i].second == symbol){
                l_q = abobus[i].first + l_q + r_q + symbol_len;
                r_q
            }


            symbol_len = abobus[i].first;
        }
    }

    return 0;
}

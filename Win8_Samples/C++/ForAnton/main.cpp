#include <iostream>
//#include <pair>
using namespace std;

string a1,a2,a3;
// ACTG

bool IsThere(string arg){
return (a1.find(arg) != -1) && (a2.find(arg) != -1) && (a3.find(arg) != -1);
}

pair<int,string> Find(string arg){
    if(IsThere(arg)){
        return max(Find(arg+'A'),max(Find(arg+'C'),max(Find(arg+'T'),Find(arg+'G'))));
    }else{
        pair<int,string> ThatPair;
        ThatPair.first = arg.size();
        ThatPair.second = arg;
    return ThatPair;
    }
}

int main()
{
    cin >> a1 >> a2 >> a3;
    //cout << IsThere("1");
    string ans =  Find("").second;
    ans.pop_back();
    cout << ans;
    return 0;
}

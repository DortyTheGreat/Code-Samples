/// https://codeforces.com/group/79H4rJ7Jub/contest/384442/problem/A
/// http://codeforces.com/contestInvitation/e1180f0bb5d1bfed72d2801e3764ae9614abb71e
#include <iostream>

using namespace std;

int give_pos(const string& str, char elem){
    for(int i = str.size() - 1;i>-1;--i){
        if (str[i] == elem) return i;
    }
    return -1;
}

int give_pos_after(const string& str, char elem, int itter){
    if (itter == -1){return -10000;}
    for(int i = itter - 1;i>-1;--i){
        if (str[i] == elem) return i;
    }
    return -10000;
}

int main()
{
    int t;
    cin >> t;
    while(t--){
        string a;
        cin >> a;
        int nul_pos = give_pos(a,'0');
        int next_nul = give_pos_after(a,'0',nul_pos);
        int op1 = a.size() - next_nul - 2;

        nul_pos = give_pos(a,'0');
        next_nul = give_pos_after(a,'5',nul_pos);
        op1 = min(op1,int(a.size() - next_nul - 2));

        nul_pos = give_pos(a,'5');
        next_nul = give_pos_after(a,'2',nul_pos);
        op1 = min(op1,int(a.size() - next_nul - 2));

        nul_pos = give_pos(a,'5');
        next_nul = give_pos_after(a,'7',nul_pos);
        op1 = min(op1,int(a.size() - next_nul - 2));

        cout << op1 << endl;
    }
    return 0;
}

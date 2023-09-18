#include <iostream>
#include <set>
using namespace std;

int main()
{
    string J;
    cin >> J;

    set<char> st;

    for(int i = 0;i < J.size(); ++i){
        st.insert(J[i]);
    }

    string S;
    cin >> S;
    int ans = 0;
    for(int i = 0;i < S.size(); ++i){
        if (st.find(S[i]) != st.end()){
            ans++;
        }
    }

    cout << ans << endl;
    return 0;
}

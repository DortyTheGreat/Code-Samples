#include <iostream>

#include <string>
#include <vector>
#include <set>
#include <map>
using namespace std;


int main()
{
    string s;
    cin >> s;

    string b;
    cin >> b;
    set<char> st;
    for(int i = 0;i < b.size(); ++i){
        st.insert(b[i]);
    }
    int ans = 228228228;
    for(int i = 0; i < s.size(); ++i){
        /// [i,j]
        set<char> st_c = st;
        for(int j = i; j < s.size(); ++j){
            if (st.find(s[j]) == st.end()){
                /// элемента нет
                break;
            }
            st_c.erase(s[j]);
            if (st_c.empty()){
                ans = min(ans,j-i);
                break;
            }
        }
    }
    if (ans == 228228228){
        cout << 0;
    }else{
        cout << ans+1;
    }
    return 0;
}

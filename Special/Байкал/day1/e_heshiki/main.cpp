#include <iostream>
#include <unordered_set>
using namespace std;

int main()
{
    string str;
    cin >> str;
    unordered_set<uint64_t> st;
    st.reserve(5005 * 1001 * 1);

    for(int l = 0; l < str.size(); ++ l){
        uint64_t hasher = 0;
        for(int r = l; r < str.size(); ++r){
            hasher *= 30;
            hasher += str[r]-'a' + 1;
            hasher %= 9212242802769551ll; /// THIS IS A PRIME
            ///cout << hasher << endl;
            st.insert(hasher);
        }
    }

    cout << st.size();
    return 0;
}

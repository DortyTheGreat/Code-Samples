#include <iostream>
#include <vector>
#include <cassert>
#include <set>

using namespace std;

#define int int64_t


signed main()
{
    ios::sync_with_stdio(0); cin.tie(0);

    int N, K;
    cin >> N >> K;

    vector<int> ans;
    vector<int> value;
    int ans_total = 0;

    ans.resize(N);
    value.resize(N);

    for(int i = 0; i < N; ++i){
        cin >> value[i];
    }

    set<pair<int,int> > st;

    for(int i = 0; i < N; ++i){

        if (i >= K){
            st.erase({value[i-K],i-K});
        }

        st.insert({value[i], i} );

        auto [val, ind] = *(st.begin());

        ans_total += val;
        ans[ind] += 1;

    }

    cout << ans_total << endl;
    for(int i = 0; i < N; ++i){
        cout << ans[i] << " ";
    }




    return 0;
}

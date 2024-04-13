#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    int n,m,q;
    cin >> n >> m >> q;

    vector<int> a(n);
    vector<int> b(m);
    map<int, int> mp; /// a - b

    for(int i = 0; i < n; ++i){
        cin >> a[i];
        mp[a[i]]++;
    }

    for(int j = 0; j < m; ++j){
        cin >> b[j];
        mp[b[j]]--;
    }




    int ans = 0;

    for(const auto& [u,v] : mp ){
        ans += abs(v);
    }

    for(int i = 0; i < q; ++i){
        int t;
        char P;
        int num;
        cin >> t >> P >> num;

        int prev = mp[num];

        if (P == 'A'){
            mp[num] += t;
        }else{
            mp[num] -= t;
        }

        ans += abs(mp[num]) - abs(prev);
        cout << ans << " ";
    }

    return 0;
}

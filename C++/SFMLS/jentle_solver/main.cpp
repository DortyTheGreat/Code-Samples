#include <iostream>
#include <map>
#define int int64_t
using namespace std;

signed main()
{
    int n,m,q;
    cin >> n >> m >> q;

    int idc1, idc2;

    cin >> idc1 >> idc2;

    for(int i = 0; i < m; ++i){
        for(int j = 0; j < n; ++j){
            int useless;
            cin >> useless;
        }
    }

    map<int,int> mp;

    for(int i = 0;i < q; ++i){
        int x,y;
        cin >> x >> y;

        int tipo_pair = x*10 * 1001 + y;
        mp[tipo_pair]++;
    }

    int ans = q*(q-1)/2;

    for(const auto& p : mp){
        ans -= p.second*(p.second-1)/2;
    }

    cout << ans;


    return 0;
}

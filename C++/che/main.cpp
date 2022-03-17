#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define int long long
signed main()
{
    int n,m;
    cin >> n >> m;

    vector<int> v1,v2;
    v1.resize(n);
    v2.resize(m);

    sort(v1.begin(),v1.end());
    reverse(v1.begin(),v1.end());
    sort(v2.begin(),v2.end());

    for(int i = 0;i<n;i++){
        cin >> v1[i];
    }

    for(int i = 0;i<m;i++){
        cin >> v2[i];
    }

    int ans = 0;
    for(int i = 0;i<min(n,m);i++){
        ans += max(0ll,v2[i]-v1[i]);
    }

    cout << ans << endl;

    return 0;
}

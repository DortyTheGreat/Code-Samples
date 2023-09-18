#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int n,m;
    cin >> n >> m;
    vector<int> vc1(n);
    vector<int> vc2(m);

    for(int i = 0; i < n; ++i){
       cin >> vc1[i];
    }

    sort(vc1.begin(),vc1.end());


    for(int i = 0; i < m; ++i){
       cin >> vc2[i];
    }

    sort(vc2.begin(),vc2.end());
    reverse(vc2.begin(),vc2.end());
    uint64_t ans = 0;

    for(int i = 0; i < min(n,m); ++i){
        if ( vc2[i] - vc1[i] > 0 ){
            ans += vc2[i] - vc1[i];
        }
    }

    cout << ans << endl;
    return 0;
}

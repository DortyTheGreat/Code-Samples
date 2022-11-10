#include <iostream>

using namespace std;
#include <set>
#include <vector>
int main()
{
    int n;
    cin >> n;
    vector<int> vc(n);
    for(int i = 0; i < n;++i){
        cin >> vc[i];
    }

    int m;
    cin >> m;
    multiset<int> ms;

    for(int i = 0; i < m;++i){
        int arg;
        cin >> arg;
        ms.insert(arg);
    }

    int ans = 0;

    for(int i = 0; i < n;++i){
        auto l_b = ms.lower_bound(vc[i]);
        if (l_b == ms.end()){cout << ans << endl; return 0;}
        ans++;
        ms.erase(l_b);
    }

    cout << m << endl;
    return 0;
}

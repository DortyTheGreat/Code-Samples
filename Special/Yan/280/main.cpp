#include <iostream>
#include <set>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<pair<int,int> > vc;
    for(int i = 0;i < n;++i){
        int a,b;
        cin >> a >> b;
        if (b < a){
            swap(a,b);
        }
        vc.push_back({a,b});
    }

    multiset<int> maxes;

    sort(vc.begin(), vc.end());

    vector<int> inserts;
    for(int i = 0;i < n - 1;++i){
        if (vc[i].first != vc[i+1].first){
            maxes.insert(vc[i].second);
            inserts.push_back(vc[i].second);
        }
    }

    maxes.insert(vc[n - 1].second);
    inserts.push_back(vc[n - 1].second);

    int ans = 0;

    int h = 0;
    maxes.erase(maxes.find(inserts[h++]));
    for(int i = 0;i < n - 1;++i){

        if (maxes.upper_bound(vc[i].second) != maxes.end()){
            ans ++;
        }

        if (vc[i].first != vc[i+1].first){

            maxes.erase(maxes.find(inserts[h++]));
        }

    }
    cout << n - ans;
    return 0;
}

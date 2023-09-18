// change to O3 to disable fast-math for geometry problems

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int k;
    int n,m;
    int l,r;
    cin>>k;
    for (int ii=0;ii<k;++ii){
        cin>>n>>m;
        vector<int> a(n, 1);
        vector<pair<int,int>> lrs(m);
        for (int i=0;i<m;++i){
            cin>>l>>r;
            l--;
            r--;
            lrs[i] = make_pair(l,r);
        }
        sort(lrs.begin(), lrs.end());

        vector<pair<int,int>> fin;
        fin.push_back(lrs[0]);

        for (int i=1;i<m;++i){
            if (lrs[i].first >= fin.back().first && lrs[i].second <= fin.back().second){
                continue;
            }
            else if (lrs[i].first <= fin.back().first){
                fin[fin.size()-1].second = max(fin.back().second, lrs[i].second);
            }
            else if (fin.back().first < lrs[i].first && lrs[i].first <= fin.back().second){
                fin.emplace_back(fin.back().second+1, lrs[i].second);
            }
            else{
                fin.push_back(lrs[i]);
            }
        }
        for (auto& i: fin){
            // cout << "\n" << i.first << ' ' << i.second << "\n--------\n";
            if (i.first<a.size()){
                a[i.first] = 1;
                for (int j=i.first+1;j<=i.second; ++j){
                    a[j] = a[j-1]+1;
                }
            }
        }
        for (int i: a){
            cout<<i<<' ';
        }
        cout<<'\n';
    }
    return 0;
}

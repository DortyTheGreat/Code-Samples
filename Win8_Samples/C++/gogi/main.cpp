#include <iostream>
#include <vector>

#include <stack>
#include <set>

using namespace std;

const int size_ = 200000;

int ans[size_]; int h = 0;
multiset<int>g[size_];
int used[size_];

void euler(int v) {
    while (!g[v].empty()) {
        int u = *g[v].begin();
        g[v].erase(g[v].find(u));
        g[u].erase(g[u].find(v));
        euler(u);
    }
    ans[h] = (v + 1);h++;
    used[v] = 1;
}

int main()
{
    int n,m,p;
    for(int i =0;i<size_;i++){
        used[i] = 0;
    }

    cin >> n >> m >> p;



    vector<int> deg (n);

    int remem = -1;

    for(int i =0;i<m;i++){
        int r1,r2;
        cin >> r1 >> r2;
        r1--;r2--;
        g[r1].insert(r2);
        g[r2].insert(r1);
        deg[r1]+=1;
        deg[r2]+=1;
        remem = r2;
    }

    int cou=0;
    int n_index = -1;

    for(int i =0;i<n;i++){
        if (deg[i]%2 == 1){
            cou++;
            n_index = i;
        }
    }

    if (cou >= 3){
        cout << "NO";
        return 0;
    }
    if (n_index == -1){
        euler(remem);
    }else{
        euler(n_index);
    }

    for(int i =0;i<n;i++){
        if (!( (used[i]==1) || (g[i].size() == 0))){
            cout << "NO";
            return 0;
        }
    }

    cout << "YES" << endl;
    if (p){
        for (int i = 1; i + 1 < h; ++i) {
            cout << ans[0] << ' ' << ans[i] << ' ' << ans[i + 1] << '\n';
        }
    }





}

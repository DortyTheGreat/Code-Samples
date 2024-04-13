#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

#define int int64_t

vector<vector<pair<int,int> > > g;



struct predl{
    int U, V, T, C, orig;
    bool operator<(predl other){
        return C < other.C;
    }
};

struct treb{
    int A,B,T;
};

vector<predl> P;
vector<treb> TREB;
int n,m;
int trebs;
int K;

vector<int> dijkstra(const vector<vector<pair<int,int> > >& g, int s){
    int n = g.size();
    vector<int> d(n, 1001 * 1001 * 1001);
    d[s] = 0;
    set<pair<int,int> > q;
    q.emplace(0,s);
    while(!q.empty()){
        int v = q.begin()->second;
        q.erase(q.begin());
        for(auto [u, w] : g[v]){
            if (d[u] > d[v] + w){
                q.erase({d[u],u});
                d[u] = d[v] + w;
                q.emplace(d[u], u);
            }
        }
    }
    return d;
}


bool f(int boundary){
    vector<vector<pair<int,int> > > g_alt;
    g_alt = g;

    for(int i = 0; i < K; ++i){
        if (P[i].C > boundary) break;
        g_alt[P[i].U].push_back({P[i].V,P[i].T});
        g_alt[P[i].V].push_back({P[i].U,P[i].T});
    }


    map<int, vector<int> > memo;
    for(int i = 0; i < trebs; ++i){
        if (memo.find(TREB[i].A) == memo.end()){
            memo[TREB[i].A] = dijkstra(g_alt,TREB[i].A);
        }
        if (memo[TREB[i].A][TREB[i].B] > TREB[i].T) return 0;
    }
    return 1;
}

signed main()
{

    cin >> n >> m;
    g.resize(n);

    for(int i = 0; i < m; ++i){
        int u,v,t;
        cin >> u >> v >> t;
        --u; --v;
        g[u].push_back({v,t});
        g[v].push_back({u,t});
    }




    cin >> K;

    for(int i = 0; i < K; ++i){
        int U,V,T,C;
        cin >> U >> V >> T >> C;
        --U;--V;
        P.push_back({U,V,T,C,i});
    }

    sort(P.begin(), P.end());


    cin >> trebs;



    for(int i = 0; i < trebs; ++i){
        int A,B,T;
        cin >> A >> B >> T;
        --A;--B;
        TREB.push_back({A,B,T});
    }


    int l = 0; /// f(0) = false
    int r = 1001 * 1001 * 1001; /// f(r) = true

    if (f(r) == 0){
        cout << -1;
        return 0;
    }

    while (r - l > 1) {
        int m = (r + l) / 2;
        if (f(m))
            r = m;
        else
            l = m;
    }

    vector<int> anses;
    for(int i = 0; i < K; ++i){
        if (P[i].C > r) break;
        anses.push_back(P[i].orig);
    }

    sort(anses.begin(),anses.end());

    cout << anses.size() << endl;
    for(auto e : anses){
        cout << e+1 << " ";
    }

    return 0;
}

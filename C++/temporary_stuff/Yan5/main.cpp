#include <iostream>
#include <map>
#include <set>

#define int long long

using namespace std;

const int maxn = 200000 + 10;
const int inf = 1e10;

const pair<int,int> inf_pair = {inf,inf};

const int secret = -1337;
const pair<int,int> secret_pair = {secret,secret};

pair<int,int> memo[maxn];

map<int,int > made_of[maxn]; /// например made_of[3] = {{1,1}, {2,13} }; делается из 1 - 1 штука, 2 - 13 штук

set<int> visited;

inline pair<int,int> operator* (const pair<int,int>& p, int mul){
    return {p.first*mul, p.second*mul};
}


inline void operator+= (pair<int,int> &p, const pair<int,int>& p2){
    p.first += p2.first;
    p.second += p2.second;
}


pair<int,int> search_(int id){

    if (memo[id] != secret_pair ){ return memo[id];}

    if (visited.find(id) != visited.end()){
        /// рекурсия
        return memo[id] = inf_pair;
    }

    visited.insert(id);
    pair<int,int> ans = {0,0};

    for(auto p : made_of[id]){
        ans += search_(p.first)*p.second;
    }

    if (ans.first >= inf || ans.second >= inf){
        ans = inf_pair;
    }
    return memo[id] = ans;
}

pair<int,int> f(int id){
    if (memo[id] != secret_pair){return memo[id];}
    visited.clear();
    return memo[id] = search_(id);
}


signed main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    for(int i = 0;i<maxn;++i){
        memo[i] = {secret, secret};
    }

    memo[1] = {1,0};
    memo[2] = {0,1};

    int n;
    cin >> n;
    n-= 2;
    for(int i = 0;i<n;++i){
        int m, id;
        cin >> m;
        map<int,int> mp; /// id, amount
        for(int j = 0; j < m;++j){
            cin >> id;
            mp[id]++;
        }

        made_of[3+i] = mp;
    }




    int q;
    cin >> q;

    for(int i = 0; i < q;++i){
        int x,y,s;
        cin >> x >> y >> s;
        auto p = f(s);
        if (p.first <= x && p.second <= y){
            cout << "1";
        }else{
            cout << "0";
        }
    }

    ///cout << "Hello world!" << endl;
    return 0;
}

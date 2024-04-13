#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main()
{
    int n,m,q;
    cin >> n >> m >> q;
    vector<vector<int>> matr(n, vector<int> (m, 0));

    map<string,int> mp;

    vector< bool> includee (n);
    vector< pair<int,int> > condense (m);

    for(int i = 0; i < m; ++i){
        condense[i] = {-1001 * 1001 * 1001, 1001 * 1001 * 1001};
    }

    for(int i = 0; i < n; ++i){
        includee[i] = 1;
    }

    for(int i = 0; i < m; ++i){
        string s;
        cin >> s;
        mp[s] = i;
    }

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            cin >> matr[i][j];
        }
    }

    for(int i = 0; i < q; ++i){
        string s;
        char equ;
        int check;
        cin >> s >> equ >> check;

        if (equ == '>'){
            condense[mp[s]].first = max(condense[mp[s]].first, check);
        }else{
            condense[mp[s]].second = min(condense[mp[s]].second, check);
        }
    }

    int64_t answer = 0;

    for(int j = 0; j < m; ++j){
        for(int i = 0; i < n; ++i){
            if ( !(matr[i][j] > condense[j].first && matr[i][j] < condense[j].second) ){
                includee[i] = false;
            }
        }
    }

    for(int j = 0; j < m; ++j){
        for(int i = 0; i < n; ++i){
            if ( includee[i] ){
                answer += matr[i][j];
            }
        }
    }

    cout << answer;


    return 0;
}

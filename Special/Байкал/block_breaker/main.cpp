#include <iostream>

using namespace std;

int n,m;

int update(int x, int y, bool** arr, bool force_delete){
    if (x < 0 || y < 0 || x >= n || y >= m) return 0;
    int ret = 0;

    bool x_fall_cond = false;
    if (x-1 >= 0) if (arr[x-1][y] == 0) x_fall_cond = true;
    if (x+1 < n) if (arr[x+1][y] == 0) x_fall_cond = true;


    bool y_fall_cond = false;
    if (y-1 >= 0) if (arr[x][y-1] == 0) y_fall_cond = true;
    if (y+1 < m) if (arr[x][y+1] == 0) y_fall_cond = true;

    bool fall_condition = y_fall_cond && x_fall_cond;

    if (force_delete || fall_condition){
        if (arr[x][y]){
            arr[x][y] = 0;
            return 1 + update(x-1,y,arr,0) + update(x+1,y,arr,0) + update(x,y-1,arr,0) + update(x,y+1,arr,0);
        }
    }

    return 0;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    int t;
    cin >> t;
    while(t--){

        cin >> n >> m;
        bool** arr = new bool*[n];

        for(int i = 0; i < n; ++i){
            arr[i] = new bool[m];
        }

        for(int i = 0; i < n; ++i){
            for(int j = 0; j < m; ++j){
                arr[i][j] = true;
            }
        }

        int q;
        cin >> q;

        for(int i = 0; i < q; ++i){
            int x,y;
            cin >> x >> y;
            --x;
            --y;

            cout << update(x,y,arr, 1) << '\n';

        }
    }

    return 0;
}

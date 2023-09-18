#include <iostream>

using namespace std;

int cool_num = 2000000023;

int main()
{
    int n;
    cin >> n;

    int inp[506][506];
    int out[506][506];
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            cin >> inp[i][j];
            if (i == j){
                out[i][j] = cool_num;
            }else{
                if (inp[i][j] == -1){
                    out[i][j] = cool_num;
                }else{
                    out[i][j] = inp[i][j];
                }
            }
        }
    }

    for(int updates = 0; updates < 3; updates++){
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < n; ++j){
                int max_found = -1;
                for(int c = 0; c < n; ++c){
                    max_found = max(max_found, min(out[i][c], out[c][j]) );
                }
                out[i][j] = max(max_found,out[i][j] );
            }
        }
    }

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            cout << out[i][j] << " ";
        }
        cout << '\n';
    }

    return 0;
}

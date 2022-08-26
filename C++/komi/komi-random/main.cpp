#include <bits/stdc++.h>
using namespace std;

int seed = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 mt(seed);

using namespace std;

const int n = 312;

int main()
{
    int arr[n];

    for(int i =0;i<n;++i){
        arr[i] = i;
    }

    int d[n][n];

    int temp_ray[n];
    ofstream fout("log.txt");
    freopen("usca312_dist.txt", "r", stdin);

    for(int i =0;i < n; ++i){
        for(int j =0;j< n; ++j){
            cin >> d[i][j];
        }
    }

    int min_len = 100000000;
    for(int ITTER = 0; ITTER < 100000000;++ITTER){
        memcpy(temp_ray,arr,n * sizeof(int));
        std::shuffle(temp_ray,temp_ray + n , mt);
        int len = 0;

        for(int i = 0;i < n -1; ++i){
            len += d[temp_ray[i]][temp_ray[i+1]];
        }
        if(len < min_len){min_len = len; cout << len << endl;}
    }



    cout << "Hello world!" << endl;
    return 0;
}

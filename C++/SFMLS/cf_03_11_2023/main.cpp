#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <chrono>
#include <random>


using namespace std;
#define all(a) (a).begin(), (a).end()



void solve() {

    int n = 23;

    vector<int> arr(n);

    for(int i = 0; i < n; ++i){
        arr[i] = i;
    }



    int seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 mt(seed);

    shuffle(arr.begin(), arr.end(),  mt);

    for(int i = 0; i < n; ++i){
        cout << arr[i] << " ";
    }
        cout << endl;

    int m = n -1;
    int highest_power_of_two = 16; /// 2^3 = 8; 8 is biggest in (orig output input n)
    vector<int> arr2(m);
    for(int i = 0; i < n-1; ++i){
        cout << ((arr[i])^(arr[i+1])) << " ";
        arr2[i] = ((arr[i])^(arr[i+1]));
    }
    cout << endl;

    vector<int> repair(m+1);

    for(int starts = 0; starts < m + 1; ++starts){
        repair[0] = starts; /// 0 or highest_power_of_two



        cout << repair[0] << " ";


        vector<int> finallium;
        for(int i = 0; i < m; ++i){
            repair[i+1] = repair[i]^arr2[i];
            cout << repair[i+1]<<  " ";
            if (repair[i+1] >= m+1){
                ///cout << repair[i+1] -  highest_power_of_two<<  " ";
                finallium.push_back(repair[i+1] -  (m+1));
            }

        }

        sort(all(finallium));

        cout << endl;
        for(auto v : finallium){
            cout << v << " ";
        }
        cout << endl;
    }




}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t = 1;
    ///cin >> t;
    while (t--)
        solve();
}

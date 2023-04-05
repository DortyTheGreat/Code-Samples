#include <iostream>
#include <utility>
#include <cmath>
using namespace std;

int main()
{
    /// 10^8 algo

    int n;
    cin >> n;
    int arr[100000 + 10];

    pair<int,int> starts[10000 + 10]; int s = 0; /// value, index
    pair<int,int> ends[10000 + 10]; int e = 0; /// value, index



    for(int i = 0; i < n; ++i){
        cin >> arr[i];
    }

    starts[0] = {arr[0],0};
    for(int i = 1; i < n; ++i){
        if (arr[i] > starts[s].first){
            starts[++s] = {arr[i],i};
        }
    }

    ends[0] = {arr[n-1],n-1};
    for(int i = n-2; i > -1; --i){
        if (arr[i] > ends[e].first){
            ends[++e] = {arr[i],i};
        }
    }
    /*
    for(int i = 0; i < s+1; ++i){
        cout << starts[i].first << " " << starts[i].second;
    }
    cout << endl;

    for(int i = 0; i < e+1; ++i){
        cout << ends[i].first << " " << ends[i].second;
    }
    cout << endl;
    */
    int maxi = 0;
    for(int i = 0; i < s+1; ++i){
        for(int j = 0; j < e+1; ++j){
            int ans = min(starts[i].first,ends[j].first);
            ans *= abs(starts[i].second - ends[j].second);
            maxi = max(maxi,ans);
        }
        ///cout << starts[i].first << " " << starts[i].second;
    }

    cout << maxi << endl;
    return 0;
}

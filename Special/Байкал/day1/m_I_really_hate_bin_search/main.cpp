#include <iostream>
#define int long long
using namespace std;

int arr[12 * 1001];
int n, k;

int f(int len){
    int ans = 0;
    for(int i = 0;i < n; ++i){
        ans += arr[i] / len;
    }

    return ans;
}

signed main()
{

    cin >> n >> k;

    for(int i = 0; i < n; ++i){
        cin >> arr[i];
    }

    if (f(1) < k){
        cout << 0;
        return 0;
    }


    int l = 1;



    int r = 2000000;


    while ( r - l > 1){
        int m = (r+l)/2;
        if ( f(m) < k ){
            r = m;
        }else{
            l = m;
        }
    }

    cout << l;

    return 0;
}

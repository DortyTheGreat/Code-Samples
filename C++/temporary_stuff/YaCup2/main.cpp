#include <iostream>
#define int long long
using namespace std;

int b;
int n;



int solve(int arg, int depth){
    if (arg < b) return 0;
    int ans = 0;
    for(int i = depth == 0 ? b : 0; i < 10; i+= b){
        ans++;
        ans += solve((arg-i) / 10, depth+1);
    }
    return ans;
}

signed main()
{
    int t;
    cin >> t;
    while(t--){
        cin >> n >> b;
        cout << solve(n,0) << endl;
    }

    return 0;
}

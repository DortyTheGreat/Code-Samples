#include <iostream>
#define int long long
using namespace std;

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        if (n % 3 == 0){
            cout << (n/3)*(n/3)*(n/3) << " ";
            continue;
        }

        if (n % 4 == 0){
            cout << (n/2)*(n/4)*(n/4) << " ";
            continue;
        }
        cout << "-1 "; continue;
    }

    return 0;
}

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

int main()
{
    int n;
    cin >> n;
    string s;
    cin >> s;

    vector<int> a(n+1); int a_c = 0;
    vector<int> b(n+1); int b_c = 0;
    vector<int> c(n+1); int c_c = 0;
    vector<int> d(n+1); int d_c = 0;

    /// Лень делать круто -_-

    a[0] = b[0] = c[0] = d[0] = 0;

    for(int i = 0;i < n;++i){
        if (s[i] == 'a') a_c++;
        if (s[i] == 'b') b_c++;
        if (s[i] == 'c') c_c++;
        if (s[i] == 'd') d_c++;

        a[i+1]= a_c;
        b[i+1]= b_c;
        c[i+1]= c_c;
        d[i+1]= d_c;
    }


    int ans = 1000 * 1000; /// INF


    for(int i = 0; i < n+1; ++i){
        auto it_a = lower_bound(a.begin(), a.end(), a[i]+1 );
        auto it_b = lower_bound(b.begin(), b.end(), b[i]+1 );
        auto it_c = lower_bound(c.begin(), c.end(), c[i]+1 );
        auto it_d = lower_bound(d.begin(), d.end(), d[i]+1 );

        if (it_a == a.end() || it_c == c.end() || it_b == b.end() || it_d == d.end() ){
            /// ничего не делай
        }else{
            int maxim = -1;
            maxim = max(maxim, int(distance(a.begin(), it_a))-i );
            maxim = max(maxim, int(distance(b.begin(), it_b))-i );
            maxim = max(maxim, int(distance(c.begin(), it_c))-i );
            maxim = max(maxim, int(distance(d.begin(), it_d))-i );

            ans = min(ans,maxim);
            ///cout << ans << " " << maxim << " " << i << endl;
        }

    }

    if (ans == 1000 * 1000){
        cout << "-1";
        return 0;
    }
    cout << ans;

    return 0;
}

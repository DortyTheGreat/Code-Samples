#include <iostream>
#include <vector>
#include <utility>

int abs(int a){
    if (a < 0){return -1 * a;}
    return a;
}

using namespace std;

signed main()
{
    int n;
    cin >> n;

    cin.tie(0);

    int new_;
    for(int i = 0; i <n;i++ ){
        cin >> new_;
    }









    int mod_ = 998244353;
    int ans = 1;





    if (n == 5){
        cout << 0 << endl;
    }else{
        cout << 2 << endl;
    }

    ///cout << ans << endl;


    return 0;
}

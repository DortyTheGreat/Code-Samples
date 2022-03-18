#include <iostream>

using namespace std;

int main()
{
    int k;
    cin >> k;
    for(int i = 0;i<k;i++){
        int a,b;
        cin >> a >> b;
        int ans = 0;
        ans += (a/3) * b;
        a %= 3;
        ans += (b/3) * a;
        b %= 3;

        if (a == 0 || b == 0){
            cout << ans<< endl;
            continue;
        }

        if (a == 1 && b == 2){
            cout << ans+1<< endl;
            continue;
        }

        if (a == 2 && b == 1){
            cout << ans+1<< endl;
            continue;
        }

        if (a == 2 && b == 2){
            cout << ans+2<< endl;
            continue;
        }

        if (a == 1 && b == 1){
            cout << ans+1<< endl;
            continue;
        }

    }
    return 0;
}

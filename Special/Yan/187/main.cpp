#include <iostream>

#include <vector>
#include <algorithm>
using namespace std;
/// вроде можно как-то по-умному при помощи бора, но там капец мозги плавятся...
int main()
{
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> vc(n);
        for(int i = 0;i < n;++i){
            cin >> vc[i];
        }
        sort(vc.begin(), vc.end());

        int min_ = 2001 * 1001 * 1001;

        for(int i = 0;i < n - 1;++i){
            min_ = min(min_, vc[i] ^ vc[i+1]);
        }
        cout << min_ << endl;
    }
    return 0;
}

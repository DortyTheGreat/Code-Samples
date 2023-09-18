#include <iostream>
#include <map>
using namespace std;

int main()
{
    int n;
    cin >> n;
    map<int,int> mp;
    int maxi = -1;
    int maxi_num = -1;
    for(int i = 0; i< n;++i){
        int b;
        cin >> b;
        if (++mp[b] > maxi){
            maxi = mp[b];
            maxi_num = b;
        }

        if (mp[b] == maxi){
            maxi_num = max(maxi_num, b);
        }
    }

    cout << maxi_num;

    return 0;
}

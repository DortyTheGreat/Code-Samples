
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
using namespace std;
int main()
{
	int n;
    cin >> n;
    map<int,int> mp;
    for(int i = 0; i < n;++i){
        int a;
        cin >> a;
        mp[a]++;
    }
    int ans = 0;
    for(auto elem : mp){
        if (elem.second == 1){
            ans++;
        }
    }
    cout << ans;
	return 0;
}

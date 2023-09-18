#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int64_t k,n;
    cin >> k >> n;
    vector<int64_t> vc(k);
    for(int i = 0;i < k;++i){
        cin >> vc[i];
    }

    sort(vc.begin(), vc.end());

    int64_t result = 0;

    int64_t offset = 0;
    for(int i = k - 1;i > -1;--i){
        int64_t t = (n-1-offset+k)/k;
        if (t > 0) result += t*vc[i];
        offset++;
    }
    cout << result;
    return 0;
}

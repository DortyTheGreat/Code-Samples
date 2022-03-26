#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

#define int long long

vector<int> all_divs(int num){
    vector<int> ret;

    int sqrt_ = sqrt(num);

    for(int i = 2;i <= sqrt_;i++){
        if (num % i == 0){
            ret.push_back(i);
            ret.push_back(num/i);
        }
    }
    ret.push_back(num);

    return ret;

}

int NOD(int a,int b){

    if (a == b){return a;}
    if (a < b){swap(a,b);}
    if (b == 1){return 1;}
    if (b == 0){return a;}
    return NOD(a%b,b);
}

int solve(int a, int b){
    if ( NOD(a,b) != 1){return 0;}
    vector<int> all_divs_ = all_divs(a);
    int ans = 1e10;
    for (int i = 0;i<all_divs_.size();i++){
        ans = min(ans,all_divs_[i] - (b % all_divs_[i]));
    }
    return ans;
}

signed main()
{

    int t;
    cin >> t;
    while(t--){
        int a,b;
        cin >> a >> b;
        cout << solve(a,b) << endl;
    }

    return 0;
}

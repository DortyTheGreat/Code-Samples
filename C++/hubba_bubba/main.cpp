#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

const int sz= 2 * 100000;
const int K = 20;


pair<int,int> f_SP(pair<int,int> &a, pair<int,int> &b) {
    return make_pair(max(a.first, b.first), min(a.second, b.second));
}

pair<int,int> TABLE_TOP[sz][K + 1];



pair<int, int> segments[sz];

int main(){




    int n, min_, max_;
    cin >> n >> min_ >> max_;



    for (int i = 0; i < n; i++) {
        cin >> segments[i].first >> segments[i].second;
    }


    for (int i = 0; i < n; ++i){
        TABLE_TOP[i][0] = segments[i];
    }

    for (int j = 1; j <= K; ++j){
        for (int i = 0; i + (1 << j) <= n; ++i){
            TABLE_TOP[i][j] = f_SP(TABLE_TOP[i][j - 1], TABLE_TOP[i + (1 << (j - 1))][j - 1]);
        }

    }



    long long ans = 0;
    for (int i = 0; i < n; i++) {

        int add_ = 0;

        int dlinna = segments[i].second - segments[i].first;

        if (dlinna < min_){
            continue;
        }



        ///
        int l = 0;
        int r = n - i;
        while (r - l > 1) {
            int mid = (l + r) / 2;

            int lg = __lg(mid+1);
            pair<int,int> s = f_SP(TABLE_TOP[i][lg], TABLE_TOP[i + mid - (1 << lg) + 1][lg]);
            int len = s.second - s.first;
            if (len < 0){
                len = 0;
            }


            if (len >= min_) {
                l = mid;
            } else {
                r = mid;
            }
        }
        ///



        add_ = r;

        if (dlinna > max_) {
            l = 0;
            r = n - i;
            while (r - l > 1) {
                int mid = (l + r) / 2;

                int lg = __lg(mid+1);
                pair<int,int> s = f_SP(TABLE_TOP[i][lg], TABLE_TOP[i + mid - (1 << lg) + 1][lg]);
                int len = s.second - s.first;

                if (len > max_) {
                    l = mid;
                } else {
                    r = mid;
                }
            }
            add_ -= r;
        }

        ans += add_;
    }
    cout << ans;
}

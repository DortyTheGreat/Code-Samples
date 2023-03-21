#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

#define int int64_t

vector<int> l;
vector<int> r;

/// Какова стоимость такого ****
int cost(int x) {
    int ss = 0;
    vector<pair<int, int> > can; /// pairs...
    vector<bool> choosing(l.size());

    for (int i = 0; i < l.size(); ++i) {

        if (x <= r[i]) {
            can.push_back({l[i], i});
        }
    }

    if (can.size() < (l.size() + 1) / 2){ /// Слишком мало
        return 1001 * 1001 * 1001; /// INF
    }

    sort(can.begin(),can.end());
    reverse(can.begin(),can.end());


    for (int i = 0; i < (l.size() + 1) / 2; ++i) {
        ss += max(can[i].first, x);
        choosing[can[i].second] = true;
    }

    for (int i = 0; i < l.size(); ++i) {
        if (choosing[i]){
            /// Ничего не делай, ибо он бесплатен.
        }else{
            ss += l[i];
        }

    }
    ///cout << x << " " << ss << endl;
    return ss;
}


signed main()
{

    int s_low, s_high;

    int n,s;
    cin >> n >> s;

    l.resize(n);
    r.resize(n);

    for(int i = 0; i < n;++i){
        cin >> l[i] >> r[i];
    }







    int l_ = 0;
    int r_ = 1001 * 1001 * 1001; /// INF

    ///cout << l_ << " " << r_ << endl;

    ///cout << cost(7) << endl;

    ///for (int i = 0; i < 100; i++) cout << cost(i) << " ";

    while (r_ - l_ > 1) {
        int m = (l_ + r_) / 2;
        if (cost(m) <= s){
            l_ = m;
        }else{
            r_ = m;
        }
    }

    cout << l_;
    return 0;
}

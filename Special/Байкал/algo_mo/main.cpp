#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>
using namespace std;

struct Query {
    int l, r, k, orig_id;
};

int K = 316; ///

bool compare(Query q1, Query q2) {

    if (q1.l / K != q2.l / K) {
        return q1.l / K < q2.l / K;
    }
    return q1.r < q2.r;
}

bool compa2(const pair<int, vector<int> > & e1, const pair<int, vector<int> > & e2) {

    return e1.first < e2.first;
}

vector<pair<int, vector<int> > > minimums_on_segments(const vector<int>& arr, const vector<Query>& queries) {
    vector<pair<int, vector<int> > > result(queries.size());

    /// [l,r]
    int curr_l = 0, curr_r = 0;
    multiset<int> heapper;
    heapper.insert(arr[0]);
    for (int i = 0; i < queries.size(); i++) {
        int l = queries[i].l;
        int r = queries[i].r;

        while (curr_l > l) {
            curr_l--;

            heapper.insert(arr[curr_l]);

        }
        while (curr_r < r) {
            curr_r++;

            heapper.insert(arr[curr_r]);

        }
        while (curr_l < l) {

            heapper.erase(heapper.find(arr[curr_l]) );


            curr_l++;
        }
        while (curr_r > r) {

            heapper.erase(heapper.find((arr[curr_r])));

            curr_r--;
        }

        auto iit = heapper.begin();
        vector<int> t;
        for (int j = 0; j < queries[i].k; ++j) {
            t.push_back(*iit);

            ++iit;
        }
        result.push_back({queries[i].orig_id,t});


    }

    return result;
}

int main() {
    int n;
    cin >> n;
    vector<int> arr;
    arr.resize(n);


    vector<Query> queries;

    for(int i = 0; i < n; ++i){
        cin >> arr[i];
    }

    int m;
    cin >> m;
    queries.resize(m);

    for(int i = 0; i < m; ++i){
        int l,r,k;
        cin >> l >> r >> k;
        --l;
        --r;
        queries[i] = {l,r,k, i};
    }



    sort(queries.begin(), queries.end(), compare);

    vector<pair<int, vector<int> > > result = minimums_on_segments(arr, queries);


    sort(result.begin(), result.end(), compa2);

    for (int i = 0; i < result.size(); i++) {
        for(int j = 0; j <result[i].second.size(); ++j ){
            cout << result[i].second[j] << " ";
        }
        cout << "\n";
    }

    return 0;
}

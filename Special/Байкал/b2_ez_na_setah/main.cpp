#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int n,m;
    cin >> n >> m;

    vector<int> starts;
    vector<int> ends;

    for(int i = 0; i < n; ++i){
        int s,e;
        cin >> s >> e;
        if (e < s)
            swap(e,s);
        starts.push_back(s);
        ends.push_back(e);
    }

    sort(starts.begin(), starts.end());
    sort(ends.begin(), ends.end());

    for(int i = 0; i < m; ++ i){
        int p;
        cin >> p;
        int before = std::distance(starts.begin(), lower_bound(starts.begin(), starts.end(), p+1)  );
        int after = std::distance(ends.begin(), lower_bound(ends.begin(), ends.end(), p) );


        cout << before - after << " ";
    }


    return 0;
}

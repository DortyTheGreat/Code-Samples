#include <iostream>
#include <set>
#include <utility>
#include <vector>
using namespace std;

#define int int64_t

signed main()
{
    int n,x,t;
    cin >> n >> x >> t;



    set< pair<int, int> > OMFG;
    /// delta, index


    for(int i = 0; i < n; ++i){
        int v;
        cin >> v;
        OMFG.insert({abs(x-v), i});
    }

    int ans = 0;
    vector<int> answers;

    while(!OMFG.empty() && t >= (*(OMFG.begin())).first ){

        auto p = *(OMFG.begin());
        ans++;
        answers.push_back(p.second);
        t -= p.first;
        OMFG.erase(p);
    }
    cout << answers.size() << endl;

    for(int i = 0; i < answers.size(); ++i){
        cout << answers[i]+1 << " ";
    }
    return 0;
}

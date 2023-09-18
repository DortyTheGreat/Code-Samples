#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <set>
#include <unordered_set>
using namespace std;

bool cmp(const pair<int,int>& l, const pair<int,int>& r){
    if (l.first<r.first){
        return true;
    }
    if (l.first>r.first){
        return false;
    }
    return l.second>r.second;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int k;
    int n,m;
    int l,r;
    cin>>k;

    set<int> available;
    for(int i = 1; i < 100 * 1001; ++i){
        available.insert(i);
    }


    for (int ii=0;ii<k;++ii){
        cin>>n>>m;
        vector<int> a(n, 1);
        vector<pair<int,int>> lrs(m);
        for (int i=0;i<m;++i){
            cin>>l>>r;
            l--;
            r--;
            lrs[i] = {l,r};
        }

        sort(lrs.begin(), lrs.end(), cmp);

        vector<pair<int,int>> lrs_cleanup;

        int maxi_luck = -1;
        for(int i = 0; i < lrs.size(); ++i){
            if (lrs[i].second > maxi_luck){
                lrs_cleanup.push_back(lrs[i]);
                maxi_luck = lrs[i].second;
            }
        }








        vector<int> ans;

        set<int> restart;

        int curr_end = lrs_cleanup[0].second; int end_h = 0;
        int curr_start = lrs_cleanup[0].first; int start_h = 0;


        for(int i = 0; i < n; ++i){

            if (i < curr_start){
                ans.push_back(1);
                continue;
            }

            if (i <= curr_end){
                auto it = available.begin();
                available.erase(it);
                restart.insert(*it);
                //cout << "e: " << (*it) << " " << i << endl;
                ans.push_back(*it);
                continue;
            }else{
                if (end_h + 1 != lrs_cleanup.size()){


                    for(int j = curr_start; j < min(lrs_cleanup[end_h].second + 1,lrs_cleanup[end_h+1].first) ; ++j){
                        //cout << "i: " << ans[j] << endl;
                        available.insert(ans[j]);
                        restart.erase(ans[j]);
                    }

                    end_h += 1;
                    curr_end = lrs_cleanup[end_h].second;

                    curr_start = lrs_cleanup[end_h].first;
                    --i;
                }
            }
        }

        for(const auto& it : restart){
            available.insert(it);
        }
        for(const auto& it : ans){
            cout << it << " ";
        }

        for(int i = 0; i < n - ans.size(); ++i){
            cout << "1 ";
        }

        cout << '\n';


    }


}

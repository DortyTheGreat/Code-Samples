#include <iostream>
#include <bits/stdc++.h>
#define int long long
using namespace std;





signed main()
{
    string a;
    cin >> a;
    int sz = a.size();
    map<char,int> mp;
    vector<int> dels;

    for(int i = 1;i<sz;++i){
        if ( sz % i == 0 ){
            dels.push_back(i);
        }
    }

    for(int i = 0;i<sz;++i){
        mp[a[i]]++;
    }

    vector<int> vc;

    for( auto elem : mp ){
        vc.push_back(elem.second);

    }

    int ans = 2000000;

    for(int i = 0;i < dels.size();++i){

        int sz_1 = dels[i];
        int sz_2 = sz / dels[i];

        int fours = (sz_1 - sz_1%2) * (sz_2 - sz_2%2) / 4;
        int twos = ( (sz_1 - sz_1%2) * (sz_2%2) + (sz_2 - sz_2%2) * (sz_1%2) )/ 2;
        int ones = ((sz_2%2) * (sz_1%2) ) / 1;
        cout << fours << " " << twos << " " << ones << endl;
        for(int j = 0;j<vc.size(); ++j){


            while (vc[j] >= 4 && fours != 0){
                vc[j] -= 4;
                fours--;
            }
        }
        if (fours != 0){
            continue;
        }

        cout << "after" << endl;
        for(int j = 0;j<vc.size(); ++j){


            while (vc[j] >= 2 && twos != 0){
                vc[j] -= 2;
                twos--;
            }
        }
        if (twos != 0){
            continue;
        }
        cout << "after" << endl;


        for(int j = 0;j<vc.size(); ++j){


            while (vc[j] >= 1 && ones != 0){
                vc[j] -= 1;
                ones--;
            }
        }
        if (ones != 0){
            continue;
        }
        cout << "after" << endl;
        cout << "here" << endl;
        ans = min(ans,sz_1 + sz_2);

    }

    if (ans == 2000000){
        cout << "-1";
    }else{
        cout << ans;
    }




    return 0;
}

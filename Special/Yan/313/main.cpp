#include <iostream>
#include <set>
using namespace std;

int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    int n;
    cin >> n;

    multiset<int> high;
    multiset<int> low;
    int64_t ans = 0;

    for(int i = 0; i < min(n,2); ++i){
        int a;
        cin >> a;
        if (i == 0){
            low.insert(a);
        }else{
            high.insert(a);
            auto val_l = (*(low.rbegin()));
            auto val_h = (*(high.begin()));

            if ( val_l > val_h ){
                high.insert( val_l );
                low.insert(val_h);

                high.erase(val_h);
                low.erase(val_l);


            }

        }

        ans += (*(low.rbegin()));

    }


    for(int i = 2; i < n; ++i){
        int a;
        cin >> a;
        if (i % 2 == 0){
            low.insert(a);
        }else{
            high.insert(a);
        }


        auto val_l = (*(low.rbegin()));
        auto val_h = (*(high.begin()));
        if ( val_l > val_h ){
            high.insert( val_l );
            low.insert(val_h);

            high.erase(val_h);
            low.erase(val_l);


        }

        ans += (*(low.rbegin()));

        //if (a )
    }
    cout << ans << endl;
    return 0;
}

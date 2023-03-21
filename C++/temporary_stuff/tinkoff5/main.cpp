#include <iostream>
#include <set>
#include <map>
using namespace std;

#define int int64_t

signed main()
{
    int n;
    cin >> n;
    set<pair<int,int> > st; /// [l,r]

    set<pair<int,int> > new_st; /// [l,r]

    map<int64_t,int> mp; /// value -> index of last seen

    int64_t summ = 0;

    mp[0] = -1;
    for(int i = 0;i < n; ++i){
        int inp;
        cin >> inp;
        summ += inp;



        if (inp == 0){
            /// Отдельный случай с нулём
            st.insert({i,i});
            mp[0] = i;
            continue;
        }

        if (mp.find(summ) != mp.end()){
            /// Такое обратное есть -> создай отерзок
            st.insert({mp[summ]+1,i});
        }

        mp[summ] = i;

    }
    /*
    cout << "pre" << endl;
    for(auto elem : st){
        cout << elem.first << " " << elem.second << endl;
    }
    cout << endl << endl;
    */

    int minim = 1001 * 1001 * 1001;
    for (auto rit = st.rbegin(); rit != st.rend(); rit++){
        ///cout << (*rit).first << " " << (*rit).second << " " << endl;
        if ( (*rit).second > minim ){

            /// minim не меняется
            /// Элемент пропускаем

        }else{
            new_st.insert( (*rit) );
            minim = (*rit).second;
        }
    }
    /*
    cout << "post" << endl;
    for(auto elem : new_st){
        cout << elem.first << " " << elem.second << endl;
    }
    cout << endl << endl;
    */
    /// Теперь мы удалили все "большие"



    int prev_open = -1;

    int64_t ans = 0;
    for(auto elem : new_st){

        ans += int64_t(elem.first - prev_open) * (n - elem.second);

        prev_open = elem.first;

        ///cout << elem.first << " " << elem.second << endl;

    }




    cout << ans<< endl;
    return 0;
}

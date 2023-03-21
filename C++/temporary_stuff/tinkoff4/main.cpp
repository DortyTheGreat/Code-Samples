#include <iostream>
#include <map>
#include <set>
using namespace std;

int main()
{
    int n;
    cin >> n;

    map<int,int> mp;
    multiset<int> st;

    int ans = -1;

    for(int i = 0; i < n;++i){
        int inp;
        cin >> inp;
        if (mp.find(inp) == mp.end() ){
            /// Элемента не было
            mp[inp] = 1;
            st.insert(1);
        }else{
            auto itr = st.find(mp[inp]);
            st.erase(itr);

            mp[inp] += 1;
            st.insert(mp[inp]);
        }

        auto last = st.end();
        --last;

        auto pre_last = last;
        --pre_last;


        auto second = st.begin();
        ++second;


        //cout << i << " " << *(st.begin()) << " " << *(second) << " " << *(pre_last) << " " << *(last) << endl;

        //for(auto elem : st){
            //cout << elem << " ";
        //}

        //cout << endl;

        if ( ( (*(st.begin())) == 1) && ( (*(last)) == 1) ){
            /// можно и одной проверкой обойтись,но так прям наглядно
            ans = i;
        }else{

            if (st.size() == 1) continue;


            if ( (*(st.begin())) == (*(pre_last)) && ( (*(pre_last)) == (*(last))-1 ) ){
                /// Первый == Предпоследнему, Предпоследний == последнему-1
                ans = i;
            }



            if ( (*(second)) == (*(last)) && ( (*(st.begin()) )+1 == (*(second)) ) ){
                /// Второй == Последнему, Первый+1 == Второму
                ans = i;
            }

        }
    }


    cout <<ans+1;
    return 0;
}

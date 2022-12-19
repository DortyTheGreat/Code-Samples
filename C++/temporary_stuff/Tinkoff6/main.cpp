#include <iostream>

/**

пример для 13 = 1101
и 5 битов

 - есть ли 1xxxx ?
 - да? -> круто, отфильтруй до этих

 1xxxx
 01101

 ищем такое, чтобы второй бит был 0.

 ЕСЛИ ТАКИЕ ЕСТЬ, то

 - нет? ->




 Чтобы искать числа в форме 101xx
 нужно искать те, что больше или равны 10100 (lower_bound)
 при этом меньше 11000



 Код вышел очень странным (лень улучшать читабельность), но
 O(bits * log(n) * n)

 bits = 32.
 Так что должно успевать
*/
#include <set>
using namespace std;

int main()
{
    int n;
    cin >> n;

    uint64_t ans = 0;
    set<uint64_t> st;
    for(int i = 0;i < n;++i){
        uint64_t t;
        cin >> t;
        if (i != 0){
            uint64_t searching = 0, p_search = 0;
            for(int bit = 31; bit >= 0; --bit){
                bool b = t & (1 << bit); /// бит нового числа
                searching += (1 << bit) * !b; /// например, вероятнее всего самый большой бит = 0, поэтому searching = 1000000...
                ///cout << t << " " << searching << endl;
                if (st.lower_bound(searching) != st.lower_bound(searching + (1 << bit))){
                    /// есть число, подходящее нам

                    /// Ничего и не делаем, ищем его дальше
                }else{
                    /// бит bit останется нулём, жаль :-(
                    searching ^= (1 << bit);
                    /// поэтому бит нужно поменять обратно
                }

            }

            uint64_t neww = searching ^ t;
            ans = max(ans,neww);
        }

        cout << ans << endl;
        st.insert(t);

    }

    ///cout << "Hello world!" << endl;
    return 0;
}

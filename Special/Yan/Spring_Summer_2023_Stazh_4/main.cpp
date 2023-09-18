#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<int> dohod_needed(n);
    vector<int> vishka_needed(n);
    vector<int> parent_bypass(n);

    for(int i = 0; i < n; ++i){
        cin >> dohod_needed[i];
    }

    for(int i = 0; i < n; ++i){
        cin >> vishka_needed[i];
    }

    for(int i = 0; i < n; ++i){
        cin >> parent_bypass[i];
    }



    int Q;
    cin >> Q;

    vector<int> dohod(Q);
    vector<int> vishka(Q);
    vector<int> grazhd(Q);

    for(int i = 0; i < Q; ++i){
        cin >> dohod[i];
    }

    for(int i = 0; i < Q; ++i){
        cin >> vishka[i];
    }

    for(int i = 0; i < Q; ++i){
        cin >> grazhd[i];
    }
    /**
    С рейтингом буду делать так -
    1000 * 1000 * 1000 - index = rating
    */


    set< pair<int,int > > FFA; /// dohod, rating
    set< pair<int,int > > with_vishka; /// dohod, rating

    int last_price_FFA = 1001 * 1001 * 1001;
    int last_price_vishka = 1001 * 1001 * 1001;

    for(int i = 0; i < n; ++i){
        if (!vishka_needed[i]){
            /// добавить этот город в пул для вышки и общий

            if (dohod_needed[i] < last_price_FFA){
                last_price_FFA = dohod_needed[i];
                FFA.insert({dohod_needed[i], i});
            }


        }

        if (dohod_needed[i] < last_price_vishka){
            last_price_vishka = dohod_needed[i];
            with_vishka.insert({dohod_needed[i], i});
        }


    }







    for(int i = 0; i < Q; ++i){
        int city = 1001 * 1001 * 1001;
        if (grazhd[i] != 0){
            if (parent_bypass[ grazhd[i] - 1 ] ){
                city = min(city, grazhd[i] - 1);
            }
        }

        if (vishka[i]){
            /// ...
            auto p = with_vishka.upper_bound({dohod[i], 1001 * 1001 * 1001});
            if (p != with_vishka.begin()){
                --p;
                city = min(city, (*p).second);
            }

        }

        auto p = FFA.upper_bound({dohod[i], 1001 * 1001 * 1001});
        if (p != FFA.begin()){
            --p;
            city = min(city, (*p).second);
        }

        if (city == 1001 * 1001 * 1001){
            cout << "0 ";
        }else{
            cout << city+1 << " ";
        }
    }

    return 0;
}

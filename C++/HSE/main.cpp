#include <iostream>
#include <set>
#include <vector>
#include <cmath>
using namespace std;

/// num
int F(int num){
    ///cout << num << endl;
    int sqrt_ = sqrt(num);

    if (num == 1){
        return 0;
    }

    for(int i = 2;i<=sqrt_;i++){
        if (num % i == 0){
            return F(num/i) + i;
        }
    }

    return num;

}

class num{
public:
    int number;
    int current;
    int carret;
    vector<pair<int,int>> abobus;
    vector<int> deliteli;
    /// cost, delit'

    friend const bool operator<(num that,num second){
        return that.current > second.current;
    }


};

signed main()
{

    ///cout <<F(17*32);
    int n,k;

    multiset<num> ms;
    cin >> n >> k;
    for(int i = 0;i<n;i++){
        int a;
        cin >> a;
        num b;
        b.number = a;
        b.current = a;
        b.carret = 0;

        set<pair<int,int>> divs;

        int sqrt_ = sqrt(a);
        for(int i = 2;i<=sqrt_;i++){
            if (a % i == 0){
                divs.insert(make_pair(F(i),i));
                b.deliteli.push_back(i);
            }
        }

        bool isSqrua = sqrt(a) == (int)(sqrt(a));

        int sz = b.deliteli.size();

        for(int i =sz-1 - isSqrua;i>-1;i--){
            divs.insert(make_pair(F(a/b.deliteli[i]),a/b.deliteli[i] ));

        }

        divs.insert(make_pair(F(a),a));


        int effect = 0;
        for (auto i : divs){
            if (i.second > effect){
                effect = i.second;
                cout << i.first << " " << i.second << endl;
                b.abobus.push_back(i);
            }else{
                cout << "bad " << i.first << " " << i.second << endl;
            }

        }

        ///cout << endl;
        ms.insert(b);

    }




    while(true){
        num first = *(ms.begin());
        ///cout << first.current << " "<< k << endl;
        if (first.current == 1){
            cout << 1 << endl;
            return 0;
        }
        int d = 0;
        if (first.carret != 0){
            d = first.abobus[first.carret - 1].first;
        }
        int c = first.abobus[first.carret].first;
        int cost = c - d;

        ///cout << "cost is " << cost << endl;

        if (cost > k){
            cout << first.current << endl;
            return 0;
        }else{
            k -= cost;
        }

        first.current = first.number / first.abobus[first.carret].second;
        first.carret++;
        ms.erase(ms.begin());
        ms.insert(first);
    }


    ///cout << first.number << endl << second.number;







    return 0;
}

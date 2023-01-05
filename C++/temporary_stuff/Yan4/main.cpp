/**

По сути нужно уметь отвечать на запрос вида "Чему равно сумма стоимостей до n",
тогда очевидно, что g(l,r) = f(r) - f(l), ну или там где-то +- 1, из-за индексации.

Для второго запроса по аналогии, но заполняя в качестве информации продолжительности, а не стоимость

Однако т.к. Start <= 10^9, то тупо сохранить префиксную сумму невозможно, поэтому придётся
сохранять всё в сетах, а потом искать upper или lower баундами
*/

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

#define int long long

using namespace std;

struct d{
    int start, end_, cost;
};

bool start_compare(const d& a, const d& b){
    return a.start < b.start;
}

bool end_compare(const d& a, const d& b){
    return a.end_ < b.end_;
}

///
int finder(const map<int,int>& mp, int bound){
    auto it = (mp.upper_bound(bound));
    it--;
    return (*it).second;

}

signed main()
{
    int n;
    cin >> n;
    vector<d> vc(n);
    for(int i = 0;i < n;++i){
        d temp;
        cin >> temp.start >> temp.end_ >> temp.cost;
        vc[i] = temp;
    }

    map<int,int> start_cost;
    start_cost[0] = 0;

    map<int,int> end_duration;
    end_duration[0] = 0;
    sort(vc.begin(), vc.end(), start_compare );
    int cost_summ = 0;
    for(int i = 0; i < vc.size(); ++i){
        if (i != (vc.size()-1) ){
            if (vc[i].start ==  vc[i+1].start){
                cost_summ += vc[i].cost;
                continue;
            }
        }

        cost_summ += vc[i].cost;
        start_cost[vc[i].start] = cost_summ;
    }

    sort(vc.begin(), vc.end(), end_compare );
    int duration_summ = 0;
    for(int i = 0; i < vc.size(); ++i){
        if (i != (vc.size()-1) ){
            if (vc[i].end_ ==  vc[i+1].end_){
                duration_summ += (vc[i].end_ - vc[i].start);
                continue;
            }
        }

        duration_summ += (vc[i].end_ - vc[i].start);
        end_duration[vc[i].end_] = duration_summ;
    }

    /// prep is done


    int q;

    cin >> q;
    for(int i = 0; i < q; ++i){
        int l,r,t;
        cin >> l >> r >> t;
        if (t == 1){
            /// [l,r] <=> [0;r] - [0;l) <=> [0;r] - [0;l-1]
            cout << finder(start_cost, r) - finder(start_cost, l-1) << " ";
        }else{
            cout << finder(end_duration, r) - finder(end_duration, l-1) << " ";
        }
    }

    return 0;
}

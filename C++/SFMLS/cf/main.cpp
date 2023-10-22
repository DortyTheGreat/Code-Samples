#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
#include <set>

#define int int64_t

using namespace std;
#include <iostream>
#include <algorithm>
using namespace std;


/**

КОНКРЕТНО С ДАННЫМИ ФУНКЦИЯМИ
Несогл. ДО не работает из-за не соблюдения инварианта, читай тут:

https://neerc.ifmo.ru/wiki/index.php?title=%D0%9D%D0%B5%D1%81%D0%BE%D0%B3%D0%BB%D0%B0%D1%81%D0%BE%D0%B2%D0%B0%D0%BD%D0%BD%D1%8B%D0%B5_%D0%BF%D0%BE%D0%B4%D0%B4%D0%B5%D1%80%D0%B5%D0%B2%D1%8C%D1%8F._%D0%A0%D0%B5%D0%B0%D0%BB%D0%B8%D0%B7%D0%B0%D1%86%D0%B8%D1%8F_%D0%BC%D0%B0%D1%81%D1%81%D0%BE%D0%B2%D0%BE%D0%B3%D0%BE_%D0%BE%D0%B1%D0%BD%D0%BE%D0%B2%D0%BB%D0%B5%D0%BD%D0%B8%D1%8F

*/


template<typename T, const T NEUTRAL_UPDATE = 0, const T NEUTRAL_GET = 1001 * 1001 * 1001, const T start_arr_val = 0>
struct DO{


    struct node {
        T value; // минимум в вершине БЕЗ учета отложенной операции
        T delayed; // отложенная операция (сколько нужно прибавить на отрезке)
        node() : value(start_arr_val), delayed(NEUTRAL_UPDATE) {}
    };

    int size;
    node* tree;

    /**

    min -> value
    add -> delayed

    */

    DO(int _size) : size(_size){
        tree = new node[(size+3) * 4];
    }

    ~DO(){
        delete[] tree;
    }

    // 0 - корень, левый сын - v * 2 + 1, правый - v * 2 + 2


    T update_function(T val, T updater){
        return val + updater;
    }

    T get_function(T val1, T val2){
        return min(val1, val2);
    }


    // получает значение в вершине v с учетом отложенной операции
    T get(int v) {
        return update_function(tree[v].value, tree[v].delayed);
    }


    void push(int v) {

        tree[v].value = update_function(tree[v].value, tree[v].delayed);

        tree[v * 2 + 1].delayed = update_function(tree[v * 2 + 1].delayed, tree[v].delayed);
        tree[v * 2 + 2].delayed = update_function(tree[v * 2 + 2].delayed, tree[v].delayed);

        tree[v].delayed = NEUTRAL_UPDATE;
    }

    // Прибавить x на отрезке
    // v - вершина
    // [tl, tr) - отрезок вершины ДО (правая граница не включается)
    // [l, r) - отрезок запроса (правая граница не включается)
    // x - то, что хотим прибавить на отрезке
    void update(int v, int tl, int tr, int l, int r, T x) {
        // вершина дерева вообще не попадает в отрезок запроса, ничего не делаем
        if (r <= tl || tr <= l) return;

        // вершина дерева полностью попадает в отрезок запроса
        if (l <= tl && tr <= r) {
            // скажем, что когда-нибудь потом в этой вершине нужно будет прибавить x
            tree[v].delayed = update_function(tree[v].delayed,x);
            return;
        }

        // если мы попали сюда, значит вершина дерева пересекается с отрезком запроса, и нужно спускаться в детей.
        // но возможно, в текущей вершине есть отложенная операция, которую нужно применить к детям, поэтому вызовем push
        push(v);

        // спускаемся в детей
        int tm = tl + (tr - tl) / 2;
        update(v * 2 + 1, tl, tm, l, r, x);
        update(v * 2 + 2, tm, tr, l, r, x);

        // в нашей вершине точно нет отложенной операции, потому что выше вызвали push, поэтому можно просто
        // пересчитать min из детей. Так как в детях могут быть отложенные операции, то получим значения в них, используя get
        tree[v].value = get_function(get(v * 2 + 1), get(v * 2 + 2));
    }

    // Получить минимум на отрезке
    // v - вершина
    // [tl, tr) - отрезок вершины ДО (правая граница не включается)
    // [l, r) - отрезок запроса (правая граница не включается)
    T get(int v, int tl, int tr, int l, int r) {
        // вершина дерева вообще не попадает в отрезок запроса, ничего не делаем
        if (r <= tl || tr <= l) {
            return NEUTRAL_GET;
        }

        // вершина дерева полностью попадает в отрезок запроса
        if (l <= tl && tr <= r) {
            // вернем минимум с учетом отложенной операции
            return get(v);
        }

        // если мы попали сюда, значит вершина дерева пересекается с отрезком запроса, и нужно спускаться в детей.
        // но возможно, в текущей вершине есть отложенная операция, которую нужно применить к детям, поэтому вызовем push
        push(v);

        // получаем ответы из детей и берем минимум из них
        int tm = tl + (tr - tl) / 2;
        T a = get(v * 2 + 1, tl, tm, l, r);
        T b = get(v * 2 + 2, tm, tr, l, r);


        ///tree[v].value = get_function( get(2*v + 1), get(2*v + 2));

        return get_function(a, b);
    }


    /// [l;r]
    void update(int l, int r, T val){
        update(0,0,size,l,r+1, val);
    }

    /// [l;r]
    T get(int l, int r){
        return get(0,0,size,l,r+1);
    }
};





signed main()
{
    int t;
    cin >> t;
    while(t--){
        int n,m;
        cin >> n >> m;



        vector<int> arr; /// i*2, i*2+1
        arr.resize(n*2);

        for(int i = 0; i < n; ++i){
            int l,r;
            cin >> l >> r;
            arr[i*2] = l;
            arr[i*2 + 1] = r;
        }


        auto b = arr;
        sort(b.begin(), b.end());

        bool empty_front = (b[0] != 1);
        bool empty_end = (b[2*n - 1] != m);


        bool any_empty = empty_end || empty_front;

        map<int, int> mp;


        int cou228 = 1;
        for (int i = 0; i < 2*n; i++) {
            if (i == 0){ mp[b[i]] = 0;}else{
                if (b[i-1] != b[i]){
                    mp[b[i]] = cou228;
                    cou228++;
                }
            }

        }
        for (int i = 0; i < 2*n; i++) {
            arr[i] = mp[arr[i]];
        }


        multiset<pair<int, int > > otkr;
        multiset<pair<int, int > > zakr;

        ///cout << "228: " << cou228 << endl;
        int st_sz = cou228;
        DO<int> my_do(st_sz);


        for(int i = 0; i < n; ++i){
            otkr.insert( {arr[i*2], arr[i*2 + 1]} ); /// l
            zakr.insert( {arr[i*2 + 1], arr[i*2]} ); /// r
        }

        auto o_it = otkr.begin();
        auto z_it = zakr.begin();

        int max_ = 0;
        int ans_ = 0;

        for(int pos = 0; pos <= st_sz; ++pos){

            while(o_it != otkr.end()){
                if ((*o_it).first <= pos){
                    /// add *o_it to DO
                    my_do.update((*o_it).first, (*o_it).second, 1);

                    ///cout << "+1: " << (*o_it).first << " " << (*o_it).second+1 <<endl;
                    max_ += 1;
                    ++o_it;
                }else{
                    break;
                }
            }

            while(z_it != zakr.end()){
                if ((*z_it).first < pos){
                    /// sub *z_it to DO
                    my_do.update((*z_it).second, (*z_it).first, -1);
                    ///cout << "-1: " << (*z_it).first << " " << (*z_it).second+1 <<endl;
                    max_ -= 1;
                    ++z_it;
                }else{
                    break;
                }
            }

            int min_ = any_empty ? 0 : my_do.get(0,st_sz-1);


            ans_ = max(ans_, max_ - min_);

        }

        cout << ans_ << endl;
    }

    return 0;
}

#include <iostream>
#include <vector>
#include <set>

using namespace std;



#define all(a) (a).begin(), (a).end()
#define ll long long


const int maxn = 1e5;
vector<int> factor[maxn];

const ll mod = 1000000007;

ll del = 1;
ll ans = 1;

const int maxa = 1e7;
int state[maxa];

ll binpow(ll a, int n) {
    ll res = 1;
    while (n != 0) {
        if (n & 1)
            res = res * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return res;
}

inline ll inv(ll x) {
    return binpow(x, mod - 2);
}



/// Структура Очереди. Нужна для сортировки запросов на подотрезках.
struct Query {
    int l, r, id;

    Query() {}

    Query(int _l, int _r, int _id) {
        l = _l;
        r = _r;
        id = _id;
    }

};


/// O((q+n) * sqrt(n))
class AlgMo{
public:

    int n;
    int q;
    vector<int> answers;


    multiset<Query> Queries;

    int l = 0, r = 0;
    void add_right();
    void add_left();

    void del_left();
    void del_right();

    void init(int n_, int q_){
        n = n_;
        q = q_;
        answers.resize(q);
    }

    friend istream& operator>> (std::istream &in, AlgMo &alga)
    {
        for (int i = 0; i < alga.q; ++i) {
            int lq, rq;
            in >> lq >> rq;
            lq--;
            alga.Queries.insert( Query(lq, rq, i));
        }
        return in;
    }


    friend ostream& operator<< (std::ostream &out, const AlgMo &alga)
    {
        for (int i = 0; i < alga.q; ++i) {
            out << alga.answers[i] << '\n';
        }

        return out;
    }




    int get_answer();

    void process_query(){
        for (Query query : Queries) {
            while (r < query.r)
                add_right();
            while (r > query.r)
                del_right();
            while (l < query.l)
                del_left();
            while (l > query.l)
                add_left();
            answers[query.id] = get_answer();
        }
    }

};






void AlgMo::add_right() {
    for (int i : factor[r]) {
        del *= state[i];
        del %= mod;
        state[i] += 1;
        ans *= state[i];
        ans %= mod;
    }
    r += 1;
}

void AlgMo::del_right() {
    r -= 1;
    for (int i : factor[r]) {
        del *= state[i];
        del %= mod;
        state[i] -= 1;
        ans *= state[i];
        ans %= mod;
    }
}

void AlgMo::add_left() {
    l -= 1;
    for (int i : factor[l]) {
        del *= state[i];
        del %= mod;
        state[i] += 1;
        ans *= state[i];
        ans %= mod;
    }
}

void AlgMo::del_left() {
    for (int i : factor[l]) {
        del *= state[i];
        del %= mod;
        state[i] -= 1;
        ans *= state[i];
        ans %= mod;
    }
    l += 1;
}

int AlgMo::get_answer(){
        return ans * inv(del) % mod;
    }

void solve() {
    fill(state, state + maxa, 1);
    int n,q;
    cin >> n >> q;

    AlgMo am;
    am.init(n,q);

    int num;
    for (int i = 0; i < n; ++i) {
        cin >> num;
        for (int j = 2; j * j <= num; ++j) {
            while (num % j == 0) {
                factor[i].push_back(j);
                num /= j;
            }
        }
        if (num != 1)
            factor[i].push_back(num);
    }

    cin >> am;
    am.process_query();
    cout << am;





}

signed main() {
    solve();
}

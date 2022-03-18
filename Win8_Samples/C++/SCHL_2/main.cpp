#include <iostream>
#include <set>
#include <vector>

#include <algorithm>

using namespace std;

const int SIZE_ = 10000;

long long  MASK_S[SIZE_];
long long  MASK_E[SIZE_];

void Mqsort(long long * A, long long  L, long long  R, long long * MASK){
if(R - L <= 1) return;
long long  mid = A[L + rand() % (R - L)];
long long  x = L, y = L;
for(long long  i = L; i < R; ++i){
    if (A[i] < mid){
    swap(A[x], A[i]);swap(MASK[x], MASK[i]);
    if (x != y){ swap(A[y], A[i]);swap(MASK[y], MASK[i]);}
    ++x; ++y;
} else if (A[i] == mid) {
swap(A[y], A[i]);swap(MASK[y], MASK[i]);
++y;
}
}
Mqsort(A, L, x, MASK);
Mqsort(A, y, R, MASK);
}

void qsort(long long* A, long long L, long long R){
if(R - L <= 1) return;
long long mid = A[L + rand() % (R - L)];
long long x = L, y = L;
for(long long i = L; i < R; ++i){
    if (A[i] < mid){
    swap(A[x], A[i]);
    if (x != y){ swap(A[y], A[i]);}
    ++x; ++y;
} else if (A[i] == mid) {
swap(A[y], A[i]);
++y;
}
}
qsort(A, L, x);
qsort(A, y, R);
}

struct Event {
    int x;
    int type;
    int id;
    bool operator<(const Event other) const {
        if (x != other.x)
            return x < other.x;
        if (type != other.type)
            return type < other.type;
        return id < other.id;
    }
};

void solve() {
    int n;
    cin >> n;
    vector<Event> a;
    for (int i = 0; i < n; ++i) {
        int st, fi;
        cin >> st >> fi;
        Event tmp;
        tmp.x = st;
        tmp.type = 1; // открытие
        tmp.id = i;
        a.push_back(tmp);
        tmp.x = fi;
        tmp.type = -1;  // закрытие
        tmp.id = i;
        a.push_back(tmp);
    }
    sort(a.begin(), a.end());
    int prev_st;
    int prev_id;
    int prev_prev_id;
    int ans_l = -1;
    int ans_r;
    int k = 0;
    int minn = 1e10;
    for (Event e : a) {
        if (e.type == 1) {
            prev_st = e.x;
            prev_prev_id = prev_id;
            prev_id = e.id;
            k += 1;
            continue;
        }
        if (k > 1) {
            int diff = e.x - prev_st;
            if (diff <= minn) {
                minn = diff;
                if (prev_id != e.id)
                    ans_l = prev_id;
                else
                    ans_l = prev_prev_id;
                ans_r = e.id;
            }
        }
        k -= 1;
    }
    if (ans_l == -1) {
        cout << "0\n";
        return;
    }
    if (ans_l > ans_r)
        swap(ans_l, ans_r);
    cout << ans_l + 1 << " " << ans_r + 1 << '\n';
}

long long S[1000], E[1000];

long long diff(int start_, int end_){
return min(E[end_],E[start_]) - max(S[end_],S[start_]);
}

signed main()
{
    int n;

    cin >> n;

    for(int i = 0;i < n;i++){
        cin >> S[i] >> E[i];
    }

    cout << diff(606-1,820-1);

    cout << endl <<diff(529-1,606-1);

    cout << endl <<diff(496-1,643-1);
}

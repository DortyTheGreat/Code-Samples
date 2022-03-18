#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <utility>
#include <vector>

using namespace std;

const int pseudo_inf  = 1000000;

const int size_ = 10000;
/// + qsort
void qsort(long long* A, long long L, long long R){
    if(R - L <= 1) return;
    long long mid = A[L + rand() % (R - L)];
    long long x = L, y = L;
    for(long long i = L; i < R; ++i){
        if (A[i] > mid){
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

int secret_num = 1337;

int main() {

    int m, n;

    cin >> m >> n;
    int Data[size_];

    int D[size_];
    int req[size_];


    for(int i =0;i<m+1;i++){
        D[i] = pseudo_inf;
        req[i] = 0;
    }


    req[0] = -1 * secret_num;
    D[0] = 1;

    for (int i = 0; i < n; i++) {
        cin >> Data[i];
    }

    for (int i = 0; i < n; i++) {
        for (int j = m; j > -1; j--) {

            if ((Data[i] + j) > m ){
                continue;
            }
            if (D[j] == pseudo_inf){
                continue;
            }
            if (D[j + Data[i]] > D[j] + 1) {
                D[j + Data[i]] = D[j] + 1;
                req[j + Data[i]] = j;
            }
        }
    }

    long long anses[size_];int h = 0;

    if (D[m] != pseudo_inf ) {

        int find_ = req[m];
        int s = 0;

        while (find_ != (-1 * secret_num)) {
            s = s + find_ - req[find_];

            anses[h] = find_ - req[find_]; h++;

            find_ = req[find_];
        }


        h--;

        anses[h] = m - s + secret_num;h++;

        qsort(anses,0,h);

        cout << h << endl;
        for (int i =0;i<h;i++) {
            //cout << i << " : " << req[i] << endl;

            cout << anses[i] << endl;
        }



    }else {

        cout << "NO";

    }
}

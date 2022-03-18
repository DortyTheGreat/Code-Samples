#include <iostream>

using namespace std;

void qsort(long long * A, long long  L, long long  R){
if(R - L <= 1) return;
long long  mid = A[L + rand() % (R - L)];
long long  x = L, y = L;
for(long long  i = L; i < R; ++i){
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

int main()
{
    long long n;
    long long DATA[10000];
    cin >> n;
    for(int i =0;i<n;i++){
        cin >> DATA[i];
    }

    qsort(DATA, 0, n);
}

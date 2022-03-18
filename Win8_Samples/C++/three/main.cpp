#include <iostream>

using namespace std;

#define int long long

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
bool in_range(int arg){
if (arg == 0){return false;}
if (arg == -1){return false;}
return true;
}
signed main()
{
    int t;
    cin >> t;

    for(int i =0;i<t;i++){
        int n;
        cin >> n;
        int arr1[103];
        int arr2[103];
        for(int j =0;j<n;j++){
            cin >> arr1[j];
        }

        for(int j =0;j<n;j++){
            cin >> arr2[j];
        }

        qsort(arr1,0,n);
        qsort(arr2,0,n);

        int flag = 1;
        for(int j =0;j<n;j++){
            if (in_range(arr1[j] - arr2[j])){
                flag = 0;
            }
        }

        if (flag){
            cout << "YES" << endl;
        }else{
            cout << "NO" << endl;
        }
    }

    return 0;
}

#include <cmath>
#include <algorithm>
#include <iostream>

using namespace std;

void qsort(int* A, int* S, int L, int R) {
    if (R - L <= 1) return;
    int mid = S[L + rand() % (R - L)];
    int x = L, y = L;
    for (int i = L; i < R; i++)
        if (S[i] < mid) {
            swap(A[x], A[i]);
            if (x != y) { swap(A[y], A[i]); }
            x++; y++;
        }
        else if (S[i] == mid) {
            swap(A[y], A[i]);
            y++;
        }
    qsort(A, S, L, x);
    qsort(A, S, y, R);
}

int a[1001];
int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }


    int count = 0;
    for (int i = 0; i < n - 1; i++) {
        bool tr = false;
        for (int j = n - 1; j >= i + 1; j--) {
            if (a[j] < a[j - 1]) {
                tr = true;
                swap(a[j], a[j - 1]);
            }
        }
        if (!tr) {
            if (count == 0)
                for (int j = 0; j < n; j++)
                    cout << a[j] << " ";
            return 0;
        }
        for (int j = 0; j < n; j++)
            cout << a[j] << " ";
        cout << "\n";
        count++;
    }



  //  for (int i = n - 1; i >= 0; i--) {
  //     cout << a[i] << " ";
 //  }
}

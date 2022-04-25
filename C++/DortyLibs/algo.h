#include <algorithm>


template <typename T>
vector<T> NOP(vector<T> A, vector<T> B){

     int n = A.size();
     int m = B.size();

    vector<vector<T> > F(n + 1, vector<T>(m + 1));

     for (int i =1;i<=n;i++){
        for (int j =1;j<=m;j++){
            if (A[i-1] == B[j-1]){
                F[i][j] = F[i - 1][j - 1] + 1;
            }else{
                F[i][j] = max(F[i - 1][j], F[i][j - 1]);
            }
        }
     }


     vector<T> Ans;
     int i = n;
     int j = m;
     while (i > 0 && j > 0){
        if (A[i - 1] == B[j - 1]){
            Ans.push_back(A[i - 1]);
            i -= 1;
            j -= 1;
        }else{
        if (F[i - 1][j] == F[i][j]){
            i--;

        }else{
            j--;
        }
        }
     }
     reverse(Ans.begin(),Ans.end());

    return Ans;
}



vector<long long> vector_generator(int n, int a1, int k, int b, int m){
    vector<long long> ret(n);
    ret[0] = a1;

    for(int i = 1;i<n;++i){
        ret[i] = (k*ret[i-1] + b) % m;
    }
    return ret;
}



/**
Можно быстрее за O(N * log(log(N))) или O(N * log(log(k)))
... https://neerc.ifmo.ru/wiki/index.php?title=%D0%91%D1%8B%D1%81%D1%82%D1%80%D1%8B%D0%B9_%D0%BF%D0%BE%D0%B8%D1%81%D0%BA_%D0%BD%D0%B0%D0%B8%D0%B1%D0%BE%D0%BB%D1%8C%D1%88%D0%B5%D0%B9_%D0%B2%D0%BE%D0%B7%D1%80%D0%B0%D1%81%D1%82%D0%B0%D1%8E%D1%89%D0%B5%D0%B9_%D0%BF%D0%BE%D0%B4%D0%BF%D0%BE%D1%81%D0%BB%D0%B5%D0%B4%D0%BE%D0%B2%D0%B0%D1%82%D0%B5%D0%BB%D1%8C%D0%BD%D0%BE%D1%81%D1%82%D0%B8

Текущий алгоритм с бин поиском.
O(N * log(N))

from wiki https://ru.wikipedia.org/wiki/%D0%97%D0%B0%D0%B4%D0%B0%D1%87%D0%B0_%D0%BF%D0%BE%D0%B8%D1%81%D0%BA%D0%B0_%D0%BD%D0%B0%D0%B8%D0%B1%D0%BE%D0%BB%D1%8C%D1%88%D0%B5%D0%B9_%D1%83%D0%B2%D0%B5%D0%BB%D0%B8%D1%87%D0%B8%D0%B2%D0%B0%D1%8E%D1%89%D0%B5%D0%B9%D1%81%D1%8F_%D0%BF%D0%BE%D0%B4%D0%BF%D0%BE%D1%81%D0%BB%D0%B5%D0%B4%D0%BE%D0%B2%D0%B0%D1%82%D0%B5%D0%BB%D1%8C%D0%BD%D0%BE%D1%81%D1%82%D0%B8

**/
template <typename T>
vector<T> NVP(vector<T> A){

    int N = A.size();

    /*
    int n = A.size();

    vector<int> d;
    d.resize(n+1);
    d[0] = -100000;
    for (int i=1; i<=n; ++i)
        d[i] = 1000000;

    for (int i=0; i<n; i++) {
        int j = int (upper_bound (d.begin(), d.end(), A[i]) - d.begin());
        if (d[j-1] < A[i] && A[i] < d[j])
            d[j] = A[i];
    }

    return d;
    */


    vector<T> P(N);
    vector<T> M(N + 1);
    int L = 0;
    for (int i=0; i< N;i++){
      int lo = 1;
      int hi = L;
      while (lo <= hi){
        int mid = ((lo+hi + 1)/2);
        if (A[M[mid]] < A[i]){
          lo = mid+1;
        }else{
          hi = mid-1;
        }
      }
      int newL = lo;
      P[i] = M[newL-1];
      M[newL] = i;
      if (newL > L){
        L = newL;
      }
    }
    vector<T> S(L);
    int k = M[L];
    for (int i= L-1;i>-1;i--){
      S[i] = A[k];
      k = P[k];
    }
    return S;

}




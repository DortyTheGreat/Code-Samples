#include <iostream>
#include <sstream>

using namespace std;

template <typename T>
  std::string NumberToString ( T Number )
  {
     std::ostringstream ss;
     ss << Number;
     return ss.str();
  }

string fillSpaces(string str, int spaces){
    while(str.size() != (spaces)){
            str += " ";
        }
        return str;
}

void qsort(int* A, int L, int R){
    if(R - L <= 1) return;
    int mid = A[L + rand() % (R - L)];
    int x = L, y = L;
    for(int i = L; i < R; ++i){
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

    int n,m; int ans=0;
    cin >> n >> m;
    int M[1000];
    int C[1000];

    for(int i=0;i<n;i++){
        cin >> M[i];
    }

    for(int i=0;i<n;i++){
        cin >> C[i];
    }

    int D[10000];
    string D_STR[10000];



    D[0] = 0;
    for(int i = 1;i <=m;++i){
        D[i] = -100000;
        D_STR[i] = "";
    }
    int index_ = 0; int maxi=0;
    for(int i = 0;i < n; ++i){
        for(int j = m - M[i]; j >= 0; --j){

                if(D[j + M[i]] > D[j] + C[i] ){

                }else{

                D[j + M[i]] = D[j] + C[i];

                D_STR[j + M[i]] = D_STR[j] +NumberToString(i+1) + " ";

                if(maxi < D[j + M[i]]){
                    maxi =  D[j + M[i]];
                    index_ = j;
                }

                }
            //D[j + M[i]] = max(D[j + M[i]], D[j] + C[i]);

        }
    }


    //cout << endl;
    int NewMax=-10; int NewIndex=-10;
    for(int i =0;i<=m;i++){
        if(NewMax < D[i]){
            NewMax = D[i];
            NewIndex = i;
        }
    }

    int To_Sort[100];int h=0;

    string carret = "";

    for(int i=0;i<D_STR[NewIndex].size();i++){


        if (D_STR[NewIndex][i] == ' '){
            To_Sort[h] = atoi(carret.c_str());h++;
            //cout << D_STR[NewIndex][i];

            carret = "";
        }else{
            carret+= D_STR[NewIndex][i];

        }
    }

    qsort(To_Sort,0,h);

    for(int i =0;i<h;i++){
        cout << To_Sort[i] << endl;
    }



    //cout << endl << NewIndex;
}

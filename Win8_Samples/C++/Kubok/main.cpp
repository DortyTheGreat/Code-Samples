#include <iostream>
#include <set>
#include <cmath>
#include <vector>

using namespace std;

bool IsPrime(int a){
    if(a < 2){return 0;}
    if(sqrt(a) == int(sqrt(a))){return 0;}
    for(int i=2;i<sqrt(a);i++){
        if(a%i == 0){return 0;}
    }
    return 1;
}

void PRINT(vector<int> CUT, vector<int> A, int n){

cout << A.size() << endl;

for(int i =0;i<n;i++){
    int flag = 1;
    for(int j =0;j<CUT.size();j++){
        if (i == CUT[j]){
            flag = 0;
        }
    }
    if (flag){
        cout << i+1 <<  " ";
    }
}
cout << endl;
}

int main()
{
    int n,m;
    cin >> n >> m;

    int ** Field;
    int ** FieldDin;

    Field = new int* [n];

        for(int i =0;i<n;i++){
            Field[i] = new int[m];
        }

        for(int i =0;i<n;i++){

            for(int j =0;j<m;j++){
                Field[i][j] = 0;
            }
        }

    FieldDin = new int* [n];

        for(int i =0;i<n;i++){
            FieldDin[i] = new int[m];
        }

        for(int i =0;i<n;i++){

            for(int j =0;j<m;j++){
                FieldDin[i][j] = 0;
            }
        }

    for(int i =0;i<n;i++){
        for(int j = 0;j<m;j++){
            char r;
            cin >> r;
            if (r == '.'){
                Field[i][j] = 1;
            }else{
                Field[i][j] = 0;
            }
        }
    }



    for(int i =0;i<n;i++){
        for(int j = 0;j<m;j++){
            if ((i == 0) || (j == 0)){
                FieldDin[i][j] = Field[i][j];
            }else{
            if (Field[i][j] == 0){FieldDin[i][j] = 0;}else{

                int value = FieldDin[i-1][j];

                FieldDin[i][j] = value;

                if (FieldDin[i][j-1] > FieldDin[i][j]){
                    FieldDin[i][j] = Field[i][j-1];
                }

            }
            }
        }
    }

    for(int i =0;i<n;i++){
        for(int j = 0;j<m;j++){
            cout << Field[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    for(int i =0;i<n;i++){
        for(int j = 0;j<m;j++){
            cout << FieldDin[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;



    //cout << endl;

    const int MU = 10000;
    int PASSES[MU];

    for(int j =0;j<m;j++){
        int isOK = 1;
        for(int i = 0;i<n;i++){
            if (Field[i][j] == 1 && FieldDin[i][j] == 0){
                isOK = 0;
            }
        }
        PASSES[j] = isOK;
    }


    cout << endl;

    int SUMMI[MU];
    SUMMI[0] = PASSES[0];

    for(int i =1;i<m;i++){
        SUMMI[i] = SUMMI[i-1] + PASSES[i];
        cout << SUMMI[i] << " ";
    }



    int f;
    cin >> f;


    for(int i =0;i<f;i++){
        int a,b;
        cin >> a >> b;
        if (SUMMI[b-1] - SUMMI[a-1] != (b-a)){
            cout << "NO";
        }else{
            cout << "YES";
        }
    }


}

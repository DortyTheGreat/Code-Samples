#include <iostream>

using namespace std;

int main()
{
    int n,m;
    long long D[16][16],NEW[16][16];

    int a,b,c,d;

    cin >> n >> m;

    cin >> a >> b >> c >> d;

    int k;

    cin >> k;

    for(int i =0;i<16;i++){
        for(int j=0;j<16;j++){
            D[i][j] =0;
        }
    }

    D[a-1][b-1] = 1;

    for(int TIMES = 0;TIMES<k;TIMES++){
            cout << endl;

        for(int i =0;i<16;i++){
            for(int j=0;j<16;j++){
                NEW[i][j] =0;
            }
        }

        for(int i =0;i<n;i++){
            for(int j=0;j<m;j++){

                int n_i,n_j;
                n_i = i;
                n_j = j+1;
                if (n_i >= 0 && n_i < n && n_j >= 0 && n_j < m){NEW[n_i][n_j] += D[i][j];}

                n_i = i;
                n_j = j-1;
                if (n_i >= 0 && n_i < n && n_j >= 0 && n_j < m){NEW[n_i][n_j] += D[i][j];}

                n_i = i-1;
                n_j = j;
                if (n_i >= 0 && n_i < n && n_j >= 0 && n_j < m){NEW[n_i][n_j] += D[i][j];}

                n_i = i+1;
                n_j = j;
                if (n_i >= 0 && n_i < n && n_j >=  0 && n_j < m){NEW[n_i][n_j] += D[i][j];}

                //cout << D[i][j] << " ";

            }
            //cout << endl;
        }



        for(int i =0;i<16;i++){
            for(int j=0;j<16;j++){
                D[i][j] =NEW[i][j];
            }
        }


    }



    cout << D[c-1][d-1];

    for(int i =0;i<16;i++){
            for(int j=0;j<16;j++){
                //cout << i <<" : " << j << " : " << D[i][j] << endl;
            }
        }


}

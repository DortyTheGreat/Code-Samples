#include <iostream>

using namespace std;

const int size_ = 1000;

int main()
{
    int H[size_][size_];

    int W[size_][size_];

    int SQ[size_][size_];

    char STD[size_][size_];

    int ans = 0;

    int n,m;
    cin >> n >> m;

    for(int i =0;i<n;i++){
        for(int j =0;j<m;j++){
            char temp;
            cin >> temp;
            STD[i][j] = temp - '0';
        }
    }

    H[0][0] = STD[0][0];
    W[0][0] = STD[0][0];


    for(int i =0;i<n;i++){
        W[i][0] = STD[i][0];

        SQ[i][0] = STD[i][0];
    }

    for(int i =0;i<m;i++){
        H[0][i] = STD[0][i];

        SQ[0][i] = STD[0][i];
    }

    for(int i =1;i<n;i++){
        if (STD[i][0] == 0){
            H[i][0] = 0;
        }else{
            H[i][0] = 1 + H[i-1][0];
        }
    }

    for(int i =1;i<m;i++){
        if (STD[0][i] == 0){
            W[0][i] = 0;
        }else{
            W[0][i] = 1 + W[0][i-1];
        }
    }

    for(int i =1;i<n;i++){
        for(int j =1;j<m;j++){
            if (STD[i][j] == 0){
                H[i][j] = 0;
                W[i][j] = 0;
            }else{
                H[i][j] = 1 + H[i-1][j];
                W[i][j] = 1 + W[i][j-1];

            }
        }

    }


    for(int i =1;i<n;i++){
        for(int j =1;j<m;j++){
            if (STD[i][j] == 0){
                SQ[i][j] = 0;
            }else{
                int H_ = min(SQ[i-1][j-1],H[i-1][j]);
                int W_ = min(SQ[i-1][j-1],W[i][j-1]);
                SQ[i][j] = min(H_,W_) + 1;

            }
        }

    }

    for(int i =0;i<n;i++){
        for(int j =0;j<m;j++){
            //cout << W[i][j] << " ";
        }
       // cout << endl;
    }

    //cout << endl;

    for(int i =0;i<n;i++){
        for(int j =0;j<m;j++){
        //    cout << H[i][j] << " ";
        }
        //cout << endl;
    }
    //cout << endl;

    for(int i =0;i<n;i++){
        for(int j =0;j<m;j++){
            //cout << SQ[i][j] << " ";
            if (ans < SQ[i][j]){
                ans = SQ[i][j];
            }
        }
        //cout << endl;
    }

    cout << ans;

}

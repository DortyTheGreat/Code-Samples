



#include <iostream>
using namespace std;

int main()
{
    string strings[10];
    int D[10000];

    int n;
    cin >> n;
    for(int i =0;i<n;i++){
        cin >> strings[i];
    }

    for(int i =0;i<n;i++){
        D[i] = 1;
    }

    for(int i =0;i<n;i++){
        for(int j =0;j<i;j++){
            if (orig[i] % orig[j] == 0){
                D[i] = max(D[i],D[j]+1);
            }
        }
    }

    int maxi_bon=-1;

    for(int i =0;i<h;i++){
        if (maxi_bon < D[i]){
            maxi_bon = D[i];
        }
    }
    cout << maxi_bon;
}

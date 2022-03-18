#include <iostream>

using namespace std;

int Data[500][500];

void f(int x,int y,int counter,int n,int m){
if( (x<n)&&(y<m)&&(x>=0)&&(y>=0) ){
    Data[x][y] = (Data[x][y] + counter) % 1000007;
    f(x+2,y-1,counter,n,m);
    f(x-1,y+2,counter,n,m);

    f(x+2,y+1,counter,n,m);
    f(x+1,y+2,counter,n,m);

}
}

int main()
{
    int n,m;
    cin >> n >> m;

    for(int i =0;i<500;i++){
        for(int j=0;j<500;j++){
            Data[i][j] = 0;
        }
    }
    f(0,0,1,n,m);
    //1000007
    cout << Data[n-1][m-1];
//cout << endl << Data[1][2];
}

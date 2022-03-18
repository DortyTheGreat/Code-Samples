#include <iostream>
#include <vector>



using namespace std;

char s[108][108];

int empty, res, n, m, a, b, i, j, c;
vector<vector<int> > g;
vector<int> mt, used, par;

double PI(int n){
double inside=0;
double total =0;
for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
            toatl++;
        if( i*i + j*j <= (n)*(n) ){
            inside++;
        }
    }
}

/// inside = PI * n
///outside = 4 * n
return inside/total * 4;
}
int main(void)
{
    cout << PI(1000);
}

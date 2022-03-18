#include <iostream>

using namespace std;

long long f(long long arg){ // Fenvivh's function
return arg & (arg+1);
}

// fill F[arg] as summ of a[f(arg)] to a[arg] ;



///

long long F[1050][1050];

long long n;


long long query(long long x, long long y){ // summ of [0,0] -> [x,y]
long long sum = 0;
for (long long i =x;i >= 0; i = f(i) - 1){
for (long long j =y; j>= 0; j = f(j) - 1){
sum+= F[i][j];
}
}
return sum;

}


void update(long long x, long long y, long long delta){ // To a[x][y] add {delta} (a[x][y]+=delta, F will change    )
for(long long i = x; i< n; i |= (i+1)){
for(long long j = y; j< n; j |= (j+1)){
F[i][j]+= delta;
}
}

}

long long FullQuery(long long x1, long long y1, long long x2, long long y2){
return query(x2,y2) - query(x1-1,y2) - query(x2,y1-1) + query(x1-1, y1-1);
}


// summ of [x1,y1] - [x2,y2] = query(x2,y2) - query(x1-1,y2) - query(x2,y1-1) + query(x1-1, y1-1);


int main(){

    for(long long i=0;i<1050;i++){
        for(long long j=0;j<1050;j++){
            F[i][j] = 0;
        }
    }


    cin >> n;
    long long k;
    cin >> k;

    for(long long i =0;i<k;i++){

    string cmd;
    cin >> cmd;

    if(cmd == "ADD"){int X,Y; cin >> X >> Y;F[X][Y]++;}
    if(cmd == "GET"){long long X1,X2,Y1,Y2; cin >> X1 >> Y1 >> X2 >> Y2;
    int cou = 0;
    for(int i=X1;i<=X2;i++){
        for(int j=Y1;j<=Y2;j++){
            cou += F[i][j];
        }
    }
    cout << cou << endl;
    }
    }





}

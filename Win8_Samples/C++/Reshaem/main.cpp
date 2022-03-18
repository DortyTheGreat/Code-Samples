#include <iostream>

using namespace std;

long long Data[10000];



class Human{
public:
    int a,b,c;

};

Human hums[10000];

long long solve(long long proc, long long Number){



if (Data[proc] != 0){
    return Data[proc];
}

if (proc > Number){
    return Data[Number];
}

if (proc < 0){
    return 1000000;
}





    Data[proc] = min(min(hums[proc].c + solve(proc+3,Number),hums[proc].b + solve(proc+2,Number)),hums[proc].a + solve(proc+1,Number));


return Data[proc];
}

int main()
{

    int n;
    cin >> n;

    for(int i =0;i<10000;i++){
        Data[i] = 0;
    }

    for(long long i =0;i<n;i++){
            cin >> hums[i].a >> hums[i].b >> hums[i].c;
    }




    cout << solve(0,n) << endl;

    //cout << Data[1] << endl;

    for(int i =0;i<n+3;i++){
        //cout << Data[i] << " ";
    }

    //for(long long i =0;i<str.size();i++){
    //    if (str[i] <= '2'){
    //        Data[i] = Data[i] + Data[i-1]
    //    }
    //}
}

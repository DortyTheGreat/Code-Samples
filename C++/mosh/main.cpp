#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");


    int t;
    fin >> t;
    while(t--){

    int arr[10] =        {0,0,0,0,0,0,0,0,0,0};
    int masks[10] = {4,5,2,3,3,1,5,4,1,2};

    int n;
    fin >> n;

    int mult = 1;

    while(n !=0){

        int digit = n%10;

        /// обработка самого числа
        for(int i=0;i<digit;i++){
            arr[i] += 1;
        }

        int M2 = mult/10;



        for(int i = 0;i<10;i++){
            arr[i] += digit*M2;
        }


        mult =mult*10 + 1;
        n /=10;

    }

    int ans = 0;

    for(int i = 0;i<10;i++){
        ans += arr[i] * masks[i];
    }


    f << ans << endl;
    }
}

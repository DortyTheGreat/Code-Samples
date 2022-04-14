
#include <iostream>
#include <cmath>
using namespace std;

#include "../DortyLibs/BigIntLib.h"

#include "../DortyLibs/DortyBuild.h"
#include <fstream>



int main()
{
    cout << std::sqrt(1) << endl;
    cout << BigInt(5) <<" " <<BigInt(12345);
    AppBuild();
    ifstream fin("input.txt");
	ofstream fout("output.txt");

    BigInt b;
    //cin >> b;
    //cout << "SQRT : " << sqrt(b) << endl;
    cout << "here" << endl;
    for(int test = 0;test < 1000000; test++){
        cout << "here" << endl;
        BigInt a(test);
        cout << "here" << endl;
        cout << sqrt(2) << endl;
        sqrt(a);
        cout << "here" << endl;
        cout << sqrt(2) << endl;
        cout << (long long)(sqrt(test)) << endl;
        cout << BigInt(intSqrt(test)) << endl;
        if (sqrt(a) != BigInt(intSqrt(test))){
            cout << test << " " << sqrt(a) << " " << test << " " << intSqrt(test) <<endl;
        }
    }



	BigInt n1;
	cin >> n1;



  BigInt ans = sqrt(n1);
  cout << "CALCULATED" << endl;
  cout << ans << endl << n1 - ans * ans;

  return 0;
}




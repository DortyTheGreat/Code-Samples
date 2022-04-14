
#include <iostream>

#include "../DortyLibs/BigIntLib.h"

#include "../DortyLibs/DortyBuild.h"
#include <fstream>

using namespace std;

int main()
{

    cout << BigInt(5) <<" " <<BigInt(12345);
    AppBuild();
    ifstream fin("input.txt");
	ofstream fout("output.txt");

    BigInt b;
    cin >> b;
    cout << "SQRT : " << sqrt(b) << endl;

    for(int test = 0;test < 1000000; test++){
        BigInt a(test);

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




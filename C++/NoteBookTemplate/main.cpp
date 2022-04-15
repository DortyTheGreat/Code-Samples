


#include <iostream>
#include <cmath>
using namespace std;

#include "../DortyLibs/BigIntLib.h"

#include "../DortyLibs/DortyBuild.h"
#include <fstream>

#include "../enviroment.h"

int main()
{

    stringstream ss;
    ss << "123 22";


    ///std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
    cin.rdbuf(ss.rdbuf());
    AppBuild();
    int a;
    cout << "here" << endl;
    cin >> a;
    cout << "cinned" << endl;
    cout << factorial(a) << endl;



    //ifstream fin("input.txt");
	//ofstream fout("output.txt");
    return 0;

    //BigInt a(-13);

    //a -= BigInt(-15);

    //cout << a << endl;
    //int b;
    //cin >> b;



    //for(int test = 0;test < 100000; test++){

        //BigInt a(test);
        //if (test % 10000 == 0){cout << "test : " << test << endl;}
        //if (sqrt(a) != BigInt(intSqrt(test))){
        //    cout << test << " " << sqrt(a) << " " << test << " " << intSqrt(test) <<endl;
        //}
    //}



	//BigInt n1;
	//fin >> n1;



  //BigInt ans = sqrt(n1);
  //cout << "CALCULATED" << endl;
  //fout << ans << endl << n1 - ans * ans;

  //1return 0;
}




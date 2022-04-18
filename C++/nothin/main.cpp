
#include <iostream>
#include <cmath>
using namespace std;

#include "../DortyLibs/BigIntLib.h"

#include "../DortyLibs/DortyBuild.h"
#include <fstream>



int main()
{

    ifstream fin("input.txt");
	ofstream fout("output.txt");
    AppBuild();
    BigInt a(138384);
    ///fin >> a;


    /*
    for(int i = 0;i < 100;++i){
        sqrt(a);
    }
    */
    cout << algoSqrt(a) << endl;




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




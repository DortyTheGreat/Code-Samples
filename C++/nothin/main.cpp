
#include <iostream>

#include "../DortyLibs/BigIntLib.h"

#include "../DortyLibs/DortyBuild.h"
#include <fstream>

using namespace std;

int main()
{


    AppBuild();
    ifstream fin("input.txt");
	ofstream fout("output.txt");




	BigInt n1;
	fin >> n1;



  BigInt ans = sqrt(n1);
  cout << "CALCULATED" << endl;
  fout << ans << endl << n1 - ans * ans;

  return 0;
}




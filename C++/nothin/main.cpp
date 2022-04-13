
#include <iostream>

#include "../DortyLibs/BigIntLib.h"

#include "../DortyLibs/DortyBuild.h"
#include <fstream>

using namespace std;

int main()
{
    AppBuild();
    ifstream fin;
	ofstream fout;
	fin.open("input.txt");
	string a;
	getline(fin, a);
	fin.close();

	BigInt n1(a);

	fout.open("output.txt");

  BigInt ans = sqrt(n1);
  cout << "CALCULATED" << endl;
  fout << ans << endl << n1 - ans * ans;
  return 0;
}




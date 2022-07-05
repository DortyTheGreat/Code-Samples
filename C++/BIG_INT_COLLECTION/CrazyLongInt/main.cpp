

#include <cstdlib>
#include <iostream>
#include "MyHardwareInfo.h"
#include "LongInteger.h"

#include "LongInteger.cpp"
#include "../DortyLibs/DortyBuild.h"


 using namespace std;

int main(int argc, char** argv) {


    AppBuild();
    string a;
    ifstream fin("input.txt");
	ofstream fout("output.txt");



    fin >> a;
    LongInteger value1(a);

    for(int i = 0;i<10;i++){
        LongInteger::sqrt(value1);
    }

    fout << LongInteger::sqrt(value1).toDecimal() << endl;
    return 0;

    LongInteger value2(10);
    LongInteger value3("10");
    LongInteger value4(value3);
    value1 = value2 * value3;
    cout << value1.toDecimal() << endl;
    value1 = value2 / value3;
    cout << value1.toDecimal() << endl;
    value1 = value2 + value3;
    cout << value1.toDecimal() << endl;
    value1 = value2 - value3;
    cout << value1.toDecimal() << endl;
    value1 = value2;
    value1.powerCalc(value3);
    cout << value1.toDecimal() << endl;

    value1 = 100000;
    cout << value1.toDecimal() << endl;
    string value = "100000000000000000000";
    value2 = value;
    cout << value2.toDecimal() << endl;
    value3 = value2 * value2;
    value3 *= value2;
    value3 *= value2;
    value3 *= value2;
    cout << value3.toDecimal() << endl;
    cout << value3.getSize() << endl;

    LongInteger::KARATSUBACUTOFF = 20;
    LongInteger::KARATSUBATHREADING = 50;
    for( int i = 0; i < 14; i++) {
        value3 *= value3;
//        cout << value3.toDecimal() << endl;
        cout << value3.getSize() << endl;
    }
    return 0;
}

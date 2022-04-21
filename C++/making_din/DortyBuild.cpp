/*
---------------------
This File was Build Automatically by DortyBuild v 1.3.
For More Information ask:
Discord: �����#9030 
---Original---Code---

//#pragma GCC target ("avx2") /// говно для ноута
//#pragma GCC optimization ("O3") /// немножко ускоряет карацубу
//#pragma GCC optimization ("unroll-loops")

#include "../DortyLibs/AdvancedStream.h"

#include <cmath>
using namespace std;
#include <stdio.h>
#include "../DortyLibs/DinBigLib.h"

#include "../DortyLibs/DortyBuild.h"


#define file_read 1



int main()
{

    #if file_read

    freopen ("input.txt","r",stdin);

    #endif // file_read
    AppBuild();

    BigUnsigned a,b,c;

    //cin >> a;
    //for(int i = 0;i<1000;++i){
    //    c = k_mul(a,a);
    //}

    ///a = k_mul(a,b);

    //a += 1;
    //fout << c << " " << a - b*c;

    return 0;
}




*/
//#pragma GCC target ("avx2") /// говно для ноута
//#pragma GCC optimization ("O3") /// немножко ускоряет карацубу
//#pragma GCC optimization ("unroll-loops")

#include <iostream>
#include <fstream>

std::ifstream fin("input.txt");
std::ofstream fout("output.txt");


#include <cmath>
using namespace std;
#include <stdio.h>
//#pragma GCC target ("avx2")
//#pragma GCC optimization ("O3")
//#pragma GCC optimization ("unroll-loops")

///#include <bits/stdc++.h>

#define default_base 10

#define CONT_TYPE unsigned int
#define ubi_szt int /// Unsigned Big Int SiZe Type

#define big_container 1

#if big_container

#define cnt_stack 9 /// 9
#define total_base 1000000000 /// 1000000000
#define sqrt_of_total_base 31622 /// 31622

#else

#define cnt_stack 1 /// 9
#define total_base 10 /// 1000000000
#define sqrt_of_total_base 3 /// 31622

#endif


template <const int def_base = default_base, int BASE = total_base, const int container_stack = cnt_stack>
class BigUnsigned{
private:
    CONT_TYPE* _digits;
    const int ui = 10;
public:

    ubi_szt size;

    BigUnsigned(){

    cout << ui;

    }

    //friend std::ostream& operator << < >(std::ostream&, const BigUnsigned&);
	//friend std::istream& operator >> < >(std::istream&, BigUnsigned&);
};




char FromIntToChar(int a){
    if (a >= 0 && a <= 10){
        return (a + '0');
    }
    return (a - 10) + 'A';
}

int FromCharToInt(char a){
    if (a >= '0' && a <= '9'){
        return a - '0';
    }
    return (a - 'A')+10;
}

// �������� ����� � ����� ������
std::ostream& operator <<(std::ostream& os, const BigUnsigned& bi) {
	/*
	if ( (bi._digits.size() == 1) && (bi._digits[0] == 0)){
        os << FromIntToChar(0);
        return os;
    }
    */

    int sz = bi._digits.size();
    if (bi._is_negative){os << '-';}
    int Carret;
    std::string buff = "";
    for(int i = 0;i<sz;++i){
        Carret = bi._digits[i];
        for(int j = 0; j < container_stack;++j){
            buff += FromIntToChar(Carret % default_base);
            Carret /= default_base;
        }

    }

    while(buff.back() == '0'){
        buff.pop_back();
    }

    reverse(buff.begin(),buff.end());
    os << buff;
	return os;
}

std::istream& operator>>(std::istream& in, BigInt &bi) {


    std::string stream_;
    in >> stream_;

    int sz = stream_.size();
    int rsz = sz;
    sz = (sz+container_stack-1)/container_stack; /// /= �� ceil
    bi._digits.resize(sz);

    int Carret;

    for(int i = 0;i<sz;++i){
        Carret = 0;
        for(int j = 0; j < container_stack;++j){
            int index = rsz - (i+1)*container_stack + j;
            if (index > -1){
                Carret *= default_base;
                Carret += FromCharToInt(stream_[index]);
            }
        }

        bi._digits[i] = Carret;
    }

    bi._remove_leading_zeros();

    return in;

}







#define file_read 1



int main()
{

    #if file_read

    freopen ("input.txt","r",stdin);

    #endif // file_read
     

    BigUnsigned a,b,c;

    //cin >> a;
    //for(int i = 0;i<1000;++i){
    //    c = k_mul(a,a);
    //}

    ///a = k_mul(a,b);

    //a += 1;
    //fout << c << " " << a - b*c;

    return 0;
}





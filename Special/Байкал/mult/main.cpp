/*
---------------------
This File was Build Automatically by DortyBuild v 1.3.
For More Information ask:
Discord: рЕЯКЮ#9030
---Original---Code---

//#pragma GCC target ("avx2") /// пЁп╬п╡п╫п╬ п╢п╩я▐ п╫п╬я┐я┌п╟
//#pragma GCC optimization ("O3") /// п╫п╣п╪п╫п╬п╤п╨п╬ я┐я│п╨п╬я─я▐п╣я┌ п╨п╟я─п╟я├я┐п╠я┐
//#pragma GCC optimization ("unroll-loops")

using namespace std;
#include <iostream>
#include "../../DortyLibs/DortyTime.h"


#include <cmath>

#include <stdio.h>
#include "../../DortyLibs/DinBigLib.h"

#include "../../DortyLibs/DortyBuild.h"


#define file_read 0



int main()
{

    ///cout << "here2 " << endl;
    #if file_read

    freopen ("double_10k.txt","r",stdin);

    #endif // file_read
    AppBuild();





    BigUnsigned a,b, r;

    cin >> a >> b;
    r = Reciprocal(b,10);
    ///print(r._digits,1<<3);
    cout << endl<< DivisionWithKnownReciprocal(a,r, b.real_size);

    /// 0.2 100 10kx10k





    return 0;
}




*/
//#pragma GCC target ("avx2") /// пЁп╬п╡п╫п╬ п╢п╩я▐ п╫п╬я┐я┌п╟
//#pragma GCC optimization ("O3") /// п╫п╣п╪п╫п╬п╤п╨п╬ я┐я│п╨п╬я─я▐п╣я┌ п╨п╟я─п╟я├я┐п╠я┐
//#pragma GCC optimization ("unroll-loops")

using namespace std;
#include <iostream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <numeric>
#include <chrono>

class Clock{
private:
    long long start_prog_time;
    long long last_time;



public:

    Clock(){
        start_prog_time = chrono::high_resolution_clock::now().time_since_epoch().count();
        last_time = chrono::high_resolution_clock::now().time_since_epoch().count();
    }

    void tick() {
        long long time = chrono::high_resolution_clock::now().time_since_epoch().count();
        ///cout << CLOCKS_PER_SEC << endl;
        cout << (time - start_prog_time) << " (+" <<time-last_time << ")" << endl;
        last_time = time;
    }

    void tick(string text){
        cout << text << " : ";
        tick();
    }


};

Clock MainClock;



#include <cmath>

#include <stdio.h>
//#pragma GCC target ("avx2")
//#pragma GCC optimization ("O3")
//#pragma GCC optimization ("unroll-loops")

///#include <bits/stdc++.h>

#include <cstdint> ///
#include <cstring> /// ц╓ц╚ц© memcpy

#define default_base 10

#define CONT_TYPE int
#define DOUBLE_CONT_TYPE long long /// ц└ц╒ц╝ц╘ц╜ц╝ц╘ ц░ц─ц┤ц▄ц┘ц░
#define ubi_szt int /// Unsigned Big Int SiZe Type, ц╞ц╝ц╙ц═ ц╝ц║ц©ц╖ц═ц╜ ц║ц╩ц╡ц╪ ц╖ц╜ц═ц╙ц╝ц╒ц╩ц╛ -_-


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

const CONT_TYPE BASE = total_base;


//template <const int def_base = default_base, int BASE = total_base, const int container_stack = cnt_stack>
class BigUnsigned{
public:
    CONT_TYPE* _digits;
    static const CONT_TYPE BASE = total_base;
public:

    ubi_szt real_size; /// ц░ц┘ц─ц▀ц°ц█ц─ц÷ ц└ц╚ц╗ц╜ц╜ц═ ц╥ц╗ц╠ц╚ц═
    ubi_szt alloc_size; /// ц└ц╚ц© цЁц╞ц╟ц╝ц╧ц╔ц╜ц╗ц© ц╟ц╔ц═ц╚ц╗ц╖ц═ц╤ц╗ц╗ alloc_size - ц╒ц╠ц╔цёц╓ц═ ц╠ц╡ц╔ц╞ц╔ц╜ц╪ ц╓ц╒ц╝ц╘ц╙ц═, ц╡ц═ц╙ ц╛ц╝ц╕ц╜ц╝ ц║цЁц╓ц╔ц╡ цЁц╓ц╝ц║ц╜ц╝ ц╓ц╔ц╚ц╗ц╡ц╪ ц╛ц═ц╠ц╠ц╗ц╒ ц╜ц═ ц╓ц╒ц╔\\ц╥ц╔ц╡ц╩ц╟ц╔ ц╟ц═ц╒ц╜ц╩ц╔ ц╥ц═ц╠ц╡ц╗.

    BigUnsigned()
        : _digits( new CONT_TYPE[1])
        , real_size(1)
        , alloc_size(1)
    {_digits[0] = 0;}


    ~BigUnsigned(){
        delete[] _digits;
    }


    BigUnsigned& operator= (BigUnsigned&& bu)
    {
        //cout << "called move equality" << endl;
        _digits = ( bu._digits  );
        real_size = ( bu.real_size );
        alloc_size = ( bu.alloc_size );


        bu._digits = NULL;
        return *this;
    }

    BigUnsigned (BigUnsigned&& bu)
        : _digits( bu._digits  )
        , real_size( bu.real_size )
        , alloc_size( bu.alloc_size )
    {
        ///cout << "called move constructor" << endl;
        bu._digits = NULL;
    }

    BigUnsigned (const string& str);





    BigUnsigned& operator= (const BigUnsigned& bu){
        ///cout << "called copy equality" << endl;
        if (bu.real_size > alloc_size){
            alloc_size = bu.alloc_size;
            _digits = new CONT_TYPE[alloc_size];


            ///_digits = (CONT_TYPE*)(ptr); /// new CONT_TYPE[alloc_size]{0} п≤п⌡п≤ new CONT_TYPE[alloc_size]()
        }
        real_size = bu.real_size;

        memcpy(_digits,bu._digits,sizeof(CONT_TYPE) * bu.alloc_size);

        return *this;
    }



     BigUnsigned(const BigUnsigned& bu)
        : real_size(bu.real_size)
    {
        ///cout << "called copy constructor" << endl;
        if (bu.real_size > alloc_size){
            alloc_size = bu.alloc_size;
            _digits = new CONT_TYPE[alloc_size];
            ///_digits = (CONT_TYPE*)(ptr); /// new CONT_TYPE[alloc_size]{0} п≤п⌡п≤ new CONT_TYPE[alloc_size]()
        }
        real_size = bu.real_size;

        memcpy(_digits,bu._digits,sizeof(CONT_TYPE) * bu.alloc_size);

    }






    void _remove_leading_zeros();

    /// ц╛ц╔ц╛ц╝ц╟ц╗ ц╠ц╡ц═ц╢ц╢
    void alloc_with_zeros(const int sz);
    void assign_from_BU(const int alloc_space, const BigUnsigned& bu);

    friend std::ostream& operator << (std::ostream&, const BigUnsigned&);
	friend std::istream& operator >> (std::istream&, BigUnsigned&);

	short inline friend compare(const BigUnsigned &left, const BigUnsigned &right);

    bool friend operator <(const BigUnsigned& left, const BigUnsigned& right);
    bool friend operator ==(const BigUnsigned& left, const BigUnsigned& right);

    // auto-defined
    bool friend operator <=(const BigUnsigned& left, const BigUnsigned& right);
    bool friend operator >(const BigUnsigned& left, const BigUnsigned& right);
    bool friend operator >=(const BigUnsigned& left, const BigUnsigned& right);
    bool friend operator !=(const BigUnsigned& left, const BigUnsigned& right);

    friend const BigUnsigned operator +(const BigUnsigned&, const BigUnsigned&);

    friend const BigUnsigned operator +(BigUnsigned&&, const BigUnsigned&);



	void operator +=(const BigUnsigned&);

    void operator++();
    void operator--();

    void operator -=(const BigUnsigned& minus);

    friend BigUnsigned x_mul(const BigUnsigned& a,const BigUnsigned& b);
    friend BigUnsigned k_mul(const BigUnsigned& left,const BigUnsigned& right);


    /// ц┼ц═ц╟ц═ц╤цЁц║ц═, ц╙ц╠ц╡ц═ц╡ц╗ ц╛ц╔ц╜ц©ц╔ц╡ ц╙ц╝ц╜ц╡ц╔ц╘ц╜ц╔ц╟ц╜ц╩ц╘ ц╟ц═ц╖ц╛ц╔ц╟ ц╥ц╗ц╠ц╔ц╚ц╝ц╙...
    friend BigUnsigned karatsuba(BigUnsigned& left,BigUnsigned& right);

    friend BigUnsigned Reciprocal(const BigUnsigned& bu,int precision);

    friend BigUnsigned DivisionWithKnownReciprocal(const BigUnsigned& number, const BigUnsigned&, const int);

	void _add(const BigUnsigned&);

	/*~BigUnsigned (){
	    _digits = NULL;
        delete[] _digits;
	}
	*/
};


#include <algorithm> /// ДКЪ ПЕБЕПЯЮ string

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

// ОЕВЮРЮЕР ВХЯКН Б ОНРНЙ БШБНДЮ
std::ostream& operator <<(std::ostream& os, const BigUnsigned& bi) {
	/*
	if ( (bi._digits.size() == 1) && (bi._digits[0] == 0)){
        os << FromIntToChar(0);
        return os;
    }
    */



    CONT_TYPE Carret;
    std::string buff = "";
    for(int i = 0;i<bi.real_size;++i){
        Carret = bi._digits[i];
        for(int j = 0; j < cnt_stack;++j){
            buff += FromIntToChar(Carret % default_base);
            Carret /= default_base;
        }

    }


    /// сАПЮРЭ КХДХПСЧЫХЕ МСКХ
    while(buff.back() == '0' ){
        buff.pop_back();
        if (buff.empty()){
            return (os << "0");
        }
    }



    reverse(buff.begin(),buff.end());

	return (os << buff);
}

int next_power_of_two(int n) {
    int i = 0;
    for (--n; n > 0; n >>= 1) {
        i++;
    }
    return 1 << i;
}

std::istream& operator>>(std::istream& in, BigUnsigned &bi) {


    std::string stream_;
    in >> stream_;

    new (&bi) BigUnsigned(stream_);

    /// ЛА РСР МЮДН ПЕЦХЯРПХПНБЮРЭ "КХДХПСЧЫХЕ" МСКХ, МН УГ

    return in;

}

/*
/// яКНФЕМХЕ ДБСУ ОНКНФХРЕКЭМШУ (ХЯЙКЧВХРЕКЭМН ЙНМРЕИМЕПНБ)
void BigInt::_add(const BigInt& right) {
    size_t extra_size = 1;

    size_t an_sz = right._digits.size();

    if (an_sz > _digits.size()){
        extra_size = an_sz - _digits.size() + 1;
    }

    for(size_t i = 0;i < extra_size; i++){
        _digits.push_back(0);
    }
    /// гЮОНКМЪЕЛ ЙНМРЕИМЕП МСКЪЛХ, ВРНАШ АШКН ЛЕЯРН ОНД МНБШЕ БНГЛНФМШЕ ВХЯКЮ(aka ПЮГПЪДШ)

    for(size_t i = 0; i < an_sz;i++){
        _digits[i] += right._digits[i];
        if (_digits[i] >= BASE){
            _digits[i] -= BASE;
            _digits[i+1]++;
        }
    }

    while(_digits[an_sz] >= BASE){
        _digits[an_sz] -= BASE;
        an_sz++;
        _digits[an_sz]++;
    }



    _remove_leading_zeros();
}

/// нАПЮАНРЙЮ БШВХРЮМХЪ ДБСУ ОНКНФХРЕКЭМШУ ВХЯЕК (ПЮАНРЮЕР, ЕЯКХ БРНПНЕ ЛЕМЭЬЕ ОЕПБНЦН)
void BigInt::_subtract(const BigInt &another){

    size_t an_sz = another._digits.size();

    for(size_t i = 0; i < an_sz;i++){
        _digits[i] -= another._digits[i];
        if (_digits[i] < 0){
            _digits[i] += BASE;
            _digits[i+1]--;
        }
    }

    while(_digits[an_sz] < 0){
        _digits[an_sz] += BASE;
        an_sz++;
        _digits[an_sz]--;
    }



    _remove_leading_zeros();
}
*/
void BigUnsigned::operator +=(const BigUnsigned& right) {
    if (right.alloc_size > alloc_size){
        /// РНВМН ОЕПЕОНКМЕМХЕ
        return;
    }

    if (right.alloc_size < alloc_size){
        if (_digits[alloc_size - 1] == (BASE-1) ){
            /// лНФЕР ОПНХГНИРХ ОЕПЕОНКМЕМХЕ
        }
    }


}
/**

яОНЯНАМН НРПЮАНРЮРЭ МНПЛЮКЭМН, ЕЯКХ ...

+ ме гюасдэ опн real_size

*/
void BigUnsigned::operator -=(const BigUnsigned& minus) {

    for(int i = 0;i< minus.real_size; ++i){
        _digits[i] -= minus._digits[i];
        if (_digits[i] < 0){
            _digits[i] += BASE;
            --_digits[i+1];
        }
    }

    if (minus.real_size != real_size){



        /// гЮЛЕВС ВРН ОЕПБШИ ОПНУНД МЕ ХЛЕЕР ЯЛШЯКЮ :-)
        for(int j = minus.real_size; _digits[j] < 0;++j){

            _digits[j] += BASE;
            --_digits[j+1];

        }
    }

    _remove_leading_zeros();




}

/**

оПХАЮБКЪЕР БРНПНЕ ВХЯКН Й НЯМНБМНЛС. нДМЮЙН НМН НАЪГЮМН ОНЛЕЫЮРЭЯЪ Б МЕЦН.

*/
void BigUnsigned::_add(const BigUnsigned& right) {

    for(int i = 0;i < right.real_size; ++i){
        _digits[i] += right._digits[i];
        if (_digits[i] >= BASE){
            _digits[i] -= BASE;
            ++_digits[i + 1];
        }
    }

    /// уНВЕРЯЪ, РН, ВРН МХФЕ ЯДЕКЮРЭ ДКЪ ТКЕЙЯЮ, МН РЮЙ РНФЕ +- МХВЕЦН
    CONT_TYPE *p = &_digits[right.real_size];
    while (*p >= BASE){
        *p -= BASE;
        ++p;
        ++(*p);
    }


    /*
    CONT_TYPE &p = _digits[right.real_size];
    while (p >= BASE){
        p -= BASE;
        (&p)++;
        ++(p);
    }
    */

    /// щРН РНФЕ ЯКЕДСЕР СКСВЬХРЭ
    real_size = max(real_size, right.real_size);
    if (real_size != alloc_size){
        if (_digits[real_size] != 0){
            ++real_size;
        }
    }


}



/*
/// бЕПМШИ НОЕПЮРНП (Я СВ╦РНЛ ГМЮЙНБ Х ОПНВЕЦН)
void BigInt::operator-=(BigInt right){

    ///std::cout << *this << " " << right << " "<<(compare(*this,right)) << std::endl;
    bool comp_ = !(compare(*this,right));
    if ( comp_){
        ///std::cout << "second is hisher" << std::endl;
        swap(right,*this);
        _is_negative = !_is_negative;
    }


    if ( (_is_negative == right._is_negative) ^ (comp_) ) {
        // нДХМЮЙНБШ ОН ГМЮЙС
        _subtract(right);
    }else{
        // пЮГМШЕ ОН ГМЮЙС.
        _add(right);
    }

}
*/





// БНГБПЮЫЮЕР ЙНОХЧ ОЕПЕДЮММНЦН ВХЯКЮ
//const BigInt BigInt::operator +() const {
//	return BigInt(*this);
//}
/*
// БНГБПЮЫЮЕР ОЕПЕДЮММНЕ ВХЯКН Я ДПСЦХЛ ГМЮЙНЛ
const BigInt BigInt::operator -() const {
	BigInt copy(*this);
	copy._is_negative = !copy._is_negative;
	return copy;
}
*/


/**

яЙКЮДШБЮЕР Х ОНЛЕЫЮЕР МНБНЕ ВХЯКН Б МНБНЕ ЛЕЯРН Б ОЮЛЪРХ (БЕПНЪРМЕЕ БЯЕЦН ОПХЯБЮХБЮРЭ ЕЦН ЛШ ГЮУНРХЛ ВЕПЕГ ->)

*/


const BigUnsigned operator +(const BigUnsigned& left, const BigUnsigned& right) {

    if (left.real_size < right.real_size){
        return right+left;
    }



    BigUnsigned ret;
    ret.assign_from_BU(left.real_size+1,left);




    ret._add(right);

	return ret;
}


const BigUnsigned operator +(BigUnsigned&& left, const BigUnsigned& right) {
    cout << "called rvalue" << endl;
    if (left.real_size < right.real_size){
        //return right+left;
    }

    left += right;

	return left;
}



// ОПЕТХЙЯМШИ ХМЙПЕЛЕМР
void BigUnsigned::operator++() {

	++_digits[0];
	for ( ubi_szt cou = 0; cou < real_size -1; ++cou){
        if (_digits[cou] < BASE){ return;}

        _digits[cou] -= BASE; /// ЛНФМН ГЮОХЯЮРЭ = 0 Б ЖЕКНЛ, ЕЯКХ ХГМЮВЮКЭМНЕ ВХЯКН ЯАЮКЮМЯХПНБЮМН
        ++_digits[cou+1];
	}

    if (_digits[real_size - 1] >= BASE ){
        if (real_size == alloc_size){
            /// reallocate memory
            CONT_TYPE * new_c = new CONT_TYPE[++alloc_size];
            memcpy(new_c, _digits, real_size * sizeof(CONT_TYPE));
            new_c[real_size] = 0;
            _digits = new_c;
        }

        _digits[real_size - 1] -= BASE;
        ++_digits[real_size++];

    }
}

void BigUnsigned::operator--() {

	--_digits[0];



    for(int j = 0; _digits[j] < 0;++j){

        _digits[j] += BASE;
        --_digits[j+1];

    }


    _remove_leading_zeros();
}


/*
// ОНЯРТХЙЯМШИ ХМЙПЕЛЕМР
const BigInt BigInt::operator ++(int) {
	*this += 1;
	return *this - 1;
}

// ОПЕТХЙЯМШИ ДЕЙПЕЛЕМР
const BigInt BigInt::operator --() {
	return *this -= 1;
}


// ОНЯРТХЙЯМШИ ДЕЙПЕЛЕМР
const BigInt BigInt::operator --(int) {
	*this -= 1;
	return *this + 1;
}

*/
/*
// БШВХРЮЕР ДБЮ ВХЯКЮ
const BigInt operator -(BigInt left, const BigInt& right) {
	left -= right;
	return left;
}

*/




void BigUnsigned::alloc_with_zeros(const int sz){
    alloc_size = sz;
    _digits = new CONT_TYPE[sz]{0};

}

/**

рНФЕ ЯЮЛНЕ, ВРН Х НОЕПЮРНП=, МН ЛНФМН СЙЮГЮРЭ ЙНКХВЕЯРБН ОЮЛЪРХ ДКЪ ЮККНЙЮЖХХ

оепеохяюрэ мю лел_яер http://cppstudio.com/post/673/

*/
void BigUnsigned::assign_from_BU(const int alloc_space, const BigUnsigned& bu){
    alloc_with_zeros(alloc_space);
    real_size = bu.real_size;
    memcpy(_digits,bu._digits,real_size * sizeof(CONT_TYPE));
}


/**
    яХЯРЕЛМЮЪ ТСМЙЖХЪ. рПЕАСЕРЯЪ ДКЪ РЕУ ЯКСВЮЕБ, ЙНЦДЮ real_size БШЬЕ ВЕЛ "ПЕЮКЭМШИ" ПЮГЛЕП.
    (ОПНЯРН СЛЕМЭЬЮЕР real_size)
*/
void BigUnsigned::_remove_leading_zeros(){
    int cur = real_size - 1;
    for( ; cur != 0 ; --cur){
        if (_digits[cur] != 0){
            break;
        }
    }
    real_size = cur + 1;
}



BigUnsigned::BigUnsigned (const string& stream_){
    ubi_szt carret_r_sz = stream_.size();
    real_size = (carret_r_sz+cnt_stack-1)/cnt_stack;
    alloc_with_zeros(next_power_of_two(real_size));

    CONT_TYPE Carret;

    for(ubi_szt i = 0;i<real_size;++i){
        Carret = 0;
        for(ubi_szt j = 0; j < cnt_stack;++j){
            int index = carret_r_sz - (i+1)*cnt_stack + j;
            if (index > -1){
                Carret *= default_base;
                Carret += FromCharToInt(stream_[index]);
            }
        }

        _digits[i] = Carret;
    }
}







/*

BigUnsigned::BigUnsigned (BigUnsigned&& ){

}

BigUnsigned::BigUnsigned (const BigUnsigned& bu){
    cout << "started equality" << endl;
    if (bu.real_size > alloc_size){
        alloc_size = bu.alloc_size;
        _digits = new CONT_TYPE[alloc_size];


        ///_digits = (CONT_TYPE*)(ptr); /// new CONT_TYPE[alloc_size]{0} хкх new CONT_TYPE[alloc_size]()
    }
    real_size = bu.real_size;

    memcpy(_digits,bu._digits,sizeof(CONT_TYPE) * bu.alloc_size);
}

*/

/*
void BigUnsigned::operator =(BigUnsigned&& bu){
    real_size = bu.real_size;
    alloc_size = bu.alloc_size;
    _digits = bu._digits;
}
*/



/*
int intlog(double base, double x) {
    return (int)(log(x) / log(base));
}

// ЯНГДЮЕР ДКХММНЕ ЖЕКНЕ ВХЯКН ЯН ГМЮВЕМХЕЛ 0
BigInt::BigInt() {
	this->_is_negative = false;
}

// ЯНГДЮЕР ДКХММНЕ ЖЕКНЕ ВХЯКН ХГ C++-ЯРПНЙХ
BigInt::BigInt(std::string str) {
	/// to_do
}

// ЯДБХЦЮЕР БЯЕ ПЮГПЪДШ МЮ 1 БОПЮБН (ДНЛМНФЮЕР МЮ BASE)
void BigInt::_shift_right() {

    /// removed exceptions

	_digits.push_back(_digits[_digits.size() - 1]);
	for (size_t i = _digits.size() - 2; i > 0; --i) _digits[i] = _digits[i - 1];
	_digits[0] = 0;
}

// ЯДБХЦЮЕР БЯЕ ПЮГПЪДШ МЮ 1 БОПЮБН (ДНЛМНФЮЕР МЮ BASE)
void BigInt::_double_shift_right() {

    /// removed exceptions

    if (_digits.size() == 1){
        _digits = {0,0,_digits[0]};
        return;
    }

	_digits.push_back(_digits[_digits.size() - 2]);
	_digits.push_back(_digits[_digits.size() - 2]);
	for (size_t i = _digits.size() - 3; i > 1; --i) _digits[i] = _digits[i - 2];
	_digits[0] = 0;
	_digits[1] = 0;
}

// СДЮКЪЕР БЕДСЫХЕ МСКХ
void BigInt::_remove_leading_zeros() {
	while (this->_digits.size() > 1 && this->_digits.back() == 0) {
		this->_digits.pop_back();
	}

	if (this->_digits.size() == 1 && this->_digits[0] == 0) this->_is_negative = false;
}

// ОПЕНАПЮГСЕР ВХЯКН Й ЯРПНЙЕ
BigInt::operator std::string() const {
	std::stringstream ss;
	ss << *this;
	return ss.str();
}

BigInt::BigInt(long long num){
    _is_negative = (num < 0);
    num = abs(num);
    while(num != 0){
        _digits.push_back(num % BASE);
        num /= BASE;
    }

    if (_digits.size() == 0){
        _digits.push_back(0);
    }
}


BigInt::BigInt(int num){
    _is_negative = (num < 0);
    num = abs(num);
    while(num != 0){
        _digits.push_back(num % BASE);
        num /= BASE;
    }

    if (_digits.size() == 0){
        _digits.push_back(0);
    }
}

// ОПНБЕПЪЕР, ЪБКЪЕРЯЪ КХ РЕЙСЫЕЕ ВХЯКН МЕВЕРМШЛ
bool BigInt::odd() const {
	if (this->_digits.size() == 0) return false;
	return this->_digits[0] & 1;
}

// ОПНБЕПЪЕР, ЪБКЪЕРЯЪ КХ РЕЙСЫЕЕ ВХЯКН ВЕРМШЛ
bool BigInt::even() const {
	return !this->odd();
}


/// [5,4,3,2,1](12345) (length=3)-> [0,0,0,5,4,3,2,1](12345000)
/// яКЕДСЕР сКСВЬХРЭ. сФЮЯМН ОКНУН ПЕЮКХГНБЮММН
void inline BigInt::_appendZeros(int length){
    std::vector<CONT_TYPE> v1(length);
    std::vector<CONT_TYPE> tmp = _digits;
    _digits.clear();
    std::merge(v1.begin(), v1.end(), tmp.begin(), tmp.end(), std::back_inserter(_digits));
}

const int BigInt::get_real_size() const{
    return (_digits.size()-1)*container_stack + intlog(default_base,_digits[_digits.size() - 1]) + 1;
}
*/






/// нАПЮАНРЙЮ ЯПЮБМЕМХЪ ДБСУ ОНКНФХРЕКЭМШУ ВХЯЕК (0 => БРНПНЕ АНКЭЬЕ, 1 => ПЮБМШ, 2 => МЮЬЕ АНКЭЬЕ)
short inline compare(const BigUnsigned &left, const BigUnsigned &right){
    size_t sz = left.real_size;
    if (right.real_size != left.real_size){
        return (left.real_size > right.real_size) << 1;
    }



    for (size_t i = 0;i<sz;i++){
        int p = sz - i - 1;
        if (left._digits[p] != right._digits[p]){
            return (left._digits[p] > right._digits[p]) << 1;
        }
    }

    return 1;
}




// ОПНБЕПЪЕР, ЪБКЪЕРЯЪ КХ КЕБШИ НОЕПЮМД ЛЕМЭЬЕ ОПЮБНЦН
bool operator <(const BigUnsigned& left, const BigUnsigned& right) {

    size_t sz = left.real_size;
    if (right.real_size != left.real_size){
        return (left.real_size < right.real_size);
    }



    for (size_t i = 0;i<sz;i++){
        int p = sz - i - 1;
        if (left._digits[p] != right._digits[p]){
            return (left._digits[p] < right._digits[p]);
        }
    }

    return 0;
}

// ОПНБЕПЪЕР, ЪБКЪЕРЯЪ КХ КЕБШИ НОЕПЮМД ЛЕМЭЬЕ ОПЮБНЦН
bool operator ==(const BigUnsigned& left, const BigUnsigned& right) {

    size_t sz = left.real_size;
    if (right.real_size != left.real_size){
        return 0;
    }



    for (size_t i = 0;i<sz;i++){
        int p = sz - i - 1;
        if (left._digits[p] != right._digits[p]){
            return 0;
        }
    }

    return 1;
}

// ЯПЮБМХБЮЕР ДБЮ ВХЯКЮ МЮ МЕПЮБЕМЯРБН
bool operator !=(const BigUnsigned& left, const BigUnsigned& right) {
	return !(left == right);
}

// ОПНБЕПЪЕР, ЪБКЪЕРЯЪ КХ КЕБШИ НОЕПЮМД ЛЕМЭЬЕ КХАН ПЮБЕМ ОПЮБНЦН
bool operator <=(const BigUnsigned& left, const BigUnsigned& right) {
	return !(right < left);
}

// ОПНБЕПЪЕР, ЪБКЪЕРЯЪ КХ КЕБШИ НОЕПЮМД АНКЭЬЕ ОПЮБНЦН
bool operator >(const BigUnsigned& left, const BigUnsigned& right) {
	return (right < left);
}

// ОПНБЕПЪЕР, ЪБКЪЕРЯЪ КХ КЕБШИ НОЕПЮМД АНКЭЬЕ КХАН ПЮБЕМ ОПЮБНЦН
bool operator >=(const BigUnsigned& left, const BigUnsigned& right) {
	return !(left < right);
}


/* Grade school multiplication, ignoring the signs.
 * Returns the absolute value of the product, or NULL if error.
 */
 /// юКЦНПХРЛ ьЙНКЭМНЦН сЛМНФЕМХЪ (БГЪРН Я ДНЙНБ оХРНМЮ -> ЯЛ. https://hg.python.org/cpython/file/b514339e41ef/Objects/longobject.c#l2694)
 /// мЕ ПЮАНРЮЕР ОПЮБХКЭМН Я МСК╦Л
BigUnsigned x_mul(const BigUnsigned& a,const BigUnsigned& b)
{
    static const CONT_TYPE BASE = a.BASE;

    BigUnsigned z;
    const ubi_szt size_a = a.real_size;
    const ubi_szt size_b = b.real_size;
    ubi_szt i;
    z.alloc_with_zeros(size_a + size_b);




    ///memset(z->ob_digit, 0, Py_SIZE(z) * sizeof(digit));

    for (i = 0; i < size_a; ++i) {
        DOUBLE_CONT_TYPE carry = 0;
        DOUBLE_CONT_TYPE f = a._digits[i];
        CONT_TYPE *pz = z._digits + i;
        CONT_TYPE *pb = b._digits;
        CONT_TYPE *pbend = b._digits + size_b;

        /// SIGCHECK ???

        while (pb < pbend) {
            carry += *pz + *pb++ * f;
            *pz++ = (carry % BASE);
            carry /= BASE;
        }
        if (carry)
            *pz += (carry % BASE);
    }


    if (z._digits[z.alloc_size - 1] == 0){
         z.real_size = z.alloc_size - 1;
    }else{
         z.real_size = z.alloc_size;
    }

    return z;
}


/// ЩРН ДКЪ ЙЮПЮЖСАШ, МЕ РПНЦЮРЭ!
/**

ю БННАЫЕ ЩРН ДКЪ ОЕПЕЛМНФЕМХЕ ДБСУ ВХЯЕК НДХМЮЙНИН ДКХММШ, МН ЯПЮГС ВЕПЕГ ЛЮЯЯХБШ.

*/
void x_mul(const CONT_TYPE *__restrict a, CONT_TYPE *__restrict b, CONT_TYPE *__restrict res,const ubi_szt n)
{

    ubi_szt i;




    ///memset(z->ob_digit, 0, Py_SIZE(z) * sizeof(digit));

    for (i = 0; i < n; ++i) {
        DOUBLE_CONT_TYPE carry = 0;
        DOUBLE_CONT_TYPE f = a[i];
        CONT_TYPE *pz = res + i;
        CONT_TYPE *pb = b;
        CONT_TYPE *pbend = b + n;

        /// SIGCHECK ???

        while (pb < pbend) {
            carry += *pz + *pb++ * f;
            *pz++ = (carry % BASE);
            carry /= BASE;
        }
        if (carry)
            *pz += (carry % BASE);
    }



}

#define KAR_TRESH 20
/*
BigUnsigned k_mul(const BigUnsigned& left,const BigUnsigned& right) {



    const ubi_szt n = left.real_size; /// size of biggest num

    if (n < right.real_size){
        return k_mul(right,left);
    }

    /// ВХЯКН ЛЕКЙНЕ, СЛМНФЮЕЛ, ЙЮЙ НАШВМН
    if (n < KAR_TRESH){return x_mul(left,right);}

    const ubi_szt fh = (n+1) / 2;   // First half Data (take more)
    const ubi_szt sh = (n - fh); // Second half of Data

    // Find the first half and second half of first string.



    BigUnsigned L0, L1, R0;

    const ubi_szt s_sz = right.real_size;

    const ubi_szt _0_sz = min(s_sz, fh);

    L0._digits = new CONT_TYPE[fh];
    L1._digits = new CONT_TYPE[sh];
    R0._digits = new CONT_TYPE[_0_sz];
    BigUnsigned Z0;
    BigUnsigned Z1;



    memcpy(L0._digits,left._digits,fh * sizeof(CONT_TYPE));
    memcpy(L1._digits,left._digits + fh,sh * sizeof(CONT_TYPE));
    memcpy(R0._digits, right._digits, _0_sz * sizeof(CONT_TYPE));








    Z0 = k_mul(L0,R0);
    const int _1_sz = s_sz - _0_sz;
    if (_1_sz == 0){
        /// Z2 = 0
        Z1 = k_mul(L1,R0); /// no swap

        Z1._appendZeros(fh);


        return Z1+Z0;
    }else{
        BigUnsigned R1;
        R1._digits.resize(_1_sz);



        for(int i = 0;i<_1_sz;++i){
            R1._digits[i] = right._digits[fh + i];
        }

        BigUnsigned Z2 = k_mul(L1,R1); /// no swap


        Z1 = k_mul(L0+L1, R0+R1);

        Z1 -= (Z0+Z2);

        ///if ( !(Z1.data.size() == 1 && Z1.data[0] == 0) )
            Z1._appendZeros(fh);

        ///if ( !(Z2.data.size() == 1 && Z2.data[0] == 0) )
            Z2._appendZeros(fh * 2);

        return Z2 + Z1 + Z0;
    }

}
*/



/**

цНДМЮЪ йЮПЮЖСАЮ.
рПЕАСЕР: 2 "АКНЙЮ" ОЮЛЪРХ ПЮБМНИ ДКХМШ, (ДКХМС АКНЙЮ ЯННРБЕРЯБЕММН РНФЕ РПЕАСЕР), Х ЛЕЯРН Б ОЮЛЪРХ, ЙСДЮ
ОНЛЕЯРХРЭ ПЕГСКЭРЮР СЛМНФЕМХЪ (ЛЕЯРН ДНКФН АШРЭ ГЮПЮМЕЕ БШДЕКЕМН Х ГЮОНКМЕМН МСКЪЛХ)

(БННАЫЕ НМ Б РПЕРХИ ЙНМРЕИМЕП ЙЮЙ АШ ДНАЮБКЪЕР ВХЯКЮ, РЮЙ ВРН ЕЯКХ МЮДН ДНАЮБКЪРЭ РН ЛХКНЯРХ ОПНЬС, ЩРЮ йЮПЮЖСАЮ ЩРН ОН ТЮЙРС Х ДЕКЮЕР)

TO-DO:

1) яФЮРХЕ ОЮЛЪРХ Б НДМС ОЕПЕЛЕММСЧ (БЛЕЯРН ДБСУ)
2) ...
3) оНВХМХРЭ "ПЮЯРСЫХЕ" ПЮГЛЕПШ
4) ОНВХМХРЭ ДНКЦХИ ЛХМСЯ


*/

void mult(const CONT_TYPE * a, CONT_TYPE * b, CONT_TYPE *__restrict res, const ubi_szt n) {

    /// яКХЬЙНЛ ЛЮКЕМЭЙНЕ ВХЯКН, ГЮОСЯЙЮЕЛ ЬЙНКЭМШИ ЮКЦНПХРЛ
    if (n <= KAR_TRESH) {
        x_mul(a,b,res,n);
    } else {

        const ubi_szt fh = (n+1) / 2;   // First half Data (take more)
        const ubi_szt sh = (n - fh); // Second half of Data

        CONT_TYPE* first = new CONT_TYPE[fh + 1];
        first[fh] = 0;

        CONT_TYPE* second = new CONT_TYPE[fh + 1]; second[fh] = 0;



        memcpy(first,a,fh * sizeof(CONT_TYPE));
        memcpy(second,b,fh * sizeof(CONT_TYPE));



        /// яРН ОПНЖ ЛНФМН СЯЙНПХРЭ ЯКНФЕМХЕ
        for (ubi_szt i = 0; i < sh; i++) {
            first[i] += a[i + fh];

            if (first[i] >= BASE){
                first[i] -= BASE;
                ++first[i+1];
            }

            second[i] += b[i + fh];
            if (second[i] >= BASE){
                second[i] -= BASE;
                ++second[i+1];
            }
        }
        /// дНО. ВЕЙ МЮ ОЕПЕБНКМЕМХЕ ОНЯКЕДМЕЦН ЙНМРЕИМЕПЮ
        if (first[fh - 1] >= BASE){
                first[fh - 1] -= BASE;
                ++first[fh];
            }
        if (second[fh - 1] >= BASE){
            second[fh - 1] -= BASE;
            ++second[fh];
        }


        /// first += a offseted by fh
        /// second += b offseted by sh


        //mult(first, second, res + fh, fh + 1);
        //delete first;
        //delete second;

        mult(a + 0, b + 0, res, fh);
        mult(a + fh, b + fh, res + fh*2, sh);
        CONT_TYPE * we_need_to_optimize_memory = new CONT_TYPE[2* (fh + 1)]{0};


        mult(first, second, we_need_to_optimize_memory, fh + 1);

        for(ubi_szt i = 0; i < 2 * sh; ++i){

            we_need_to_optimize_memory[i] -= (res[i] + res[2 * fh + i]);

        }

        if (sh != fh){

            we_need_to_optimize_memory[2 * sh] -= res[2 * sh];
            we_need_to_optimize_memory[2 * sh + 1] -= res[2 * sh + 1];
        }

        /// щРН РНФЕ СФЮЯМНЕ БШВХРЮМХЕ !!
        for(ubi_szt i = 0; i < 2 * fh + 2;++i){

            res[fh + i] += we_need_to_optimize_memory[i];
            if (res[fh + i]  >= BASE){
                res[fh + i] -= BASE;
                ++res[fh + 1 + i];
            }else{
                while (res[fh + i]  < 0){
                    res[fh + i] += BASE;
                    --res[fh + 1 + i];
                }
            }
        }

        delete[] we_need_to_optimize_memory;
        delete[] first;
        delete[] second;







        /// мЕ ГЮАШРЭ МЕ РНКЭЙН НРОХЛХГХПБЮРЭ ОЮЛЪРЭ, МН Х ПЮГЛЕПШ



    }


}



/// оНЙЮ йЮПЮЖСАЮ дСЛЮЕР, ВРН С ВХЯЕК НДХМЮЙНБШИ ПЮГЛЕП

/// мЕ ДН ЙНМЖЮ ДНДЕКЮМН, ПЮГЛЕП real_size НАЙСПЕММШИ -> ОПХ СЛМНФЕМХХ МЮ МСКЭ ДЕКЮЕР оХБН
/// еЫ╦ ХГЛЕМЪЕР ПЮГЛЕП Б ДНАЮБНЙ
BigUnsigned karatsuba(BigUnsigned& left, BigUnsigned& right){
    /// еЯКХ ОПЮБШИ АНКЭЬЕ -> РНЦДЮ ПЕГСКЭРЮР АСДЕР ЛЕМЭЬЕ РПЕАСЕЛНЦН
    if (left.alloc_size < right.real_size){
        CONT_TYPE *remem = left._digits;
        left.alloc_with_zeros(right.real_size);

        memcpy(left._digits, remem, left.real_size * sizeof(CONT_TYPE));
    }


    /// еЯКХ КЕБШИ АНКЭЬЕ -> БУНДХЛ Б МЕЮККНЙЕИРЕД ОЮЛЪРЭ
    if (right.alloc_size < left.real_size){
        //cout << right << endl;
        CONT_TYPE *remem = right._digits;
        right.alloc_with_zeros(left.real_size);

        memcpy(right._digits, remem, right.real_size * sizeof(CONT_TYPE));
        //cout << right << endl;
    }





    BigUnsigned res;
    res.alloc_with_zeros(2 * max(left.real_size,right.real_size));
    mult(left._digits,right._digits,res._digits,max(left.real_size,right.real_size));



    if (res._digits[res.alloc_size - 1] == 0){
         res.real_size = res.alloc_size - 1;
    }else{
         res.real_size = res.alloc_size;
    }



    return res;

}





/* A helper for Karatsuba multiplication (k_mul).
   Takes a long "n" and an integer "size" representing the place to
   split, and sets low and high such that abs(n) == (high << size) + low,
   viewing the shift as being by digits.  The sign bit is ignored, and
   the return values are >= 0.
   Returns 0 on success, -1 on failure.
*/
/*
void kmul_split(const BigUnsigned& n,
           ubi_szt size,
           BigUnsigned& high,
           BigUnsigned& low)
{

    ubi_szt size_lo, size_hi;
    const ubi_szt size_n = n.real_size;

    size_lo = min(size_n, size);
    size_hi = size_n - size_lo;

    hi._digits = new CONT_TYPE[size_hi];
    lo._digits = new CONT_TYPE[size_lo];

    memcpy(lo->ob_digit, n->ob_digit, size_lo * sizeof(digit));
    memcpy(hi->ob_digit, n->ob_digit + size_lo, size_hi * sizeof(digit));

    *high = long_normalize(hi);
    *low = long_normalize(lo);
    return 0;
}
*/

#include <cmath>
int intlog(double base, double x) {
    return (int)(log(x) / log(base));
}
/// 9 223 372 036 854 775 807
/// 2147483647
const long long INT_MAXI = 9223372036854775807;

int inline intSqrt(long long arg){
    return (long long)(sqrt(arg));
}

template <typename T>
void print(T* a, int n ){
    for(int i = 0;i<n;i++){
        cout << a[i] << " ";
    }
    cout << endl;
}
/**
мЕ ПЮАНРЮЕР ДКЪ ВХЯЕК РХОЮ:
1, 10, 100, 1000, 10000 Х Р.Д.

upd: СФЕ ПЮАНРЮЕР, МН ЩРН ПЕЬЕМХЕ - ЕЯРЭ ЙНЯРШКЭ...
*/
BigUnsigned Reciprocal(const BigUnsigned& bu,int precision)
{
    ///MainClock.tick("Started Reciprocal");
    ubi_szt cool_num = 1 << precision;

    BigUnsigned res;

    /// яЙНКЭЙН МСКЕИ ДЮБЮРЭ Ъ УГ
    res.alloc_with_zeros(cool_num);
    res.real_size = res.alloc_size;


    /// ЯКЕДСЕР МЮИРХ АНКЕЕ ЦПЮЛНРМШИ ЛЕРНД ТХЙЯЮ ЩРНЦН АЮЦЮ...
    if (bu._digits[bu.real_size - 1] == 1){
        bool flag = 1;
        for(int i = 0;i < bu.real_size - 1;++i){
            if (bu._digits[i] != 0){
                flag = 0;
                break;
            }
        }
        if (flag){
            /// ВХЯКН ЩРН 1, 10, 100, 1000 Х Р.Д.
            res._digits[res.alloc_size - 1] = BASE;
            ///cout << "special case" << endl;

            return res;
        }
    }

    ubi_szt mx_sz = intlog(BASE, INT_MAXI);
    ubi_szt sz = bu.real_size;
    ubi_szt len{ (sz > (mx_sz - 1)) ? (mx_sz) : sz };

    DOUBLE_CONT_TYPE divisor = 0;









    for(int i = 0;i<len;i++){
        divisor *= BASE;
        divisor += bu._digits[sz - i - 1];
    }

    DOUBLE_CONT_TYPE dividend = 1;
    for(int i = 0;i<len;++i){
        dividend *= BASE;
    }

    dividend = dividend / divisor;


    while ( dividend >= BASE){
        dividend /= BASE;
    }

    /// йЮПНВЕ, ЩРН РХОН... сЯЙНПЪЕР БШВХЯКЕМХЪ, ХАН НАПЮЫЕМХЕ ВЮЯРН ОН ЯЯШКЙЕ ОПНХЯУНДХР ХКХ РХО РНЦН ...
    CONT_TYPE* & approx = res._digits;

    /// йЮПНВЕ... мЮДН ПЮЯЬХПХРЭ НПХЦХМЮКЭМНЕ ВХЯКН РХОЮ... МН МЕЛМНФЙН НАЙСПЕММН ...
    CONT_TYPE * expanded = new CONT_TYPE[cool_num]{0};

    memcpy(expanded + (cool_num - bu.real_size), bu._digits, bu.real_size * sizeof(CONT_TYPE));

    ///cout << "expanded " << endl;
    ///print(expanded, cool_num);

    CONT_TYPE* sqr = new CONT_TYPE[cool_num]{0};
    CONT_TYPE* minus = new CONT_TYPE[cool_num * 2]{0};


    approx[res.alloc_size - 1] = dividend;

    ///write_to = dividend / divisor;
    ///write_to._appendZeros(precision - sz);

    ///MainClock.tick("Reciprocal prep done");

    // Do the interation to fullfil the precision
    for (int i = 1; i != cool_num; i <<= 1)
    {
        ///MainClock.tick("itterarion start");
        ///cout << i << endl;

       /// cout << "old approx ";
        ///print(approx,cool_num);

        memset(sqr, 0, (cool_num) * sizeof(CONT_TYPE));
        memset(minus, 0, (2 * cool_num) * sizeof(CONT_TYPE));

        mult(approx + cool_num - i,approx + cool_num - i,sqr,i);
        ///cout << "sqr ";
        ///print(sqr, i * 2);
        /// рЕОЕПЭ sqr ХЛЕЕР ПЮГЛЕП 2n, minus -> 4n, МН ЯКЕДСЕР truncatenut' ДН 2n

        ///cout << "expanded ";
        ///print(expanded + cool_num - 2*i , i*2);

        ///cout << "full expanded ";
        ///print(expanded , cool_num);

        mult(sqr, expanded + cool_num - 2*i , minus ,i*2 );


        ///cout << "minus ";
        ///print(minus, i * 4);

        /// aprox = 2*approx - minus
        for (int cou = 0;cou < i * 2;cou++){
                approx[cool_num - cou - 1] *= 2;
        }
        for (int cou = 0;cou < i * 2;cou++){
            CONT_TYPE& r = approx[cool_num - i*2 + cou];
            ///cout << r << " " << minus[i*2 + cou - 1];
            r -= minus[i*2 + cou - 1];

            ///cout << " " << r << endl;

            if (r  >= BASE){
                r -= BASE;
                ++approx[cool_num - i*2 + cou + 1];
            }else{
                if (r  < 0){
                    r += BASE;
                    --approx[cool_num - i*2 + cou + 1];
                }
            }




        }

        ///cout << "new approx ";
        ///print(approx,cool_num);
        ///cout << res << endl << endl;


        ///MainClock.tick("itterarion finish");
        /// a = 2*a - truncated_bits(n*a*a)
        ///write_to.Interate(*this, precision);
    }
    ///cout << res.alloc_size << endl;



    return res;
}

/**
мНБЮЪ ХДЕЪ

(number+1) * Reciprocal(1+ extra digit, rounded down) - 1
мЮОПХЛЕП:
1) 7 / 4 -> 8 * 25 - 1 -> 199 -> 1
*/
BigUnsigned DivisionWithKnownReciprocal(const BigUnsigned& number, const BigUnsigned& Reciprocal, const int shift){
    BigUnsigned res;
    res.alloc_with_zeros(number.real_size * 2 + 1);


    /// йНОХЪ МСФМЮ МЕ БЯЕЦДЮ, ЛНФМН ЯДЕКЮРЭ ДКЪ ЩРНЦН ДЕРЕЙР
    BigUnsigned copy;
    copy.assign_from_BU(number.real_size + 1, number);

    mult(copy._digits, Reciprocal._digits + (Reciprocal.alloc_size - number.real_size - 1), res._digits, number.real_size + 1);
    ///print(res._digits,res.alloc_size);
    res.real_size = res.alloc_size;
    ///print(res._digits,res.alloc_size);
    ///res += Reciprocal
    for(int i = 0;i< number.real_size + 1; ++i){
        res._digits[i] += Reciprocal._digits[(Reciprocal.alloc_size - number.real_size - 1) + i];
        if (res._digits[i] >= BASE){
            res._digits[i] -= BASE;
            ++res._digits[i+1];
        }
    }

    /// уНВЕРЯЪ, РН, ВРН МХФЕ ЯДЕКЮРЭ ДКЪ ТКЕЙЯЮ, МН РЮЙ РНФЕ +- МХВЕЦН
    CONT_TYPE *p = &res._digits[number.real_size + 1];
    while (*p >= BASE){
        *p -= BASE;
        ++p;
        ++(*p);
    }

    /// оЕПЕОНКМЕМХЪ real_size ХКХ alloc_size ОПНХГНИРХ МЕ ЛНФЕР, РЮЙ ВРН БЯ╦ НЙ



    ///
    ///print(res._digits,res.alloc_size);
    --res;
    ///print(res._digits,res.alloc_size);
    res._digits += (number.real_size + shift);

    res.real_size = (res.alloc_size -= (number.real_size + shift));
    res._remove_leading_zeros();

    return res;
}



/**

BigUnsigned DivisionWithKnownReciprocal(const BigUnsigned& number, const BigUnsigned& Reciprocal, BigUnsigned& div, const int shift){
    BigUnsigned res;
    res.alloc_with_zeros(number.real_size + Reciprocal.real_size);

    mult(number._digits, Reciprocal._digits + (Reciprocal.alloc_size - number.real_size), res._digits, number.real_size);

    ///cout << number << endl << Reciprocal << endl;


    res._digits += shift;

    res.real_size = (res.alloc_size -= shift);
    res._remove_leading_zeros();




    BigUnsigned m = karatsuba(res,div);
    /// ъ МЕ ОНИЛС ВРН ЩРН ГЮ НАЙСПЕММШЕ ГЮЛНПНВЙХ, МН ЕЯКХ ОХЯЮРЭ
    /// BigUnsigned rem = number, РН НМ БНГЭЛ╦Р ДЮММШЕ МЮОПЪЛСЧ, ХЦМНПХПСЪ ЛНИ НОЕПЮРНП =. мЮБЕПМНЕ С ЩРНЦН ЕЯРЭ ЙПСРНЕ НАЗЪЯМЕМХЕ Я ЮККНЙЮЖХЕИ ОЮЛЪРХ
    /// Х Ъ +- ЩРН ОНМХЛЮЧ, МН БЯ╦ ПЮБМН МЕНАШВМЕМЭЙН


    16.05.2022 - рЕОЕПЭ Ъ ОНМХЛЮЧ Б В╦Л ДЕКН, МН ОНВЕЛС-РН ЕЯКХ Ъ ДНАЮБКЧ йнмярпсйрнп ЙНОХПНБЮМХЪ, РН АСДЕР ОНОЮ...
    рЮЙ ВРН ОНЙЮ МХВЕЦН МЕ ЛЕМЪЧ


    BigUnsigned rem;
    rem = number;
    rem -= m;



    if ( rem >= div){
        ++res;
    }


    return res;
}

*/


/**
    void inline _DivUnrefined( BigInt &divisor, size_t precision, BigInt &write_to)
    {

        divisor.Reciprocal(precision,write_to);
        write_to._mult(*this, write_to);
    }

    void inline _DivInt( BigInt &divisor, BigInt &write_to)
    {

        if ( (data[data.size() - 1] == 0) || (divisor.data.size() > data.size()) ){write_to = 0; return;}
        size_t precision = data.size() + 4;
        _DivUnrefined(divisor,precision,write_to);
        write_to._ShiftR(precision);
        if (write_to.data.size() == 0){
            write_to.data.push_back(0);
        }
    }

    void inline _DivIntRem( BigInt &divisor, BigInt &write_to, BigInt &rem_write_to)
    {
        _DivInt(divisor,write_to);
        rem_write_to = *this;
        BigInt minus_ = write_to;
        minus_._mult(divisor,minus_);
        rem_write_to._subtract(minus_);
    }
    */








#define file_read 0



int main()
{






    int t;
    cin >> t;
    BigUnsigned a,b;
    while(t--){



        cin >> a >> b;

        ///print(r._digits,1<<3);
        cout << karatsuba(a,b) << endl;

    }
    /// 0.2 100 10kx10k





    return 0;
}

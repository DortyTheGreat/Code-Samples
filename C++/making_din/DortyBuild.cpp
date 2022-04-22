/*
---------------------
This File was Build Automatically by DortyBuild v 1.3.
For More Information ask:
Discord: Тесла#9030 
---Original---Code---

//#pragma GCC target ("avx2") /// РіРѕРІРЅРѕ РґР»СЏ РЅРѕСѓС‚Р°
//#pragma GCC optimization ("O3") /// РЅРµРјРЅРѕР¶РєРѕ СѓСЃРєРѕСЂСЏРµС‚ РєР°СЂР°С†СѓР±Сѓ
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

    cin >> a;
    b = a;
    b.real_size -= 100;
    ///cout << a <<endl;
    ///cout << a << " " << b << endl;

    for(int i = 0;i<1000;++i){
        BigUnsigned::x_mul(&a,&a);
        //a._add(b);
    }

    ///cout << x_mul(a,a);


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
//#pragma GCC target ("avx2") /// РіРѕРІРЅРѕ РґР»СЏ РЅРѕСѓС‚Р°
//#pragma GCC optimization ("O3") /// РЅРµРјРЅРѕР¶РєРѕ СѓСЃРєРѕСЂСЏРµС‚ РєР°СЂР°С†СѓР±Сѓ
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

#include <cstdint> ///
#include <cstring> /// для memcpy

#define default_base 10

#define CONT_TYPE unsigned int
#define DOUBLE_CONT_TYPE unsigned long long /// Двойной РАЗМЕР
#define ubi_szt int /// Unsigned Big Int SiZe Type, пока обязан быть знаковым -_-


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


//template <const int def_base = default_base, int BASE = total_base, const int container_stack = cnt_stack>
class BigUnsigned{
private:
    CONT_TYPE* _digits;
    static const unsigned int BASE = total_base;
public:

    ubi_szt real_size; /// РЕАЛЬНАЯ Длинна числа
    ubi_szt alloc_size; /// Для упрощения реализации alloc_size - всегда степень двойка, так можно будет удобно делить массив на две\\четыре равные части.

    BigUnsigned(){}

    /// мемори стафф
    void alloc_with_zeros(const int sz);
    void assign_from_BU(const int alloc_space, const BigUnsigned& bu);

    friend std::ostream& operator << (std::ostream&, const BigUnsigned&);
	friend std::istream& operator >> (std::istream&, BigUnsigned&);

	friend const BigUnsigned operator +(const BigUnsigned&, const BigUnsigned&);
	void operator +=(const BigUnsigned&);

    static BigUnsigned * x_mul( BigUnsigned * a, BigUnsigned * b);

	void operator =(const BigUnsigned&);

	void _add(const BigUnsigned&);
};


#include <algorithm> /// для реверса string

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

// печатает число в поток вывода
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

    reverse(buff.begin(),buff.end());
    os << buff;
	return os;
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

    ubi_szt carret_r_sz = stream_.size();
    bi.real_size = (carret_r_sz+cnt_stack-1)/cnt_stack;
    bi.alloc_with_zeros(next_power_of_two( bi.real_size));

    CONT_TYPE Carret;

    for(ubi_szt i = 0;i<bi.real_size;++i){
        Carret = 0;
        for(ubi_szt j = 0; j < cnt_stack;++j){
            int index = carret_r_sz - (i+1)*cnt_stack + j;
            if (index > -1){
                Carret *= default_base;
                Carret += FromCharToInt(stream_[index]);
            }
        }

        bi._digits[i] = Carret;
    }

    /// мб тут надо регистрировать "лидирующие" нули, но хз

    return in;

}

/*
/// Сложение двух положительных (исключительно контейнеров)
void BigInt::_add(const BigInt& right) {
    size_t extra_size = 1;

    size_t an_sz = right._digits.size();

    if (an_sz > _digits.size()){
        extra_size = an_sz - _digits.size() + 1;
    }

    for(size_t i = 0;i < extra_size; i++){
        _digits.push_back(0);
    }
    /// Заполняем контейнер нулями, чтобы было место под новые возможные числа(aka разряды)

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

/// Обработка вычитания двух положительных чисел (работает, если второе меньше первого)
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
        /// точно переполнение
        return;
    }

    if (right.alloc_size < alloc_size){
        if (_digits[alloc_size - 1] == (BASE-1) ){
            /// Может произойти переполнение
        }
    }


}

/**

Прибавляет второе число к основному. Однако оно обязано помещаться в него.

*/
void BigUnsigned::_add(const BigUnsigned& right) {

    for(int i = 0;i < right.real_size; ++i){
        _digits[i] += right._digits[i];
        if (_digits[i] >= BASE){
            _digits[i] -= BASE;
            ++_digits[i + 1];
        }
    }

    /// Хочется, то, что ниже сделать для флекса, но так тоже +- ничего
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

    /// Это тоже следует улучшить
    real_size = max(real_size, right.real_size);
    if (real_size != alloc_size){
        if (_digits[real_size] != 0){
            ++real_size;
        }
    }


}



/*
/// Верный оператор (с учётом знаков и прочего)
void BigInt::operator-=(BigInt right){

    ///std::cout << *this << " " << right << " "<<(compare(*this,right)) << std::endl;
    bool comp_ = !(compare(*this,right));
    if ( comp_){
        ///std::cout << "second is hisher" << std::endl;
        swap(right,*this);
        _is_negative = !_is_negative;
    }


    if ( (_is_negative == right._is_negative) ^ (comp_) ) {
        // Одинаковы по знаку
        _subtract(right);
    }else{
        // Разные по знаку.
        _add(right);
    }

}
*/





// возвращает копию переданного числа
//const BigInt BigInt::operator +() const {
//	return BigInt(*this);
//}
/*
// возвращает переданное число с другим знаком
const BigInt BigInt::operator -() const {
	BigInt copy(*this);
	copy._is_negative = !copy._is_negative;
	return copy;
}
*/


/**

Складывает и помещает новое число в новое место в памяти (вероятнее всего присваивать его мы захотим через ->)

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


/*
// префиксный инкремент
const BigInt BigInt::operator++() {
	return (*this += 1);
}

// постфиксный инкремент
const BigInt BigInt::operator ++(int) {
	*this += 1;
	return *this - 1;
}

// префиксный декремент
const BigInt BigInt::operator --() {
	return *this -= 1;
}


// постфиксный декремент
const BigInt BigInt::operator --(int) {
	*this -= 1;
	return *this + 1;
}

*/
/*
// вычитает два числа
const BigInt operator -(BigInt left, const BigInt& right) {
	left -= right;
	return left;
}

*/


/**

Оператор полного присваивания (копирования). Дольше, чем ->

Придётся ещё ебаться с нулями, которые могут лежать в памяти(точнее как раз не лежать в памяти)

Есть 2 варианта

1) Всё-таки заполнять нулями
2) Ебаться отдельно во всех других функциях.

*/
void BigUnsigned::operator =(const BigUnsigned& bu){
    if (bu.real_size > alloc_size){
        alloc_size = next_power_of_two(bu.real_size);
        _digits = new CONT_TYPE[alloc_size]; /// new CONT_TYPE[alloc_size]{0} ИЛИ new CONT_TYPE[alloc_size]()
    }
    real_size = bu.real_size;
    memcpy(_digits,bu._digits,sizeof(CONT_TYPE) * real_size);
}

void BigUnsigned::alloc_with_zeros(const int sz){
    alloc_size = sz;
    _digits = new CONT_TYPE[sz]{0};

}

/**

Тоже самое, что и оператор=, но можно указать количество памяти для аллокации

ПЕРЕПИСАТЬ НА МЕМ_СЕТ http://cppstudio.com/post/673/

*/
void BigUnsigned::assign_from_BU(const int alloc_space, const BigUnsigned& bu){
    alloc_with_zeros(alloc_space);
    real_size = bu.real_size;
    memcpy(_digits,bu._digits,real_size * sizeof(CONT_TYPE));
}

/*
int intlog(double base, double x) {
    return (int)(log(x) / log(base));
}

// создает длинное целое число со значением 0
BigInt::BigInt() {
	this->_is_negative = false;
}

// создает длинное целое число из C++-строки
BigInt::BigInt(std::string str) {
	/// to_do
}

// сдвигает все разряды на 1 вправо (домножает на BASE)
void BigInt::_shift_right() {

    /// removed exceptions

	_digits.push_back(_digits[_digits.size() - 1]);
	for (size_t i = _digits.size() - 2; i > 0; --i) _digits[i] = _digits[i - 1];
	_digits[0] = 0;
}

// сдвигает все разряды на 1 вправо (домножает на BASE)
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

// удаляет ведущие нули
void BigInt::_remove_leading_zeros() {
	while (this->_digits.size() > 1 && this->_digits.back() == 0) {
		this->_digits.pop_back();
	}

	if (this->_digits.size() == 1 && this->_digits[0] == 0) this->_is_negative = false;
}

// преобразует число к строке
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

// проверяет, является ли текущее число нечетным
bool BigInt::odd() const {
	if (this->_digits.size() == 0) return false;
	return this->_digits[0] & 1;
}

// проверяет, является ли текущее число четным
bool BigInt::even() const {
	return !this->odd();
}


/// [5,4,3,2,1](12345) (length=3)-> [0,0,0,5,4,3,2,1](12345000)
/// Следует Улучшить. Ужасно плохо реализованно
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




/* Grade school multiplication, ignoring the signs.
 * Returns the absolute value of the product, or NULL if error.
 */
 /// Алгоритм Школьного Умножения (взято с доков Питона -> см. https://hg.python.org/cpython/file/b514339e41ef/Objects/longobject.c#l2694)
 /// Не работает правильно с нулём
BigUnsigned *
BigUnsigned::x_mul( BigUnsigned * a, BigUnsigned * b)
{
    //cout << "HERE" << endl;
    BigUnsigned* z = new BigUnsigned;
    //cout << "HERE" << endl;
    const ubi_szt size_a = a->real_size;
    const ubi_szt size_b = b->real_size;

    static const CONT_TYPE BASE = a->BASE;
    //cout << "HERE" << endl;
    z->alloc_with_zeros(size_a + size_b);
    //cout << "HERE" << endl;

    ubi_szt i;


    ///memset(z->ob_digit, 0, Py_SIZE(z) * sizeof(digit));

    for (i = 0; i < size_a; ++i) {
        DOUBLE_CONT_TYPE carry = 0;
        DOUBLE_CONT_TYPE f = a->_digits[i];
        CONT_TYPE *pz = z->_digits + i;
        CONT_TYPE *pb = b->_digits;
        CONT_TYPE *pbend = b->_digits + size_b;

        /// SIGCHECK ???

        while (pb < pbend) {
            carry += *pz + *pb++ * f;
            *pz++ = (CONT_TYPE)(carry % BASE);
            carry /= BASE;
        }
        if (carry)
            *pz += (CONT_TYPE)(carry % BASE);
    }

    if (z->_digits[z->alloc_size - 1] == 0){
         z->real_size = z->alloc_size - 1;
    }else{
         z->real_size = z->alloc_size;
    }

    return z;
}


/* A helper for Karatsuba multiplication (k_mul).
   Takes a long "n" and an integer "size" representing the place to
   split, and sets low and high such that abs(n) == (high << size) + low,
   viewing the shift as being by digits.  The sign bit is ignored, and
   the return values are >= 0.
   Returns 0 on success, -1 on failure.
*/
/**
/// бла-бла-бла. Питоновцы придумали конечно...
static int
kmul_split(BigUnsigned *n,
           ubi_szt size,
           BigUnsigned **high,
           BigUnsigned **low)
{
    BigUnsigned *hi, *lo;
    ubi_szt size_lo, size_hi;
    const ubi_szt size_n = n.real_size;

    size_lo = MIN(size_n, size);
    size_hi = size_n - size_lo;

    if ((hi = _PyLong_New(size_hi)) == NULL)
        return -1;
    if ((lo = _PyLong_New(size_lo)) == NULL) {
        Py_DECREF(hi);
        return -1;
    }

    memcpy(lo->ob_digit, n->ob_digit, size_lo * sizeof(digit));
    memcpy(hi->ob_digit, n->ob_digit + size_lo, size_hi * sizeof(digit));

    *high = long_normalize(hi);
    *low = long_normalize(lo);
    return 0;
}

*/
///static BigUnsigned *k_lopsided_mul(BigUnsigned *a, BigUnsigned *b);

/* Karatsuba multiplication.  Ignores the input signs, and returns the
 * absolute value of the product (or NULL if error).
 * See Knuth Vol. 2 Chapter 4.3.3 (Pp. 294-295).
 */







#define file_read 1



int main()
{

    #if file_read

    freopen ("input.txt","r",stdin);

    #endif // file_read
     

    BigUnsigned a,b,c;

    cin >> a;
    b = a;
    b.real_size -= 100;
    ///cout << a <<endl;
    ///cout << a << " " << b << endl;

    for(int i = 0;i<1000;++i){
        BigUnsigned::x_mul(&a,&a);
        //a._add(b);
    }

    ///cout << x_mul(a,a);


    //cin >> a;
    //for(int i = 0;i<1000;++i){
    //    c = k_mul(a,a);
    //}

    ///a = k_mul(a,b);

    //a += 1;
    //fout << c << " " << a - b*c;

    return 0;
}





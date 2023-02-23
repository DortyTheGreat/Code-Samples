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

    ///freopen ("million.txt","r",stdin);

    #endif // file_read
    AppBuild();

    BigUnsigned a,b,c;

    cin >> a >> b;
    ///b = a;
    //cout << a <<endl;
    ///cout << a << " " << b << endl;

    ///c.alloc_with_zeros(1000);

    /// 100k memcpy of 100k ints (aka 1 million decimal places) in 5 s
    /// -> 100 allocs in 5 ms
    /// -> 1 alloc in 0.05 ms (INSANELY QUICKLY!)
    for(int i = 0;i<1;++i){

        ///b = a;
        //CONT_TYPE * d = new CONT_TYPE[100000];
        cout << karatsuba(a,b);



        ///x_mul(a,a);

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
#include <cmath>

#include <cstdint> ///
#include <cstring> /// для memcpy
#include <stdio.h>
#include <algorithm> /// для реверса string

#include <vector>
/// REF : http://web.mit.edu/~ecprice/acm/acm08/notebook.html#file12

/// USAGE :
/// v and u - are vector<int>
/// FFT::convolution(v, u);

#include <vector>

#include <cmath>
#include <iostream>



#define int long long


std::ifstream fin("input.txt");
std::ofstream fout("output.txt");



using namespace std;

//#pragma GCC target ("avx2")
//#pragma GCC optimization ("O3")
//#pragma GCC optimization ("unroll-loops")

///#include <bits/stdc++.h>


#define default_base 10

#define CONT_TYPE long long
#define DOUBLE_CONT_TYPE long long /// Двойной РАЗМЕР
#define ubi_szt int /// Unsigned Big Int SiZe Type, пока обязан быть знаковым -_-


#define big_container 1

#if big_container

#define cnt_stack 3 /// 9
#define total_base 1000 /// 1000000000
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

    friend BigUnsigned x_mul(const BigUnsigned& a,const BigUnsigned& b);
    friend BigUnsigned k_mul(const BigUnsigned& left,const BigUnsigned& right);


    /// Карацуба, кстати меняет контейнерный размер чиселок...
    friend BigUnsigned karatsuba(BigUnsigned& left,BigUnsigned& right);

	void operator =(const BigUnsigned&);

	void _add(const BigUnsigned&);
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

    /// Убрать лидирующие нули
    while(buff.back() == '0'){
        buff.pop_back();
    }

    reverse(buff.begin(),buff.end());
    if (buff.empty()){
        buff = "0";
    }
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


/// это для карацубы, не трогать!
/**

А вообще это для перемножение двух чисел одинакойо длинны, но сразу через массивы.

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

    /// число мелкое, умножаем, как обычно
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

Годная Карацуба.
Требует: 2 "блока" памяти равной длины, (длину блока соответсвенно тоже требует), и место в памяти, куда
поместить результат умножения (место должо быть заранее выделено и заполнено нулями)

(вообще он в третий контейнер как бы добавляет числа, так что если надо добавлять то милости прошу, эта Карацуба это по факту и делает)

TO-DO:

1) Сжатие памяти в одну переменную (вместо двух)
2) ...
3) Починить "растущие" размеры
4) починить долгий минус


*/

void mult(const CONT_TYPE *__restrict a, CONT_TYPE *__restrict b, CONT_TYPE *__restrict res, const ubi_szt n) {

    if (n <= KAR_TRESH) {

            /*
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                res[i + j] += a[i] * b[j];
            }
        }
        */

        x_mul(a,b,res,n);


    } else {

        const ubi_szt fh = (n+1) / 2;   // First half Data (take more)
        const ubi_szt sh = (n - fh); // Second half of Data



        /// alignas(align) ???


        CONT_TYPE* first = new CONT_TYPE[fh + 1];

         first[fh] = 0;

        CONT_TYPE* second = new CONT_TYPE[fh + 1]; second[fh] = 0;



        memcpy(first,a,fh * sizeof(CONT_TYPE));
        memcpy(second,b,fh * sizeof(CONT_TYPE));



        /// Сто проц можно ускорить сложение
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
        /// Доп. чек на переволнение последнего контейнера
        if (first[fh - 1] >= BASE){
                first[fh - 1] -= BASE;
                ++first[fh];
            }
        if (second[fh - 1] >= BASE){
            second[fh - 1] -= BASE;
            ++second[fh];
        }


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

        /// Это тоже ужасное вычитание !!
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







        /// Не забыть не только отпимизирвать память, но и размеры



    }


}



/// Пока Карацуба Думает, что у чисел одинаковый размер

/// Не до конца доделано, размер real_size обкуренный -> при умножении на нуль делает Пиво
BigUnsigned karatsuba(BigUnsigned& left, BigUnsigned& right){
    /// Если правый больше -> тогда результат будет меньше требуемого
    if (left.alloc_size < right.real_size){
        CONT_TYPE *remem = left._digits;
        left.alloc_with_zeros(right.real_size);

        memcpy(left._digits, remem, left.real_size * sizeof(CONT_TYPE));
    }


    /// Если левый больше -> входим в неаллокейтед память
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





using namespace std;

#define VI vector<long long>
double PI = acos(0) * 2;

class complex
{
public:
	long double a, b;
	complex() {a = 0.0; b = 0.0;}
	complex(long double na, long double nb) {a = na; b = nb;}
	const complex operator+(const complex &c) const
		{return complex(a + c.a, b + c.b);}
	const complex operator-(const complex &c) const
		{return complex(a - c.a, b - c.b);}
	const complex operator*(const complex &c) const
		{return complex(a*c.a - b*c.b, a*c.b + b*c.a);}
	long double magnitude() {return sqrt(a*a+b*b);}
	void print() {printf("(%.3f %.3f)\n", a, b);}
};

class FFT
{
public:
	vector<complex> data;
	vector<complex> roots;
	VI rev;
	int s, n;

	void setSize(int ns)
	{
		s = ns;
		n = (1 << s);
		int i, j;
		rev = VI(n);
		data = vector<complex> (n);
		roots = vector<complex> (n+1);
		for (i = 0; i < n; i++)
			for (j = 0; j < s; j++)
				if ((i & (1 << j)) != 0)
					rev[i] += (1 << (s-j-1));
		roots[0] = complex(1, 0);
		complex mult = complex(cos(2*PI/n), sin(2*PI/n));
		for (i = 1; i <= n; i++)
			roots[i] = roots[i-1] * mult;
	}

	void bitReverse(vector<complex> &array)
	{
		vector<complex> temp(n);
		int i;
		for (i = 0; i < n; i++)
			temp[i] = array[rev[i]];
		for (i = 0; i < n; i++)
			array[i] = temp[i];
	}

	void transform(bool inverse = false)
	{
		bitReverse(data);
		int i, j, k;
		for (i = 1; i <= s; i++) {
			int m = (1 << i), md2 = m / 2;
			int start = 0, increment = (1 << (s-i));
			if (inverse) {
				start = n;
				increment *= -1;
			}
			complex t, u;
			for (k = 0; k < n; k += m) {
				int index = start;
				for (j = k; j < md2+k; j++) {
					t = roots[index] * data[j+md2];
					index += increment;
					data[j+md2] = data[j] - t;
					data[j] = data[j] + t;
				}
			}
		}
		if (inverse)
			for (i = 0; i < n; i++) {
				data[i].a /= n;
				data[i].b /= n;
			}
	}

	static VI convolution(VI &a, VI &b)
	{
		int alen = a.size(), blen = b.size();
		int resn = alen + blen - 1;	// size of the resulting array
		int s = 0, i;
		while ((1 << s) < resn) s++;	// n = 2^s
		int n = 1 << s;	// round up the the nearest power of two

		FFT pga, pgb;
		pga.setSize(s);	// fill and transform first array
		for (i = 0; i < alen; i++) pga.data[i] = complex(a[i], 0);
		for (i = alen; i < n; i++)	pga.data[i] = complex(0, 0);
		pga.transform();

		pgb.setSize(s);	// fill and transform second array
		for (i = 0; i < blen; i++)	pgb.data[i] = complex(b[i], 0);
		for (i = blen; i < n; i++)	pgb.data[i] = complex(0, 0);
		pgb.transform();

		for (i = 0; i < n; i++)	pga.data[i] = pga.data[i] * pgb.data[i];
		pga.transform(true);	// inverse transform
		VI result = VI (resn);	// round to nearest integer
		for (i = 0; i < resn; i++)	result[i] = (long long) (pga.data[i].a + 0.5);

		int actualSize = resn - 1;	// find proper size of array
		while (result[actualSize] == 0)
			actualSize--;
		if (actualSize < 0) actualSize = 0;
		result.resize(actualSize+1);
		return result;
	}
};




#undef VI

BigUnsigned FFT_mult(const BigUnsigned& one, const BigUnsigned& two){
    vector<long long> one_(one.real_size);
    vector<long long> two_(two.real_size);

    for(int i = 0;i < one.real_size; ++i){
        one_[i] = one._digits[i];
    }

    for(int i = 0;i < two.real_size; ++i){
        two_[i] = two._digits[i];
    }

    vector<long long> res_ = FFT::convolution(one_, two_);
    for(int i = 0; i < res_.size();++i){
        //cout << res_[i] << " ";
    }
    BigUnsigned res;
    res.alloc_with_zeros(res_.size() + 50);
    res.real_size = res_.size() + 50;

    for(int i = 0;i < res_.size(); ++i){

        res._digits[i] += res_[i];
        res._digits[i+1] += res._digits[i]/BASE;
        res._digits[i] %= BASE;



    }

    for(int i = res_.size(); i < res_.size() + 10; ++i){
        res._digits[i+1] += res._digits[i]/BASE;
        res._digits[i] %= BASE;
    }
    return res;

}



signed main()
{
    ios::sync_with_stdio(0); cin.tie(0);

    BigUnsigned a,b,c;
    cin >> a >> b;
    cout << FFT_mult(a,b);


    return 0;
}




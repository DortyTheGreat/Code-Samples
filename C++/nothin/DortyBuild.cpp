/*
---------------------
This File was Build Automatically by DortyBuild v 1.3.
For More Information ask:
Discord: Тесла#9030 
---Original---Code---


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




*/

#include <iostream>
#include <cmath>
using namespace std;

//#pragma GCC target ("avx2")
//#pragma GCC optimization ("O3")
//#pragma GCC optimization ("unroll-loops")

#include <bits/stdc++.h>

#define default_base 10

#define big_container 0

#if big_container

#define container_stack 9 /// 9
#define total_base 1000000000 /// 1000000000
#define sqrt_of_total_base 31622 /// 31622

#else

#define container_stack 1 /// 9
#define total_base 10 /// 1000000000
#define sqrt_of_total_base 3 /// 31622

#endif



class BigInt {


	// внутреннее хранилище числа


	// знак числа
	bool _is_negative;

	void _remove_leading_zeros();
	void _shift_right();
	void _double_shift_right();

public:
    static const int BASE = total_base;
    std::vector<long long> _digits;


    // основание системы счисления (1 000 000 000)



	// класс-исключение, бросаемое при делении на ноль
	class divide_by_zero : public std::exception {  };

	BigInt();
	BigInt(std::string);
	BigInt(signed char);
	BigInt(unsigned char);
	BigInt(signed short);
	BigInt(unsigned short);
	BigInt(signed int);
	BigInt(unsigned int);
	BigInt(signed long);
	BigInt(unsigned long);
	BigInt(signed long long);
	BigInt(unsigned long long);

    friend BigInt handSqrt(const BigInt& n);
    friend BigInt algoSqrt(const BigInt& n);

	friend std::ostream& operator <<(std::ostream&, const BigInt&);
	friend std::istream& operator >>(std::istream&, BigInt&);
	operator std::string() const;

	void _add(const BigInt&);
    void _subtract(const BigInt&);

    void _mult(const int number);
    const friend BigInt operator *(BigInt,const int);
    void operator *=(int);

	const BigInt operator +() const;
	const BigInt operator -() const;
	const BigInt operator ++();
	const BigInt operator ++(int);
	const BigInt operator --();
	const BigInt operator --(int);

	friend short inline compare(const BigInt&, const BigInt&);
	friend bool operator ==(const BigInt&, const BigInt&);
	friend bool operator <(const BigInt&, const BigInt&);
	friend bool operator !=(const BigInt&, const BigInt&);
	friend bool operator <=(const BigInt&, const BigInt&);
	friend bool operator >(const BigInt&, const BigInt&);
	friend bool operator >=(const BigInt&, const BigInt&);

	friend const BigInt operator +(BigInt, const BigInt&);
	void operator +=(const BigInt&);
	friend const BigInt operator -(BigInt, const BigInt&);
	void operator -=(BigInt);
	friend const BigInt operator *(const BigInt&, const BigInt&);
	BigInt& operator *=(const BigInt&);

	friend int g_div(BigInt left, BigInt right);

	friend const BigInt operator /(const BigInt&, const int);
	friend const BigInt operator /(const BigInt&, const BigInt&);


	BigInt& operator /=(const BigInt&);
	friend const BigInt operator %(const BigInt&, const BigInt&);
	BigInt& operator %=(const BigInt&);

	bool odd() const;
	bool even() const;
	const BigInt pow(BigInt) const;
    const int get_real_size() const;

	/// [5,4,3,2,1](12345) (length=3)-> [0,0,0,5,4,3,2,1](12345000)
    /// Следует Улучшить. Ужасно плохо реализованно
    void inline _appendZeros(int);
};





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
    std::vector<long long> v1(length);
    std::vector<long long> tmp = _digits;
    _digits.clear();
    std::merge(v1.begin(), v1.end(), tmp.begin(), tmp.end(), std::back_inserter(_digits));
}

const int BigInt::get_real_size() const{
    return (_digits.size()-1)*container_stack + intlog(default_base,_digits[_digits.size() - 1]) + 1;
}







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
std::ostream& operator <<(std::ostream& os, const BigInt& bi) {
	if ( (bi._digits.size() == 1) && (bi._digits[0] == 0)){
        os << FromIntToChar(0);
        return os;
    }

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
    sz = (sz+container_stack-1)/container_stack; /// /= по ceil
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


/// Обработка сравнения двух положительных чисел (0 => второе больше, 1 => равны, 2 => наше больше)
short inline compare(const BigInt &left, const BigInt &right){
    size_t sz = left._digits.size();
    if (right._digits.size() != sz){
        return (sz > right._digits.size()) << 1;
    }



    for (size_t i = 0;i<sz;i++){
        int p = sz - i - 1;
        if (left._digits[p] != right._digits[p]){
            return (left._digits[p] > right._digits[p]) << 1;
        }
    }

    return 1;
}




// проверяет, является ли левый операнд меньше правого
bool operator <(const BigInt& left, const BigInt& right) {

    if (left._is_negative != right._is_negative){
        return left._is_negative;
    }

	if (left._digits.size() != right._digits.size()){
        return (left._digits.size() < right._digits.size()) ^ (left._is_negative);
    }

    int sz = left._digits.size();

    for (int i = 0;i<sz;i++){
        int p = sz - i - 1;
        if (left._digits[p] != right._digits[p]){
            return (left._digits[p] < right._digits[p]) ^ (left._is_negative);
        }
    }

    // Числа равны
    return 0;
}

// проверяет, является ли левый операнд меньше правого
bool operator ==(const BigInt& left, const BigInt& right) {

    if (left._is_negative != right._is_negative){
        return 0;
    }

	if (left._digits.size() != right._digits.size()){
        return 0;
    }

    int sz = left._digits.size();

    for (int i = 0;i<sz;i++){
        int p = sz - i - 1;
        if (left._digits[p] != right._digits[p]){
            return 0;
        }
    }

    // Числа равны
    return 1;
}

// сравнивает два числа на неравенство
bool operator !=(const BigInt& left, const BigInt& right) {
	return !(left == right);
}

// проверяет, является ли левый операнд меньше либо равен правого
bool operator <=(const BigInt& left, const BigInt& right) {
	return !(right < left);
}

// проверяет, является ли левый операнд больше правого
bool operator >(const BigInt& left, const BigInt& right) {
	return (right < left);
}

// проверяет, является ли левый операнд больше либо равен правого
bool operator >=(const BigInt& left, const BigInt& right) {
	return !(left < right);
}



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

void BigInt::operator +=(const BigInt& right) {
    if (_is_negative == right._is_negative){
        _add(right);
    }else{
        /// Следует наоптимизировать
        _is_negative = !_is_negative;
        *this -= right;
        _is_negative = !_is_negative;
    }
}




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
// складывает два числа
const BigInt operator +(BigInt left, const BigInt& right) {
	left += right;
	return left;
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

// вычитает два числа
const BigInt operator -(BigInt left, const BigInt& right) {
	left -= right;
	return left;
}




/// Обработка умножения числа на маленькое( из-за этой функции контейнер нельзя ставить на оч. высокую базу (1 миллиард - примерно придел для интов) )
void BigInt::_mult(const int number){
    //cout << "Called Simple Mult for " << *this << " " << number << endl;


    if (number == 0){_digits = {0}; return;}


    int sz = _digits.size();
    long long carr;
    int carry = 0;

    for(int i = 0;i < sz; ++i ){
        carr = _digits[i];
        carr *= number;
        carr += carry;
        _digits[i] = carr % BASE;
        carry = carr / BASE;

    }
    if (carry != 0){
        _digits.push_back(carry);
    }

}

// домножает текущее число на указанное
void BigInt::operator *=(int number) {
    _is_negative ^= (number<0);
    number = abs(number);
    _mult(number);
}

const BigInt operator *(BigInt bi, int number){
    bi *= number;
    return bi;
}

// перемножает два числа
const BigInt operator *(const BigInt& left, const BigInt& right) {
    //cout << "called y" << endl;
	BigInt result;
	result._digits.resize(left._digits.size() + right._digits.size());
	for (size_t i = 0; i < left._digits.size(); ++i) {
		int carry = 0;
		for (size_t j = 0; j < right._digits.size() || carry != 0; ++j) {
			long long cur = result._digits[i + j] +
				left._digits[i] * 1LL * (j < right._digits.size() ? right._digits[j] : 0) + carry;
			result._digits[i + j] = static_cast<int>(cur % left.BASE);
			carry = static_cast<int>(cur / left.BASE);
		}
	}

	result._is_negative = left._is_negative != right._is_negative;
	result._remove_leading_zeros();
	return result;
}

// домножает текущее число на указанное
BigInt& BigInt::operator *=(const BigInt& value) {
	return *this = (*this * value);
}





const BigInt operator /(const BigInt& left, const int digit_){

    BigInt ret;
    ret._digits.clear();

    long long Carret = 0;
    int sz = left._digits.size() - 1;
    for(int i = sz;i > -1; --i){
        Carret *= left.BASE;
        Carret +=  left._digits[i];
        ret._digits.push_back(Carret / digit_);
        Carret %= digit_;
    }



    reverse(ret._digits.begin(),ret._digits.end());

    ret._remove_leading_zeros();

    return ret;
}
/// guessable division
/// "путём угадывания",
/// left будет доделено, return вернёт результат
int g_div(BigInt left, BigInt right){
    right._is_negative = false;
    const int b_sz = right._digits.size();
    if (b_sz == 1){left = left / right._digits[0]; return left._digits[0];} /// т.к. g div гарантирует возврат контейнерного числа, то можно возвращать [0], ибо так мы всегда гарантируем данное

    int curr_sz = left._digits.size();
    if (curr_sz < b_sz){
        /// x = 0 -> current = current - b * x; -> current -= 0 -> current не меняется
        ///std::cout << "free itteration : " << std::endl;
        return 0;
    }

    int x;
    long long tfb = right._digits.back();
    tfb *= left.BASE;
    tfb += right._digits[b_sz - 2];

    long long two_from_left = left._digits.back();
    two_from_left *= left.BASE;
    two_from_left += left._digits[curr_sz - 2];



    if (curr_sz == b_sz){
        x = (two_from_left/tfb);
    }else{
        /// тут надо применить хитрость, ибо в таком случае надо делить
        /// (два_числа_из_куррент*Base) / два_числа_из_б
        /// однако три числа не поменщаются в long long, при максимальном пакинге...
        /// приходится "хитрить" и делать "псевдо-длинку" на лишние биты
        long double d = two_from_left;
        d *= left.BASE;
        d /= tfb;
        x = d;
    }

    left -= right*x;
    if (left._is_negative){
        left += right;
        return (x - 1);
    }

    if (left >= right){
        left -= right;
        return (x + 1);
    }
    return x;

}


// делит два числа
const BigInt operator /(const BigInt& left, const BigInt& right) {
    ///std::cout << "Called div" << std::endl;
	if (right == 0) throw BigInt::divide_by_zero();
	const int b_sz = right._digits.size();
    if (b_sz == 1){return left / right._digits[0];}

	BigInt b = right;


	b._is_negative = false;
	BigInt result, current;
	result._digits.resize(left._digits.size());
    result._is_negative = left._is_negative != right._is_negative;

    /// b = 45678, two_from_b = 45
    long long tfb = b._digits.back();
    tfb *= left.BASE;
    tfb += b._digits[b_sz - 2];

    const long long two_from_b = tfb;

	int x,curr_sz;

	for (long long i = static_cast<long long>(left._digits.size()) - 1; i >= 0; --i) {
		current._shift_right();
		current._digits[0] = left._digits[i];
		current._remove_leading_zeros();

        curr_sz = current._digits.size();

        if (curr_sz < b_sz){
            /// x = 0 -> current = current - b * x; -> current -= 0 -> current не меняется
            ///std::cout << "free itteration : " << std::endl;
            result._digits[i] = 0;
            continue;
        }

        /// curr.size >= b.size
        /// b_sz != 1 (т.к. выше было это исключено)


        /// current = 123456, two_from_current = 12
		long long two_from_current = current._digits.back();
		two_from_current *= left.BASE;
		two_from_current += current._digits[curr_sz - 2];



		if (curr_sz == b_sz){
            x = (two_from_current/two_from_b);
		}else{
            /// тут надо применить хитрость, ибо в таком случае надо делить
            /// (два_числа_из_куррент*Base) / два_числа_из_б
            /// однако три числа не поменщаются в long long, при максимальном пакинге...
            /// приходится "хитрить" и делать "псевдо-длинку" на лишние биты
            long double d = two_from_current;
            d *= left.BASE;
            d /= two_from_b;
            x = d;
		}


		current -= b*x;
		if (current._is_negative){
            current += b;
            result._digits[i] = x - 1;
            continue;
		}

		if (current >= b){
            current -= b;
            result._digits[i] = x + 1;
            continue;
		}
		result._digits[i] = x;
	}


	result._remove_leading_zeros();
	return result;
}

// делит текущее число на указанное
BigInt& BigInt::operator /=(const BigInt& value) {
	return *this = (*this / value);
}





BigInt factorial(int num){
    BigInt ret = 1;
    for(int mul = 1; mul <= num;++mul){
        ret._mult(mul);
    }
    return ret;
}

// возводит текущее число в указанную степень
const BigInt BigInt::pow(BigInt n) const {
	BigInt a(*this), result(1);
	while (n != 0) {
		if (n.odd()) result *= a;
		a *= a;
		n /= 2;
	}

	return result;
}



long long  intSqrt(long long arg){
    return (long long)(sqrt(arg));
}





// возвращает остаток от деления двух чисел
const BigInt operator %(const BigInt& left, const BigInt& right) {
	BigInt result = left - (left / right) * right;
	if (result._is_negative) result += right;
	return result;
}

// присваивает текущему числу остаток от деления на другое число
BigInt& BigInt::operator %=(const BigInt& value) {
	return *this = (*this % value);
}


/**
* Надо ещё написать "ручной" алгоритм корня. с O(n^2)
* Сложность O(n^2 * log(n))
* Примерная скорость выполнения -> log(n) * Скорость(Деления Двух Длинных)
* Алгоритм Вавилонский(Герона) - обобщённый Ньютон.
* Краткое пояснение: т.к. среднее арифметическое приближенно равно среднему геометрическому -> sqrt(n) = sqrt( x * (n / x) ) ~= (x + (n/x))/2
* Достаточно примерно log2(n) итераций для сходимости к целочисленному ответу.
* @author Dorty_Schmorty
* @return целочисленный длинный корень целочисленного длинного числа
*
*/
BigInt sqrt(BigInt n) {

    int sz = n._digits.size();

    if (sz == 1){return BigInt(intSqrt(n._digits[sz-1]));}
    long long a = n._digits[sz-1];
    a *= n.BASE;
    a += n._digits[sz-2];

    BigInt x(intSqrt(a));

    x._mult( (((sz-1)%2) ? 1 : sqrt_of_total_base) );
    x._appendZeros((sz) / 2 - 1);

    /// Хз, от чего это константа зависит, следует подумать
    int end_ = (int)(log2(sz)) + 1;


    for (int i = 0;i<end_;++i) {
        x = (x + n / x) / 2;
    }

    /// В некоторых случаях, если число - это на 1 меньше, чем полный квадрат, то ответом будет число на один больше
    /// Например 24 -> 5, 48 -> 7, 35 -> 6
    /// safe_sqrt избегает этого
    BigInt sv = (x + n / x) / 2;
    if (sv != x){return min(x,sv);}

    return x;
}


BigInt handSqrt(const BigInt& n){
    BigInt ret;
    int prefix = 2;
    int sz = n._digits.size();

    int Carret = n._digits.back();


    if (sz % 2 == 0){
        Carret *= n.BASE;
        Carret += n._digits[sz - 2];
        prefix++;
    }

    ret._digits.resize(1 + (sz - prefix + 1)/2);

    int curDigit = intSqrt(Carret);
    cout << "iSQRT : " << curDigit << endl;
    ret._digits.back() = curDigit;
    Carret = Carret - curDigit*curDigit;


    cout << "Carret : "<< Carret << endl;
    /// A = two_first_digits - ret*currDigit
    BigInt A = Carret;


    for (int i = sz-prefix;i>=0;i-=2)
    {
        A._double_shift_right();
        A._digits[0] = n._digits[i - 1];
        A._digits[1] = n._digits[i];

        Carret *= n.BASE;
        Carret += n._digits[i];

        Carret *= n.BASE;
        Carret += n._digits[i - 1];

        /// curDigit = A/a      intSqrt()

        /*
        cout << "Carret : "<< Carret << endl;
        ret._digits[i / 2] = iSqrt_;
        cout << "i : " << i/2 << endl;
        Carret -= iSqrt_*iSqrt_;
        cout << "Carret : "<< Carret << endl;

        A -= a * curDigit;
        */
    }

    return ret;
}


BigInt algoSqrt(const BigInt& n){
    BigInt ret;
    int prefix = 2;
    int sz = n._digits.size();

    int Carret = n._digits.back();


    if (sz % 2 == 0){
        Carret *= n.BASE;
        Carret += n._digits[sz - 2];
        prefix++;
    }

    ///ret._digits.resize(1 + (sz - prefix + 1)/2);

    int curDigit = intSqrt(Carret);
    cout << "iSQRT : " << curDigit << endl;
    ///ret._digits.back() = curDigit;

    ret = curDigit;

    Carret = Carret - curDigit*curDigit;


    cout << "Carret : "<< Carret << endl;
    /// A = two_first_digits - ret*currDigit
    BigInt A = Carret, a;

    for (int i = sz-prefix;i>=0;i-=2)
    {

        cout << "i : " << i << endl;

        A._double_shift_right();

        A._digits[0] = n._digits[i - 1];
        A._digits[1] = n._digits[i];
        cout <<"ABef : " <<A << endl;

        a = ret * 2;


        cout << A << " " << a << endl;

        curDigit = sqrt(A / a)._digits[0]; ///(g. div)

        cout << curDigit << endl;

        ret._shift_right();
        ret._digits[0] = curDigit;

        a._shift_right();
        a._digits[0] = curDigit;
        cout << "A1 " << A << endl;
        A -= a*curDigit;
        cout << "A2 " << A << endl;
    }
    return ret;
}





#include <fstream>



int main()
{

    ifstream fin("input.txt");
	ofstream fout("output.txt");
     
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





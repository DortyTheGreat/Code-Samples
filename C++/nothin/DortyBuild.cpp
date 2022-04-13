/*
---------------------
This File was Build Automatically by DortyBuild v 1.3.
For More Information ask:
Discord: Тесла#9030 
---Original---Code---


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




*/

#include <iostream>

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

#include <bits/stdc++.h>

#define default_base 10

#define container_stack 9 /// 6

#define total_base 1000000000 /// 1000000

#define sqrt_of_total_base 10000 /// 1000

class BigInt {


	// внутреннее хранилище числа

    std::vector<int> _digits;
	// знак числа
	bool _is_negative;

	void _remove_leading_zeros();
	void _shift_right();
    static const int BASE = 1000000000;
public:



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

	friend std::ostream& operator <<(std::ostream&, const BigInt&);
	friend std::istream& operator >>(std::istream&, BigInt&);
	operator std::string() const;
	const BigInt operator +() const;
	const BigInt operator -() const;
	const BigInt operator ++();
	const BigInt operator ++(int);
	const BigInt operator --();
	const BigInt operator --(int);
	friend bool operator ==(const BigInt&, const BigInt&);
	friend bool operator <(const BigInt&, const BigInt&);
	friend bool operator !=(const BigInt&, const BigInt&);
	friend bool operator <=(const BigInt&, const BigInt&);
	friend bool operator >(const BigInt&, const BigInt&);
	friend bool operator >=(const BigInt&, const BigInt&);
	friend const BigInt operator +(BigInt, const BigInt&);
	BigInt& operator +=(const BigInt&);
	friend const BigInt operator -(BigInt, const BigInt&);
	BigInt& operator -=(const BigInt&);
	friend const BigInt operator *(const BigInt&, const BigInt&);
	BigInt& operator *=(const BigInt&);
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

int intlog(double base, double x) {
    return (int)(log(x) / log(base));
}
/// 9 223 372 036 854 775 807
/// 2147483647
const int INT_MAXI = 9223372036854775807;

int inline intSqrt(int arg){
    return (int)(sqrt(arg));
}


// создает длинное целое число со значением 0
BigInt::BigInt() {
	this->_is_negative = false;
}

// создает длинное целое число из C++-строки
BigInt::BigInt(std::string str) {
	if (str.length() == 0) {
		this->_is_negative = false;
	}
	else {
		if (str[0] == '-') {
			str = str.substr(1);
			this->_is_negative = true;
		}
		else {
			this->_is_negative = false;
		}

		for (long long i = str.length(); i > 0; i -= 9) {
			if (i < 9)
				this->_digits.push_back(atoi(str.substr(0, i).c_str()));
			else
				this->_digits.push_back(atoi(str.substr(i - 9, 9).c_str()));
		}

		this->_remove_leading_zeros();
	}
}

// удаляет ведущие нули
void BigInt::_remove_leading_zeros() {
	while (this->_digits.size() > 1 && this->_digits.back() == 0) {
		this->_digits.pop_back();
	}

	if (this->_digits.size() == 1 && this->_digits[0] == 0) this->_is_negative = false;
}



// сравнивает два числа на равенство
bool operator ==(const BigInt& left, const BigInt& right) {
	if (left._is_negative != right._is_negative) return false;
	if (left._digits.empty()) {
		if (right._digits.empty() || (right._digits.size() == 1 && right._digits[0] == 0)) return true;
		else return false;
	}

	if (right._digits.empty()) {
		if (left._digits.size() == 1 && left._digits[0] == 0) return true;
		else return false;
	}

	if (left._digits.size() != right._digits.size()) return false;
	for (size_t i = 0; i < left._digits.size(); ++i) if (left._digits[i] != right._digits[i]) return false;

	return true;
}

// возвращает копию переданного числа
const BigInt BigInt::operator +() const {
	return BigInt(*this);
}

// возвращает переданное число с другим знаком
const BigInt BigInt::operator -() const {
	BigInt copy(*this);
	copy._is_negative = !copy._is_negative;
	return copy;
}

// проверяет, является ли левый операнд меньше правого
bool operator <(const BigInt& left, const BigInt& right) {
	if (left == right) return false;
	if (left._is_negative) {
		if (right._is_negative) return ((-right) < (-left));
		else return true;
	}
	else if (right._is_negative) return false;
	else {
		if (left._digits.size() != right._digits.size()) {
			return left._digits.size() < right._digits.size();
		}
		else {
			for (long long i = left._digits.size() - 1; i >= 0; --i) {
				if (left._digits[i] != right._digits[i]) return left._digits[i] < right._digits[i];
			}

			return false;
		}
	}
}

// сравнивает два числа на неравенство
bool operator !=(const BigInt& left, const BigInt& right) {
	return !(left == right);
}

// проверяет, является ли левый операнд меньше либо равен правого
bool operator <=(const BigInt& left, const BigInt& right) {
	return (left < right || left == right);
}

// проверяет, является ли левый операнд больше правого
bool operator >(const BigInt& left, const BigInt& right) {
	return !(left <= right);
}

// проверяет, является ли левый операнд больше либо равен правого
bool operator >=(const BigInt& left, const BigInt& right) {
	return !(left < right);
}

// складывает два числа
const BigInt operator +(BigInt left, const BigInt& right) {
	if (left._is_negative) {
		if (right._is_negative) return -(-left + (-right));
		else return right - (-left);
	}
	else if (right._is_negative) return left - (-right);
	int carry = 0;
	for (size_t i = 0; i < std::max(left._digits.size(), right._digits.size()) || carry != 0; ++i) {
		if (i == left._digits.size()) left._digits.push_back(0);
		left._digits[i] += carry + (i < right._digits.size() ? right._digits[i] : 0);
		carry = left._digits[i] >= left.BASE;
		if (carry != 0) left._digits[i] -= left.BASE;
	}

	return left;
}

// прибавляет к текущему числу новое
BigInt& BigInt::operator +=(const BigInt& value) {
	return *this = (*this + value);
}

// префиксный инкремент
const BigInt BigInt::operator++() {
	return (*this += 1);
}

// преобразует число к строке
BigInt::operator std::string() const {
	std::stringstream ss;
	ss << *this;
	return ss.str();
}

// преобразует signed char к BigInt
BigInt::BigInt(signed char c) {
	if (c < 0) this->_is_negative = true;
	else this->_is_negative = false;
	this->_digits.push_back(std::abs(c));
}

// преобразует unsigned char к BigInt
BigInt::BigInt(unsigned char c) {
	this->_is_negative = false;
	this->_digits.push_back(c);
}

// преобразует signed short к BigInt
BigInt::BigInt(signed short s) {
	if (s < 0) this->_is_negative = true;
	else this->_is_negative = false;
	this->_digits.push_back(std::abs(s));
}

// преобразует unsigned short к BigInt
BigInt::BigInt(unsigned short s) {
	this->_is_negative = false;
	this->_digits.push_back(s);
}

// преобразует signed int к BigInt
BigInt::BigInt(signed int i) {
	if (i < 0) this->_is_negative = true;
	else this->_is_negative = false;
	this->_digits.push_back(std::abs(i) % BASE);
	i /=    BASE;
	if (i != 0) this->_digits.push_back(std::abs(i));
}

// преобразует unsigned int к BigInt
BigInt::BigInt(unsigned int i) {
	this->_digits.push_back(i % BASE);
	i /= BASE;
	if (i != 0) this->_digits.push_back(i);
}

// преобразует signed long к BigInt
BigInt::BigInt(signed long l) {
	if (l < 0) this->_is_negative = true;
	else this->_is_negative = false;
	this->_digits.push_back(std::abs(l) % BASE);
	l /= BASE;
	if (l != 0) this->_digits.push_back(std::abs(l));
}

// преобразует unsigned long к BigInt
BigInt::BigInt(unsigned long l) {
	this->_digits.push_back(l % BASE);
	l /= BASE;
	if (l != 0) this->_digits.push_back(l);
}

// преобразует signed long long к BigInt
BigInt::BigInt(signed long long l) {
	if (l < 0) { this->_is_negative = true; l = -l; }
	else this->_is_negative = false;
	do {
		this->_digits.push_back(l % BASE);
		l /= BASE;
	} while (l != 0);
}

// преобразует unsigned long long к BigInt
BigInt::BigInt(unsigned long long l) {
	this->_is_negative = false;
	do {
		this->_digits.push_back(l % BASE);
		l /= BASE;
	} while (l != 0);
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

// вычитает два числа
const BigInt operator -(BigInt left, const BigInt& right) {
	if (right._is_negative) return left + (-right);
	else if (left._is_negative) return -(-left + right);
	else if (left < right) return -(right - left);
	int carry = 0;
	for (size_t i = 0; i < right._digits.size() || carry != 0; ++i) {
		left._digits[i] -= carry + (i < right._digits.size() ? right._digits[i] : 0);
		carry = left._digits[i] < 0;
		if (carry != 0) left._digits[i] += left.BASE;
	}

	left._remove_leading_zeros();
	return left;
}

// вычитает из текущего числа новое
BigInt& BigInt::operator -=(const BigInt& value) {
	return *this = (*this - value);
}

// перемножает два числа
const BigInt operator *(const BigInt& left, const BigInt& right) {
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

// сдвигает все разряды на 1 вправо (домножает на BASE)
void BigInt::_shift_right() {
	if (this->_digits.size() == 0) {
		this->_digits.push_back(0);
		return;
	}
	this->_digits.push_back(this->_digits[this->_digits.size() - 1]);
	for (size_t i = this->_digits.size() - 2; i > 0; --i) this->_digits[i] = this->_digits[i - 1];
	this->_digits[0] = 0;
}

// делит два числа
const BigInt operator /(const BigInt& left, const BigInt& right) {
	if (right == 0) throw BigInt::divide_by_zero();
	BigInt b = right;
	b._is_negative = false;
	BigInt result, current;
	result._digits.resize(left._digits.size());
	for (long long i = static_cast<long long>(left._digits.size()) - 1; i >= 0; --i) {
		current._shift_right();
		current._digits[0] = left._digits[i];
		current._remove_leading_zeros();
		int x = 0, l = 0, r = left.BASE;
		while (l <= r) {
			int m = (l + r) / 2;
			BigInt t = b * m;
			if (t <= current) {
				x = m;
				l = m + 1;
			}
			else r = m - 1;
		}

		result._digits[i] = x;
		current = current - b * x;
	}

	result._is_negative = left._is_negative != right._is_negative;
	result._remove_leading_zeros();
	return result;
}

// делит текущее число на указанное
BigInt& BigInt::operator /=(const BigInt& value) {
	return *this = (*this / value);
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

// проверяет, является ли текущее число нечетным
bool BigInt::odd() const {
	if (this->_digits.size() == 0) return false;
	return this->_digits[0] & 1;
}

// проверяет, является ли текущее число четным
bool BigInt::even() const {
	return !this->odd();
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

// печатает число в поток вывода
std::ostream& operator <<(std::ostream& os, const BigInt& bi) {
	if (bi._digits.empty()) os << 0;
	else {
		if (bi._is_negative) os << '-';
		os << bi._digits.back();
		char old_fill = os.fill('0');
		for (long long i = static_cast<long long>(bi._digits.size()) - 2; i >= 0; --i) os << std::setw(9) << bi._digits[i];
		os.fill(old_fill);
	}

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

/// [5,4,3,2,1](12345) (length=3)-> [0,0,0,5,4,3,2,1](12345000)
/// Следует Улучшить. Ужасно плохо реализованно
void inline BigInt::_appendZeros(int length){
    std::vector<int> v1(length);
    std::vector<int> tmp = _digits;
    _digits.clear();
    std::merge(v1.begin(), v1.end(), tmp.begin(), tmp.end(), std::back_inserter(_digits));
}

const int BigInt::get_real_size() const{
    return (_digits.size()-1)*container_stack + intlog(default_base,_digits[_digits.size() - 1]) + 1;
}




using namespace std;

const BigInt eps = BigInt(1);



string a,b;
BigInt sqrt(BigInt n) {


    BigInt x;
    int rsz = n.get_real_size();
    /*
    //cout << sz <<" rsz : " << rsz << endl;
    x._digits.clear();

    x._digits.push_back (intSqrt(n._digits[sz-1]) * ((sz%2) ? 1 : sqrt_of_total_base) );


    x._appendZeros((sz - 1) / 2 );
    */
    x = 10;
    x = x.pow(rsz / 2 + 1);
  BigInt last = 0;
  int iter = 0;

  //cout << last << endl << x << endl << endl;

  while (last != x) {
    last = x;
    x = (x + n / x) / 2;
    //cout << last << endl << x << endl << endl;
    ++iter;
  }
  cout << iter << endl;
  return x;
}
/*
int main() {
	ifstream fin;
	ofstream fout;
	fin.open("input.txt");
	fin >> a >> b;

	BigInt n1(a), n2(b);

	fout.open("output.txt");

    BigInt ans = n1/n2;
    BigInt an2 = n1 % n2;
    fout << ans << endl << an2;

ending:
	cout << endl;

	return 0;
}
*/




#include <fstream>

using namespace std;

int main()
{
     
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





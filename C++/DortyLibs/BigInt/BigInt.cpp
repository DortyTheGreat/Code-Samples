
#include "core.cpp" /// примитивнейшие операции
#include "io.cpp" /// ввод-вывод

#include "compare.cpp"
#include "add.cpp"

#include "exponential.cpp"


long long  intSqrt(long long arg){
    return (long long)(sqrt(arg));
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

// сдвигает все разр€ды на 1 вправо (домножает на BASE)
void BigInt::_shift_right() {
	if (this->_digits.size() == 0) {
		this->_digits.push_back(0);
		return;
	}
	this->_digits.push_back(this->_digits[this->_digits.size() - 1]);
	for (size_t i = this->_digits.size() - 2; i > 0; --i) this->_digits[i] = this->_digits[i - 1];
	this->_digits[0] = 0;
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
            /// x = 0 -> current = current - b * x; -> current -= 0 -> current не мен€етс€
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
            /// однако три числа не поменщаютс€ в long long, при максимальном пакинге...
            /// приходитс€ "хитрить" и делать "псевдо-длинку" на лишние биты
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

// возвращает остаток от делени€ двух чисел
const BigInt operator %(const BigInt& left, const BigInt& right) {
	BigInt result = left - (left / right) * right;
	if (result._is_negative) result += right;
	return result;
}

// присваивает текущему числу остаток от делени€ на другое число
BigInt& BigInt::operator %=(const BigInt& value) {
	return *this = (*this % value);
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

BigInt sqrt(BigInt n) {

    int sz = n._digits.size();

    if (sz == 1){return BigInt(intSqrt(n._digits[sz-1]));}
    long long a = n._digits[sz-1];
    a *= n.BASE;
    a += n._digits[sz-2];

    BigInt x(intSqrt(a));

    const int m = (((sz-1)%2) ? 1 : sqrt_of_total_base);

    x._mult( m); /// € хз почему € не могу использовать “”“ _mult, он ломаетс€ не на этой строчке, а дальше... ’от€ переменна€ та же
    /// «.џ. ¬сЄ починил, была прикольна€ проблема в переполнении))



    x._appendZeros((sz) / 2 - 1);


    int end_ = (int)(log2(sz)) + 1;


    for (int i = 0;i<end_;++i) {
        x = (x + n / x) / 2;
    }

    /// ¬ некоторых случа€х, если число - это на 1 меньше, чем полный квадрат, то ответом будет число на один больше
    /// Ќапример 24 -> 5, 48 -> 7, 35 -> 6
    /// safe_sqrt избегает этого
    BigInt sv = (x + n / x) / 2;
    if (sv != x){return min(x,sv);}

    return x;
}





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
//const int INT_MAXI = 9223372036854775807;

long long intSqrt(long long arg){
    return (long long)(sqrt(arg));
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

BigInt::BigInt(long long num){
    _is_negative = (num < 0);
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
    while(num != 0){
        _digits.push_back(num % BASE);
        num /= BASE;
    }

    if (_digits.size() == 0){
        _digits.push_back(0);
    }
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
	int b_sz = right._digits.size();
    if (b_sz == 1){return left / right._digits[0];}

	BigInt b = right;


	b._is_negative = false;
	BigInt result, current;
	result._digits.resize(left._digits.size());

	int x;

	for (long long i = static_cast<long long>(left._digits.size()) - 1; i >= 0; --i) {
		current._shift_right();
		current._digits[0] = left._digits[i];
		current._remove_leading_zeros();

        int curr_sz = current._digits.size();

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


        /// b = 45678, two_from_b = 45
		long long two_from_b = b._digits.back();
		two_from_b *= left.BASE;
		two_from_b += b._digits[b_sz - 2];


        //cout << two_from_current << endl << two_from_b;


		if (curr_sz == b_sz){
            /// check x, x-1, x+1
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



        ///std::cout << current <<" : " << b << std::endl;
        ///std::cout << "X found " << x << std::endl;

		int l = x - 1, r = x + 1;
		int itteration = 0;
		while (l <= r) {
            ++itteration;
			int m = (l + r) / 2;
			BigInt t = b * m;

			///std::cout << t <<" " << current <<" " << m << " " << b << std::endl;

			if (t <= current) {
				x = m;
				l = m + 1;
			}
			else r = m - 1;
		}

		///std::cout << "X after " << x << std::endl;

		///std::cout << "IT : " << itteration << std::endl;
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
    std::cout << "called sqrt" << std::endl;




    int sz = n._digits.size();

    if (sz == 1){return BigInt(intSqrt(n._digits[sz-1]));}

    BigInt x(intSqrt(n._digits[sz-1]*n.BASE +  n._digits[sz-2]));

    x *= (((sz-1)%2) ? 1 : sqrt_of_total_base);

    x._appendZeros((sz) / 2 - 1);

    ///std::cout << "Initial Guess : " << x << std::endl;

    int end{  (int)(log2(sz)) + 6 };

    //x = 10;
    //x = x.pow(rsz / 2 + 1);

  int iter = 0;

  //cout << last << endl << x << endl << endl;

  for (int i = 0;i<end;++i) {

    ///cout << endl<<n << " " << x << " "<<n/x << endl;

    x = (x + n / x) / 2;

    ++iter;
  }
  ///cout << iter << endl;


    /// В некоторых случаях, если число - это на 1 меньше, чем полный квадрат, то ответом будет число на один больше
    /// Например 24 -> 5, 48 -> 7, 35 -> 6
    /// safe_sqrt избегает этого

    BigInt sq_test = x*x;
    if ( sq_test > n){
        ///std::cout <<"new " << sq_test << " " << x << " "<< n <<  std::endl;
        --x;
    }


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

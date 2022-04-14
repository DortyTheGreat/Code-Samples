
#include "core.cpp" /// �������������� ��������
#include "io.cpp" /// ����-�����

#include "compare.cpp"
#include "add.cpp"


long long  intSqrt(long long arg){
    return (long long)(sqrt(arg));
}


// ����������� ��� �����
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

// ��������� ������� ����� �� ���������
BigInt& BigInt::operator *=(const BigInt& value) {
	return *this = (*this * value);
}

// �������� ��� ������� �� 1 ������ (��������� �� BASE)
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

// ����� ��� �����
const BigInt operator /(const BigInt& left, const BigInt& right) {
    ///std::cout << "Called div" << std::endl;
	if (right == 0) throw BigInt::divide_by_zero();
	int b_sz = right._digits.size();
    if (b_sz == 1){return left / right._digits[0];}

	BigInt b = right;


	b._is_negative = false;
	BigInt result, current;
	result._digits.resize(left._digits.size());

    /// b = 45678, two_from_b = 45
    long long two_from_b = b._digits.back();
    two_from_b *= left.BASE;
    two_from_b += b._digits[b_sz - 2];

	int x;

	for (long long i = static_cast<long long>(left._digits.size()) - 1; i >= 0; --i) {
		current._shift_right();
		current._digits[0] = left._digits[i];
		current._remove_leading_zeros();

        int curr_sz = current._digits.size();

        if (curr_sz < b_sz){
            /// x = 0 -> current = current - b * x; -> current -= 0 -> current �� ��������
            ///std::cout << "free itteration : " << std::endl;
            result._digits[i] = 0;
            continue;
        }

        /// curr.size >= b.size
        /// b_sz != 1 (�.�. ���� ���� ��� ���������)


        /// current = 123456, two_from_current = 12
		long long two_from_current = current._digits.back();
		two_from_current *= left.BASE;
		two_from_current += current._digits[curr_sz - 2];




        ///cout << "Current : " << current << endl;
        ///cout << two_from_current << endl << two_from_b << endl;


		if (curr_sz == b_sz){
            /// check x, x-1, x+1
            x = (two_from_current/two_from_b);
		}else{
            /// ��� ���� ��������� ��������, ��� � ����� ������ ���� ������
            /// (���_�����_��_�������*Base) / ���_�����_��_�
            /// ������ ��� ����� �� ����������� � long long, ��� ������������ �������...
            /// ���������� "�������" � ������ "������-������" �� ������ ����
            long double d = two_from_current;
            d *= left.BASE;
            d /= two_from_b;
            x = d;
		}

		//std::cout << "guessed x for div : " << x << std::endl;


		/// current -= b*x

		current -= b*x;
		if (current._is_negative){
                //cout << current << " " << b<< endl;
            current += b;
            //cout << "curr is neg -> " << current << endl;
            result._digits[i] = x - 1;
            continue;
		}

		if (current >= b){
            current -= b;
            result._digits[i] = x + 1;
            continue;
		}

		//cout << "after : " << current << endl;

		result._digits[i] = x;



	}

	result._is_negative = left._is_negative != right._is_negative;
	result._remove_leading_zeros();
	return result;
}

// ����� ������� ����� �� ���������
BigInt& BigInt::operator /=(const BigInt& value) {
	return *this = (*this / value);
}

// ���������� ������� �� ������� ���� �����
const BigInt operator %(const BigInt& left, const BigInt& right) {
	BigInt result = left - (left / right) * right;
	if (result._is_negative) result += right;
	return result;
}

// ����������� �������� ����� ������� �� ������� �� ������ �����
BigInt& BigInt::operator %=(const BigInt& value) {
	return *this = (*this % value);
}


// �������� ������� ����� � ��������� �������
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
    //std::cout << "called sqrt" << std::endl;




    int sz = n._digits.size();

    if (sz == 1){return BigInt(intSqrt(n._digits[sz-1]));}
    long long a = n._digits[sz-1];
    a *= n.BASE;
    a += n._digits[sz-2];
    //std::cout << "taking sqrt of" << a <<" "<<  n._digits[sz-2] << std::endl;

    BigInt x(intSqrt(a));

    //std::cout << "Initial Guess : " << x << std::endl;

    x *= (((sz-1)%2) ? 1 : sqrt_of_total_base);

    //std::cout << "Initial Guess : " << x << std::endl;

    x._appendZeros((sz) / 2 - 1);

    //std::cout << "Initial Guess : " << x << std::endl;

    int end{  (int)(log2(sz)) + 5 };

    //x = 10;
    //x = x.pow(rsz / 2 + 1);

  int iter = 0;

  //cout << last << endl << x << endl << endl;

  for (int i = 0;i<end;++i) {

    //cout << endl<<n << " " << x << " "<<n/x << endl;

    x = (x + n / x) / 2;

    ++iter;
  }

  /// � ��������� �������, ���� ����� - ��� �� 1 ������, ��� ������ �������, �� ������� ����� ����� �� ���� ������
    /// �������� 24 -> 5, 48 -> 7, 35 -> 6
    /// safe_sqrt �������� �����
  BigInt sv = (x + n / x) / 2;
  if (sv != x){return min(x,sv);}


  ///cout << iter << endl;







    return x;
}


/// ��������� ��������� ����� �� ���������( ��-�� ���� ������� ��������� ������ ������� �� ��. ������� ���� (1 �������� - �������� ������ ��� �����) )
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

// ��������� ������� ����� �� ���������
void BigInt::operator *=(const int number) {
    _is_negative ^= (number<0);
    _mult(abs(number));
}

const BigInt operator *(BigInt bi, int number){
    bi *= number;
    return bi;
}

// ����������� ��� �����
const BigInt operator *(const BigInt& left, const BigInt& right) {
    //cout << "called y" << endl;
	BigInt result;
	int n = left._digits.size(), m = right._digits.size();
	result._digits.resize(n + m);
	for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                CONT_TYPE& pts = result._digits[i + j]; /// ����� �������� �� ������ ����-���� �������� ���������
                pts += left._digits[i]*right._digits[i];
                if (pts >= left.BASE){
                    pts -= left.BASE;
                    ++result._digits[i + j + 1];
                }
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
/// "���� ����������",
/// left ����� ��������, return ����� ���������
int g_div(BigInt left, BigInt right){
    right._is_negative = false;
    const int b_sz = right._digits.size();
    if (b_sz == 1){left = left / right._digits[0]; return left._digits[0];} /// �.�. g div ����������� ������� ������������� �����, �� ����� ���������� [0], ��� ��� �� ������ ����������� ������

    int curr_sz = left._digits.size();
    if (curr_sz < b_sz){
        /// x = 0 -> current = current - b * x; -> current -= 0 -> current �� ��������
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
        /// ��� ���� ��������� ��������, ��� � ����� ������ ���� ������
        /// (���_�����_��_�������*Base) / ���_�����_��_�
        /// ������ ��� ����� �� ����������� � long long, ��� ������������ �������...
        /// ���������� "�������" � ������ "������-������" �� ������ ����
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


// ����� ��� �����
const BigInt operator /(const BigInt& left, const BigInt& right) {

	if (right == 0) throw BigInt::divide_by_zero();
	const int b_sz = right._digits.size();
    if (b_sz == 1){return left / right._digits[0];}

	BigInt b = right;


	b._is_negative = false;
	BigInt result, current(0);
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



		if (curr_sz == b_sz){
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

// ����� ������� ����� �� ���������
BigInt& BigInt::operator /=(const BigInt& value) {
	return *this = (*this / value);
}

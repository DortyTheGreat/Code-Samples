
#include "core.cpp" /// �������������� ��������
#include "io.cpp" /// ����-�����

#include "compare.cpp"
#include "add.cpp"
#include "mult.cpp"
#include "exponential.cpp"


long long  intSqrt(long long arg){
    return (long long)(sqrt(arg));
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


/**
* ���� ��� �������� "������" �������� �����. � O(n^2)
* ��������� O(n^2 * log(n))
* ��������� �������� ���������� -> log(n) * ��������(������� ���� �������)
* �������� �����������(������) - ���������� ������.
* ������� ���������: �.�. ������� �������������� ����������� ����� �������� ��������������� -> sqrt(n) = sqrt( x * (n / x) ) ~= (x + (n/x))/2
* ���������� �������� log2(n) �������� ��� ���������� � �������������� ������.
* @author Dorty_Schmorty
* @return ������������� ������� ������ �������������� �������� �����
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

    /// ��, �� ���� ��� ��������� �������, ������� ��������
    int end_ = (int)(log2(sz)) + 1;


    for (int i = 0;i<end_;++i) {
        x = (x + n / x) / 2;
    }

    /// � ��������� �������, ���� ����� - ��� �� 1 ������, ��� ������ �������, �� ������� ����� ����� �� ���� ������
    /// �������� 24 -> 5, 48 -> 7, 35 -> 6
    /// safe_sqrt �������� �����
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


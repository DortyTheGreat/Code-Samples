
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



#include "core.cpp" /// примитивнейшие операции
#include "io.cpp" /// ввод-вывод

#include "compare.cpp"
#include "add.cpp"
#include "mult.cpp"
#include "exponential.cpp"


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


BigInt BigInt::handSqrt(const BigInt& n){
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
        A[0] = n._digits[i - 1];
        A[1] = n._digits[i];

        Carret *= n.BASE;
        Carret += n._digits[i];

        Carret *= n.BASE;
        Carret += n._digits[i - 1];

        /// curDigit = A/a      intSqrt()
        iSqrt_ = intSqrt(Carret);
        cout << iSqrt_ << endl;
        cout << "Carret : "<< Carret << endl;
        ret._digits[i / 2] = iSqrt_;
        cout << "i : " << i/2 << endl;
        Carret -= iSqrt_*iSqrt_;
        cout << "Carret : "<< Carret << endl;

        A -= a * curDigit;
    }

    return ret;
}

/**
BigInt algoSqrt(const BigInt& n){
    BigInt A = 0;
    BigInt curRes;
    for (int i = amount-1;i>=0;i--)
    {

        A.Shift(2,digits[i]);
        int curDigit = 0;

        int l = 0, r = 9;
        BigInt a = 2*curRes;
        a.Shift(1,0);
        while (l<=r)
        {
            int m = (l + r)>>1;
            a.digits[0] = m;
            if (a*m <= A)
            {
                curDigit = m;
                l = m + 1;
            }
            else
                r = m - 1;
        }
        curRes.Shift(1,curDigit);
        a.digits[0] = curDigit;
        A = A - a*curDigit;
    }
    return curRes;
}
*/

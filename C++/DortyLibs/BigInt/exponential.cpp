
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

const BigInt operator *(BigInt bi, int number){
    //cout << "called that" << endl;
    bi._is_negative ^= (number<0);
    number = abs(number);
    bi._mult(number);
    return bi;
}

//const int PSEUDO_MAX_INT

BigInt factorial(int num){
    BigInt ret = 1;
    for(int mul = 1; mul <= num;++mul){
        ret._mult(mul);
        //xcout << ret << endl;
    }
    return ret;
}

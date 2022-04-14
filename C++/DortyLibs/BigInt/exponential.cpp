
/// ќбработка умножени€ числа на маленькое( такое, что (Base-1)*number < INT_MAX )
void BigInt::_mult(const int number){

    if (number == 0){_digits = {0}; return;}

    size_t sz = _digits.size();
    long long carr;
    _digits.push_back(0);
    _digits.push_back(0);
    for(size_t i = 0;i < sz; ++i ){
        carr = _digits[i];

        carr *= number;
        _digits[i] = carr % BASE;
        _digits[i+1] += carr / BASE;
        _digits[i+1] +=
    }


    while (_digits[sz] >= BASE){
        _digits.push_back(_digits[sz] % BASE);
        _digits[sz] /= BASE;
        ++sz;
    }

    _remove_leading_zeros();

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

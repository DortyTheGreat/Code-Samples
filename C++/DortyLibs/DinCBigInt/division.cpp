
int intlog(double base, double x) {
    return (int)(log(x) / log(base));
}
/// 9 223 372 036 854 775 807
/// 2147483647
const long long INT_MAXI = 9223372036854775807;

int inline intSqrt(long long arg){
    return (long long)(sqrt(arg));
}

BigUnsigned Reciprocal(const BigUnsigned& bu,int precision)
{
    int mx_sz = intlog(BASE, INT_MAXI);
    int sz = bu.real_size;
    size_t len{ (sz > (mx_sz - 1)) ? (mx_sz) : sz };

    int divisor = 0;
    BigUnsigned res;

    /// Сколько нулей давать я хз
    res.alloc_with_zeros(2 << precision);




    for(int i = 0;i<len;i++){
        divisor *= BASE;
        divisor += bu._digits[sz - i - 1];
    }

    int dividend = 1;
    for(int i = 0;i<len;++i){
        dividend *= BASE;
    }
    /// Кароче, это типо... Ускоряет вычисления, ибо обращение часто по ссылке происходит или тип того ...
    CONT_TYPE* & approx = res._digits;

    ///cout << dividend << endl << divisor << endl;
    // Extra condition for initial guess is: x(i) < 2R/b

    /// В некоторый бит следует записать dividend / divisor (это типо мы записываем аппроксимизацию)

    write_to = dividend / divisor;
    write_to._appendZeros(precision - sz);



    // Do the interation to fullfil the precision
    int end{ (int)(std::log2(precision)) + 4 };
    for (int i = 0; i < end; i++)
    {
        /// a = 2*a - truncated_bits(n*a*a)
        write_to.Interate(*this, precision);
        ///cout << "InCycle " << write_to << endl;
    }



}

    void inline _DivUnrefined( BigInt &divisor, size_t precision, BigInt &write_to)
    {

        divisor.Reciprocal(precision,write_to);
        write_to._mult(*this, write_to);
    }

    void inline _DivInt( BigInt &divisor, BigInt &write_to)
    {

        if ( (data[data.size() - 1] == 0) || (divisor.data.size() > data.size()) ){write_to = 0; return;}
        size_t precision = data.size() + 4;
        _DivUnrefined(divisor,precision,write_to);
        write_to._ShiftR(precision);
        if (write_to.data.size() == 0){
            write_to.data.push_back(0);
        }
    }

    void inline _DivIntRem( BigInt &divisor, BigInt &write_to, BigInt &rem_write_to)
    {
        _DivInt(divisor,write_to);
        rem_write_to = *this;
        BigInt minus_ = write_to;
        minus_._mult(divisor,minus_);
        rem_write_to._subtract(minus_);
    }

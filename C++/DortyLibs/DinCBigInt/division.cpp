
int intlog(double base, double x) {
    return (int)(log(x) / log(base));
}
/// 9 223 372 036 854 775 807
/// 2147483647
const long long INT_MAXI = 9223372036854775807;

int inline intSqrt(long long arg){
    return (long long)(sqrt(arg));
}

template <typename T>
void print(T* a, int n ){
    for(int i = 0;i<n;i++){
        cout << a[i] << " ";
    }
    cout << endl;
}

BigUnsigned Reciprocal(const BigUnsigned& bu,int precision)
{
    ubi_szt mx_sz = intlog(BASE, INT_MAXI);
    ubi_szt sz = bu.real_size;
    ubi_szt len{ (sz > (mx_sz - 1)) ? (mx_sz) : sz };

    DOUBLE_CONT_TYPE divisor = 0;
    BigUnsigned res;

    /// Сколько нулей давать я хз
    res.alloc_with_zeros(1 << precision);




    for(int i = 0;i<len;i++){
        divisor *= BASE;
        divisor += bu._digits[sz - i - 1];
    }

    int dividend = 1;
    for(int i = 0;i<len;++i){
        dividend *= BASE;
    }

    dividend = dividend / divisor;

    while ( dividend >= BASE){
        dividend /= BASE;
    }

    /// Кароче, это типо... Ускоряет вычисления, ибо обращение часто по ссылке происходит или тип того ...
    CONT_TYPE* & approx = res._digits;
    //CONT_TYPE* sqr = new CONT_TYPE[1 << precision]{0};

    approx[res.alloc_size - 1] = dividend;

    ///write_to = dividend / divisor;
    ///write_to._appendZeros(precision - sz);



    // Do the interation to fullfil the precision
    for (int i = 1; i != 1 << 1; i <<= 1)
    {
        //memset(sqr, 0, (1 << precision) * sizeof(CONT_TYPE));
        //mult(approx,approx,sqr,i);

        //print(sqr, i);

        /// a = 2*a - truncated_bits(n*a*a)
        ///write_to.Interate(*this, precision);
        ///cout << "InCycle " << write_to << endl;
    }
    cout << res.alloc_size << endl;
    res.real_size = res.alloc_size;


    return res;
}
/**
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
    */


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

    ubi_szt cool_num = 1 << precision;

    /// Сколько нулей давать я хз
    res.alloc_with_zeros(cool_num);
    res.real_size = res.alloc_size;




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

    /// Кароче... Надо расширить оригинальное число типа... но немножко обкуренно ...
    CONT_TYPE * expanded = new CONT_TYPE[cool_num]{0};

    memcpy(expanded + (cool_num - bu.real_size), bu._digits, bu.real_size * sizeof(CONT_TYPE));

    cout << "expanded " << endl;
    print(expanded, cool_num);

    CONT_TYPE* sqr = new CONT_TYPE[cool_num]{0};
    CONT_TYPE* minus = new CONT_TYPE[cool_num * 2]{0};


    approx[res.alloc_size - 1] = dividend;
    cout << "dividend " << dividend << endl;
    ///write_to = dividend / divisor;
    ///write_to._appendZeros(precision - sz);



    // Do the interation to fullfil the precision
    for (int i = 1; i != cool_num; i <<= 1)
    {
        memset(sqr, 0, (cool_num) * sizeof(CONT_TYPE));
        memset(minus, 0, (2 * cool_num) * sizeof(CONT_TYPE));

        mult(approx + cool_num - i,approx + cool_num - i,sqr,i);

        print(sqr, i * 2);
        /// Теперь sqr имеет размер 2n, minus -> 4n, но следует truncatenut' до 2n

        print(expanded + cool_num - 2*i , i*2);

        mult(sqr, expanded + cool_num - 2*i , minus ,i*2 );

        print(minus, i * 4);

        /// aprox = 2*approx - minus
        for (int cou = 0;cou < i * 2;cou++){

            CONT_TYPE& r = approx[cool_num - cou - 1];
            cout << r << " " << minus[i*4 - cou - 2];
            r = r*2 - minus[i*4 - cou - 2];

            cout << " " << r << endl;

            if (r  >= BASE){
                r -= BASE;
                ++approx[cool_num - cou];
            }else{
                if (r  < 0){
                    r += BASE;
                    --approx[cool_num - cou];
                }
            }




        }
        cout << res << endl << endl;



        /// a = 2*a - truncated_bits(n*a*a)
        ///write_to.Interate(*this, precision);
        ///cout << "InCycle " << write_to << endl;
    }
    cout << res.alloc_size << endl;



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

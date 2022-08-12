#include <cmath>
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
/**
Не работает для чисел типа:
1, 10, 100, 1000, 10000 и т.д.

upd: уже работает, но это решение - есть костыль...
*/
BigUnsigned Reciprocal(const BigUnsigned& bu,int precision)
{
    ///MainClock.tick("Started Reciprocal");
    ubi_szt cool_num = 1 << precision;

    BigUnsigned res;

    /// Сколько нулей давать я хз
    res.alloc_with_zeros(cool_num);
    res.real_size = res.alloc_size;


    /// следует найти более грамотный метод фикса этого бага...
    if (bu._digits[bu.real_size - 1] == 1){
        bool flag = 1;
        for(int i = 0;i < bu.real_size - 1;++i){
            if (bu._digits[i] != 0){
                flag = 0;
                break;
            }
        }
        if (flag){
            /// число это 1, 10, 100, 1000 и т.д.
            res._digits[res.alloc_size - 1] = BASE;
            ///cout << "special case" << endl;

            return res;
        }
    }

    ubi_szt mx_sz = intlog(BASE, INT_MAXI);
    ubi_szt sz = bu.real_size;
    ubi_szt len{ (sz > (mx_sz - 1)) ? (mx_sz) : sz };

    DOUBLE_CONT_TYPE divisor = 0;









    for(int i = 0;i<len;i++){
        divisor *= BASE;
        divisor += bu._digits[sz - i - 1];
    }

    DOUBLE_CONT_TYPE dividend = 1;
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

    ///cout << "expanded " << endl;
    ///print(expanded, cool_num);

    CONT_TYPE* sqr = new CONT_TYPE[cool_num]{0};
    CONT_TYPE* minus = new CONT_TYPE[cool_num * 2]{0};


    approx[res.alloc_size - 1] = dividend;

    ///write_to = dividend / divisor;
    ///write_to._appendZeros(precision - sz);

    ///MainClock.tick("Reciprocal prep done");

    // Do the interation to fullfil the precision
    for (int i = 1; i != cool_num; i <<= 1)
    {
        ///MainClock.tick("itterarion start");
        ///cout << i << endl;

       /// cout << "old approx ";
        ///print(approx,cool_num);

        memset(sqr, 0, (cool_num) * sizeof(CONT_TYPE));
        memset(minus, 0, (2 * cool_num) * sizeof(CONT_TYPE));

        mult(approx + cool_num - i,approx + cool_num - i,sqr,i);
        ///cout << "sqr ";
        ///print(sqr, i * 2);
        /// Теперь sqr имеет размер 2n, minus -> 4n, но следует truncatenut' до 2n

        ///cout << "expanded ";
        ///print(expanded + cool_num - 2*i , i*2);

        ///cout << "full expanded ";
        ///print(expanded , cool_num);

        mult(sqr, expanded + cool_num - 2*i , minus ,i*2 );


        ///cout << "minus ";
        ///print(minus, i * 4);

        /// aprox = 2*approx - minus
        for (int cou = 0;cou < i * 2;cou++){
                approx[cool_num - cou - 1] *= 2;
        }
        for (int cou = 0;cou < i * 2;cou++){
            CONT_TYPE& r = approx[cool_num - i*2 + cou];
            ///cout << r << " " << minus[i*2 + cou - 1];
            r -= minus[i*2 + cou - 1];

            ///cout << " " << r << endl;

            if (r  >= BASE){
                r -= BASE;
                ++approx[cool_num - i*2 + cou + 1];
            }else{
                if (r  < 0){
                    r += BASE;
                    --approx[cool_num - i*2 + cou + 1];
                }
            }




        }

        ///cout << "new approx ";
        ///print(approx,cool_num);
        ///cout << res << endl << endl;


        ///MainClock.tick("itterarion finish");
        /// a = 2*a - truncated_bits(n*a*a)
        ///write_to.Interate(*this, precision);
    }
    ///cout << res.alloc_size << endl;



    return res;
}

/**
Новая идея

(number+1) * Reciprocal(1+ extra digit, rounded down) - 1
Например:
1) 7 / 4 -> 8 * 25 - 1 -> 199 -> 1
объяснение +- простое, но это работает

*/
BigUnsigned DivisionWithKnownReciprocal(const BigUnsigned& number, const BigUnsigned& Reciprocal, const int shift){
    BigUnsigned res;
    res.alloc_with_zeros(number.real_size * 2 + 1);


    /// Копия нужна не всегда, можно сделать для этого детект
    BigUnsigned copy;
    copy.assign_from_BU(number.real_size + 1, number);

    mult(copy._digits, Reciprocal._digits + (Reciprocal.alloc_size - number.real_size - 1), res._digits, number.real_size + 1);
    ///print(res._digits,res.alloc_size);
    res.real_size = res.alloc_size;
    ///print(res._digits,res.alloc_size);
    ///res += Reciprocal
    for(int i = 0;i< number.real_size + 1; ++i){
        res._digits[i] += Reciprocal._digits[(Reciprocal.alloc_size - number.real_size - 1) + i];
        if (res._digits[i] >= BASE){
            res._digits[i] -= BASE;
            ++res._digits[i+1];
        }
    }

    /// Хочется, то, что ниже сделать для флекса, но так тоже +- ничего
    CONT_TYPE *p = &res._digits[number.real_size + 1];
    while (*p >= BASE){
        *p -= BASE;
        ++p;
        ++(*p);
    }

    /// Переполнения real_size или alloc_size произойти не может, так что всё ок



    ///
    ///print(res._digits,res.alloc_size);
    --res;
    ///print(res._digits,res.alloc_size);
    res._digits += (number.real_size + shift);

    res.real_size = (res.alloc_size -= (number.real_size + shift));
    res._remove_leading_zeros();

    return res;
}



/**

BigUnsigned DivisionWithKnownReciprocal(const BigUnsigned& number, const BigUnsigned& Reciprocal, BigUnsigned& div, const int shift){
    BigUnsigned res;
    res.alloc_with_zeros(number.real_size + Reciprocal.real_size);

    mult(number._digits, Reciprocal._digits + (Reciprocal.alloc_size - number.real_size), res._digits, number.real_size);

    ///cout << number << endl << Reciprocal << endl;


    res._digits += shift;

    res.real_size = (res.alloc_size -= shift);
    res._remove_leading_zeros();




    BigUnsigned m = karatsuba(res,div);
    /// Я не пойму что это за обкуренные заморочки, но если писать
    /// BigUnsigned rem = number, то он возьмёт данные напрямую, игнорируя мой оператор =. Наверное у этого есть крутое объяснение с аллокацией памяти
    /// и я +- это понимаю, но всё равно необычненько


    16.05.2022 - Теперь я понимаю в чём дело, но почему-то если я добавлю КОНСТРУКТОР копирования, то будет попа...
    Так что пока ничего не меняю


    BigUnsigned rem;
    rem = number;
    rem -= m;



    if ( rem >= div){
        ++res;
    }


    return res;
}

*/


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

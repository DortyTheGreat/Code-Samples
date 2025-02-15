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
/**
template <typename T>
void print(T* a, int n ){
    for(int i = 0;i<n;i++){
        cout << a[i] << " ";
    }
    cout << endl;
}
*/
/**
�� �������� ��� ����� ����:
1, 10, 100, 1000, 10000 � �.�.

upd: ��� ��������, �� ��� ������� - ���� �������...
*/
BigUnsigned Reciprocal(const BigUnsigned& bu,int precision)
{
    ///MainClock.tick("Started Reciprocal");
    ubi_szt cool_num = 1 << precision;

    BigUnsigned res;

    /// ������� ����� ������ � ��
    res.alloc_with_zeros(cool_num);
    res.real_size = res.alloc_size;


    /// ������� ����� ����� ��������� ����� ����� ����� ����...
    if (bu.digits[bu.real_size - 1] == 1){
        bool flag = 1;
        for(int i = 0;i < bu.real_size - 1;++i){
            if (bu.digits[i] != 0){
                flag = 0;
                break;
            }
        }
        if (flag){
            /// ����� ��� 1, 10, 100, 1000 � �.�.
            res.digits[res.alloc_size - 1] = BASE;
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
        divisor += bu.digits[sz - i - 1];
    }

    DOUBLE_CONT_TYPE dividend = 1;
    for(int i = 0;i<len;++i){
        dividend *= BASE;
    }

    dividend = dividend / divisor;


    while ( dividend >= BASE){
        dividend /= BASE;
    }

    /// ������, ��� ����... �������� ����������, ��� ��������� ����� �� ������ ���������� ��� ��� ���� ...
    CONT_TYPE* & approx = res.digits;

    /// ������... ���� ��������� ������������ ����� ����... �� �������� ��������� ...
    CONT_TYPE * expanded = new CONT_TYPE[cool_num]{0};

    memcpy(expanded + (cool_num - bu.real_size), bu.digits, bu.real_size * sizeof(CONT_TYPE));

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
        /// ������ sqr ����� ������ 2n, minus -> 4n, �� ������� truncatenut' �� 2n

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
����� ����

(number+1) * Reciprocal(1+ extra digit, rounded down) - 1
��������:
1) 7 / 4 -> 8 * 25 - 1 -> 199 -> 1
���������� +- �������, �� ��� ��������

*/
BigUnsigned DivisionWithKnownReciprocal(const BigUnsigned& number, const BigUnsigned& Reciprocal, const int shift){
    BigUnsigned res;
    res.alloc_with_zeros(number.real_size * 2 + 1);


    /// ����� ����� �� ������, ����� ������� ��� ����� ������
    BigUnsigned copy;
    copy.assign_from_BU(number.real_size + 1, number);

    mult(copy.digits, Reciprocal.digits + (Reciprocal.alloc_size - number.real_size - 1), res.digits, number.real_size + 1);
    ///print(res.digits,res.alloc_size);
    res.real_size = res.alloc_size;
    ///print(res.digits,res.alloc_size);
    ///res += Reciprocal
    for(int i = 0;i< number.real_size + 1; ++i){
        res.digits[i] += Reciprocal.digits[(Reciprocal.alloc_size - number.real_size - 1) + i];
        if (res.digits[i] >= BASE){
            res.digits[i] -= BASE;
            ++res.digits[i+1];
        }
    }

    /// �������, ��, ��� ���� ������� ��� ������, �� ��� ���� +- ������
    CONT_TYPE *p = &res.digits[number.real_size + 1];
    while (*p >= BASE){
        *p -= BASE;
        ++p;
        ++(*p);
    }

    /// ������������ real_size ��� alloc_size ��������� �� �����, ��� ��� �� ��



    ///
    ///print(res.digits,res.alloc_size);
    --res;
    ///print(res.digits,res.alloc_size);
    res.digits += (number.real_size + shift);

    res.real_size = (res.alloc_size -= (number.real_size + shift));
    res._remove_leading_zeros();

    return res;
}



/* Grade school multiplication, ignoring the signs.
 * Returns the absolute value of the product, or NULL if error.
 */
 /// Алгоритм Школьного Умножения (взято с доков Питона -> см. https://hg.python.org/cpython/file/b514339e41ef/Objects/longobject.c#l2694)
 /// Не работает правильно с нулём
BigUnsigned x_mul(const BigUnsigned& a,const BigUnsigned& b)
{
    static const CONT_TYPE BASE = a.BASE;

    BigUnsigned z;
    const ubi_szt size_a = a.real_size;
    const ubi_szt size_b = b.real_size;
    ubi_szt i;
    z.alloc_with_zeros(size_a + size_b);




    ///memset(z->ob_digit, 0, Py_SIZE(z) * sizeof(digit));

    for (i = 0; i < size_a; ++i) {
        DOUBLE_CONT_TYPE carry = 0;
        DOUBLE_CONT_TYPE f = a._digits[i];
        CONT_TYPE *pz = z._digits + i;
        CONT_TYPE *pb = b._digits;
        CONT_TYPE *pbend = b._digits + size_b;

        /// SIGCHECK ???

        while (pb < pbend) {
            carry += *pz + *pb++ * f;
            *pz++ = (carry % BASE);
            carry /= BASE;
        }
        if (carry)
            *pz += (carry % BASE);
    }


    if (z._digits[z.alloc_size - 1] == 0){
         z.real_size = z.alloc_size - 1;
    }else{
         z.real_size = z.alloc_size;
    }

    return z;
}

#define KAR_TRESH 70

BigUnsigned k_mul(const BigUnsigned& left,const BigUnsigned& right) {



    const ubi_szt n = left.real_size; /// size of biggest num

    if (n < right.real_size){
        return k_mul(right,left);
    }

    /// число мелкое, умножаем, как обычно
    if (n < KAR_TRESH){return x_mul(left,right);}

    const ubi_szt fh = (n+1) / 2;   // First half Data (take more)
    const ubi_szt sh = (n - fh); // Second half of Data

    // Find the first half and second half of first string.



    BigUnsigned L0, L1, R0;

    const ubi_szt s_sz = right.real_size;

    const ubi_szt _0_sz = min(s_sz, fh);

    L0._digits = new CONT_TYPE[fh];
    L1._digits = new CONT_TYPE[sh];
    R0._digits = new CONT_TYPE[_0_sz];
    BigUnsigned Z0;
    BigUnsigned Z1;



    memcpy(L0._digits,left._digits,fh * sizeof(CONT_TYPE));
    memcpy(L1._digits,left._digits + fh,sh * sizeof(CONT_TYPE));
    memcpy(R0._digits, right._digits, _0_sz * sizeof(CONT_TYPE));








    Z0 = k_mul(L0,R0);
    const int _1_sz = s_sz - _0_sz;
    if (_1_sz == 0){
        /// Z2 = 0
        Z1 = k_mul(L1,R0); /// no swap

        Z1._appendZeros(fh);


        return Z1+Z0;
    }else{
        BigUnsigned R1;
        R1._digits.resize(_1_sz);



        for(int i = 0;i<_1_sz;++i){
            R1._digits[i] = right._digits[fh + i];
        }

        BigUnsigned Z2 = k_mul(L1,R1); /// no swap


        Z1 = k_mul(L0+L1, R0+R1);

        Z1 -= (Z0+Z2);

        ///if ( !(Z1.data.size() == 1 && Z1.data[0] == 0) )
            Z1._appendZeros(fh);

        ///if ( !(Z2.data.size() == 1 && Z2.data[0] == 0) )
            Z2._appendZeros(fh * 2);

        return Z2 + Z1 + Z0;
    }

}





/* A helper for Karatsuba multiplication (k_mul).
   Takes a long "n" and an integer "size" representing the place to
   split, and sets low and high such that abs(n) == (high << size) + low,
   viewing the shift as being by digits.  The sign bit is ignored, and
   the return values are >= 0.
   Returns 0 on success, -1 on failure.
*/
void kmul_split(const BigUnsigned& n,
           ubi_szt size,
           BigUnsigned& high,
           BigUnsigned& low)
{

    ubi_szt size_lo, size_hi;
    const ubi_szt size_n = n.real_size;

    size_lo = min(size_n, size);
    size_hi = size_n - size_lo;

    hi._digits = new CONT_TYPE[size_hi];
    lo._digits = new CONT_TYPE[size_lo];

    memcpy(lo->ob_digit, n->ob_digit, size_lo * sizeof(digit));
    memcpy(hi->ob_digit, n->ob_digit + size_lo, size_hi * sizeof(digit));

    *high = long_normalize(hi);
    *low = long_normalize(lo);
    return 0;
}

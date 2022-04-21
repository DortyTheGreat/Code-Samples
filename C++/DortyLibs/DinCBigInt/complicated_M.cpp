#define KAR_TRESH 50

/* Grade school multiplication, ignoring the signs.
 * Returns the absolute value of the product, or NULL if error.
 */
 /*
static BigInt *
x_mul(BigInt *a, BigInt *b)
{
    BigInt *z;
    int size_a = a->_digits.size();
    int size_b = a->_digits.size();
    int i;

    z->_digits.resize(size_a + size_b);

    ///memset(z->ob_digit, 0, Py_SIZE(z) * sizeof(digit));


    for (i = 0; i < size_a; ++i) {
        long long carry = 0;
        long long f = a->_digits[i];
        auto pz = z->_digits[i];
        auto pb = b->_digits[0];
        auto pbend = b->_digits[size_b];

        SIGCHECK({
                Py_DECREF(z);
                return NULL;
            });

        while (pb < pbend) {
            carry += *pz + *pb++ * f;
            *pz++ = (digit)(carry & PyLong_MASK);
            carry >>= PyLong_SHIFT;
            assert(carry <= PyLong_MASK);
        }
        if (carry)
            *pz += (digit)(carry & PyLong_MASK);
        assert((carry >> PyLong_SHIFT) == 0);
    }

    return long_normalize(z);
}

*/
 BigInt k_mul(const BigInt& left,const BigInt& right) {



    const int n = left._digits.size(); /// size of biggest num

    if (n < right._digits.size()){
        return k_mul(right,left);
    }

    /// число мелкое, умножаем, как обычно
    if (n < KAR_TRESH){return left*right;}

    const int fh = (n+1) / 2;   // First half Data (take more)
    const int sh = (n - fh); // Second half of Data

    // Find the first half and second half of first string.



    BigInt L0, L1, R0;

    const int s_sz = right._digits.size();

    const int _0_sz = min(s_sz, fh);

    L0._digits.resize(fh);
    L1._digits.resize(sh);
    R0._digits.resize(_0_sz);
    BigInt Z0;
    BigInt Z1;






    for(int i = 0;i<fh;++i){
        L0._digits[i] = left._digits[i];
    }



    /// tut oshibka
    for(int i = 0;i<_0_sz;++i){
        R0._digits[i] = right._digits[i];
    }



    for(int i = 0;i<sh;++i){
        L1._digits[i] = left._digits[fh + i];
    }




    Z0 = k_mul(L0,R0);
    const int _1_sz = s_sz - _0_sz;
    if (_1_sz == 0){
        /// Z2 = 0
        Z1 = k_mul(L1,R0); /// no swap

        Z1._appendZeros(fh);


        return Z1+Z0;
    }else{
        BigInt R1;
        R1._digits.resize(_1_sz);



        for(int i = 0;i<_1_sz;++i){
            R1._digits[i] = right._digits[fh + i];
        }

        BigInt Z2 = k_mul(L1,R1); /// no swap


        Z1 = k_mul(L0+L1, R0+R1);

        Z1 -= (Z0+Z2);

        ///if ( !(Z1.data.size() == 1 && Z1.data[0] == 0) )
            Z1._appendZeros(fh);

        ///if ( !(Z2.data.size() == 1 && Z2.data[0] == 0) )
            Z2._appendZeros(fh * 2);

        return Z2 + Z1 + Z0;
    }

}
/*
bool BigInt::split(BigInt* liFront, BigInt* liBack, int iSplit) const {
	// Split the current BigInt into 2 bits at the point specified by iSplit

	if (iSplit >= _digits.size()) {
		(*liFront) = (*this);
		*liBack = 0;
		return false;
	}

	// Put the first half of the current BigInt in liFront

	liFront->_digits = vector<CONT_TYPE>(_digits.begin(),_digits.begin() + iSplit);
	liFront->_is_negative = _is_negative;

	// Put the second half in liBack


	liBack->_digits = vector<CONT_TYPE>(_digits.begin() + iSplit,_digits.end());
	liBack->_is_negative = _is_negative;

	return true;
}

BigInt* karatsuba(const BigInt& liOne, const BigInt& liTwo)
{
	if ((liOne._digits.size() < KAR_TRESH) && (liTwo._digits.size() < KAR_TRESH))
	{

		return new BigInt (liOne * liTwo);
	}

	// Determine the size of the numbers, so we know where to split them
	int iSize = (liOne._digits.size() > liTwo._digits.size()) ? liOne._digits.size() : liTwo._digits.size();
	int iHalfSize = iSize / 2;

	// Split the digit sequences about the middle
	BigInt* liHighOne = new BigInt();
	BigInt* liLowOne = new BigInt();
	BigInt* liHighTwo = new BigInt();
	BigInt* liLowTwo = new BigInt();
	liOne.split(liLowOne, liHighOne, iHalfSize);
	liTwo.split(liLowTwo, liHighTwo, iHalfSize);

	BigInt* liZ0;
	BigInt* liZ1;
	BigInt* liZ2;



		// 3 calls made to numbers approximately half the size
		liZ0 = karatsuba(*liLowOne, *liLowTwo);
		liZ1 = karatsuba((*liLowOne + *liHighOne), (*liLowTwo + *liHighTwo));
		liZ2 = karatsuba(*liHighOne, *liHighTwo);

	// The next step is this calculation:
	// return (z2*10^(2*m2))+((z1-z2-z0)*10^(m2))+(z0)
	// This calc is in base 10 whereas we are in base BASEVAL, which is the size of 1 byte
	// The numbers are represented internally as a byte array
	// So we will start with most complex bit - z1-z2-z0 * BASEVAL^(halfsize)
	// We will do the sums, then move liZ1 left by halfsize bytes
	(*liZ1) -= (*liZ2);
	(*liZ1) -= (*liZ0);
	liZ1->_appendZeros(iHalfSize);
	// Then move liZ2 left by iSize bytes
	liZ2->_appendZeros(iHalfSize * 2);
	// Then we add liZ0, liZ1 and liZ2 together

	BigInt* returnValue = new BigInt((*liZ2) + (*liZ1) + (*liZ0));

	delete liLowOne;
	delete liLowTwo;
	delete liHighOne;
	delete liHighTwo;
	delete liZ0;
	delete liZ1;
	delete liZ2;

	return returnValue;
}
*/

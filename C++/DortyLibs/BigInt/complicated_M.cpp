#define KAR_TRESH 50

/* Grade school multiplication, ignoring the signs.
 * Returns the absolute value of the product, or NULL if error.
 */
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



/// Karatsuba, пока не делает ничего со знаком, left.size() > right.size()
static BigInt *
k_mul(BigInt *a, BigInt *b)
{
    int asize = a->_digits.size();
    int bsize = b->_digits.size();
    BigInt *ah = NULL;
    BigInt *al = NULL;
    BigInt *bh = NULL;
    BigInt *bl = NULL;
    BigInt *ret = NULL;
    BigInt *t1, *t2, *t3;
    int shift;           /* the number of digits we split off */
    int i;

    /* (ah*X+al)(bh*X+bl) = ah*bh*X*X + (ah*bl + al*bh)*X + al*bl
     * Let k = (ah+al)*(bh+bl) = ah*bl + al*bh  + ah*bh + al*bl
     * Then the original product is
     *     ah*bh*X*X + (k - ah*bh - al*bl)*X + al*bl
     * By picking X to be a power of 2, "*X" is just shifting, and it's
     * been reduced to 3 multiplies on numbers half the size.
     */

    /* We want to split based on the larger number; fiddle so that b
     * is largest.
     */
    if (asize > bsize) {
        t1 = a;
        a = b;
        b = t1;

        i = asize;
        asize = bsize;
        bsize = i;
    }

    /* Use gradeschool math when either number is too small. */
    if (asize <= KAR_TRESH) {
        if (asize == 0)
            return 0;
        else
            return x_mul(a, b);
    }

    /* If a is small compared to b, splitting on b gives a degenerate
     * case with ah==0, and Karatsuba may be (even much) less efficient
     * than "grade school" then.  However, we can still win, by viewing
     * b as a string of "big digits", each of width a->ob_size.  That
     * leads to a sequence of balanced calls to k_mul.
     */
    if (2 * asize <= bsize)
        return k_lopsided_mul(a, b);

    /* Split a & b into hi & lo pieces. */
    shift = bsize >> 1;
    if (kmul_split(a, shift, &ah, &al) < 0) goto fail;
    assert(Py_SIZE(ah) > 0);            /* the split isn't degenerate */

    if (a == b) {
        bh = ah;
        bl = al;
        Py_INCREF(bh);
        Py_INCREF(bl);
    }
    else if (kmul_split(b, shift, &bh, &bl) < 0) goto fail;

    /* The plan:
     * 1. Allocate result space (asize + bsize digits:  that's always
     *    enough).
     * 2. Compute ah*bh, and copy into result at 2*shift.
     * 3. Compute al*bl, and copy into result at 0.  Note that this
     *    can't overlap with #2.
     * 4. Subtract al*bl from the result, starting at shift.  This may
     *    underflow (borrow out of the high digit), but we don't care:
     *    we're effectively doing unsigned arithmetic mod
     *    PyLong_BASE**(sizea + sizeb), and so long as the *final* result fits,
     *    borrows and carries out of the high digit can be ignored.
     * 5. Subtract ah*bh from the result, starting at shift.
     * 6. Compute (ah+al)*(bh+bl), and add it into the result starting
     *    at shift.
     */

    /* 1. Allocate result space. */
    ret = _PyLong_New(asize + bsize);
    if (ret == NULL) goto fail;
#ifdef Py_DEBUG
    /* Fill with trash, to catch reference to uninitialized digits. */
    memset(ret->ob_digit, 0xDF, Py_SIZE(ret) * sizeof(digit));
#endif

    /* 2. t1 <- ah*bh, and copy into high digits of result. */
    if ((t1 = k_mul(ah, bh)) == NULL) goto fail;
    assert(Py_SIZE(t1) >= 0);
    assert(2*shift + Py_SIZE(t1) <= Py_SIZE(ret));
    memcpy(ret->ob_digit + 2*shift, t1->ob_digit,
           Py_SIZE(t1) * sizeof(digit));

    /* Zero-out the digits higher than the ah*bh copy. */
    i = Py_SIZE(ret) - 2*shift - Py_SIZE(t1);
    if (i)
        memset(ret->ob_digit + 2*shift + Py_SIZE(t1), 0,
               i * sizeof(digit));

    /* 3. t2 <- al*bl, and copy into the low digits. */
    if ((t2 = k_mul(al, bl)) == NULL) {
        Py_DECREF(t1);
        goto fail;
    }
    assert(Py_SIZE(t2) >= 0);
    assert(Py_SIZE(t2) <= 2*shift); /* no overlap with high digits */
    memcpy(ret->ob_digit, t2->ob_digit, Py_SIZE(t2) * sizeof(digit));

    /* Zero out remaining digits. */
    i = 2*shift - Py_SIZE(t2);          /* number of uninitialized digits */
    if (i)
        memset(ret->ob_digit + Py_SIZE(t2), 0, i * sizeof(digit));

    /* 4 & 5. Subtract ah*bh (t1) and al*bl (t2).  We do al*bl first
     * because it's fresher in cache.
     */
    i = Py_SIZE(ret) - shift;  /* # digits after shift */
    (void)v_isub(ret->ob_digit + shift, i, t2->ob_digit, Py_SIZE(t2));
    Py_DECREF(t2);

    (void)v_isub(ret->ob_digit + shift, i, t1->ob_digit, Py_SIZE(t1));
    Py_DECREF(t1);

    /* 6. t3 <- (ah+al)(bh+bl), and add into result. */
    if ((t1 = x_add(ah, al)) == NULL) goto fail;
    Py_DECREF(ah);
    Py_DECREF(al);
    ah = al = NULL;

    if (a == b) {
        t2 = t1;
        Py_INCREF(t2);
    }
    else if ((t2 = x_add(bh, bl)) == NULL) {
        Py_DECREF(t1);
        goto fail;
    }
    Py_DECREF(bh);
    Py_DECREF(bl);
    bh = bl = NULL;

    t3 = k_mul(t1, t2);
    Py_DECREF(t1);
    Py_DECREF(t2);
    if (t3 == NULL) goto fail;
    assert(Py_SIZE(t3) >= 0);

    /* Add t3.  It's not obvious why we can't run out of room here.
     * See the (*) comment after this function.
     */
    (void)v_iadd(ret->ob_digit + shift, i, t3->ob_digit, Py_SIZE(t3));
    Py_DECREF(t3);

    return long_normalize(ret);

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

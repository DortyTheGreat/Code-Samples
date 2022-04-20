//#pragma GCC target ("avx2")
//#pragma GCC optimization ("O3")
//#pragma GCC optimization ("unroll-loops")

#include <bits/stdc++.h>

#define default_base 10

#define CONT_TYPE long long

#define big_container 1

#if big_container

#define container_stack 9 /// 9
#define total_base 1000000000 /// 1000000000
#define sqrt_of_total_base 31622 /// 31622

#else

#define container_stack 1 /// 9
#define total_base 10 /// 1000000000
#define sqrt_of_total_base 3 /// 31622

#endif



class BigInt {


	// ���������� ��������� �����


	// ���� �����
	bool _is_negative;

	void _remove_leading_zeros();
	void _shift_right();
	void _double_shift_right();

public:
    static const int BASE = total_base;
    std::vector<CONT_TYPE> _digits;


    // ��������� ������� ��������� (1 000 000 000)



	// �����-����������, ��������� ��� ������� �� ����
	class divide_by_zero : public std::exception {  };

	BigInt();
	BigInt(std::string);
	BigInt(signed char);
	BigInt(unsigned char);
	BigInt(signed short);
	BigInt(unsigned short);
	BigInt(signed int);
	BigInt(unsigned int);
	BigInt(signed long);
	BigInt(unsigned long);
	BigInt(signed long long);
	BigInt(unsigned long long);

    friend BigInt handSqrt(const BigInt& n);
    friend BigInt algoSqrt(const BigInt& n);

	friend std::ostream& operator <<(std::ostream&, const BigInt&);
	friend std::istream& operator >>(std::istream&, BigInt&);
	operator std::string() const;

	void _add(const BigInt&);
    void _subtract(const BigInt&);

    void _mult(const int number);
    const friend BigInt operator *(BigInt,const int);
    void operator *=(int);


    //bool split(BigInt* liFront, BigInt* liBack, int iSplit) const;
    //friend BigInt* karatsuba(const BigInt& liOne, const BigInt& liTwo);

    friend BigInt k_mul(const BigInt&, const BigInt&);

	const BigInt operator +() const;
	const BigInt operator -() const;
	const BigInt operator ++();
	const BigInt operator ++(int);
	const BigInt operator --();
	const BigInt operator --(int);

	friend short inline compare(const BigInt&, const BigInt&);
	friend bool operator ==(const BigInt&, const BigInt&);
	friend bool operator <(const BigInt&, const BigInt&);
	friend bool operator !=(const BigInt&, const BigInt&);
	friend bool operator <=(const BigInt&, const BigInt&);
	friend bool operator >(const BigInt&, const BigInt&);
	friend bool operator >=(const BigInt&, const BigInt&);

	friend const BigInt operator +(BigInt, const BigInt&);
	void operator +=(const BigInt&);
	friend const BigInt operator -(BigInt, const BigInt&);
	void operator -=(BigInt);
	friend const BigInt operator *(const BigInt&, const BigInt&);
	BigInt& operator *=(const BigInt&);

	friend int g_div(BigInt left, BigInt right);

	friend const BigInt operator /(const BigInt&, const int);
	friend const BigInt operator /(const BigInt&, const BigInt&);


	BigInt& operator /=(const BigInt&);
	friend const BigInt operator %(const BigInt&, const BigInt&);
	BigInt& operator %=(const BigInt&);

	bool odd() const;
	bool even() const;
	const BigInt pow(BigInt) const;
    const int get_real_size() const;

	/// [5,4,3,2,1](12345) (length=3)-> [0,0,0,5,4,3,2,1](12345000)
    /// ������� ��������. ������ ����� ������������
    void inline _appendZeros(int);
};


#include "BigInt.cpp"

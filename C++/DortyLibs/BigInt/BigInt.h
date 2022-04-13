#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

#include <bits/stdc++.h>

#define default_base 10

#define container_stack 9 /// 6

#define total_base 1000000000 /// 1000000

#define sqrt_of_total_base 10000 /// 1000

class BigInt {


	// внутреннее хранилище числа

    std::vector<int> _digits;
	// знак числа
	bool _is_negative;

	void _remove_leading_zeros();
	void _shift_right();

public:



    // основание системы счисления (1 000 000 000)
	int BASE = total_base;


	// класс-исключение, бросаемое при делении на ноль
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

	friend std::ostream& operator <<(std::ostream&, const BigInt&);
	friend std::istream& operator >>(std::istream&, BigInt&);
	operator std::string() const;
	const BigInt operator +() const;
	const BigInt operator -() const;
	const BigInt operator ++();
	const BigInt operator ++(int);
	const BigInt operator --();
	const BigInt operator --(int);
	friend bool operator ==(const BigInt&, const BigInt&);
	friend bool operator <(const BigInt&, const BigInt&);
	friend bool operator !=(const BigInt&, const BigInt&);
	friend bool operator <=(const BigInt&, const BigInt&);
	friend bool operator >(const BigInt&, const BigInt&);
	friend bool operator >=(const BigInt&, const BigInt&);
	friend const BigInt operator +(BigInt, const BigInt&);
	BigInt& operator +=(const BigInt&);
	friend const BigInt operator -(BigInt, const BigInt&);
	BigInt& operator -=(const BigInt&);
	friend const BigInt operator *(const BigInt&, const BigInt&);
	BigInt& operator *=(const BigInt&);
	friend const BigInt operator /(const BigInt&, const BigInt&);
	BigInt& operator /=(const BigInt&);
	friend const BigInt operator %(const BigInt&, const BigInt&);
	BigInt& operator %=(const BigInt&);

	bool odd() const;
	bool even() const;
	const BigInt pow(BigInt) const;
    const int get_real_size() const;

	/// [5,4,3,2,1](12345) (length=3)-> [0,0,0,5,4,3,2,1](12345000)
    /// Следует Улучшить. Ужасно плохо реализованно
    void inline _appendZeros(int);
};


#include "BigInt.cpp"

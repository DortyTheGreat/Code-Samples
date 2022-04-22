//#pragma GCC target ("avx2")
//#pragma GCC optimization ("O3")
//#pragma GCC optimization ("unroll-loops")

///#include <bits/stdc++.h>

#include <cstdint> ///
#include <cstring> /// дл€ memcpy

#define default_base 10

#define CONT_TYPE unsigned int
#define DOUBLE_CONT_TYPE unsigned long long /// ƒвойной –ј«ћ≈–
#define ubi_szt int /// Unsigned Big Int SiZe Type, пока об€зан быть знаковым -_-


#define big_container 1

#if big_container

#define cnt_stack 9 /// 9
#define total_base 1000000000 /// 1000000000
#define sqrt_of_total_base 31622 /// 31622

#else

#define cnt_stack 1 /// 9
#define total_base 10 /// 1000000000
#define sqrt_of_total_base 3 /// 31622

#endif


//template <const int def_base = default_base, int BASE = total_base, const int container_stack = cnt_stack>
class BigUnsigned{
private:
    CONT_TYPE* _digits;
    static const unsigned int BASE = total_base;
public:

    ubi_szt real_size; /// –≈јЋ№Ќјя ƒлинна числа
    ubi_szt alloc_size; /// ƒл€ упрощени€ реализации alloc_size - всегда степень двойка, так можно будет удобно делить массив на две\\четыре равные части.

    BigUnsigned(){}

    /// мемори стафф
    void alloc_with_zeros(const int sz);
    void assign_from_BU(const int alloc_space, const BigUnsigned& bu);

    friend std::ostream& operator << (std::ostream&, const BigUnsigned&);
	friend std::istream& operator >> (std::istream&, BigUnsigned&);

	friend const BigUnsigned operator +(const BigUnsigned&, const BigUnsigned&);
	void operator +=(const BigUnsigned&);

    friend BigUnsigned x_mul(const BigUnsigned& a,const BigUnsigned& b);
    friend BigUnsigned k_mul(const BigUnsigned& left,const BigUnsigned& right);

	void operator =(const BigUnsigned&);

	void _add(const BigUnsigned&);
};

#include "BigUnsigned.cpp"

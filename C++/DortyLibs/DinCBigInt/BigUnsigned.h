//#pragma GCC target ("avx2")
//#pragma GCC optimization ("O3")
//#pragma GCC optimization ("unroll-loops")

///#include <bits/stdc++.h>

#define default_base 10

#define CONT_TYPE unsigned int
#define ubi_szt int /// Unsigned Big Int SiZe Type, пока об€зан быть знаковым -_-

#define big_container 0

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
    const int BASE = total_base;
public:

    ubi_szt real_size; /// –≈јЋ№Ќјя ƒлинна числа
    ubi_szt alloc_size; /// ƒл€ упрощени€ реализации alloc_size - всегда степень двойка, так можно будет удобно делить массив на две\\четыре равные части.

    BigUnsigned(){}

    friend std::ostream& operator << (std::ostream&, const BigUnsigned&);
	friend std::istream& operator >> (std::istream&, BigUnsigned&);

	friend const BigUnsigned operator +(BigUnsigned, const BigUnsigned&);
	void operator +=(const BigUnsigned&);
};

#include "BigUnsigned.cpp"

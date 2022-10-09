#include <cstdint> ///
#include <cstring> /// äëÿ memcpy

#define default_base 10

#define CONT_TYPE int
#define DOUBLE_CONT_TYPE long long /// Äâîéíîé ÐÀÇÌÅÐ
#define ubi_szt int /// Unsigned Big Int SiZe Type, ïîêà îáÿçàí áûòü çíàêîâûì -_-


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

const CONT_TYPE BASE = total_base;
template<typename T>
struct custom_array{
    T* digits;

    ubi_szt real_size;
    ubi_szt alloc_size;
};

//template <const int def_base = default_base, int BASE = total_base, const int container_stack = cnt_stack>
class BigUnsigned{
public:
    custom_array<CONT_TYPE> digits;
    static const CONT_TYPE BASE = total_base;

public:



    BigUnsigned();
    BigUnsigned(const BigUnsigned& bu);
    BigUnsigned (BigUnsigned&& bu);
    BigUnsigned (const std::string& str);

    template <typename T>
    inline CONT_TYPE& operator[] (const T& index){return digits[index];}



    BigUnsigned& operator= (BigUnsigned&& bu);
    BigUnsigned& operator= (const BigUnsigned& bu);










    void _remove_leading_zeros();

    /// ìåìîðè ñòàôô
    void alloc_with_zeros(const int sz);
    void assign_from_BU(const int alloc_space, const BigUnsigned& bu);

    explicit operator std::string() const;

    friend std::ostream& operator << (std::ostream&, const BigUnsigned&);
	friend std::istream& operator >> (std::istream&, BigUnsigned&);

	short inline friend compare(const BigUnsigned &left, const BigUnsigned &right);

    bool friend operator <(const BigUnsigned& left, const BigUnsigned& right);
    bool friend operator ==(const BigUnsigned& left, const BigUnsigned& right);

    // auto-defined
    bool friend operator <=(const BigUnsigned& left, const BigUnsigned& right);
    bool friend operator >(const BigUnsigned& left, const BigUnsigned& right);
    bool friend operator >=(const BigUnsigned& left, const BigUnsigned& right);
    bool friend operator !=(const BigUnsigned& left, const BigUnsigned& right);

    friend const BigUnsigned operator +(const BigUnsigned&, const BigUnsigned&);

    friend const BigUnsigned operator +(BigUnsigned&&, const BigUnsigned&);



	void operator +=(const BigUnsigned&);

    void operator++();
    void operator--();

    void operator -=(const BigUnsigned& minus);

    friend BigUnsigned x_mul(const BigUnsigned& a,const BigUnsigned& b);
    friend BigUnsigned k_mul(const BigUnsigned& left,const BigUnsigned& right);


    /// Êàðàöóáà, êñòàòè ìåíÿåò êîíòåéíåðíûé ðàçìåð ÷èñåëîê...
    friend BigUnsigned karatsuba(BigUnsigned& left,BigUnsigned& right);

    friend BigUnsigned Reciprocal(const BigUnsigned& bu,int precision);

    friend BigUnsigned DivisionWithKnownReciprocal(const BigUnsigned& number, const BigUnsigned&, const int);

	void _add(const BigUnsigned&);
};

#include "BigUnsigned.cpp"

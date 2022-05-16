//#pragma GCC target ("avx2")
//#pragma GCC optimization ("O3")
//#pragma GCC optimization ("unroll-loops")

///#include <bits/stdc++.h>

#include <cstdint> ///
#include <cstring> /// äëÿ memcpy

#define default_base 10

#define CONT_TYPE int
#define DOUBLE_CONT_TYPE long long /// Äâîéíîé ÐÀÇÌÅÐ
#define ubi_szt int /// Unsigned Big Int SiZe Type, ïîêà îáÿçàí áûòü çíàêîâûì -_-


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

const CONT_TYPE BASE = total_base;


//template <const int def_base = default_base, int BASE = total_base, const int container_stack = cnt_stack>
class BigUnsigned{
private:
    CONT_TYPE* _digits;
    static const CONT_TYPE BASE = total_base;
public:

    ubi_szt real_size; /// ÐÅÀËÜÍÀß Äëèííà ÷èñëà
    ubi_szt alloc_size; /// Äëÿ óïðîùåíèÿ ðåàëèçàöèè alloc_size - âñåãäà ñòåïåíü äâîéêà, òàê ìîæíî áóäåò óäîáíî äåëèòü ìàññèâ íà äâå\\÷åòûðå ðàâíûå ÷àñòè.

    BigUnsigned()
        : _digits( new CONT_TYPE[1])
        , real_size(1)
        , alloc_size(1)
    {_digits[0] = 0;}

    void operator= (BigUnsigned&& bu)
    {
        cout << "called move equality" << endl;
        _digits = ( bu._digits  );
        real_size = ( bu.real_size );
        alloc_size = ( bu.alloc_size );


        bu._digits = NULL;
    }

    BigUnsigned (BigUnsigned&& bu)
        : _digits( bu._digits  )
        , real_size( bu.real_size )
        , alloc_size( bu.alloc_size )
    {
        cout << "called constructor" << endl;
        bu._digits = NULL;
    }





    void operator= (const BigUnsigned& bu){
        cout << "called copy equality" << endl;
        if (bu.real_size > alloc_size){
            alloc_size = bu.alloc_size;
            _digits = new CONT_TYPE[alloc_size];


            ///_digits = (CONT_TYPE*)(ptr); /// new CONT_TYPE[alloc_size]{0} ИЛИ new CONT_TYPE[alloc_size]()
        }
        real_size = bu.real_size;

        memcpy(_digits,bu._digits,sizeof(CONT_TYPE) * bu.alloc_size);
    }
    /*
    BigUnsigned (const BigUnsigned& bu)
        : real_size(bu.real_size)
    {
        cout << "called copy constructor" << endl;
        if (bu.real_size > alloc_size){
            alloc_size = bu.alloc_size;
            _digits = new CONT_TYPE[alloc_size];
            ///_digits = (CONT_TYPE*)(ptr); /// new CONT_TYPE[alloc_size]{0} ИЛИ new CONT_TYPE[alloc_size]()
        }
        real_size = bu.real_size;

        memcpy(_digits,bu._digits,sizeof(CONT_TYPE) * bu.alloc_size);
    }
    */



    void _remove_leading_zeros();

    /// ìåìîðè ñòàôô
    void alloc_with_zeros(const int sz);
    void assign_from_BU(const int alloc_space, const BigUnsigned& bu);

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
	void operator +=(const BigUnsigned&);

    void operator++();

    void operator -=(const BigUnsigned& minus);

    friend BigUnsigned x_mul(const BigUnsigned& a,const BigUnsigned& b);
    friend BigUnsigned k_mul(const BigUnsigned& left,const BigUnsigned& right);


    /// Êàðàöóáà, êñòàòè ìåíÿåò êîíòåéíåðíûé ðàçìåð ÷èñåëîê...
    friend BigUnsigned karatsuba(BigUnsigned& left,BigUnsigned& right);

    friend BigUnsigned Reciprocal(const BigUnsigned& bu,int precision);

    friend BigUnsigned DivisionWithKnownReciprocal(const BigUnsigned& number, const BigUnsigned&, BigUnsigned& div, const int );

	void _add(const BigUnsigned&);

	~BigUnsigned (){
	    _digits = NULL;
        delete[] _digits;
	}
};

#include "BigUnsigned.cpp"

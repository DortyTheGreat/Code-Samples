/*
---------------------
This File was Build Automatically by DortyBuild v 1.4.
For More Information ask:
Discord: �����#9030 
---Original---Code---

#include <bits/stdc++.h>
#include "../../../DortyLibs/DortyBuild.h"
using namespace std;
#include "../../../../DortyLibs/DinCBigInt/BigUnsigned.h"




signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    BigUnsigned a,b;
    while(cin >> a >> b){
        cout << a + b << endl;
    }




}



*/
#include <bits/stdc++.h>
#include <fstream>
using namespace std;
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


//template <const int def_base = default_base, int BASE = total_base, const int container_stack = cnt_stack>
class BigUnsigned{
public:
    CONT_TYPE* digits;
    static const CONT_TYPE BASE = total_base;
    ubi_szt real_size; /// ÐÅÀËÜÍÀß Äëèííà ÷èñëà
    ubi_szt alloc_size; /// Äëÿ óïðîùåíèÿ ðåàëèçàöèè alloc_size - âñåãäà ñòåïåíü äâîéêà, òàê ìîæíî áóäåò óäîáíî äåëèòü ìàññèâ íà äâå\\÷åòûðå ðàâíûå ÷àñòè.
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

	~BigUnsigned (){
	    digits = NULL;
        delete[] digits;
	}
};


#include <algorithm> /// ��� ������� string

char FromIntToChar(int a){
    if (a >= 0 && a <= 10){
        return (a + '0');
    }
    return (a - 10) + 'A';
}

int FromCharToInt(char a){
    if (a >= '0' && a <= '9'){
        return a - '0';
    }
    return (a - 'A')+10;
}

BigUnsigned::operator std::string() const{
    /*
	if ( (bi.digits.size() == 1) && (bi.digits[0] == 0)){
        os << FromIntToChar(0);
        return os;
    }
    */



    CONT_TYPE Carret;
    std::string buff = "";
    for(int i = 0;i<real_size;++i){
        Carret = digits[i];
        for(int j = 0; j < cnt_stack;++j){
            buff += FromIntToChar(Carret % default_base);
            Carret /= default_base;
        }

    }


    /// ������ ���������� ����
    while(buff.back() == '0' ){
        buff.pop_back();
        if (buff.empty()){
            return "0";
        }
    }



    reverse(buff.begin(),buff.end());

	return buff;
}

// �������� ����� � ����� ������
std::ostream& operator <<(std::ostream& os, const BigUnsigned& bi) {
    return os << std::string(bi);
}

int next_power_of_two(int n) {
    int i = 0;
    for (--n; n > 0; n >>= 1) {
        i++;
    }
    return 1 << i;
}

std::istream& operator>>(std::istream& in, BigUnsigned &bi) {


    std::string stream_;
    in >> stream_;

    new (&bi) BigUnsigned(stream_);

    /// �� ��� ���� �������������� "����������" ����, �� ��

    return in;

}

/*
/// �������� ���� ������������� (������������� �����������)
void BigInt::_add(const BigInt& right) {
    size_t extra_size = 1;

    size_t an_sz = right.digits.size();

    if (an_sz > digits.size()){
        extra_size = an_sz - digits.size() + 1;
    }

    for(size_t i = 0;i < extra_size; i++){
        digits.push_back(0);
    }
    /// ��������� ��������� ������, ����� ���� ����� ��� ����� ��������� �����(aka �������)

    for(size_t i = 0; i < an_sz;i++){
        digits[i] += right.digits[i];
        if (digits[i] >= BASE){
            digits[i] -= BASE;
            digits[i+1]++;
        }
    }

    while(digits[an_sz] >= BASE){
        digits[an_sz] -= BASE;
        an_sz++;
        digits[an_sz]++;
    }



    _remove_leading_zeros();
}

/// ��������� ��������� ���� ������������� ����� (��������, ���� ������ ������ �������)
void BigInt::_subtract(const BigInt &another){

    size_t an_sz = another.digits.size();

    for(size_t i = 0; i < an_sz;i++){
        digits[i] -= another.digits[i];
        if (digits[i] < 0){
            digits[i] += BASE;
            digits[i+1]--;
        }
    }

    while(digits[an_sz] < 0){
        digits[an_sz] += BASE;
        an_sz++;
        digits[an_sz]--;
    }



    _remove_leading_zeros();
}
*/
void BigUnsigned::operator +=(const BigUnsigned& right) {
    if (right.alloc_size > alloc_size){
        /// ����� ������������
        return;
    }

    if (right.alloc_size < alloc_size){
        if (digits[alloc_size - 1] == (BASE-1) ){
            /// ����� ��������� ������������
        }
    }


}
/**

�������� ���������� ���������, ���� ...

+ �� ������ ��� real_size

*/
void BigUnsigned::operator -=(const BigUnsigned& minus) {

    for(int i = 0;i< minus.real_size; ++i){
        digits[i] -= minus.digits[i];
        if (digits[i] < 0){
            digits[i] += BASE;
            --digits[i+1];
        }
    }

    if (minus.real_size != real_size){



        /// ������ ��� ������ ������ �� ����� ������ :-)
        for(int j = minus.real_size; digits[j] < 0;++j){

            digits[j] += BASE;
            --digits[j+1];

        }
    }

    _remove_leading_zeros();




}

/**

���������� ������ ����� � ���������. ������ ��� ������� ���������� � ����.

*/
void BigUnsigned::_add(const BigUnsigned& right) {

    for(int i = 0;i < right.real_size; ++i){
        digits[i] += right.digits[i];
        if (digits[i] >= BASE){
            digits[i] -= BASE;
            ++digits[i + 1];
        }
    }

    /// �������, ��, ��� ���� ������� ��� ������, �� ��� ���� +- ������
    CONT_TYPE *p = &digits[right.real_size];
    while (*p >= BASE){
        *p -= BASE;
        ++p;
        ++(*p);
    }


    /*
    CONT_TYPE &p = digits[right.real_size];
    while (p >= BASE){
        p -= BASE;
        (&p)++;
        ++(p);
    }
    */

    /// ��� ���� ������� ��������
    real_size = std::max(real_size, right.real_size);
    if (real_size != alloc_size){
        if (digits[real_size] != 0){
            ++real_size;
        }
    }


}



/*
/// ������ �������� (� ������ ������ � �������)
void BigInt::operator-=(BigInt right){

    ///std::cout << *this << " " << right << " "<<(compare(*this,right)) << std::endl;
    bool comp_ = !(compare(*this,right));
    if ( comp_){
        ///std::cout << "second is hisher" << std::endl;
        swap(right,*this);
        _is_negative = !_is_negative;
    }


    if ( (_is_negative == right._is_negative) ^ (comp_) ) {
        // ��������� �� �����
        _subtract(right);
    }else{
        // ������ �� �����.
        _add(right);
    }

}
*/





// ���������� ����� ����������� �����
//const BigInt BigInt::operator +() const {
//	return BigInt(*this);
//}
/*
// ���������� ���������� ����� � ������ ������
const BigInt BigInt::operator -() const {
	BigInt copy(*this);
	copy._is_negative = !copy._is_negative;
	return copy;
}
*/


/**

���������� � �������� ����� ����� � ����� ����� � ������ (��������� ����� ����������� ��� �� ������� ����� ->)

*/


const BigUnsigned operator +(const BigUnsigned& left, const BigUnsigned& right) {
    if (left.real_size < right.real_size){
        return right+left;
    }


    BigUnsigned ret;
    ret.assign_from_BU(left.real_size+1,left);




    ret._add(right);

	return ret;
}


const BigUnsigned operator +(BigUnsigned&& left, const BigUnsigned& right) {
    ///cout << "called rvalue" << endl;
    if (left.real_size < right.real_size){
        //return right+left;
    }

    left += right;

	return left;
}



// ���������� ���������
void BigUnsigned::operator++() {

	++digits[0];
	for ( ubi_szt cou = 0; cou < real_size -1; ++cou){
        if (digits[cou] < BASE){ return;}

        digits[cou] -= BASE; /// ����� �������� = 0 � �����, ���� ����������� ����� ��������������
        ++digits[cou+1];
	}

    if (digits[real_size - 1] >= BASE ){
        if (real_size == alloc_size){
            /// reallocate memory
            CONT_TYPE * new_c = new CONT_TYPE[++alloc_size];
            memcpy(new_c, digits, real_size * sizeof(CONT_TYPE));
            new_c[real_size] = 0;
            digits = new_c;
        }

        digits[real_size - 1] -= BASE;
        ++digits[real_size++];

    }
}

void BigUnsigned::operator--() {

	--digits[0];



    for(int j = 0; digits[j] < 0;++j){

        digits[j] += BASE;
        --digits[j+1];

    }


    _remove_leading_zeros();
}




BigUnsigned::BigUnsigned()
: digits( new CONT_TYPE[1])
, real_size(1)
, alloc_size(1)
{digits[0] = 0;}

BigUnsigned::BigUnsigned (BigUnsigned&& bu)
: digits( bu.digits  )
, real_size( bu.real_size )
, alloc_size( bu.alloc_size )
{bu.digits = NULL;}

BigUnsigned::BigUnsigned(const BigUnsigned& bu) : real_size(bu.real_size)
{
    ///cout << "called copy constructor" << endl;
    if (bu.real_size > alloc_size){
        alloc_size = bu.alloc_size;
        digits = new CONT_TYPE[alloc_size];
        ///digits = (CONT_TYPE*)(ptr); /// new CONT_TYPE[alloc_size]{0} ��� new CONT_TYPE[alloc_size]()
    }
    real_size = bu.real_size;

    memcpy(digits,bu.digits,sizeof(CONT_TYPE) * bu.alloc_size);

}

BigUnsigned& BigUnsigned::operator= (BigUnsigned&& bu)
{
    //cout << "called move equality" << endl;
    digits = ( bu.digits  );
    real_size = ( bu.real_size );
    alloc_size = ( bu.alloc_size );


    bu.digits = NULL;
    return *this;
}

BigUnsigned& BigUnsigned::operator= (const BigUnsigned& bu){
    ///cout << "called copy equality" << endl;
    if (bu.real_size > alloc_size){
        alloc_size = bu.alloc_size;
        digits = new CONT_TYPE[alloc_size];


        ///digits = (CONT_TYPE*)(ptr); /// new CONT_TYPE[alloc_size]{0} ��� new CONT_TYPE[alloc_size]()
    }
    real_size = bu.real_size;

    memcpy(digits,bu.digits,sizeof(CONT_TYPE) * bu.alloc_size);

    return *this;
}

void BigUnsigned::alloc_with_zeros(const int sz){
    alloc_size = sz;
    digits = new CONT_TYPE[sz]{0};

}

/**

���� �����, ��� � ��������=, �� ����� ������� ���������� ������ ��� ���������

���������� �� ���_��� http://cppstudio.com/post/673/

*/
void BigUnsigned::assign_from_BU(const int alloc_space, const BigUnsigned& bu){
    alloc_with_zeros(alloc_space);
    real_size = bu.real_size;
    memcpy(digits,bu.digits,real_size * sizeof(CONT_TYPE));
}


/**
    ��������� �������. ��������� ��� ��� �������, ����� real_size ���� ��� "��������" ������.
    (������ ��������� real_size)
*/
void BigUnsigned::_remove_leading_zeros(){
    int cur = real_size - 1;
    for( ; cur != 0 ; --cur){
        if (digits[cur] != 0){
            break;
        }
    }
    real_size = cur + 1;
}



BigUnsigned::BigUnsigned (const std::string& stream_){
    ubi_szt carret_r_sz = stream_.size();
    real_size = (carret_r_sz+cnt_stack-1)/cnt_stack;
    alloc_with_zeros(next_power_of_two(real_size));

    CONT_TYPE Carret;

    for(ubi_szt i = 0;i<real_size;++i){
        Carret = 0;
        for(ubi_szt j = 0; j < cnt_stack;++j){
            int index = carret_r_sz - (i+1)*cnt_stack + j;
            if (index > -1){
                Carret *= default_base;
                Carret += FromCharToInt(stream_[index]);
            }
        }

        digits[i] = Carret;
    }
}










/// ��������� ��������� ���� ������������� ����� (0 => ������ ������, 1 => �����, 2 => ���� ������)
short inline compare(const BigUnsigned &left, const BigUnsigned &right){
    size_t sz = left.real_size;
    if (right.real_size != left.real_size){
        return (left.real_size > right.real_size) << 1;
    }



    for (size_t i = 0;i<sz;i++){
        int p = sz - i - 1;
        if (left.digits[p] != right.digits[p]){
            return (left.digits[p] > right.digits[p]) << 1;
        }
    }

    return 1;
}




// ���������, �������� �� ����� ������� ������ �������
bool operator <(const BigUnsigned& left, const BigUnsigned& right) {

    size_t sz = left.real_size;
    if (right.real_size != left.real_size){
        return (left.real_size < right.real_size);
    }



    for (size_t i = 0;i<sz;i++){
        int p = sz - i - 1;
        if (left.digits[p] != right.digits[p]){
            return (left.digits[p] < right.digits[p]);
        }
    }

    return 0;
}

// ���������, �������� �� ����� ������� ������ �������
bool operator ==(const BigUnsigned& left, const BigUnsigned& right) {

    size_t sz = left.real_size;
    if (right.real_size != left.real_size){
        return 0;
    }



    for (size_t i = 0;i<sz;i++){
        int p = sz - i - 1;
        if (left.digits[p] != right.digits[p]){
            return 0;
        }
    }

    return 1;
}

bool operator !=(const BigUnsigned& left, const BigUnsigned& right) {
	return !(left == right);
}

bool operator <=(const BigUnsigned& left, const BigUnsigned& right) {
	return !(right < left);
}

bool operator >(const BigUnsigned& left, const BigUnsigned& right) {
	return (right < left);
}

bool operator >=(const BigUnsigned& left, const BigUnsigned& right) {
	return !(left < right);
}


/* Grade school multiplication, ignoring the signs.
 * Returns the absolute value of the product, or NULL if error.
 */
 /// �������� ��������� ��������� (����� � ����� ������ -> ��. https://hg.python.org/cpython/file/b514339e41ef/Objects/longobject.c#l2694)
 /// �� �������� ��������� � ����
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
        DOUBLE_CONT_TYPE f = a.digits[i];
        CONT_TYPE *pz = z.digits + i;
        CONT_TYPE *pb = b.digits;
        CONT_TYPE *pbend = b.digits + size_b;

        /// SIGCHECK ???

        while (pb < pbend) {
            carry += *pz + *pb++ * f;
            *pz++ = (carry % BASE);
            carry /= BASE;
        }
        if (carry)
            *pz += (carry % BASE);
    }


    if (z.digits[z.alloc_size - 1] == 0){
         z.real_size = z.alloc_size - 1;
    }else{
         z.real_size = z.alloc_size;
    }

    return z;
}


/// ��� ��� ��������, �� �������!
/**

� ������ ��� ��� ������������ ���� ����� ��������� ������, �� ����� ����� �������.

*/
void x_mul(const CONT_TYPE *__restrict a, CONT_TYPE *__restrict b, CONT_TYPE *__restrict res,const ubi_szt n)
{

    ubi_szt i;




    ///memset(z->ob_digit, 0, Py_SIZE(z) * sizeof(digit));

    for (i = 0; i < n; ++i) {
        DOUBLE_CONT_TYPE carry = 0;
        DOUBLE_CONT_TYPE f = a[i];
        CONT_TYPE *pz = res + i;
        CONT_TYPE *pb = b;
        CONT_TYPE *pbend = b + n;

        /// SIGCHECK ???

        while (pb < pbend) {
            carry += *pz + *pb++ * f;
            *pz++ = (carry % BASE);
            carry /= BASE;
        }
        if (carry)
            *pz += (carry % BASE);
    }



}

#define KAR_TRESH 20



/**

������ ��������.
�������: 2 "�����" ������ ������ �����, (����� ����� ������������� ���� �������), � ����� � ������, ����
��������� ��������� ��������� (����� ����� ���� ������� �������� � ��������� ������)

(������ �� � ������ ��������� ��� �� ��������� �����, ��� ��� ���� ���� ��������� �� ������� �����, ��� �������� ��� �� ����� � ������)

TO-DO:

1) ������ ������ � ���� ���������� (������ ����)
2) ...
3) �������� "��������" �������
4) �������� ������ �����


*/

void mult(const CONT_TYPE * a, CONT_TYPE * b, CONT_TYPE *__restrict res, const ubi_szt n) {

    /// ������� ��������� �����, ��������� �������� ��������
    if (n <= KAR_TRESH) {
        x_mul(a,b,res,n);
    } else {

        const ubi_szt fh = (n+1) / 2;   // First half Data (take more)
        const ubi_szt sh = (n - fh); // Second half of Data

        CONT_TYPE* first = new CONT_TYPE[fh + 1];
        first[fh] = 0;

        CONT_TYPE* second = new CONT_TYPE[fh + 1]; second[fh] = 0;



        memcpy(first,a,fh * sizeof(CONT_TYPE));
        memcpy(second,b,fh * sizeof(CONT_TYPE));



        /// ��� ���� ����� �������� ��������
        for (ubi_szt i = 0; i < sh; i++) {
            first[i] += a[i + fh];

            if (first[i] >= BASE){
                first[i] -= BASE;
                ++first[i+1];
            }

            second[i] += b[i + fh];
            if (second[i] >= BASE){
                second[i] -= BASE;
                ++second[i+1];
            }
        }
        /// ���. ��� �� ������������ ���������� ����������
        if (first[fh - 1] >= BASE){
                first[fh - 1] -= BASE;
                ++first[fh];
            }
        if (second[fh - 1] >= BASE){
            second[fh - 1] -= BASE;
            ++second[fh];
        }


        /// first += a offseted by fh
        /// second += b offseted by sh


        //mult(first, second, res + fh, fh + 1);
        //delete first;
        //delete second;

        mult(a + 0, b + 0, res, fh);
        mult(a + fh, b + fh, res + fh*2, sh);
        CONT_TYPE * we_need_to_optimize_memory = new CONT_TYPE[2* (fh + 1)]{0};


        mult(first, second, we_need_to_optimize_memory, fh + 1);

        for(ubi_szt i = 0; i < 2 * sh; ++i){

            we_need_to_optimize_memory[i] -= (res[i] + res[2 * fh + i]);

        }

        if (sh != fh){

            we_need_to_optimize_memory[2 * sh] -= res[2 * sh];
            we_need_to_optimize_memory[2 * sh + 1] -= res[2 * sh + 1];
        }

        /// ��� ���� ������� ��������� !!
        for(ubi_szt i = 0; i < 2 * fh + 2;++i){

            res[fh + i] += we_need_to_optimize_memory[i];
            if (res[fh + i]  >= BASE){
                res[fh + i] -= BASE;
                ++res[fh + 1 + i];
            }else{
                while (res[fh + i]  < 0){
                    res[fh + i] += BASE;
                    --res[fh + 1 + i];
                }
            }
        }







        /// �� ������ �� ������ ������������� ������, �� � �������



    }


}



/// ���� �������� ������, ��� � ����� ���������� ������

/// �� �� ����� ��������, ������ real_size ���������� -> ��� ��������� �� ���� ������ ����
/// ��� �������� ������ � �������
BigUnsigned karatsuba(BigUnsigned& left, BigUnsigned& right){
    /// ���� ������ ������ -> ����� ��������� ����� ������ ����������
    if (left.alloc_size < right.real_size){
        CONT_TYPE *remem = left.digits;
        left.alloc_with_zeros(right.real_size);

        memcpy(left.digits, remem, left.real_size * sizeof(CONT_TYPE));
    }


    /// ���� ����� ������ -> ������ � ������������ ������
    if (right.alloc_size < left.real_size){
        //cout << right << endl;
        CONT_TYPE *remem = right.digits;
        right.alloc_with_zeros(left.real_size);

        memcpy(right.digits, remem, right.real_size * sizeof(CONT_TYPE));
        //cout << right << endl;
    }





    BigUnsigned res;
    res.alloc_with_zeros(2 * std::max(left.real_size,right.real_size));
    mult(left.digits,right.digits,res.digits,std::max(left.real_size,right.real_size));



    if (res.digits[res.alloc_size - 1] == 0){
         res.real_size = res.alloc_size - 1;
    }else{
         res.real_size = res.alloc_size;
    }



    return res;

}





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










signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    BigUnsigned a,b;
    while(cin >> a >> b){
        cout << a + b << endl;
    }




}




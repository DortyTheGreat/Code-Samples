/*
---------------------
This File was Build Automatically by DortyBuild v 1.3.
For More Information ask:
Discord: Тесла#9030 
---Original---Code---

//#pragma GCC optimize("fast-math")

#include <iostream>
#include <iomanip>

using namespace std;

#include <algorithm>

#include "../DortyLibs/OperatorBigInt.h"
#include "../DortyLibs/DortyBuild.h"

#include <fstream>



using namespace std;

int main()
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    AppBuild();

    BigInt a,b;

    BigInt * c;

    fin >> a >> b;
    c = k_mul(&a,&b);
    fout << *c << endl;


    return 0;
}

*/
//#pragma GCC optimize("fast-math")

#include <iostream>
#include <iomanip>

using namespace std;

#include <algorithm>

#include <vector>


#define debug_delenie false

#include <cmath>

//#define int long long

#define char_zero '0'

int intlog(double base, double x) {
    return (int)(log(x) / log(base));
}
/// 9 223 372 036 854 775 807
/// 2 147 483 647
const int INT_MAXI = 2147483647;

int inline intSqrt(int arg){
    return (int)(sqrt(arg));
}

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

const int zero = 0;

#define default_base 10

#define container_stack 9 /// 6

#define total_base 1000000000 /// 1000000

#define sqrt_of_total_base 3 /// 1000

/// Реализация класса больших чисел, через массив нестабильных битов.
class BigInt{
private:
    void _remove_leading_zeros();
    bool _is_negative = false;



public:
    /// 1234 === [4,3,2,1]
    vector<int> data;
    int Base = -1;

    int rsz = -1;

    void operator=(const BigInt &another){
        data = another.data;
        Base = another.Base;
    }

    BigInt(){data = {0};Base = total_base;}

    BigInt(long long num, int Base_ = total_base){
        Base = Base_;
        while(num != 0){
            data.push_back(num % Base_);
            num /= Base;
        }

        if (data.size() == 0){
            data.push_back(0);
        }
    }

    /// Обработка сравнения двух положительных чисел (0 => второе больше, 1 => равны, 2 => наше больше)
    short inline compare(const BigInt &another){
        if (another.data.size() != data.size()){
            return (data.size() > another.data.size()) << 1;
        }

        int sz = data.size();

        for (int i = 0;i<sz;i++){
            int p = sz - i - 1;
            if (data[p] != another.data[p]){
                return (data[p] > another.data[p]) << 1;
            }
        }

        return 1;
    }

    friend bool operator <(const BigInt&, const BigInt&);
    friend bool operator ==(const BigInt&, const BigInt&);
	friend bool operator !=(const BigInt&, const BigInt&);
	friend bool operator <=(const BigInt&, const BigInt&);
	friend bool operator >(const BigInt&, const BigInt&);
	friend bool operator >=(const BigInt&, const BigInt&);

    /// Обработка сложения двух положительных чисел
    void inline _add(const BigInt &another){

        size_t extra_size = 1;

        size_t an_sz = another.data.size();

        if (an_sz > data.size()){
            extra_size = an_sz - data.size() + 1;
        }

        for(size_t i = 0;i < extra_size; i++){
            data.push_back(zero);
        }
        /// Заполняем контейнер нулями, чтобы было место под новые возможные числа(aka разряды)

        for(size_t i = 0; i < an_sz;i++){
            data[i] += another.data[i];
            if (data[i] >= Base){
                data[i] -= Base;
                data[i+1]++;
            }
        }

        while(data[an_sz] >= Base){
            data[an_sz] -= Base;
            an_sz++;
            data[an_sz]++;
        }



        _remove_leading_zeros();
    }

    void operator +=(const BigInt& right) {
        if (_is_negative == right._is_negative){
            _add(right);
        }else{
            _is_negative = !_is_negative;
            *this -= right;
        }
    }

    const BigInt operator +() const;
    const BigInt operator -() const;


    /// Верный оператор (с учётом знаков и прочего)
    void operator-=(BigInt another){
        short comp_ = !(compare(another));
        if ( comp_){
            swap(another,*this);
            _is_negative = !_is_negative;
        }


        if ( (_is_negative == another._is_negative) ^ (comp_) ) {
            // Одинаковы по знаку
            _subtract(another);
        }else{
            // Разные по знаку.
            _add(another);
        }

    }



    /// Обработка вычитания двух положительных чисел (работает, если второе меньше первого)
    void _subtract(const BigInt &another){

        size_t an_sz = another.data.size();

        for(size_t i = 0; i < an_sz;i++){
            data[i] -= another.data[i];
            if (data[i] < zero){
                data[i] += Base;
                data[i+1]--;
            }
        }

        while(data[an_sz] < 0){
            data[an_sz] += Base;
            an_sz++;
            data[an_sz]--;
        }



        _remove_leading_zeros();
    }

    /// Обработка умножения числа на маленькое( такое, что (Base-1)*number < INT_MAX )
    void inline _mult(const int number){

        if (number == 0){data = {0}; return;}

        size_t sz = data.size();
        for(size_t i = 0;i < sz; ++i ){
            data[i] *= number;
        }
        --sz;
        for(size_t i = 0;i < sz; ++i){
            data[i+1] += data[i] / Base;
            data[i] %= Base;
        }

        while (data[sz] >= Base){
            data.push_back(data[sz] / Base);
            data[sz] %= Base;
            ++sz;
        }

    }

    void operator *=(int);
    void operator /=(int);
    /// FFT <- friend const BigInt operator *(const BigInt&, const BigInt&);
    friend const BigInt operator *(const BigInt&,const BigInt&);
    friend const BigInt operator *(BigInt, int);
    friend const BigInt operator /(BigInt, BigInt);
    const BigInt operator /(int);
    void operator *=(const BigInt&);

    //BigInt& operator *=(const big_integer&);

    BigInt reqKar(int l, int r, BigInt& another){
        /*
        int n = MakeEqualLength(X, Y);

        if (n == 1) return std::to_string(std::stoi(Y) * std::stoi(X));

        int fh = n / 2;   // First half of string
        int sh = (n - fh); // Second half of string, ceil(n/2)

        // Find the first half and second half of first string.
        std::string X1 = X.substr(0, fh);    // high half
        std::string X0 = X.substr(fh, sh);   // low half

        // Find the first half and second half of second string
        std::string Y1 = Y.substr(0, fh);
        std::string Y0 = Y.substr(fh, sh);

        // Recursively calculate the three products of inputs of size n/2
        // Z0 = X0 * Y0
        std::string Z0 = MultiplyRecur(X0, Y0);
        // Z2 = X1 * Y1
        std::string Z2 = MultiplyRecur(X1, Y1);
        // Z1 = (X0 + X1)(Y0 + Y1) - Z0 - Z2
        std::string Z1 = MultiplyRecur(Add(X0, X1), Add(Y0, Y1));
        Z1 = Subtraction(Z1, Add(Z0, Z2));

        // return added string version
        // Z = Z2 * (10^(low half digits * 2)) + Z1 * (10^(low half digit)) + Z0
        return Add(Add(Shift(Z2, sh*2), Z0), Shift(Z1, sh));
        */
        return BigInt(12);
    }

    void _kar_mult(const BigInt& another, BigInt &write_to){



    }

    /// Возводит число в натуральную степень
    void inline _pow(int pow_){

        BigInt cp = (*this);
        data = {1};
        for (; pow_; pow_ >>= 1) {
            if (pow_ & 1)
                (*this) *= cp;
            cp *= cp;
        }


    }

    /// Возводит число в натуральную степень, оставляя лишь
    void inline _pow(int pow_,BigInt &write_to, size_t truncateddata){

        BigInt cp = (*this);
        data = {1};
        for (; pow_; pow_ >>= 1) {
            if (pow_ & 1)
                (*this) *= cp;
            cp *= cp;



            if (cp.data.size() > truncateddata){cp.data.resize(truncateddata);cp._remove_leading_zeros();}
            if (data.size() > truncateddata){data.resize(truncateddata);_remove_leading_zeros();}
        }


    }

    /// Делит число на короткое
    int inline _divide(int digit_, BigInt &to_write){
        to_write.data = {};
        to_write.Base = Base;
        int Carret = 0;
        int sz = data.size() - 1;
        for(int i = sz;i > -1; --i){
            Carret *= Base;
            Carret += data[i];
            to_write.data.push_back(Carret / digit_);
            Carret %= digit_;
        }



        reverse(to_write.data.begin(),to_write.data.end());

        to_write._remove_leading_zeros();

        return Carret;

    }

    void inline Interate(BigInt &b, int precision)
    {

        // 2 * X(i)
        BigInt minus_ = *this;
        minus_ *= minus_;
        minus_ *= b;

        minus_._ShiftR(precision);

        _mult(2);

        _subtract(minus_);
        /// this - 2*this*this*b*SHIFT_R

    }

    /// То сколько можно взять в int чисел из контейнеров


    const BigInt Reciprocal(int precision);

    void inline _DivUnrefined( BigInt &divisor, size_t precision, BigInt &write_to)
    {

        write_to = divisor.Reciprocal(precision) * (*this);
    }

    void inline _DivInt( BigInt &divisor, BigInt &write_to)
    {

        if ( (data[data.size() - 1] == 0) || (divisor.data.size() > data.size()) ){write_to = 0; return;}
        size_t precision = data.size() + 4;
        _DivUnrefined(divisor,precision,write_to);
        write_to._ShiftR(precision);
        if (write_to.data.size() == 0){
            write_to.data.push_back(0);
        }
    }

    void inline _DivIntRem( BigInt &divisor, BigInt &write_to, BigInt &rem_write_to)
    {
        _DivInt(divisor,write_to);
        rem_write_to = *this;
        BigInt minus_ = write_to;
        minus_ *= divisor;
        rem_write_to._subtract(minus_);
    }

    /// В некоторых случаях, если число - это на 1 меньше, чем полный квадрат, то ответом будет число на один больше
    /// Например 24 -> 5, 48 -> 7, 35 -> 6
    /// safe_sqrt избегает этого
    void inline _sqrt()
    {
        if (data.size() == 1){*this = (intSqrt(data[0])); return;}
        BigInt copy_ = (*this);



        int sz = data.size();
        ///int rsz = (sz-1)*container_stack + intlog(default_base,data[sz - 1]) + 1;
        //cout << sz <<" rsz : " << rsz << endl;
        data.clear();



        data.push_back (intSqrt(data[sz-1]) * ((sz%2) ? 1 : sqrt_of_total_base) );

        _appendZeros((sz - 1) / 2 );

        ///cout << *this << endl;

        // Do the interation to fullfil the precision
        int end{  (int)(log2(sz)) + 6 };

        //cout << *this << endl;

        BigInt smth;
        BigInt tmp;

        for (int i = 0; i < end; i++)
        {

            // x(i) * 10^precision + a * 10^(2*precision) / x(i)
            copy_._DivInt(*this, smth); /// double the precision here (of normal)


            _add(smth);
            tmp = *this;
            tmp._divide(2,*this);
            ///cout << "Cycle "<< i << " " << (*this) << endl;
        }





        ///_ShiftR(1);


    }



    void inline safe_sqrt(){

        BigInt orig = *this;

        _sqrt();

        BigInt cp = *this;
        cp *= cp;
        if ( orig < cp){
            *this -= 1;
        }
    }


    /// Дописывает "подчисло" в write_to, начиная с БОЛЬШИХ разрядов

    /// Пример
    /// write_to = [4,3,2,1](1234), this=[8,7,6,5](5678), length = 2

    /// => write_to = [4,3,2,1,6,5](561234)
    void _subInt(int length, BigInt &write_to){
        int sz = data.size();
        for(int i = 0;i<length;i++){
            write_to.data.push_back(data[i + sz -length]);
        }
    }

    /// Убирает с конца числа length цифр
    /// [5,4,3,2,1](12345) (length=3)-> [2,1](12)
    void inline _ShiftR(int length){

        data.erase(data.begin(), data.begin() + length);

    }

    /// [5,4,3,2,1](12345) (length=3)-> [0,0,0,5,4,3,2,1](12345000)
    /// Следует Улучшить. Ужасно плохо реализованно
    void inline _appendZeros(int length){
        vector<int> v1(length);
        vector<int> tmp = data;
        data.clear();
        std::merge(v1.begin(), v1.end(), tmp.begin(), tmp.end(), std::back_inserter(data));
    }




    friend istream& operator>>(istream& in, BigInt &bi) {



        if (bi.Base == -1){
            bi.Base = total_base;
        }

        string stream_;
        in >> stream_;

        int sz = stream_.size();
        bi.rsz = sz;
        sz = (sz+container_stack-1)/container_stack; /// /= по ceil
        bi.data.resize(sz);

        int Carret;

        for(int i = 0;i<sz;++i){
            Carret = 0;
            for(int j = 0; j < container_stack;++j){
                int index = bi.rsz - (i+1)*container_stack + j;
                if (index > -1){
                    Carret *= default_base;
                    Carret += FromCharToInt(stream_[index]);
                }
            }

            bi.data[i] = Carret;
        }

        bi._remove_leading_zeros();

        return in;

    }

    friend ostream& operator<<(ostream &in, const BigInt &bi) {

        if ( (bi.data.size() == 1) && (bi.data[0] == 0)){
            in << FromIntToChar(0);
            return in;
        }

        int sz = bi.data.size();
        if (bi._is_negative){in << '-';}
        int Carret;
        string buff = "";
        for(int i = 0;i<sz;++i){
            Carret = bi.data[i];
            for(int j = 0; j < container_stack;++j){
                buff += FromIntToChar(Carret % default_base);
                Carret /= default_base;
            }

        }

        while(buff.back() == char_zero){
            buff.pop_back();
        }

        reverse(buff.begin(),buff.end());

        in << buff;
        return in;
    }

    /*
    void Stabilize(){
        for(int i=SIZEE_-1;i>-1;i--){
            OneNumTransform(i);
        }
    }
    */

};

void get_sqrt(BigInt &take_from, BigInt &to_write){

    to_write = 0;
    int prefix = 2;
    int sz = take_from.data.size();

    int Carret = take_from.data.back();

    vector<int> reverse_ans;

    if (sz % 2 == 0){
        Carret *= take_from.Base;
        Carret += take_from.data[sz - 2];
        prefix++;
    }

    int iSqrt_ = intSqrt(Carret);
    reverse_ans.push_back(iSqrt_);
    Carret = Carret - iSqrt_*iSqrt_;


    cout << "Carret : "<< Carret << endl;


    for (int i = sz-prefix;i>=0;i-=2)
    {

        Carret *= take_from.Base;
        Carret += take_from.data[i];

        Carret *= take_from.Base;
        Carret += take_from.data[i - 1];


        iSqrt_ = intSqrt(Carret);
        cout << iSqrt_ << endl;
        cout << "Carret : "<< Carret << endl;
        reverse_ans.push_back(iSqrt_);
        Carret -= iSqrt_*iSqrt_;
        cout << "Carret : "<< Carret << endl;
    }



}


///

const BigInt operator +(BigInt left, const BigInt& right) {
    left += right;
    return left;
}

const BigInt operator -(BigInt left, const BigInt& right) {
    left -= right;
    return left;
}

void BigInt::operator *=(int number) {
    if (number == 0){data = {0}; return;}
    if (number < 0){_is_negative = !_is_negative; number = abs(number);}
    size_t sz = data.size();
    for(size_t i = 0;i < sz; ++i ){
        data[i] *= number;
    }
    --sz;
    for(size_t i = 0;i < sz; ++i){
        data[i+1] += data[i] / Base;
        data[i] %= Base;
    }

    while (data[sz] >= Base){
        data.push_back(data[sz] / Base);
        data[sz] %= Base;
        ++sz;
    }
}

const BigInt BigInt::operator / (int number) {
    BigInt write_to;
    write_to.data = {};
    write_to.Base = Base;
    int Carret = 0;
    int sz = data.size() - 1;
    for(int i = sz;i > -1; --i){
        Carret *= Base;
        Carret += data[i];
        write_to.data.push_back(Carret / number);
        Carret %= number;
    }



    reverse(write_to.data.begin(),write_to.data.end());

    write_to._remove_leading_zeros();

    return write_to;

    ///
    /// Остаток <- return Carret;
}


/** FFT
const BigInt operator *(const BigInt& left, const BigInt& right) {
    BigInt ret;
    ret._is_negative = left._is_negative != right._is_negative;
    ret.Base = left.Base;
    ret.data = FFT::convolution(left.data, right.data);


    size_t sz = ret.data.size() - 1;
    for(size_t i = 0;i < sz; ++i ){
        ret.data[i + 1] += ret.data[i] / ret.Base;
        ret.data[i] %= ret.Base;
    }


    while (ret.data[sz] >= ret.Base){
        ret.data.push_back(ret.data[sz] / ret.Base);
        ret.data[sz] %= ret.Base;
        ++sz;
    }

    return ret;
}

*/


/// Karatsuba, пока не делает ничего со знаком
const BigInt operator *(const BigInt& left, const BigInt& right) {
    bool flag = (right.data.size() > left.data.size());


    int n = flag ? right.data.size() : left.data.size(); /// size of biggest num

    if (n == 1){return BigInt(left.data[0] * right.data[0]);}
    int fh = (n+1) / 2;   // First half Data (take more)
    int sh = (n - fh); // Second half of Data

    // Find the first half and second half of first string.

    BigInt L0,L1;
    L0.data.resize(fh);
    L1.data.resize(sh);

    BigInt R0;
    BigInt Z0;
    BigInt Z1;


    int _0_sz;
    int s_sz;

    if (!flag){
        for(int i = 0;i<fh;++i){
            L0.data[i] = left.data[i];
        }

        for(int i = 0;i<sh;++i){
            L1.data[i] = left.data[fh + i];
        }


        s_sz = right.data.size();

        _0_sz = min(s_sz, fh);

        R0.data.resize(_0_sz);

        for(int i = 0;i<_0_sz;++i){
            R0.data[i] = right.data[i];
        }

    }else{

        for(int i = 0;i<fh;++i){
            L0.data[i] = right.data[i];
        }

        for(int i = 0;i<sh;++i){
            L1.data[i] = right.data[fh + i];
        }


        s_sz = left.data.size();

        _0_sz = min(s_sz, fh);

        R0.data.resize(_0_sz);

        for(int i = 0;i<_0_sz;++i){
            R0.data[i] = left.data[i];
        }
    }


    Z0 = L0 * R0;
    int _1_sz = s_sz - _0_sz;
    if (_1_sz == 0){
        /// Z2 = 0
        Z1 = L1 * R0; /// no swap

        ///Z1._appendZeros(fh);

        Z1 += Z0;


        return Z1;
    }else{
        BigInt R1;
        R1.data.resize(_1_sz);


        if (!flag){
            for(int i = 0;i<_1_sz;++i){
                R1.data[i] = right.data[fh + i];
            }
        }else{
            for(int i = 0;i<_1_sz;++i){
                R1.data[i] = left.data[fh + i];
            }
        }
        BigInt Z2 = L1 * R1; /// no swap

        Z1 = (L0+L1) * (R0+R1) - (Z2 + Z0);

        ///if ( !(Z1.data.size() == 1 && Z1.data[0] == 0) )
            ///Z1._appendZeros(fh);

        ///if ( !(Z2.data.size() == 1 && Z2.data[0] == 0) )
            ///Z2._appendZeros(fh * 2);

        Z2 += Z1;
        Z2 += Z0;

        return Z2;
    }

}



/*
const BigInt operator *(const BigInt& left, const BigInt& right) {
	BigInt result;
	result.data.resize(left.data.size() + right.data.size());
	for (size_t i = 0; i < left.data.size(); ++i) {
		int carry = 0;
		for (size_t j = 0; j < right.data.size() || carry != 0; ++j) {
			long long cur = result.data[i + j] +
				left.data[i] * 1LL * (j < right.data.size() ? right.data[j] : 0) + carry;
			result.data[i + j] = static_cast<int>(cur % left.Base);
			carry = static_cast<int>(cur / left.Base);
		}
	}

	result._is_negative = left._is_negative != right._is_negative;
	result._remove_leading_zeros();
	return result;
}
*/
// домножает текущее число на указанное
void BigInt::operator *=(const BigInt& value) {
    *this = (*this * value);
}

const BigInt operator /(BigInt left, BigInt right)
{

    if ( (left.data[left.data.size() - 1] == 0) || (right.data.size() > left.data.size()) ){return 0;}
    size_t precision = left.data.size() + 4;
    left._DivUnrefined(right,precision,left);
    left._ShiftR(precision);
    if (left.data.size() == 0){
        left.data.push_back(0);
    }
    return left;
}




const BigInt BigInt::Reciprocal(int precision)
{
    BigInt write_to;

    int mx_sz = intlog(Base, INT_MAXI);
    int sz = data.size();
    int len{ (sz > (mx_sz - 1)) ? (mx_sz) : sz };

    int divisor = 0;





    for(int i = 0;i<len;i++){
        divisor *= write_to.Base;
        divisor += data[sz - i - 1];
    }

    int dividend = 1;
    for(int i = 0;i<len;++i){
        dividend *= Base;
    }


    ///cout << dividend << endl << divisor << endl;
    // Extra condition for initial guess is: x(i) < 2R/b
    write_to = dividend / divisor;



    write_to._appendZeros(precision - sz);

    ///cout << "TestPut " << write_to << endl;

    // Do the interation to fullfil the precision
    int end{ (int)(std::log2(precision)) + 4 };
    for (int i = 0; i < end; i++)
    {
        write_to.Interate(*this, precision);
        ///cout << "InCycle " << write_to << endl;
    }

    return write_to;
}


// проверяет, является ли левый операнд меньше правого
bool operator <(const BigInt& left, const BigInt& right) {

    if (left._is_negative != right._is_negative){
        return left._is_negative;
    }

	if (left.data.size() != right.data.size()){
        return (left.data.size() < right.data.size()) ^ (left._is_negative);
    }

    int sz = left.data.size();

    for (int i = 0;i<sz;i++){
        int p = sz - i - 1;
        if (left.data[p] != right.data[p]){
            return (left.data[p] < right.data[p]) ^ (left._is_negative);
        }
    }

    // Числа равны
    return 0;
}

// проверяет, является ли левый операнд меньше правого
bool operator !=(const BigInt& left, const BigInt& right) {

    if (left._is_negative != right._is_negative){
        return 1;
    }

	if (left.data.size() != right.data.size()){
        return 1;
    }

    int sz = left.data.size();

    for (int i = 0;i<sz;i++){
        int p = sz - i - 1;
        if (left.data[p] != right.data[p]){
            return 1;
        }
    }

    // Числа равны
    return 0;
}


void BigInt::_remove_leading_zeros() {
	while (this->data.size() > 1 && this->data.back() == 0) {
		this->data.pop_back();
	}

	if (this->data.size() == 1 && this->data[0] == 0) this->_is_negative = false;
}




/// Karatsuba, пока не делает ничего со знаком
static BigInt* k_mul(BigInt* left, BigInt* right) {

    BigInt *t1;
    if (left->data.size() < right->data.size()){
        t1 = left;
        left = right;
        right = t1;
    }

    int n = left->data.size(); /// size of biggest num

    if (n == 1){return new BigInt(left->data[0] * right->data[0]);}
    int fh = (n+1) / 2;   // First half Data (take more)
    int sh = (n - fh); // Second half of Data

    // Find the first half and second half of first string.

    BigInt *L0, *L1;
    L0->data.resize(fh);
    L1->data.resize(sh);

    BigInt *R0;
    BigInt *Z0;
    BigInt *Z1;


    int _0_sz;
    int s_sz;


    for(int i = 0;i<fh;++i){
        L0->data[i] = left->data[i];
    }

    for(int i = 0;i<sh;++i){
        L1->data[i] = left->data[fh + i];
    }



    Z0 = k_mul(L0,R0);
    int _1_sz = s_sz - _0_sz;
    if (_1_sz == 0){
        /// Z2 = 0
        Z1 = k_mul(L1,R0); /// no swap

        ///Z1._appendZeros(fh);


        return new BigInt((*Z1)+(*Z0));
    }else{
        BigInt *R1;
        R1->data.resize(_1_sz);



        for(int i = 0;i<_1_sz;++i){
            R1->data[i] = right->data[fh + i];
        }

        BigInt *Z2 = k_mul(L1,R1); /// no swap

        Z1 = new BigInt((*L0+*L1) * (*R0+*R1) - (*Z2 + *Z0));

        ///if ( !(Z1.data.size() == 1 && Z1.data[0] == 0) )
            ///Z1._appendZeros(fh);

        ///if ( !(Z2.data.size() == 1 && Z2.data[0] == 0) )
            ///Z2._appendZeros(fh * 2);

        return new BigInt(*Z2 + *Z1 + *Z0);
    }

}


#undef int



#include <fstream>



using namespace std;

int main()
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");
     

    BigInt a,b;

    BigInt * c;

    fin >> a >> b;
    c = k_mul(&a,&b);
    fout << *c << endl;


    return 0;
}


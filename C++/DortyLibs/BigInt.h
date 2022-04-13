#include <vector>
#include "Simple_FFT.h"

#define debug_delenie false

#define int long long

#define char_zero '0'

int intlog(double base, double x) {
    return (int)(log(x) / log(base));
}
/// 9 223 372 036 854 775 807
/// 2147483647
const int INT_MAXI = 9223372036854775807;

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

#define container_stack 6 /// 6

#define total_base 1000000 /// 1000000

#define sqrt_of_total_base 1000 /// 1000

/// Реализация класса больших чисел, через массив нестабильных битов.
class BigInt{
private:
    void _remove_leading_zeros();
    bool _is_negative = false;



public:
    /// 1234 === [4,3,2,1]
    vector<int> data;
    const static int Base = total_base;

    int rsz = -1;

    void operator=(BigInt another){
        data = another.data;
        ///Base = another.Base;
    }

    BigInt(){data = {0};
    //Base = total_base;
    }

    BigInt(long long num){
        while(num != 0){
            data.push_back(num % Base);
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

    /// Обработка умножения числа на БОЛЬШОЕ( О УЖАС! )
    void inline _mult(const BigInt &number, BigInt &write_to){
        write_to.data = FFT::convolution(data, number.data);


        size_t sz = write_to.data.size() - 1;
        for(size_t i = 0;i < sz; ++i ){
            write_to.data[i + 1] += write_to.data[i] / Base;
            write_to.data[i] %= Base;
        }


        while (write_to.data[sz] >= Base){
            write_to.data.push_back(write_to.data[sz] / Base);
            write_to.data[sz] %= Base;
            ++sz;
        }

    }

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
    void inline _pow(int pow_, BigInt &write_to){

        BigInt cp = (*this);
        write_to = cp;
        data = {1};
        for (; pow_; pow_ >>= 1) {
            if (pow_ & 1)
                _mult(cp,write_to);
            cp._mult(cp,cp);
        }


    }

    /// Возводит число в натуральную степень, оставляя лишь
    void inline _pow(int pow_,BigInt &write_to, int truncated_digits){

        BigInt cp = (*this);
        write_to = cp;
        data = {1};
        for (; pow_; pow_ >>= 1) {
            if (pow_ & 1)
                _mult(cp,write_to);
            cp._mult(cp,cp);


            if (cp.data.size() > truncated_digits){cp.data.resize(truncated_digits);cp._remove_leading_zeros();}
            if (data.size() > truncated_digits){data.resize(truncated_digits);_remove_leading_zeros();}
        }


    }

    /// Делит число на короткое
    int inline _divide(int digit_, BigInt &to_write){
        to_write.data = {};

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
        minus_._mult(minus_, minus_);
        minus_._mult(b, minus_);

        minus_._ShiftR(precision);

        _mult(2);

        _subtract(minus_);
        /// this - 2*this*this*b*SHIFT_R

    }

    /// То сколько можно взять в int чисел из контейнеров


    void inline Reciprocal(int precision, BigInt &write_to)
    {
        int mx_sz = intlog(Base, INT_MAXI);
        int sz = data.size();
        size_t len{ (sz > (mx_sz - 1)) ? (mx_sz) : sz };

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
    }

    void inline _DivUnrefined( BigInt &divisor, size_t precision, BigInt &write_to)
    {

        divisor.Reciprocal(precision,write_to);
        write_to._mult(*this, write_to);
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
        minus_._mult(divisor,minus_);
        rem_write_to._subtract(minus_);
    }

    /// В некоторых случаях, если число - это на 1 меньше, чем полный квадрат, то ответом будет число на один больше
    /// Например 24 -> 5, 48 -> 7, 35 -> 6
    /// safe_sqrt избегает этого
    void inline _sqrt()
    {
        if (data.size() == 1){*this = (intSqrt(data[0])); return;}
        BigInt copy_ = (*this);
        ///copy_._appendZeros();
        // x(i+1) = ( x(i) + a / x(i) ) / 2


        int sz = data.size();
        int rsz = (sz-1)*container_stack + intlog(default_base,data[sz - 1]) + 1;
        //cout << sz <<" rsz : " << rsz << endl;
        data.clear();



        data.push_back (intSqrt(data[sz-1]) * ((sz%2) ? 1 : sqrt_of_total_base) );

        _appendZeros((sz - 1) / 2 );

        ///cout << *this << endl;

        // Do the interation to fullfil the precision
        int end{  log2(sz) + 6 };

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
        cp._mult(cp,cp);
        if ( cp.compare(orig) == 2){
            _subtract(BigInt(1));
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


    /// Верный оператор (с учётом знаков и прочего)
    void operator-=(BigInt another){
        short comp_ = compare(another);
        if ( !comp_){
            swap(another,*this);
        }


        if (_is_negative == another._is_negative){
            // Одинаковы по знаку
            _subtract(another);
        }else{
            // Разные по знаку.
            _add(another);
        }

        if ( !comp_){
            _is_negative = !_is_negative;
        }

    }

    friend istream& operator>>(istream& in, BigInt &bi) {


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




/*
void SqrtRem(BigInt &take_from, BigInt &s, BigInt &r){

    BigInt s_, r_;

    if (take_from.data.size() < 4){
        /// == 2
    }else{
        SqrtRem(take_from)
    }
}
*/














/*
void Karatsuba_Sqrt(BigInt &num, int precision, BigInt &write_to)
{
    // x(i+1) = ( x(i) + a / x(i) ) / 2

    // Initial guess
    BigInt x0;
    if (num.data.size() == 1)
    {
        num._divide(2,x0); /// x0 = num / 2
        ///x0.append(precision, '0');  MK_IN_FUTURE
    }
    else
    {
        //std::string x0{ std::to_string(atoi(num.c_str()) / 2) };

        for(int i = 0;i < (num.data.size() - 1) / 2; ++i ){
            x0.data.push_back(zero);
        }

        x0.data.push_back( (num.data.size() % 2) ? (num.Base/4) : (num.Base*3/4));
    }


    Division div{};
    Karatsuba kar{};

    // Do the interation to fullfil the precision
    int end{ int(std::log2(precision)) + 1 };
    for (int i = 0; i < end; i++)
    {
        // x(i) * 10^precision + a * 10^(2*precision) / x(i)
        std::string v{ div.DivInt(num, x0, 2 * precision) };
        x0 = div.Div(kar.Add(x0, v), "2", precision);
        PrintDetails(i + 1, x0);
    }

    size_t i_cnt{ x0.length() - precision };
    return x0.substr(0, i_cnt) + '.' + x0.substr(i_cnt, precision - i_cnt);
}
*/

void BigInt::_remove_leading_zeros() {
	while (this->data.size() > 1 && this->data.back() == 0) {
		this->data.pop_back();
	}

	if (this->data.size() == 1 && this->data[0] == 0) this->_is_negative = false;
}


#undef int


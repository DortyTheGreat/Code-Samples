#include <vector>
#include "Simple_FFT.h"

#define debug_delenie false



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
/// Реализация класса больших чисел, через массив нестабильных битов.
class BigInt{
private:
    void _remove_leading_zeros();
    bool _is_negative = false;



public:
    /// 1234 === [4,3,2,1]
    vector<int> data;
    int Base = -1;

    void operator=(BigInt another){
        data = another.data;
        Base = another.Base;
    }

    BigInt(){data = {0};Base = 10;}

    BigInt(long long num, int Base_ = 10){
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
    short compare(BigInt &another){
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
    void _add(BigInt &another){

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
    void _subtract(BigInt &another){

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
    void _mult(int number){

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
    void _mult(BigInt &number){
        data = FFT::convolution(data, number.data);


        size_t sz = data.size() - 1;
        for(size_t i = 0;i < sz; ++i ){
            data[i + 1] += data[i] / Base;
            data[i] %= Base;
        }


        while (data[sz] >= Base){
            data.push_back(data[sz] / Base);
            data[sz] %= Base;
            ++sz;
        }

    }

    /// Возводит число в натуральную степень
    void _pow(int pow_){

        BigInt cp = (*this);

        data = {1};
        for (; pow_; pow_ >>= 1) {
            if (pow_ & 1)
                _mult(cp);
            cp._mult(cp);
        }


    }

    /// Возводит число в натуральную степень, оставляя лишь
    void _pow(int pow_, int truncated_digits){

        BigInt cp = (*this);

        data = {1};
        for (; pow_; pow_ >>= 1) {
            if (pow_ & 1)
                _mult(cp);
            cp._mult(cp);

            if (cp.data.size() > truncated_digits){cp.data.resize(truncated_digits);cp._remove_leading_zeros();}
            if (data.size() > truncated_digits){data.resize(truncated_digits);_remove_leading_zeros();}
        }


    }

    /// Делит число на короткое
    int _divide(int digit_, BigInt &to_write){
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

    void Interate(BigInt &b, int precision)
    {

        // 2 * X(i)
        BigInt minus_ = *this;
        minus_._mult(minus_);
        minus_._mult(b);

        minus_._ShiftR(precision);

        _mult(2);

        _subtract(minus_);


    }

    /// То сколько можно взять в int чисел из контейнеров
    const int mx_sz = 8;

    void Reciprocal(int precision, BigInt &write_to)
    {
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
        int end{ int(std::log2(precision)) + 3 };
        for (int i = 0; i < end; i++)
        {
            write_to.Interate(*this, precision);
            //cout << "InCycle " << write_to << endl;
        }
    }

    void _DivUnrefined(BigInt &divisor, size_t precision, BigInt &write_to)
    {

        divisor.Reciprocal(precision,write_to);
        write_to._mult(*this);
    }

    void _DivInt(BigInt &divisor, BigInt &write_to)
    {

        if ( (data[data.size() - 1] == 0) || (divisor.data.size() > data.size()) ){write_to = 0; return;}
        size_t precision = data.size() + 4;
        _DivUnrefined(divisor,precision,write_to);
        write_to._ShiftR(precision);
        if (write_to.data.size() == 0){
            write_to.data.push_back(0);
        }
    }

    void _DivIntRem(BigInt &divisor, BigInt &write_to, BigInt &rem_write_to)
    {
        _DivInt(divisor,write_to);
        rem_write_to = *this;
        BigInt minus_ = write_to;
        minus_._mult(divisor);
        rem_write_to._subtract(minus_);
    }


    void _sqrt()
    {
        BigInt copy_ = (*this);
        copy_._appendZeros(2);
        int sz = data.size();
        // x(i+1) = ( x(i) + a / x(i) ) / 2

        data.clear();

        data.push_back ((sz % 2) ? (Base/4) : (Base*3/4) );

        _appendZeros((sz - 1) / 2 + 2);

        ///cout << *this << endl;

        // Do the interation to fullfil the precision
        int end{  log2(sz) + 5 };

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

        _ShiftR(1);


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
    void _ShiftR(int length){

        data.erase(data.begin(), data.begin() + length);

    }

    /// [5,4,3,2,1](12345) (length=3)-> [0,0,0,5,4,3,2,1](12345000)
    /// Следует Улучшить. Ужасно плохо реализованно
    void _appendZeros(int length){
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

        if (bi.Base == -1){
            bi.Base = 10;
        }

        string stream_;
        in >> stream_;

        int sz = stream_.size();

        bi.data.resize(sz);

        for(int i = 0;i<sz;i++){
            bi.data[sz - i - 1] = FromCharToInt(stream_[i]);
        }

        bi._remove_leading_zeros();

        return in;

    }

    friend ostream& operator<<(ostream &in, const BigInt &bi) {

        int sz = bi.data.size();
        if (bi._is_negative){in << '-';}
        for(int i = 0;i<sz;i++){
            in << FromIntToChar(bi.data[sz - i - 1]);
        }

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


/// [l,r]
void fill_as_factorial(int l, int r, BigInt &to_write){
    to_write.Base = 10;
}

int int_sqrt(int n){
    return 1;
}
/*
void get_sqrt(BigInt &take_from, BigInt &to_write){
    BigInt ost;
    BigInt curRes;
    for (int i = amount-1;i>=0;i--)
    {
        BigInt A = ost;
        A.Shift(2,digits[i]);
        int curDigit = 0;

        int l = 0, r = 9;
        BigInt a = 2*curRes;
        a.Shift(1,0);
        while (l<=r)
        {
            int m = (l + r)>>1;
            a.digits[0] = m;
            if (a*m <= A)
            {
                curDigit = m;
                l = m + 1;
            }
            else
                r = m - 1;
        }
        curRes.Shift(1,curDigit);
        a.digits[0] = curDigit;
        ost = A - curDigit*a;
    }
    return curRes;



}

*/


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



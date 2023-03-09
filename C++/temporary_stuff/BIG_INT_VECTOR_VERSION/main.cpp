#include <iostream>
#include <vector>
using namespace std;

#define FORCE_INLINE __attribute__( ( always_inline ) ) static inline
/// #define FORCE_INLINE __attribute__((always_inline)) inline
FORCE_INLINE char FromIntToChar(const int& a){
    //if (a >= 0 && a <= 10){
        return (a + '0');
    //}
    //return (a - 10) + 'A';
}

FORCE_INLINE int FromCharToInt(const char& a){
    //if (a >= '0' && a <= '9'){
        return a - '0';
    //}
    //return (a - 'A')+10;
}

int times = 0;

const int cnt_stack = 9;
const int default_base = 10;
const int BASE = 1000 * 1000 * 1000;
struct BigUnsigned : vector<int>{
    BigUnsigned (const std::string& str="0");
    explicit operator std::string() const;
    friend std::ostream& operator << (std::ostream&, const BigUnsigned&);
	friend std::istream& operator >> (std::istream&, BigUnsigned&);


	BigUnsigned& operator*=(int mult){
	    times++;
	    push_back(0);
	    int64_t value;

	    int* low = &((*this)[size() - 1]);
	    int* high = &((*this)[size()]);

        for(int i = size() - 1; i > -1; --i){
            value = ((int64_t)(*low) ) * mult;
            int64_t divis = value / BASE;
            if ( ((*high) += divis) >= BASE ){
                (*high) -= BASE;
                ++(*(high+1));
            }
            (*low) = value - divis*BASE;

            low--;
            high--;
        }

        if ((*this)[size() - 1] == 0)
            pop_back();
        return *this;
	}
};


#include <algorithm> /// для реверса string



BigUnsigned::operator std::string() const{
    /*
	if ( (bi.digits.size() == 1) && (bi.digits[0] == 0)){
        os << FromIntToChar(0);
        return os;
    }
    */




    int Carret;
    std::string buff = "";
    for(size_t i = 0;i<size();++i){
        Carret = (*this)[i];
        for(int j = 0; j < cnt_stack;++j){
            buff += FromIntToChar(Carret % default_base);
            Carret /= default_base;
        }

    }


    /// Убрать лидирующие нули
    while(buff.back() == '0' ){
        buff.pop_back();
        if (buff.empty()){
            return "0";
        }
    }



    reverse(buff.begin(),buff.end());

	return buff;
}

// печатает число в поток вывода
std::ostream& operator <<(std::ostream& os, const BigUnsigned& bi) {
    return os << std::string(bi);
}


std::istream& operator>>(std::istream& in, BigUnsigned &bi) {


    std::string stream_;
    in >> stream_;

    new (&bi) BigUnsigned(stream_);

    /// мб тут надо регистрировать "лидирующие" нули, но хз

    return in;

}


BigUnsigned::BigUnsigned (const std::string& stream_){
    size_t carret_r_sz = stream_.size();
    resize((carret_r_sz+cnt_stack-1)/cnt_stack);


    int Carret;

    for(size_t i = 0;i<size();++i){
        Carret = 0;
        for(size_t j = 0; j < cnt_stack;++j){
            int index = carret_r_sz - (i+1)*cnt_stack + j;
            if (index > -1){
                Carret *= default_base;
                Carret += FromCharToInt(stream_[index]);
            }
        }

        (*this)[i] = Carret;
    }
}

long long factorial_power(long long n, long long p) {
    long long power = 0;
    while (n > 0) {
        n /= p;
        power += n;
    }
    return power;
}

int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    BigUnsigned bi = string("1");

    int a;
    cin >> a;

    int multi = 1;

    int zeros;
    int alt_zeros;

    alt_zeros = zeros = factorial_power(a,5);

    for(int i = 2; i <= a; ++i){

        int copy = i;
        while(copy % 5 == 0){
            copy /= 5;
        }

        if (alt_zeros > 0 && copy % 2 == 0){
            copy /= 2;
            alt_zeros -= 1;
        }

        if ( ((int64_t)multi * copy)  >= BASE){
            bi *= multi;
            multi = copy;
        }else{
            multi *= copy;
        }

        //cout << bi << endl;
    }

    bi *= multi;


    cout << bi;


    cout << string(zeros,'0');


    //cout << endl << times;


    return 0;
}

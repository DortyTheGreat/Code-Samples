#include <iostream>
#include <vector>
#include <cstring>
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

template<typename T, typename size_t_custom, typename DOUBLE_T = int64_t>
void x_mul(const T *__restrict a, T *__restrict b, T *__restrict res,const size_t_custom n)
{

    for (size_t_custom i = 0; i < n; ++i) {
        DOUBLE_T carry = 0;
        DOUBLE_T f = a[i];
        T *pz = res + i;
        T *pb = b;
        T *pbend = b + n;

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
template <typename T, typename size_t_custom>
void mult(const T * a, T * b, T *__restrict res, const size_t_custom n) {

    /// яКХЬЙНЛ ЛЮКЕМЭЙНЕ ВХЯКН, ГЮОСЯЙЮЕЛ ЬЙНКЭМШИ ЮКЦНПХРЛ

    if (n <= KAR_TRESH) {
        x_mul(a,b,res,n);
        return;
    }

    const size_t_custom fh = (n+1) / 2;   // First half Data (take more)
    const size_t_custom sh = (n - fh); // Second half of Data

    T* first = new T[fh + 1];
    first[fh] = 0;

    T* second = new T[fh + 1]; second[fh] = 0;



    memcpy(first,a,fh * sizeof(T));
    memcpy(second,b,fh * sizeof(T));



    /// яРН ОПНЖ ЛНФМН СЯЙНПХРЭ ЯКНФЕМХЕ
    for (size_t_custom i = 0; i < sh; i++) {
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
    /// дНО. ВЕЙ МЮ ОЕПЕБНКМЕМХЕ ОНЯКЕДМЕЦН ЙНМРЕИМЕПЮ
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
    T * we_need_to_optimize_memory = new T[2* (fh + 1)]{0};


    mult(first, second, we_need_to_optimize_memory, fh + 1);

    for(size_t_custom i = 0; i < 2 * sh; ++i){

        we_need_to_optimize_memory[i] -= (res[i] + res[2 * fh + i]);

    }

    if (sh != fh){

        we_need_to_optimize_memory[2 * sh] -= res[2 * sh];
        we_need_to_optimize_memory[2 * sh + 1] -= res[2 * sh + 1];
    }

    /// щРН РНФЕ СФЮЯМНЕ БШВХРЮМХЕ !!
    for(size_t_custom i = 0; i < 2 * fh + 2;++i){

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




    delete[] we_need_to_optimize_memory;
    delete[] first;
    delete[] second;


    /// мЕ ГЮАШРЭ МЕ РНКЭЙН НРОХЛХГХПБЮРЭ ОЮЛЪРЭ, МН Х ПЮГЛЕПШ






}



/// оНЙЮ йЮПЮЖСАЮ дСЛЮЕР, ВРН С ВХЯЕК НДХМЮЙНБШИ ПЮГЛЕП

/// мЕ ДН ЙНМЖЮ ДНДЕКЮМН, ПЮГЛЕП real_size НАЙСПЕММШИ -> ОПХ СЛМНФЕМХХ МЮ МСКЭ ДЕКЮЕР оХБН
/// еЫ╦ ХГЛЕМЪЕР ПЮГЛЕП Б ДНАЮБНЙ
BigUnsigned karatsuba(BigUnsigned& left, BigUnsigned& right){
    /// еЯКХ ОПЮБШИ АНКЭЬЕ -> РНЦДЮ ПЕГСКЭРЮР АСДЕР ЛЕМЭЬЕ РПЕАСЕЛНЦН
    if (left.capacity() < right.size()){
        left.reserve(right.size());
        memset(left.data() + left.size(),0, sizeof(int) * (right.size() - left.size()) );
    }


    /// еЯКХ КЕБШИ АНКЭЬЕ -> БУНДХЛ Б МЕЮККНЙЕИРЕД ОЮЛЪРЭ
    if (right.capacity() < left.size()){

        right.reserve(left.size());
        memset(right.data() + right.size(),0, sizeof(int) * (left.size() - right.size()) );
        /**
        cout << "reserved: " << endl;
        for(int i = 0; i < left.size(); ++i){
            cout << right[i] << " ";
        }
        cout << endl << endl;;
        */
    }





    BigUnsigned res;
    res.resize(2 * max(left.size(),right.size()));

    mult(left.data(),right.data(),res.data(),max(left.size(),right.size()));



    if (res.data()[res.capacity() - 1] == 0){
         res.resize(res.capacity() - 1);
    }else{
         res.resize(res.capacity());
    }




    return res;

}



#define FACT_TREE_TRASH 30
int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    BigUnsigned bi = string("1");

    int jumper;
    cin >> jumper;

    int a;
    cin >> a;



    int multi = 1;




    vector<BigUnsigned> TREE;


    for(int counter = a; counter > 1; counter -= jumper){
        if ( ((int64_t)multi * counter)  >= BASE){
            bi *= multi;
            if (bi.size() >= FACT_TREE_TRASH){
                TREE.push_back(bi);
                bi = string("1");
            }
            multi = counter;
        }else{
            multi *= counter;
        }
    }

    bi *= multi;
    TREE.push_back(bi);

    /// Это супер тупо, но думаю пойдёт
    while(TREE.size() != 1){
        //cout << TREE.size() << endl;

        //for(int i = 0; i < TREE.size(); ++i){
        //    cout << TREE[i] << endl << endl;
        //}
        vector<BigUnsigned> NEW_TREE;

        for(int i = 0; i < TREE.size()/2; ++i){
            NEW_TREE.push_back(karatsuba(TREE[2*i],TREE[2*i+1]));
        }
        if (TREE.size() % 2 == 1){
            NEW_TREE.push_back(TREE[TREE.size() - 1]);
        }
        TREE = NEW_TREE;
    }




    cout << TREE[0];



    //cout << endl << times;


    return 0;
}

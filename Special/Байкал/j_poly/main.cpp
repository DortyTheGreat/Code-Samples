#include <iostream>
#include <iostream>
using namespace std;


constexpr uint32_t __high_type(uint16_t) {return uint32_t(0);}
constexpr uint64_t __high_type(uint32_t) {return uint64_t(0);}
constexpr __uint128_t __high_type(uint64_t) {return __uint128_t(0);}

#define high_type(x) decltype(__high_type(x(0)))
#define FORCE_INLINE __attribute__((always_inline)) inline

template<typename T>
class fast_div{
protected:
    high_type(T) my_magic = 1;
    unsigned char shift;

public:
    fast_div(){}
    fast_div(T val){
        shift = (sizeof(high_type(T)) * 8 - 1);
        my_magic = (my_magic << shift) / val;

        while(my_magic >= (high_type(T))(1) << (sizeof(high_type(T)) * 4) ) {
            my_magic >>= 1;--shift;
        }

        if (!((++my_magic) & 1)){my_magic >>= 1; --shift;}
    }


    FORCE_INLINE friend T  operator/(const T& val, const fast_div<T>& fd){
        return ((fd.my_magic * val) >> fd.shift);
    }
};

/// Возвращает большую часть от 128: 64x64
FORCE_INLINE uint64_t hmul64(const uint64_t& a,const uint64_t& b){
    uint64_t ret, low;
    asm ("mulq %3" : "=a"(low), "=d"(ret) : "a"(a), "g"(b) : "cc");
    return ret;
}

class fast_div64{
protected:
    uint64_t my_magic = 1;
    uint_fast8_t shift;

public:
    fast_div64(){}
    fast_div64(const uint64_t& val){
        shift = (sizeof(high_type(uint64_t)) * 8 - 1);

        __uint128_t temp = (__uint128_t(1) << 127) / val;
        shift = __builtin_clzll(temp  >> 64); /// zeros
        my_magic = (temp >> (64-shift));
        --shift;

        if (!((++my_magic) & 1)){my_magic >>= 1; --shift;}
        ///cout << my_magic << " " << (int)shift << endl;
    }


    __attribute__((always_inline)) friend uint64_t operator/(const uint64_t& val, const fast_div64& fd){



        return (hmul64(val,fd.my_magic) >> fd.shift ) ;
    }
};

template<typename T>
class fast_mod : fast_div<T>{
private:
    T div;
public:
    fast_mod(){}
    fast_mod(T val) : fast_div<T>(val), div(val){}
    FORCE_INLINE friend T  operator%(const T& val, const fast_mod<T>& fm){
        return val - val/fm * fm.div;
    }
};

class fast_mod64 : fast_div64{
private:
    uint64_t div;
public:
    fast_mod64(){}
    fast_mod64(uint64_t val) : fast_div64(val), div(val){}
    FORCE_INLINE friend uint64_t operator%(const uint64_t& val, const fast_mod64& fm){
        return val - val/fm * fm.div;
    }
};


template<typename T, typename quick_mod = fast_mod<T>>
class LCM{
public:
    T mult, old_rand, add;
    quick_mod fm;
    LCM(T _mult,T _old_rand,T _add,T _mod) : mult(_mult), old_rand(_old_rand), add(_add), fm(_mod){}
    FORCE_INLINE T get(){
        return old_rand = (mult * old_rand + add) % fm;
    }

};
using namespace std;

int main()
{
    uint64_t n,k,m;
    cin >> n >> k >> m;

    fast_mod64 FM(m);
    uint64_t arr[3000];

    for(uint64_t i = 0; i < n; ++i){
        cin >> arr[i];
    }


    for(uint64_t i = 0; i <= k; ++i){
        uint64_t runner = 1;
        uint64_t summ = 0;

        if (m == 1){
            cout << "0 ";
            /// WHY????
        }else{

            for(uint64_t j = 0; j < n; ++j){
                summ += runner*arr[j];
                summ = summ % FM;

                runner *= i;
                runner = runner % FM;
            }
            cout << summ << " ";
        }

    }



    return 0;
}

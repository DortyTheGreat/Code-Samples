#include <iostream>
using namespace std;







constexpr uint64_t high_type(uint32_t) {
  return uint64_t(0);
}

constexpr __uint128_t high_type(uint64_t) {
  return __uint128_t(0);
}

template<typename T>
class fast_div{
protected:
    decltype(high_type(T(0))) my_magic = 1;
    unsigned char shift;

public:
    fast_div(){}
    fast_div(T val){
        shift = (sizeof(decltype(high_type(T(0)))) * 8 - 1);
        my_magic = (my_magic << shift) / val;

        while(my_magic >= (decltype(high_type(T(0)))(1) << (sizeof(decltype(high_type(T(0)))) * 4) ) ){
            my_magic >>= 1;--shift;
        }

        if (!((++my_magic) & 1)){my_magic >>= 1; --shift;}
    }


    __attribute__((always_inline)) friend T  operator/(const T& val, const fast_div<T>& fd){
        return ((fd.my_magic * val) >> fd.shift);
    }
};

template<typename T>
class fast_mod{
private:
    T div;

public:
    fast_div<T> fd;
    fast_mod(){}
    fast_mod(T val) : div(val), fd(val){}


    __attribute__((always_inline)) friend T  operator%(const T& val, const fast_mod<T>& fm){
        return val - val/fm.fd * fm.div;
    }
};

template<typename T>
class LCM{
public:
    T mult, old_rand, add;
    fast_mod<T> fm;

    LCM(T _mult,T _old_rand,T _add,T _mod) : mult(_mult), old_rand(_old_rand), add(_add){
        fm = _mod;
    }

    __attribute__((always_inline)) T get(){
        return old_rand = (mult * old_rand + add) % fm;
    }

};

int main()
{

    uint32_t a, old_rand, b,c,n;
    cin >> a >> old_rand >> b >> c >> n;
    LCM<uint32_t> my_method(a,old_rand, b, c);
    uint64_t ans = 0;

    for(int i = 0;i < n;++i){
        ans += my_method.get();
    }


    cout << ans<< endl;
    return 0;
}

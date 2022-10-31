#include "../BitsPrecision/high_type.h"
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


    __attribute__((always_inline)) friend T  operator/(const T& val, const fast_div<T>& fd){
        return ((fd.my_magic * val) >> fd.shift);
    }
};

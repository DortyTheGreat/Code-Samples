 #include "fast_div.h"
template<typename T>
class fast_mod : fast_div<T>{
private:
    T div;
public:
    fast_mod(){}
    fast_mod(T val) : fast_div<T>(val), div(val){}
    __attribute__((always_inline)) friend T  operator%(const T& val, const fast_mod<T>& fm){
        return val - val/fm * fm.div;
    }
};

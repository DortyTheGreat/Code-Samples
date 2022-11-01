#include "fast_mod.h"
template<typename T>
class LCM : fast_mod<T>{
public:
    T mult, old_rand, add;

    LCM(T _mult,T _old_rand,T _add,T _mod) : fast_mod<T>(_mod), mult(_mult), old_rand(_old_rand), add(_add){}

    __attribute__((always_inline)) T get(){
        return old_rand = (mult * old_rand + add) % (*this);
    }

};

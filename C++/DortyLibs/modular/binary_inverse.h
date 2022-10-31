#include "../BitsPrecision/type_log_2.h"
template<typename T>
T binary_inverse(const T& n){
    T inv = n;

    for (uint8_t i = 0; i < type_log_2(T(0)); i++)
        inv *= 2 - n * inv;
    return inv;
}

#include "../modular/binary_inverse.h"
template <typename T>
class fast_divisibility{
public:
    T inverse;
    T limit;
public:
    fast_divisibility() = default;
    fast_divisibility(const T& mod){
        limit = ~T(0) / mod;
        inverse = binary_inverse(mod);
    }
    __attribute__((always_inline)) constexpr bool check(const T& data) const{
        return (data*inverse) <= limit;
    }
};

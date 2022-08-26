// Finds 2^-64 mod m and (-m)^-1 mod m for odd m (hacker's delight).
// equivalent to xbinGCD ?

/// since (a == 0) === !a

#include <utility> /// pair

template <typename T>
inline std::pair<T, T> mont_modinv(T m) {
    const size_t shift = sizeof(m) * 8 - 1;
    T a = T(1) << shift;
    T u = 1;
    T v = 0;

    while (a) {
        a >>= 1;
        if (u & 1) {
            u = ((u ^ m) >> 1) + (u & m);
            v = (v >> 1) + (T(1) << shift);
        }
        else {
            u >>= 1; v >>=1;
        }
    }
    return std::make_pair(u, v);
}

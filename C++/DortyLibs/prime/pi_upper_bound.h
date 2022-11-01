// Pierre Dusart's maximum primes: PI(x) < (x/ln x)(1 + 1.2762/ln x)
template<typename T>
constexpr T pi_upper_bound(const T& x){
    return x / log(x) * (1 + 1.2762 / log(x));
}

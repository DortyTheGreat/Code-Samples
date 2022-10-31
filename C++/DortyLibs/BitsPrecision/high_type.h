constexpr uint32_t __high_type(uint16_t) {return 0;}
constexpr uint64_t __high_type(uint32_t) {return 0;}
constexpr __uint128_t __high_type(uint64_t) {return 0;}

#define high_type(x) decltype(__high_type(x(0)))

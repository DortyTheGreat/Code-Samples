#pragma once
constexpr uint8_t type_log_2(uint32_t) {return 5;}
constexpr uint8_t type_log_2(uint64_t) {return 6;}
constexpr uint8_t type_log_2(__uint128_t) {return 7;}

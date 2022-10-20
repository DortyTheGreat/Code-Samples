#include <iostream>
#include <vector>
#include <algorithm>

#include <cstdlib>
#include <ctime>
#include <cstdio>

const size_t LARGE_SIZE = 1000 * 1000 * 30;

struct rnd {
    int operator()() {
        return rand() % LARGE_SIZE;
    }
};

int comp( const void* a, const void* b ) {
    return ( *( int* )a - *( int* )b );
}

int main() {
    int *ary = new int[LARGE_SIZE];
    int *ary_copy = new int[LARGE_SIZE];
    // generate random data
    std::generate( ary, ary + LARGE_SIZE, rnd() );
    std::copy( ary, ary + LARGE_SIZE, ary_copy );
    // get time
    std::time_t start = std::clock();
    // perform quick sort C using function pointer
    std::qsort( ary, LARGE_SIZE, sizeof( int ), comp );
    std::cout << "C quick-sort time elapsed: " << static_cast<double>( clock() - start ) / CLOCKS_PER_SEC << "\n";
    // get time again
    start = std::clock();
    // perform quick sort C++ using function object
    std::sort( ary_copy, ary_copy + LARGE_SIZE );
    std::cout << "C++ quick-sort time elapsed: " << static_cast<double>( clock() - start ) / CLOCKS_PER_SEC << "\n";
}

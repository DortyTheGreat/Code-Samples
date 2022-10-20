/// @file     segmented_sieve.cpp
/// @author   Kim Walisch, <kim.walisch@gmail.com>
/// @brief    This is a simple implementation of the segmented sieve of
///           Eratosthenes with a few optimizations. It generates the
///           primes below 10^9 in 0.8 seconds (single-threaded) on an
///           Intel Core i7-6700 3.4 GHz CPU.
/// @license  Public domain.

#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <stdint.h>
#include <bitset>
#include <climits>
#include <cstring>
#include <iostream>

/// Set your CPU's L1 data cache size (in bytes) here
const int64_t L1D_CACHE_SIZE = 32768;

/// Generate primes using the segmented sieve of Eratosthenes.
/// This algorithm uses O(n log log n) operations and O(sqrt(n)) space.
/// @param limit  Sieve primes <= limit.
///


void segmented_sieve(int64_t limit)
{
    int64_t sqrt = (int64_t) std::sqrt(limit);
    int64_t segment_size = std::max(sqrt, L1D_CACHE_SIZE);
    int64_t count = 0;
    if (limit >= 2){count++;}
    if (limit >= 3){count++;}
    // we sieve primes >= 5
    int64_t i_5 = 5; int64_t i_1 = 7;
    int64_t n_5 = 5; int64_t n_1 = 7;
    int64_t s_5 = 5; int64_t s_1 = 7;

    std::vector<char> sieve(segment_size);



    std::vector<char> is_prime(sqrt + 1,true);

    int64_t primes[50000]; std::size_t sz_prime = 0;

    int64_t multiples_0[50000];
    int64_t multiples_24[50000];

    for (int64_t low = 0; low <= limit; low += segment_size)
    {
        /*
        for(std::size_t i = 3; i < segment_size; i += 6){
            sieve[i] = true;
        }

        for(std::size_t i = 1; i < segment_size; i += 6){
            sieve[i] = true;
        }

        for(std::size_t i = 5; i < segment_size; i += 6){
            sieve[i] = true;
        }
        */
        ///memset(sieve, true, (segment_size) * sizeof(char));
        std::fill(sieve.begin(),sieve.end(),true);
        // current segment = [low, high]
        int64_t high = low + segment_size - 1;
        high = std::min(high, limit);

        // generate sieving primes using simple sieve of Eratosthenes
        for (; i_5 * i_5 <= high; i_5 += 6)
            if (is_prime[i_5])
                for (int64_t j = i_5 * i_5; j <= sqrt; j += i_5){
                    is_prime[j] = false;
                }


        for (; i_1 * i_1 <= high; i_1 += 6)
            if (is_prime[i_1])
                for (int64_t j = i_1 * i_1; j <= sqrt; j += i_1)
                    is_prime[j] = false;

        // initialize sieving primes for segmented sieve
        for (; s_5 * s_5 <= high; s_5 += 6){
            if (is_prime[s_5]){

                multiples_0[sz_prime] = (s_5 * s_5 - low);
                multiples_24[sz_prime] = (s_5 * s_5 + 2*s_5 - low);



                primes[sz_prime++] = s_5*6;

            }
        }

        for (; s_1 * s_1 <= high; s_1 += 6){
            if (is_prime[s_1]){

                multiples_0[sz_prime] = (s_1 * s_1 - low);

                multiples_24[sz_prime] = (s_1 * s_1 + 4*s_1 - low);
                primes[sz_prime++] = s_1*6;

            }
        }

        // sieve the current segment
        for (std::size_t i = 0; i < sz_prime; i++)
        {

            int64_t j = multiples_0[i];
            for (int64_t k = primes[i]; j < segment_size; j += k){

                sieve[j] = false;
            }
            multiples_0[i] = j - segment_size;

            j = multiples_24[i];
            for (int64_t k = primes[i]; j < segment_size; j += k){

                sieve[j] = false;
            }
            multiples_24[i] = j - segment_size;
        }



        for (; n_1 <= high; n_1 += 6)
          if (sieve[n_1 - low]){

            count++;
          } // n is a prime



        for (; n_5 <= high; n_5 += 6)
          if (sieve[n_5 - low]){

            count++;
          } // n is a prime

    }


    std::cout << count << " primes found." << std::endl;

}

/// Usage: ./segmented_sieve n
/// @param n  Sieve the primes up to n.
///
int main(int argc, char** argv)
{
  if (argc >= 2)
    segmented_sieve(std::atoll(argv[1]));
  else
    segmented_sieve(1000 * 1000 * 1000);



  return 0;
}

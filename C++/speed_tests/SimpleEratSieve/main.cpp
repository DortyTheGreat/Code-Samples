
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <stdint.h>


const int64_t L1D_CACHE_SIZE = 32768;
using namespace std;

void segmented_sieve(int64_t limit)
{
    int64_t sqrt = (int64_t) std::sqrt(limit);



    // we sieve primes >= 3


    int64_t s = 3;

    std::vector<char> sieve(limit);
    sieve[0] = sieve[1] = false; /// some of the edge cases

    std::fill(sieve.begin(), sieve.end(), true);

    cout << "here" << endl;
    std::vector<int64_t> primes;
    ///primes.reserve()





    // generate sieving primes using simple sieve of Eratosthenes
    for (int64_t i = 3; i < sqrt; i += 2)
      if (sieve[i])
        for (int64_t j = i * i; j < limit; j += 2*i)
          sieve[j] = false;

    // initialize sieving primes for segmented sieve


    cout << "filling" << endl;

    for (int64_t n = 3; n < limit; n += 2)
      if (sieve[n]){

        primes.push_back(n);
      } // n is a prime



  std::cout << primes.size() << " primes found." << std::endl;
  std::cout << primes.size() << std::endl;
  std::cout << primes[0] << std::endl;
}

/// Usage: ./segmented_sieve n
/// @param n  Sieve the primes up to n.
///
int main(int argc, char** argv)
{
  if (argc >= 2)
    segmented_sieve(std::atoll(argv[1]));
  else
    segmented_sieve(1000 * 1000 * 100);



  return 0;
}

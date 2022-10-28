

#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <stdint.h>


const int64_t L1D_CACHE_SIZE = 32768;


void segmented_sieve(int64_t limit)
{
  int64_t sqrt = (int64_t) std::sqrt(limit);
  int64_t segment_size = std::max(sqrt, L1D_CACHE_SIZE);
  int64_t count = (limit < 2) ? 0 : 1;

  // we sieve primes >= 3
  int64_t i = 3;
  int64_t n = 3;
  int64_t s = 3;

  std::vector<char> sieve(segment_size);


  std::vector<char> is_prime(sqrt + 1, true);
  std::vector<int64_t> primes;
  std::vector<int64_t> multiples;

    std::vector<int64_t> all_the_primes; int h = 0;
    all_the_primes.reserve(60847534); /// insert some good pi approximation from the top
    all_the_primes.push_back(2);
    std::vector<char> entire_sieve(limit);
    std::fill(entire_sieve.begin(), entire_sieve.end(), false);

  for (int64_t low = 0; low <= limit; low += segment_size)
  {
    ///for(std::size_t i = 1; i < segment_size; i += 2){
        ///sieve[i] = true;
    ///}
    std::fill(sieve.begin(), sieve.end(), true);

    // current segment = [low, high]
    int64_t high = low + segment_size - 1;
    high = std::min(high, limit);

    // generate sieving primes using simple sieve of Eratosthenes
    for (; i * i <= high; i += 2)
      if (is_prime[i])
        for (int64_t j = i * i; j <= sqrt; j += i)
          is_prime[j] = false;

    // initialize sieving primes for segmented sieve
    for (; s * s <= high; s += 2)
    {
      if (is_prime[s])
      {
           primes.push_back(s);
        multiples.push_back(s * s - low);

      }
    }

    // sieve the current segment
    for (std::size_t i = 0; i < primes.size(); i++)
    {
      int64_t j = multiples[i];
      for (int64_t k = primes[i] * 2; j < segment_size; j += k){

        sieve[j] = false;
      }
      multiples[i] = j - segment_size;
    }

    for (; n <= high; n += 2)
      if (sieve[n - low]){

        all_the_primes[++h] =  (n);
        entire_sieve[n] = true;
      } // n is a prime

  }

  std::cout << h+1 << " primes found." << std::endl;
  std::cout << primes.size() << std::endl;
  std::cout << primes[0] << std::endl;
  std::cout << multiples.size();
}

/// Usage: ./segmented_sieve n
/// @param n  Sieve the primes up to n.
///
int main(int argc, char** argv)
{
  if (argc >= 2)
    segmented_sieve(std::atoll(argv[1]));
  else
    segmented_sieve(1000000000);



  return 0;
}

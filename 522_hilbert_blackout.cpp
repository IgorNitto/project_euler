/**
 * @file 522.cpp
 *
 * @brief Solution to Hilbert's Blackout
 *        (https://projecteuler.net/problem=522)
 */
#include <iostream>

constexpr int mod = 135707531;

std::uint64_t mod_pow (std::uint64_t x, std::uint64_t e)
{
  std::uint64_t res = 1;

  for (; e != 0 ; x = (x * x) % mod, e >>=1)
  {
    if (e & 1) {res = (res * x) % mod;}
  }

  return res;
}

int count (std::uint64_t N)
{
  std::uint64_t res = 0;
  std::uint64_t fact = 1;

  for (std::uint64_t k=1; k <= N-2; ++k)
  {
    fact = (fact *  (N - k + 1)) % mod; 

    std::uint64_t t = (k == 1) ? (N-1) * N : fact;
    t = (t * mod_pow (k, mod - 2)) % mod;
    t = (t * mod_pow(N - 1 - k, N - k)) % mod;
    res = (res + t) % mod;
  }

  return res;
}

int main ()
{
  std::cerr << count (8) << std::endl;
  std::cerr << count (100) << std::endl;
  std::cerr << count (12344321) << std::endl;
}

/**
 * Not terribly fast to run (5/6 minutes on i3-4010U 1.7 GHz)
 */
#include <vector>
#include <cmath>
#include <iostream>

using uint32_t = std::uint32_t;
using uint64_t = std::uint64_t;

uint64_t solve (const uint32_t N)
{

  /*
   * Vector of bool to the rescue. Most of the time
   * is spent here in sieving all primes.
   */
  std::vector<bool> is_prime;
  std::vector<bool> is_square_free;

  is_prime.resize (N+1, true);
  is_square_free.resize (N+1, true);

  is_prime[1] = false;

  for (uint32_t j = 2; j < N; ++j)
  {
    for (uint32_t v = 2*j; v <= N; v+=j)
    {
      is_prime [v] = false;
    }
  }

  for (uint32_t j = 1; j < N; ++j)
  {
    for (uint64_t t = 2; j*t*t <= N; ++t)
    {
      is_square_free[j*t*t] = false;
    }
  }

  /*
   * Look for integer triples of the form (s*u^2, s*u*v, s*v^2)
   * where s is square free and each element is off by 1 to
   * a prime.
   */
  std::vector<uint32_t> L;
  L.reserve (static_cast<size_t> (std::ceil (std::sqrt (N))));

  uint64_t result = 0;

  for (uint32_t a = 1; a <= N; ++a)
  {
    if (!is_square_free[a]) continue;
    L.clear ();

    for (uint32_t j = 1; /*a*j*j <= N*/; ++j)
    {
      uint64_t x = a*j*j;
      if (x > N)
      {
	break;
      }
      if (is_prime[x-1])
      {
	L.push_back (j);
      }
    }

    for (size_t i = 0; i < L.size (); ++i)
    {
      for (size_t j = i+1; j < L.size (); ++j)
      {
	uint32_t l = a * L[i] * L[i];
	uint32_t u = a * L[j] * L[j];
	uint32_t m = a * L[i] * L[j];

	if (is_prime[m-1])
	{
	  //	  std::cerr << "(" << l-1 << "," << m-1 << "," << u-1 << ")"
	  //	    << std::endl;
	  result += (l-1) + (m-1) + (u-1);
	}
      }
    }
  }

  return result;
}

int main ()
{
  std::cerr << solve (100000000);
}

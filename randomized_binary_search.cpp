/**
 * A solution to "Randomized Binary Search" problem
 */
#include <iomanip>
#include <iostream>
#include <cmath>

/*
 * Estimate n-th harmonic number within an additive error
 * of O(1/n^6) (see Knuth)
 */
double h_n (const std::uint64_t N)
{
  const double gamma = //< The Euler-Mascheroni constant
    0.57721566490153286060651209008240243104215933593992;

  return std::log (N)
         + gamma
         + 1.0/(2 * N)
         - (1.0/ (12 * N)) / N
         + (1.0/ (120 *N)) / N / N / N;
}

/*
 * Estimate R_n value, the average number of comparison
 * done by binary search with randomized pivot choice
 */
double r_n (const std::uint64_t N)
{
  return 2* (1 + 1.0/N) * h_n (N) - 3;
}

/*
 * Calculate B_n value, the average number of comparison
 * done by ordinary binary search
 */
double b_n (const std::uint64_t N)
{
  std::uint64_t node_count =0;
  std::uint64_t height =0;
  double result = 0.;

  while (node_count < N)
  {
    const auto level_size = std::min(
      std::uint64_t{1} << height, N - node_count);

    result += (static_cast<double> (level_size)/N) *
                (height + 1);

    node_count += level_size;
    ++height;
  }

  return result;
}

int main ()
{
  const std::uint64_t N = 10000000000ULL;

  std::cout << std::setprecision (23);
  std::cout << r_n(N) - b_n(N) << std::endl;
}

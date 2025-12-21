#include <iostream>

#include "norm_dist.h"

int main ()
{
  const double x = 1.0;
  std::cout << "N(x) = " << norm_dist (x, 0.0, 1.0) << " at x = " << x << "\n";

  return 0;
}

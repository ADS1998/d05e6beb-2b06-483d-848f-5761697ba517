#include <cmath>

#include "sqrt.h"

double babylonian_sqrt (const double value, int& niter)
{
  double x_current = value;
  double x_prev = 0.0;

  niter = 0;
  while (std::abs (x_current-x_prev) > 1e-12) {
    x_prev = x_current;
    x_current = 0.5 * (x_prev + value/x_prev);
    niter++;
  }

  return x_current;
}


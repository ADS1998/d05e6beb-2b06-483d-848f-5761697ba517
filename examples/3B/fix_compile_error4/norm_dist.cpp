#include <cmath>

#include "norm_dist.h"

double norm_dist (double x, double mean, double standard_dev)
{
  const double pi = 3.141592653589793238462643;

  double norm = 1.0/std::sqrt(2*pi*standard_dev*standard_dev);
  return norm * std::exp (- (x - mean)*(x-mean) / (2.0*standard_dev*standard_dev));
}

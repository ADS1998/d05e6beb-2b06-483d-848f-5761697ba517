#include <iostream>

#include "sqrt.h"

int main ()
{
  std::cout << "Enter a number: ";
  double x;
  std::cin >> x;

  int n;   // <- note we need to provide an integer to store the number of iterations!
  double val = babylonian_sqrt (x, n);
  std::cout << "Series evaluates to: " << val << " in " << n << " iterations\n";

  return 0;
}

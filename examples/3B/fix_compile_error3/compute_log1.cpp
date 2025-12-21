#include <iostream>

#include "log_one_plus_x.h"

int main ()
{
  const double x = 0.1;
  std::cout << "log (1+" << x << ") = " << log_one_plus_x(x) << "\n";

  std::cout << "------------------------\n";
  std::cout << "log (1+" << x << ") for different numbers of elements:\n";
  for (int n = 1; n < 10; n++)
    std::cout << n << " elements: value = " << log_one_plus_x(x, n) << "\n";

  return 0;
}


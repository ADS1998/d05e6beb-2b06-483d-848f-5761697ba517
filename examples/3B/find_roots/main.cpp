#include <iostream>

float eval_function (float x)     { return x*x*x - 3.0*x + 3.0; }
float eval_derivative (float x)   { return 3.0*x*x - 3.0; }

int main()
{
  float dx, x = 0.0;
  int n = 0;

  do {
    dx = -eval_function (x) / eval_derivative (x);
    x += dx;
  } while (dx != 0.0);

  std::cout << "solution is at x = " << x << "\n";

  return 0;
}

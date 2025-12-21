#include "prime.h"

bool is_prime (int in)
{
  for (int n = 2; n < in/2; n++)
    if (in%n == 0)
      return false;
  return true;
}

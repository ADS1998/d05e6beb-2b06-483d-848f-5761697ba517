#include <iostream>
#include <string>

#include "string_utils.h"

int main (int argc, char* argv[])
{
  // go through argument list in reverse order:
  for (int n = argc-1; n > 0; n--)
    std::cout << capitalise (invert (argv[n])) << " ";
  std::cout << "\n";

  return 0;
}

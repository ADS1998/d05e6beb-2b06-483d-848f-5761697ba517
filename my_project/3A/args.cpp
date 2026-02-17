#include <iostream>

int main (int argc, char* argv[])
{
  std::cout << "Number of arguments: " << argc << "\n";
  for (int n = 0; n < argc; n++)
    std::cout << "  argument " << n << ": \"" << argv[n] << "\"\n";
  return 0;
}
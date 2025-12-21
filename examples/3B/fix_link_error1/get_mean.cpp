#include <iostream>
#include <string>
#include <vector>

#include "stats.h"

int main (int argc, char* argv[])
{
  // convert all command-line arguments to float and push into a vector:

  std::vector<float> data;
  for (int n = 1; n < argc; n++)
    data.push_back (std::stod (argv[n]));

  std::cout << "mean = " << compute_mean (data) << "\n";

  return 0;
}

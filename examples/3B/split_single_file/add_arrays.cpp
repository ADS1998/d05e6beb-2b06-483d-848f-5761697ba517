#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>


std::vector<float> load_array (const std::string& filename)
{
  std::ifstream infile (filename);
  if (!infile)
    throw std::runtime_error ("failed to open file \"" + filename + "\" for reading");

  std::vector<float> data;
  float value;
  while (infile >> value)
      data.push_back (value);

  if (data.empty())
    throw std::runtime_error ("file \"" + filename + "\" contains no usable data");

  return data;
}



void save_array (const std::string& filename, const std::vector<float>& data)
{
  std::ofstream outfile (filename);
  if (!outfile)
    throw std::runtime_error ("failed to open file \"" + filename + "\" for writing");

  for (const auto x : data)
    outfile << x << " ";
  outfile << "\n";
}



std::vector<float> add_arrays (const std::vector<float>& v1, const std::vector<float>& v2)
{
  if (v1.size() != v2.size())
    throw std::runtime_error ("add_arrays(): cannot add arrays of different sizes");

  std::vector<float> out (v1.size());
  for (int n = 0; n < v1.size(); n++)
    out[n] = v1[n] + v2[n];

  return out;
}



int main (int argc, char* argv[])
{
  if (argc != 4) {
    std::cerr <<
      "ERROR: unexpected number of arguments\n"
      "\n"
      "  usage: add_arrays input1 input2 output\n"
      "\n"
      "  - input1 & input2 are the two text files containing the arrays\n"
      "    of values to add.\n"
      "\n"
      "  - output is the nome of the text file that will be produced to\n"
      "    store the sum of the two arrays.\n\n";

    return 1;
  }

  try {
    // main processing block:

    auto v1 = load_array (argv[1]);
    auto v2 = load_array (argv[2]);

    save_array (argv[3], add_arrays (v1,v2));

    // end of main processing block
  }
  catch (std::exception& err) {
    std::cerr << "ERROR: " << err.what() << " - aborting\n";
    return 1;
  }
  catch (...) {
    std::cerr << "ERROR: exception of unknown type was thrown - aborting\n";
    return 1;
  }

  return 0;
}

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

#include "debug.h"
#include "file_loader.h"

/**
 * @brief Prints program usage instructions
 * @param progname Name of the executable
 */
void print_usage(const std::string &progname)
{
  std::cerr << "Usage:\n"
               "  "
            << progname << " <input_file> <output_file> [param1] [param2]\n\n"
                           "Arguments:\n"
                           "  <input_file>   Path to input data file (time series, matrix, sequence, or PGM)\n"
                           "  <output_file>  Path to output file for processed results\n"
                           "  [param1]       Optional numeric parameter (default = 0.5)\n"
                           "  [param2]       Optional numeric parameter (default = 0.3)\n"
                           "Example:\n"
                           "  "
            << progname << " data.txt results.txt 0.7 0.2\n";
}

int main(int argc, char* argv[])
{
    debug::log_level = 0;

    std::vector<std::string> positional;

    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];

        if (arg == "-v")        debug::log_level = 1;
        else if (arg == "-vv")  debug::log_level = 2;
        else if (arg == "-vvv") debug::log_level = 3;
        else
            positional.push_back(arg);   // store non-flag args
    }

    if (positional.size() < 2)
    {
        std::cerr << "ERROR: Missing required arguments.\n\n";
        print_usage(argv[0]);
        return 1;
    }

    std::string input_file  = positional[0];
    std::string output_file = positional[1];

    double param1 = (positional.size() > 2) ? std::stod(positional[2]) : 0.5;
    double param2 = (positional.size() > 3) ? std::stod(positional[3]) : 0.3;


    try {

 
    // --- Load Data from File ---
    // You can call only the loader you need based on file type
    // Here are examples for all types:
    // TimeSeries ts_data;
    // MatrixData matrix_data;
    // SequenceData seq_data;
    // Image2D img_data;

    // Load time series
    try
    {
      auto data = load_time_series(input_file);
      debug::log(2, std::to_string(data.values.size()));
      visualise(data);
    }
    catch (...)
    { /* ignore if not TS */
    }

    // Load matrix
    try
    {
      auto data = load_matrix(input_file);
      debug::log(2, std::to_string(data.values.size()));
    }
    catch (...)
    { /* ignore if not matrix */
    }

    // Load sequence
    try
    {
      auto data = load_sequence(input_file);
      debug::log(2, std::to_string(data.data.size()));
    }
    catch (...)
    { /* ignore if not sequence */
    }

    // Load PGM image
    try
    {
      auto data = load_pgm_image(input_file);
      debug::log(2, std::to_string(data.pixels.size()));
    }
    catch (...)
    { /* ignore if not PGM */
    }

    debug::log(1, "Data loaded successfully.");
    // debug::log(2, "Data loaded successfully."); std::to_string(data.size()
    //  debug::log(3, "Data loaded successfully."); +call visulise(data)

    // --- Example processing ---
    // auto processed = process_data(ts_data.values, param1, param2);
    // auto metrics = stats::min_mean_max(processed);
    // auto rmssd = stats::rmssd(processed);
    // write_report(output_file, metrics, rmssd);

    std::cout << "Processing complete. Output written to: " << output_file << "\n";
    }
  catch (const std::exception &err)
  {
    std::cerr << "ERROR: " << err.what() << " - aborting\n";
    print_usage(argv[0]);
    return 1;
  }
  catch (...)
  {
    std::cerr << "ERROR: Unknown exception occurred - aborting\n";
    print_usage(argv[0]);
    return 1;
  }

  return 0;
}
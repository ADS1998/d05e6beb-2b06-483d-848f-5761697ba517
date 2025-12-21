#include <iostream>
#include <stdexcept>

#include "debug.h"


int main (int argc, char* argv[])
{
  debug::set_verbose_mode (argc, argv);

  if (argc != 1) { // <- adjust as required
    std::cerr <<
      "ERROR: invalid number of arguments.\n\n"
      "Command usage:\n\n"
      "   command arg1 arg2 ...\n\n";  // <- edit as required
    return 1;
  }


  try {
    // main processing block:

    // YOUR CODE HERE

    // end of main processing block
  }
  catch (std::exception& err) {
    // if any exceptions were thrown, we can handle them here:
    std::cerr << "ERROR: " << err.what() << " - aborting\n";
    return 1;
  }
  catch (...) { // <- the catch-all handler
    std::cerr << "ERROR: exception of unknown type was thrown - aborting\n";
    return 1;
  }

  return 0;
}

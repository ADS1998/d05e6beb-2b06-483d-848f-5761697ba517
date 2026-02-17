#include <iostream>
#include <stdexcept>
#include <string>

int main(int argc, char* argv[])
{
    try
    {
        // Show received command-line arguments
        std::cout << "Number of arguments: " << argc << "\n";
        for (int i = 0; i < argc; ++i)
            std::cout << "  argv[" << i << "] = " << argv[i] << "\n";

        // Require one user-supplied argument
        if (argc < 2)
            throw std::runtime_error(
                "Missing argument.\nUsage: ./a.out <number>"
            );

        // Convert argument from string to int
        // std::stoi throws on invalid or out-of-range input
        int value = std::stoi(argv[1]);

        // Use the validated value
        std::cout << "Valid number received: " << value << "\n";
    }
    catch (const std::invalid_argument&)
    {
        // Input was not numeric (e.g. letters)
        std::cerr << "ERROR: Argument is not a valid number.\n";
        return 1;
    }
    catch (const std::out_of_range&)
    {
        // Number does not fit in an int
        std::cerr << "ERROR: Number is out of range for int.\n";
        return 1;
    }
    catch (const std::exception& e)
    {
        // Any other runtime error
        std::cerr << "ERROR: " << e.what() << "\n";
        return 1;
    }

    return 0;
}

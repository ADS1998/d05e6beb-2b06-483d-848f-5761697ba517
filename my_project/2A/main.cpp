#include <iostream>

float promt_val() {
    float val{};
    do
    {
        // Prompt user for float 5-100
        std::cout << "Type a number between 5 and 100: ";
        // Get input
        if (!(std::cin >> val)) {
            std::cout << "NAN. Try again: " << "\n";
            std::cin.clear(); // Reset input errors
            std::cin.ignore(10000, '\n'); // Remove bad input
            continue;
        }
    } while (val < 5.0 ||  val > 100.0);

    return val; // Return if valid
}

double pow2(double val) {
    double sqr = val*val;
    return sqr;
}

bool is_prime(int val)
{
    if (val <= 1)
        return false;

    if (val == 2)
        return true;

    if (val % 2 == 0)
        return false;

    for (int i = 3; i * i <= val; i += 2)
    {
        if (val % i == 0)
            return false;
    }

    return true;
}

int main() {
    // auto val = promt_val();
    // std::cout << "prompt_val() returned val: " << val << "\n";

    // auto val = pow2(2.543);
    // std::cout << "pow2() returned val: " << val << "\n";

    int val{13};
    std::cout << (is_prime(val) ? "Is a prime\n" : "Is not a prime\n");

    return 0;
}
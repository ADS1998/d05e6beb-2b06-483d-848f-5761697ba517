#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main () {
    std::vector<int> v{};

    do
    {
        // Prompt user interger values
        std::cout << "Type an integer: ";
        // Get input
        if (!(std::cin >> v)) {
            std::cout << "NAN. Try again: " << "\n";
            std::cin.clear(); // Reset input errors
            std::cin.ignore(10000, '\n'); // Remove bad input
            continue;
        }
    } while (v > -1);

    // Display v
    for (const auto& x : v) {
        std::cout << x << " ";
    }
    // Sort v acending and display
    std::sort (v.begin(), v.end());
    for (const auto& x : v) {
        std::cout << x << " ";
    }
    // Reverse v and display
    std::reverse (v.begin(), v.end());
    for (const auto& x : v) {
        std::cout << x << " ";
    }
    //Calculate mean of v
    double mean(const std::vector<int>& v) {
        if (v.empty()) return 0.0;

        double sum = std::accumulate(v.begin(), v.end(), 0.0);
        return sum / v.size();
    }


    return 0;
}
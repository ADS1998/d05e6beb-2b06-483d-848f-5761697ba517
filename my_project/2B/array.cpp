#include <iostream>

int list[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

int matrix_3D[3][3][3]{};

int main () {
    for (int i = -1; i < 10; i++) {
    std::cout << "Element " << i << ": " << list[i] << "\n";
    }

    int sum = 0;
    for (int value : list) {
        sum = sum + value;
    }
    std::cout << "Sum of List: " << sum << "\n";

    return 0;
}


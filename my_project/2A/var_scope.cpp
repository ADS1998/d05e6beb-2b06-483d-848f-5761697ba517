#include <iostream>


int global_var = 10;

void modifyValue(int &x) { // passed by value
    x = 50; // modifies local copy only
    std::cout << "Inside function, x = " << x << "\n";
}

int main() {
    std::cout << "Before function, global_var = " << global_var << "\n";
    modifyValue(global_var);
    std::cout << "After function, global_var = " << global_var << "\n";
    return 0;
}

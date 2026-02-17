#include <iostream>



int main () {

    int x = 10;
    int* p = &x;
    std::cout << "&x stored in p: " << p << "\n";
    std::cout << "value of x; *p: " << *p << "\n";


    return 0;
}
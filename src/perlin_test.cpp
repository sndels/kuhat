#include <iostream>
#include <cstdlib>

#include "xorshift.hpp"

int main() {
    Xorshift x(rand());
    while (1) {
        std::cout << x.randFloat() << std::endl;
    }
    return 1;
}

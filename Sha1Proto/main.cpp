#include <iostream>
#include <bitset>
#include <vector>
#include <c++/sstream>
#include "Sha1.h"

int main() {

    Sha1 hasher;
    hasher.Hash("abc");
    std::cout << std::endl;
    Sha1 hasher1("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt "
                         "ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco "
                         "laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur."
                         " Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum");

    return 0;
}
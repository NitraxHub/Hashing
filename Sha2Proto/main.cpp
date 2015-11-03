#include <iostream>
#include "SHA256.h"
#include "SHA2_2.h"

using namespace std;

int main() {
    cout << "Hello, World!" << endl;

    //SHA256 test("abc");

    uint64_t tall;
    tall = 0x80;

    unsigned long long longtall = 0x80;

    std::cout << longtall << endl;


    //SHA2_2 test("abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu");

    //abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu
    //string s = (string)0x200;

    uint32_t myNumber = 0x0001233B;

    std::cout << std::hex << myNumber << std::endl;



    return 0;
}
#include <iostream>
#include <bitset>

using namespace std;


unsigned int Ch(unsigned int x,unsigned int y,unsigned int z){
    unsigned int f = x & y;
    unsigned int e = ~x & z;

    return f^e;
}

unsigned int Parity(unsigned int x,unsigned int y,unsigned int z){
    return x ^ y ^ z;
}

unsigned int Maj(unsigned int x,unsigned int y,unsigned int z){
    return (x & y) ^ (x & z) ^ (y & z);
}




int main() {
    unsigned int t = Ch(1231,240,123541);
    std::bitset<32>x(t);
    cout << x;

    unsigned int K1 = 0x5a827999;
    unsigned int K2 = 0x6ed9eba1;
    unsigned int K3 = 0x8f1bbcdc;
    unsigned int K4 = 0xca62c1d6;

    cout << endl << K1 << endl;

    cout << 512 - (1472%512);

    return 0;
}
#include <iostream>
#include <bitset>
#include <vector>

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
    unsigned int tass = Ch(1231,240,123541);
    std::bitset<32>x(tass);
    cout << x;

    //vector<bitset<8>> bitMessage;

    vector<uint8_t> bitsMessage;

    string input;
    cout << endl;
    getline(cin,input);

    for(int i = 0;i<input.length();i++){
        bitsMessage.push_back(input[i]);
        cout << endl << bitset<8>(bitsMessage[i]);
    }


    cout << endl;
    //bitsMessage.push_back(0);
    //bitsMessage.push_back(0);
    //bitsMessage.push_back(128); // 1000 0000
    for(auto &attack : bitsMessage){
        cout << bitset<8>(attack) << " ";
    }


    cout << endl<<"Message contains " << bitsMessage.size()*8 << " bits";


    cout << endl << "Need to add " << (448 - bitsMessage.size()*8)/8 << " byte";


    cout << endl;



    cout <<endl<< "----------"<<endl;
    cout << 448-bitsMessage.size()*8;
    cout << endl;
    cout << endl;

    //De siste 64 bits!!
    uint64_t  t = bitsMessage.size()*8;
    uint8_t t1 = (uint8_t)(t >> 56);
    uint8_t t2 = (uint8_t)(t >> 48);
    uint8_t t3 = (uint8_t)(t >> 40);
    uint8_t t4 = (uint8_t)(t >> 32);
    uint8_t t5 = (uint8_t)(t >> 24);
    uint8_t t6 = (uint8_t)(t >> 16);
    uint8_t t7 = (uint8_t)(t >> 8);
    uint8_t t8 = (uint8_t)(t);
    cout << bitset<8>(t1) << " " <<bitset<8>(t2)<< " " <<bitset<8>(t3)<< " " <<bitset<8>(t4)<< " " <<bitset<8>(t5)<< " " <<bitset<8>(t6)<< " " <<bitset<8>(t7)<< " " <<bitset<8>(t8);

    for(int i = 0; i<53;i++){
        if(i == 0){
            bitsMessage.push_back(128);
        }
        else{

            bitsMessage.push_back(0);
        }
        cout << endl << i;
    }


    bitsMessage.push_back(t1);
    bitsMessage.push_back(t2);
    bitsMessage.push_back(t3);
    bitsMessage.push_back(t4);
    bitsMessage.push_back(t5);
    bitsMessage.push_back(t6);
    bitsMessage.push_back(t7);
    bitsMessage.push_back(t8);

    //Adde de siste 64 bits (8 byte)
    /*
    for(int i = 1;i<=8;i++){
        bitsMessage.push_back((uint8_t)(t>>(64-(8*i))));
        cout <<endl<< 64-(8*i) << endl << bitset<8>((uint8_t)(t));
    }
     */

    cout << endl;
    //cout << bitsMessage.size();
    for(auto &attack : bitsMessage){
        cout << bitset<8>(attack) << " ";
    }
    cout <<endl<< "----------"<<endl;
    cout << bitsMessage.size();
    cout << endl;
    //cout << (int)bitMessage[0].to_ulong() & (int)bitMessage[1].to_ulong() ;
    //cout << bitsMessage[0] & bitsMessage[1];
    uint32_t K1 = 0x5a827999;
    uint32_t K2 = 0x6ed9eba1;
    uint32_t K3 = 0x8f1bbcdc;
    unsigned int K4 = 0xca62c1d6;

    cout << K1 + K4;

    uint32_t test = 2;
    unsigned int e3 = bitsMessage[0] & bitsMessage[1];


    vector<uint32_t> Words;
    int counter = 0;
    //Words.push_back(bitsMessage[0] << 24 | bitsMessage[1]<<16 | bitsMessage[2]<<8 | bitsMessage[3]);
    //cout << Words[0];

    for(int i = 0;i<bitsMessage.size();i = i + 4){
        Words.push_back(bitsMessage[i] << 24 | bitsMessage[i+1]<<16 | bitsMessage[i+2]<<8 | bitsMessage[i+3]);
    }

    cout << endl;
    cout << Words.size();
    cout << endl;

    for(auto &current : Words){
        cout << bitset<32>(current) << " ";
    }



    uint32_t digest[5];
    //Hex
    digest[0] = 0x67452301;
    digest[1] = 0xefcdab89;
    digest[2] = 0x98badcfe;
    digest[3] = 0x10325476;
    digest[4] = 0xc3d2e1f0;


    uint32_t A = digest[0];
    uint32_t B = digest[1];
    uint32_t C = digest[2];
    uint32_t D = digest[3];
    uint32_t E = digest[4];

    for(int t = 0;t<80;t++){
        if(t < 20){
            //Round 1
            //cout << endl << t << "R1";


        }
        else if(t > 19 && t < 40){
            //Round 2
            //cout << endl << t <8< "R2";78

        }
        else if(t > 39 && t < 60){
            //Round 3
            //cout << endl << t << "R3";

        }
        else{
            //Round 4
            //cout << endl << t << "R4";


        }



    }


    /*
    char a = 'a';
    char c = 'c';
    unsigned int b = a;
    unsigned int d = c;
    unsigned int e2 = b&d;
    unsigned int e3 = bitsMessage[0] & bitsMessage[1];
    cout << "---------------------" << endl << e3 << endl;

    cout << endl << K1 << endl;

    cout << 512 - (1472%512);
    */

    return 0;
}
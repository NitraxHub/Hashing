//
// Created by Mello on 31.10.2015.
//

#include "SHA2_2.h"

#include <c++/iostream>



inline uint64_t Ch(uint64_t x,uint64_t y,uint64_t z)
{
    return ( x & y) ^ (~x & z);
}

inline uint64_t Maj(uint64_t x,uint64_t y,uint64_t z)
{
    return (x & y) ^ (x & z) ^ (y & z);
}

template <typename T>
inline T SHR(T var, uint8_t n)
{
    return var >> n;
};

template<typename T>
inline T ROTL(T var, uint8_t num)
{
    constexpr size_t type_size = 8 * sizeof(T);
    return (var << num) | (var >> (type_size - num));
};


template<typename T>
inline T ROTR(T var, uint8_t num)
{
    constexpr size_t type_size = 8 * sizeof(T);
    return (var >> num) | (var << (type_size - num));
};



template <typename T>
inline T sum1(T var)
{
    return ROTR(var,14) ^ ROTR(var,18) ^ ROTR(var,41);
}


template <typename T>
inline T sum0(T var)
{
    return ROTR(var,28) ^ ROTR(var,34) ^ ROTR(var,39);
}

template<typename T>
inline T Sigma0(T var)
{
    return ROTR(var,1) ^ ROTR(var,8) ^ SHR(var,7);
};

template<typename T>
inline T Sigma1(T var)
{
    return ROTR(var,19) ^ ROTR(var,61) ^ SHR(var,6);
};

std::vector<uint64_t> SHA2_2::MessageParser(size_t currentBlock){
    std::vector<uint64_t> Words;
    std::cout << std::endl << "-----------------------------------------" << std::endl;
    Words.clear();
    size_t startingPoint = currentBlock*128;
    for(size_t i = startingPoint;i<startingPoint+128;i = i+8){
        Words.push_back(
                bitsMessage[i] << 56 | bitsMessage[i+1]<<48 | bitsMessage[i+2]<<40 | bitsMessage[i+3] << 32
                | bitsMessage[i+4] << 24 | bitsMessage[i+5]<<16 | bitsMessage[i+6]<<8 | bitsMessage[i+7]);
    }

    return Words;


}
void reset(std::vector<uint64_t>& PlaceHolder)
{
    for(size_t t = 0;t<8;t++)
    {
        PlaceHolder.push_back(SHA2_2::InitialVal[t]);
    }
}

SHA2_2::SHA2_2(std::string to_hash)
{

    size_t size = MessagePadding(to_hash);


    std::cout << "Padding done, size: " << size << std::endl;

    std::vector<uint64_t> Block;

    std::vector<uint64_t> PlaceHolder;

    reset(PlaceHolder);


    for(size_t i = 0; i<size;i++)
    {
        std::cout << "|-------------------- Block -----------------------|" << std::endl;
        Block = MessageParser(i);
        A=PlaceHolder[0];
        B=PlaceHolder[1];
        C=PlaceHolder[2];
        D=PlaceHolder[3];
        E=PlaceHolder[4];
        F=PlaceHolder[5];
        G=PlaceHolder[6];
        H=PlaceHolder[7];

        for(uint64_t b : Block){
            std::cout << std::hex << b << std::endl;
        }

        for(size_t t = 0;t<80;t++){

            if(t<16){
                CurrentWord = Block[t];
            }
            else{
                //uint32_t one = Block[t-2];
                //uint32_t two = Blo
                Block.push_back(Sigma1(Block[t-2]) + Block[t-7] + Sigma0(Block[t-15]) + Block[t-16]);
                CurrentWord = Block[t];
                //std::cout<<" "<< t << " ";
                //uint32_t kT = K[t];
            }





            T1 = H + sum1(E) + Ch(E,F,G) + K[t] + CurrentWord;
            //T1 = H + (ROTR(E,14) ^ROTR(E,18) ^ ROTR(E,41)) +  ((E & F) ^ (~E & G)) + K[t] + CurrentWord;

            T2 = sum0(A) + Maj(A,B,C);


            //T2 = (ROTR(A,28) ^ROTR(A,34)^ROTR(A,39)) + Maj(A,B,C);

            //std::cout << "Round " << t << "   T1: " << T1 << "  T2: " << T2 << std::endl;

            H = G;
            G = F;
            F = E;
            E = D + T1;
            D = C;
            C = B;
            B = A;
            A = T1 + T2;



            if(t > 21){
                //std::cout << "d";
            }
            //std::cout << "Round " << t << std::hex <<" K: " << K[t]<<  std::endl;



            std::cout << "Round " << t;
            std::cout << std::endl;
            std::cout << std::hex <<" A " << A << " B " << B << " C " << C << " D "  << D << std::endl <<" E " << E <<" F " << F <<" G " << G << " H " << H << std::endl;
            std::cout << "-------------------------------------------------------------" << std::endl;



        }


        PlaceHolder[0] = A + PlaceHolder[0];
        PlaceHolder[1] = B + PlaceHolder[1];
        PlaceHolder[2] = C + PlaceHolder[2];
        PlaceHolder[3] = D + PlaceHolder[3];
        PlaceHolder[4] = E + PlaceHolder[4];
        PlaceHolder[5] = F + PlaceHolder[5];
        PlaceHolder[6] = G + PlaceHolder[6];
        PlaceHolder[7] = H + PlaceHolder[7];
    }
    std::cout << std::endl;
    for(uint64_t t : PlaceHolder){
        std::cout << std::hex << t << " ";
    }



}


size_t SHA2_2::MessagePadding(std::string Message)
{

    bitsMessage.clear();

    for(int i = 0;i<Message.length();i++)
    {
        bitsMessage.push_back(Message[i]);
    }

    size_t AmountOf0Bytes = 1024-(((Message.length()*8)+128)%1024);

    std::cout << "Needs: 0's " << AmountOf0Bytes/8 << std::endl;

    for(int i=0;i<AmountOf0Bytes/8;i++)
    {
        if(i==0){
            bitsMessage.push_back(128);

        }
        else{
            bitsMessage.push_back(0);
        }
    }


    //Last 128 bits
    uint64_t MessageSize = Message.size()*8;
    //32
    bitsMessage.push_back(0);
    bitsMessage.push_back(0);
    bitsMessage.push_back(0);
    bitsMessage.push_back(0);
    //32
    bitsMessage.push_back(0);
    bitsMessage.push_back(0);
    bitsMessage.push_back(0);
    bitsMessage.push_back(0);


    //last 64 bits
    bitsMessage.push_back((uint8_t)(MessageSize >> 56));
    bitsMessage.push_back((uint8_t)(MessageSize >> 48));
    bitsMessage.push_back((uint8_t)(MessageSize >> 40));
    bitsMessage.push_back((uint8_t)(MessageSize >> 32));
    bitsMessage.push_back((uint8_t)(MessageSize >> 24));
    bitsMessage.push_back((uint8_t)(MessageSize >> 16));
    bitsMessage.push_back((uint8_t)(MessageSize >> 8));
    bitsMessage.push_back((uint8_t)(MessageSize));

    std::cout << "Amout of bytes: " << bitsMessage.size() << std::endl;

    return bitsMessage.size()/128; //Number of rounds needed ?

}




//SHA-512 Inital Values
const uint64_t SHA2_2::InitialVal[] {
        0x6a09e667f3bcc908, 0xbb67ae8584caa73b, 0x3c6ef372fe94f82b, 0xa54ff53a5f1d36f1,
        0x510e527fade682d1, 0x9b05688c2b3e6c1f, 0x1f83d9abfb41bd6b, 0x5be0cd19137e2179
};



//SHA-512 Round constants:
const uint64_t SHA2_2::K[] {
        0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc, 0x3956c25bf348b538,
        0x59f111f1b605d019, 0x923f82a4af194f9b, 0xab1c5ed5da6d8118, 0xd807aa98a3030242, 0x12835b0145706fbe,
        0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2, 0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235,
        0xc19bf174cf692694, 0xe49b69c19ef14ad2, 0xefbe4786384f25e3, 0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
        0x2de92c6f592b0275, 0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5, 0x983e5152ee66dfab,
        0xa831c66d2db43210, 0xb00327c898fb213f, 0xbf597fc7beef0ee4, 0xc6e00bf33da88fc2, 0xd5a79147930aa725,
        0x06ca6351e003826f, 0x142929670a0e6e70, 0x27b70a8546d22ffc, 0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed,
        0x53380d139d95b3df, 0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6, 0x92722c851482353b,
        0xa2bfe8a14cf10364, 0xa81a664bbc423001, 0xc24b8b70d0f89791, 0xc76c51a30654be30, 0xd192e819d6ef5218,
        0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8, 0x19a4c116b8d2d0c8, 0x1e376c085141ab53,
        0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8, 0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb, 0x5b9cca4f7763e373,
        0x682e6ff3d6b2b8a3, 0x748f82ee5defb2fc, 0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec,
        0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915, 0xc67178f2e372532b, 0xca273eceea26619c,
        0xd186b8c721c0c207, 0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178, 0x06f067aa72176fba, 0x0a637dc5a2c898a6,
        0x113f9804bef90dae, 0x1b710b35131c471b, 0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc,
        0x431d67c49c100d4c, 0x4cc5d4becb3e42b6, 0x597f299cfc657e2a, 0x5fcb6fab3ad6faec, 0x6c44198c4a475817


};

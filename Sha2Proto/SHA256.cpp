//
// Created by Mello on 27.10.2015.
//

#include <c++/iostream>
#include "SHA256.h"


inline uint32_t Ch(uint32_t x,uint32_t y,uint32_t z){
        return ( x & y) ^ (~x & z);
}

inline uint32_t Maj(uint32_t x,uint32_t y,uint32_t z){
        return (x & y) ^ (x & z) ^ (y & z);
}

template <typename T>
inline T SHR(T var, uint8_t n){
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
inline T sum1(T var){
        return ROTR(var,6) ^ ROTR(var,11) ^ ROTR(var,25);
}


template <typename T>
inline T sum0(T var){
        return ROTR(var,2) ^ ROTR(var,13) ^ ROTR(var,22);
}

template<typename T>
inline T Sigma0(T var)
{
        return ROTR(var,7) ^ ROTR(var,18) ^ SHR(var,3);
};

template<typename T>
inline T Sigma1(T var)
{
        return ROTR(var,17) ^ ROTR(var,19) ^ SHR(var,10);
};


void reset(std::vector<uint32_t>& PlaceHolder){
        PlaceHolder.clear();
        PlaceHolder.push_back(0x6a09e667);
        PlaceHolder.push_back(0xbb67ae85);
        PlaceHolder.push_back(0x3c6ef372);
        PlaceHolder.push_back(0xa54ff53a);
        PlaceHolder.push_back(0x510e527f);
        PlaceHolder.push_back(0x9b05688c);
        PlaceHolder.push_back(0x1f83d9ab);
        PlaceHolder.push_back(0x5be0cd19);
}


SHA256::SHA256(std::string to_hash) {
        std::vector<uint32_t> Block;
        std::cout << "Hello" << std::endl << "hashing: " << to_hash << std::endl;
        uint32_t co = K[0];
        std::cout << "Constant test: " << K[2] << std::endl;

        uint32_t numBlocks = MessagePadding(to_hash);
        std::vector<uint32_t> PlaceHolder;

        reset(PlaceHolder);
        


        for(int i =0;i<numBlocks;i++){

                Block = MessageParser(i);

                A=PlaceHolder[0];
                B=PlaceHolder[1];
                C=PlaceHolder[2];
                D=PlaceHolder[3];
                E=PlaceHolder[4];
                F=PlaceHolder[5];
                G=PlaceHolder[6];
                H=PlaceHolder[7];

                for(size_t t = 0;t<64;t++){

                        if(t<16){
                                CurrentWord = Block[t];
                        }
                        else{
                                //uint32_t one = Block[t-2];
                                //uint32_t two = Blo
                                Block.push_back(Sigma1(Block[t-2]) + Block[t-7] + Sigma0(Block[t-15]) + Block[t-16]);
                                CurrentWord = Block[t];
                                //std::cout<<" "<< t << " ";
                                uint32_t kT = K[t];
                        }




                        std::cout << "Round " << t << " A " << A << " B " << B << " C " << C << " D " << D << std::endl;
                        T1 = H + sum1(E) + Ch(E,F,G) + K[t] + CurrentWord;
                        T2 = sum0(A) + Maj(A,B,C);

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


                }


                PlaceHolder[0] = A + PlaceHolder[0];
                PlaceHolder[1] = B + PlaceHolder[1];
                PlaceHolder[2] = C + PlaceHolder[2];
                PlaceHolder[3] = D + PlaceHolder[3];
                PlaceHolder[4] = E + PlaceHolder[4];
                PlaceHolder[5] = F + PlaceHolder[5];
                PlaceHolder[6] = G + PlaceHolder[6];
                PlaceHolder[7] = H + PlaceHolder[7];





        };

}



uint32_t SHA256::MessagePadding(std::string Message){
        bitsMessage.clear();

        for(int i = 0;i<Message.length();i++){
                //Add character by character to a list, of type unsigned int
                bitsMessage.push_back(Message[i]);
        }



        int AmountOf0Bytes = 512-(((Message.length()*8) + 64)%512);


        for(int i = 0; i<AmountOf0Bytes/8;i++){
                if(i == 0){
                        bitsMessage.push_back(128);
                }
                else{

                        bitsMessage.push_back(0);
                }

        }

        //Last 64 bits
        uint64_t MessageSize = Message.size()*8; //Size in number of bits.
        // Taking 8 bits at the time from the messageSize
        bitsMessage.push_back((uint8_t)(MessageSize >> 56));
        bitsMessage.push_back((uint8_t)(MessageSize >> 48));
        bitsMessage.push_back((uint8_t)(MessageSize >> 40));
        bitsMessage.push_back((uint8_t)(MessageSize >> 32));
        bitsMessage.push_back((uint8_t)(MessageSize >> 24));
        bitsMessage.push_back((uint8_t)(MessageSize >> 16));
        bitsMessage.push_back((uint8_t)(MessageSize >> 8));
        bitsMessage.push_back((uint8_t)(MessageSize));

        return bitsMessage.size()/64;
}


std::vector<uint32_t> SHA256::MessageParser(int currentBlock){

std::vector<uint32_t> Words;
int startingPoint = currentBlock*64;
for(int i = startingPoint;i<startingPoint+64;i = i + 4){ //Legger inn chunks på 32 bit (4 8 bits i gangen)
Words.push_back(bitsMessage[i] << 24 | bitsMessage[i+1]<<16 | bitsMessage[i+2]<<8 | bitsMessage[i+3]);
}
return Words;
}




const std::vector<SHA256::stage_info> SHA256::stage_info_list
        {
                {
                        32,
                        [](uint32_t x,uint32_t y,uint32_t z)
                        {
                            return (x & y) ^ (~x & z);
                        }

                },
                {
                        32,
                        [](uint32_t x,uint32_t y,uint32_t z)
                        {
                            return (x & y) ^ (~x & z);
                        }

                },
                {
                        32,
                        [](uint32_t x,uint32_t y,uint32_t z)
                        {
                            return (x & y) ^ (~x & z);
                        }

                }

        };




const uint32_t SHA256::K[] =
        {
                0x428A2F98, 0x71374491, 0xB5C0FBCF, 0xE9B5DBA5,
                0x3956C25B, 0x59F111F1, 0x923F82A4, 0xAB1C5ED5,
                0xD807AA98, 0x12835B01, 0x243185BE, 0x550C7DC3,
                0x72BE5D74, 0x80DEB1FE, 0x9BDC06A7, 0xC19BF174,
                0xE49B69C1, 0xEFBE4786, 0x0FC19DC6, 0x240CA1CC,
                0x2DE92C6F, 0x4A7484AA, 0x5CB0A9DC, 0x76F988DA,
                0x983E5152, 0xA831C66D, 0xB00327C8, 0xBF597FC7,
                0xC6E00BF3, 0xD5A79147, 0x06CA6351, 0x14292967,
                0x27B70A85, 0x2E1B2138, 0x4D2C6DFC, 0x53380D13,
                0x650A7354, 0x766A0ABB, 0x81C2C92E, 0x92722C85,
                0xA2BFE8A1, 0xA81A664B, 0xC24B8B70, 0xC76C51A3,
                0xD192E819, 0xD6990624, 0xF40E3585, 0x106AA070,
                0x19A4C116, 0x1E376C08, 0x2748774C, 0x34B0BCB5,
                0x391C0CB3, 0x4ED8AA4A, 0x5B9CCA4F, 0x682E6FF3,
                0x748F82EE, 0x78A5636F, 0x84C87814, 0x8CC70208,
                0x90BEFFFA, 0xA4506CEB, 0xBEF9A3F7, 0xC67178F2,
        };

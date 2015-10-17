//
// Created by Mello on 17.10.2015.
//

#include <stdint.h>
#include "Sha1.h"



unsigned int Ch(unsigned int x,unsigned int y,unsigned int z){
    return ( x & y) ^ (~x & z);
}

unsigned int Parity(unsigned int x,unsigned int y,unsigned int z){
    return x ^ y ^ z;
}

unsigned int Maj(unsigned int x,unsigned int y,unsigned int z){
    return (x & y) ^ (x & z) ^ (y & z);
}

void Reset(std::vector<unsigned int>& PlaceHolder){
    PlaceHolder.clear();
    PlaceHolder.push_back(0x67452301);
    PlaceHolder.push_back(0xefcdab89);
    PlaceHolder.push_back(0x98badcfe);
    PlaceHolder.push_back(0x10325476);
    PlaceHolder.push_back(0xc3d2e1f0);
}

//Needs work!! Doesnt work on more than one block
std::vector<unsigned int> Sha1::MessageParser(std::string Message){

    for(int i = 0;i<Message.length();i++){
        //Add character by character to a list, of type unsigned int
        bitsMessage.push_back(Message[i]);
    }
    uint64_t MessageSize = bitsMessage.size()*8; //Size in number of bits.

    int tall = bitsMessage.size();
    int tall1 = Message.length();

    for(int i = 0; i<53;i++){
        if(i == 0){
            bitsMessage.push_back(128);
        }
        else{

            bitsMessage.push_back(0);
        }
    }

    //Taking 8 bits at the time from the messageSize
    bitsMessage.push_back((uint8_t)(MessageSize >> 56));
    bitsMessage.push_back((uint8_t)(MessageSize >> 48));
    bitsMessage.push_back((uint8_t)(MessageSize >> 40));
    bitsMessage.push_back((uint8_t)(MessageSize >> 32));
    bitsMessage.push_back((uint8_t)(MessageSize >> 24));
    bitsMessage.push_back((uint8_t)(MessageSize >> 16));
    bitsMessage.push_back((uint8_t)(MessageSize >> 8));
    bitsMessage.push_back((uint8_t)(MessageSize));


    //Senere i egen funksjon? må gjøres for hver block
    std::vector<unsigned int> Words;

    for(int i = 0;i<64;i = i + 4){ //Legger inn chunks på 32 bit (4 8 bits i gangen)
        Words.push_back(bitsMessage[i] << 24 | bitsMessage[i+1]<<16 | bitsMessage[i+2]<<8 | bitsMessage[i+3]);
    }

    return Words;

}


void Sha1::Hash(std::string in){

    //Message Parser
    std::vector<unsigned int> Words;
    Words = MessageParser(in);


    std::vector <unsigned int> PlaceHolder;
    Reset(PlaceHolder);




    unsigned int A = PlaceHolder[0];
    unsigned int B = PlaceHolder[1];
    unsigned int C = PlaceHolder[2];
    unsigned int D = PlaceHolder[3];
    unsigned int E = PlaceHolder[4];
    unsigned int T;




    for(int i = 1;i<2;i++){
        for(int t = 0;t<80;t++){
            if(t < 16){
                CurrentWord = Words[t];
                //cout << endl << t << " " << CurrentWord;
            }
            else{
                Words.push_back(((Words[t-3] ^ Words[t-8] ^ Words[t-14] ^ Words[t-16]) <<1) | ((Words[t-3] ^ Words[t-8] ^ Words[t-14] ^ Words[t-16]) >> 32-1));
                CurrentWord = Words[t];
            }

            if(t <= 19){            //Round 1
                T = ((A << 5) | (A >> 32-5)) + Ch(B,C,D) + E + K1 + CurrentWord;
            }
            else if(t > 19 && t <= 39){
                T = ((A << 5) | (A >> 32-5)) + Parity(B,C,D) + E + K2 + CurrentWord;
            }
            else if(t > 39 && t <= 59){            //Round 3
                T = ((A << 5) | (A >> 32-5)) + Maj(B,C,D) + E + K3 + CurrentWord;
            }
            else{            //Round 4
                T = ((A << 5) | (A >> 32-5)) + Parity(B,C,D) + E + K4 + CurrentWord;
            }

            E = D;
            D = C;
            C = ((B << 30) | (B >> 32-30));
            B = A;
            A = T;

        }

        PlaceHolder[0] = A + PlaceHolder[0];
        PlaceHolder[1] = B + PlaceHolder[1];
        PlaceHolder[2] = C + PlaceHolder[2];
        PlaceHolder[3] = D + PlaceHolder[3];
        PlaceHolder[4] = E + PlaceHolder[4];

    }

    //End of Block

    std::cout << "Message Digest is: "<<std::endl;

    std::stringstream sstream;
    sstream << std::uppercase <<std::hex << PlaceHolder[0] << PlaceHolder[1] << PlaceHolder[2] << PlaceHolder[3]<< PlaceHolder[4];
    std::string answer = sstream.str();
    std::cout << std::endl;
    std::cout << answer;

}
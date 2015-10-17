//
// Created by Mello on 17.10.2015.
//

#ifndef SHA1PROTO_SHA1_H
#define SHA1PROTO_SHA1_H

#include<string>
#include<vector>
#include<sstream>
#include<iostream>

class Sha1 {
public:
    Sha1(){};
    Sha1(std::string in){
        this->input = in;
        Hash(input);
    };

    void Hash(std::string in);
    //std::string Sha1(std::string in);

    ~Sha1(){};

protected:
    std::string input;
    std::vector<unsigned int> bitsMessage;


private:
    std::vector<unsigned int> MessageParser(std::string Message);
    unsigned int K1 = 0x5a827999;
    unsigned int K2 = 0x6ed9eba1;
    unsigned int K3 = 0x8f1bbcdc;
    unsigned int K4 = 0xca62c1d6;

    unsigned int CurrentWord;



};


#endif //SHA1PROTO_SHA1_H

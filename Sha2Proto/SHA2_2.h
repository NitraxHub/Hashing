//
// Created by Mello on 31.10.2015.
//

#ifndef SHA2PROTO_SHA2_2_H
#define SHA2PROTO_SHA2_2_H


#include <stdint.h>
#include<string>
#include <vector>

class SHA2_2 {
public:
    static const uint64_t K[];
    static const uint64_t InitialVal[];

    SHA2_2(std::string to_hash);

protected:
    std::vector<uint64_t> bitsMessage;

private:
    size_t MessagePadding(std::string Message);
    std::vector<uint64_t> MessageParser(size_t currentBlock);
    uint64_t CurrentWord;

    uint64_t A;
    uint64_t B;
    uint64_t C;
    uint64_t D;
    uint64_t E;
    uint64_t F;
    uint64_t G;
    uint64_t H;

    uint64_t T1;
    uint64_t T2;

};




//Message Pading
//Ta current 512-64? 1024-128?



//Message Parsing
//Kalkulere Words
// 0 - 15
// 16-79





#endif //SHA2PROTO_SHA2_2_H

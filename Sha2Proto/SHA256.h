//
// Created by Mello on 27.10.2015.
//

#ifndef SHA2PROTO_SHA256_H
#define SHA2PROTO_SHA256_H


#include <stdint.h>
#include <c++/functional>
#include <vector>

class SHA256 {
public:

    SHA256(std::string to_hash);

    struct stage_info
    {
        const uint32_t constant;
        const std::function<uint32_t(uint32_t, uint32_t,uint32_t)> function;
    };

    static const std::vector<stage_info> stage_info_list;

    static const uint32_t K[];



protected:
    std::vector<uint32_t> bitsMessage;



private:
    uint32_t MessagePadding(std::string Message);
    std::vector<uint32_t> MessageParser(int currentBlock);
    uint32_t CurrentWord;

    uint32_t A;
    uint32_t B;
    uint32_t C;
    uint32_t D;
    uint32_t E;
    uint32_t F;
    uint32_t G;
    uint32_t H;

    uint32_t T1;
    uint32_t T2;

};




#endif //SHA2PROTO_SHA256_H

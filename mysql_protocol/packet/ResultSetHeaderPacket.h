//
// Created by zhukovasky on 2020/10/8.
//

#ifndef XSQL_RESULTSETHEADERPACKET_H
#define XSQL_RESULTSETHEADERPACKET_H

#include "BinaryPacket.h"

namespace MyProtocol {
    class ResultSetHeaderPacket : public BinaryPacket {
    public:
        int fieldCount;
        long extra;

        void read(std::vector<byte> data);

        int calPacketSize() override;

        std::string getPacketInfo() override;

        muduo::net::Buffer &writeBuf(muduo::net::Buffer &buffer) override;
    };
};


#endif //XSQL_RESULTSETHEADERPACKET_H

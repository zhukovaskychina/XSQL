//
// Created by zhukovasky on 2020/10/8.
//

#ifndef XSQL_EOFPACKET_H
#define XSQL_EOFPACKET_H


#include "BinaryPacket.h"

namespace MyProtocol {
    class EOFPacket : public MyProtocol::BinaryPacket {

    public:

        void read(BinaryPacket *bin);

        void read(std::vector<byte> data);

        int calPacketSize() override;

        std::string getPacketInfo() override;

        void write(const muduo::net::TcpConnectionPtr &conn, muduo::net::Buffer &buffer) override;

        muduo::net::Buffer &writeBuf(muduo::net::Buffer &buffer) override;

        static const byte FIELD_COUNT = (byte) 0xfe;

        byte fieldCount = FIELD_COUNT;
        int warningCount;
        int status = 2;
    };
};


#endif //XSQL_EOFPACKET_H

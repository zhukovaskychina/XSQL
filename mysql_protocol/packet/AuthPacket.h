//
// Created by zhukovasky on 2020/9/21.
//

#ifndef MUDUO_SERVER_AUTHPACKET_H
#define MUDUO_SERVER_AUTHPACKET_H


#include "BinaryPacket.h"

namespace MyProtocol {

    class AuthPacket:public BinaryPacket{
    public:
        AuthPacket();

        long clientFlag;
        long maxPacketSize;
        int charsetIndex;
        std::vector<byte > extra;

        std::vector<byte> FILTER;

        std::string user;

        std::vector<byte > password;

        std::string database;

        void read(const BinaryPacket *binaryPacket);

        void write(const muduo::net::TcpConnectionPtr &conn, muduo::net::Buffer &buffer) override;

        int calPacketSize() override;
    };
}
#endif //MUDUO_SERVER_AUTHPACKET_H

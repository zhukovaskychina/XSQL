//
// Created by zhukovasky on 2020/9/18.
//

#ifndef MUDUO_SERVER_HANDSHAKEPACKET_H
#define MUDUO_SERVER_HANDSHAKEPACKET_H


#include <mysql_protocol/MySqlPacket.h>
#include <utils/StringUtils.h>
#include "BinaryPacket.h"

namespace MyProtocol{
    class HandshakePacket: public MyProtocol::MySQLPacket {
    public:

        int calPacketSize() override;

        std::string getPacketInfo() override;

        void write(const muduo::net::TcpConnectionPtr &conn, muduo::net::Buffer &buffer) override;

        muduo::net::Buffer &writeBuf(muduo::net::Buffer &buffer) override;

    public:

        void read(BinaryPacket *bin);

        byte protocolVersion;
        std::vector<byte> serverVersion=Utils::StringUtils::convertStringToBytes("mysql-version-5.1.1");
        long threadId;
        std::vector<byte > seed;
        int serverCapabilities;
        byte setCharsetIndex;
        int serverStatus;
        std::vector<byte> restOfScrambleBuff;
        byte serverCharsetIndex;
        std::vector<byte> FILLER_13={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    };

}


#endif //MUDUO_SERVER_HANDSHAKEPACKET_H

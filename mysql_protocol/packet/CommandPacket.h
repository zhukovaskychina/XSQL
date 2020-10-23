//
// Created by zhukovasky on 2020/10/8.
//

#ifndef XSQL_COMMANDPACKET_H
#define XSQL_COMMANDPACKET_H


#include "BinaryPacket.h"

namespace MyProtocol {

    class CommandPacket : public BinaryPacket {

    public:
        CommandPacket(std::string query,byte command);

        CommandPacket(std::string query);

        int calPacketSize() override;

        std::string getPacketInfo() override;

        void read(std::vector<byte > data);

        void write(const muduo::net::TcpConnectionPtr &conn, muduo::net::Buffer &buffer) override;

    public:
         byte command;
         std::vector<byte > arg;
    };
}

#endif //XSQL_COMMANDPACKET_H

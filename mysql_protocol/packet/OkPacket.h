//
// Created by zhukovasky on 2020/9/17.
//

#ifndef MUDUO_SERVER_OKPACKET_H
#define MUDUO_SERVER_OKPACKET_H

#include <mysql_protocol/MySqlPacket.h>
#include <muduo/net/Callbacks.h>
#include "BinaryPacket.h"

namespace MyProtocol{
    class OkPacket: public MyProtocol::BinaryPacket {
    public:
        OkPacket();


        int calPacketSize() override;

        std::string getPacketInfo() override;

        void read(MyProtocol::BinaryPacket *binaryPacket);

        void write(const muduo::net::TcpConnectionPtr &conn, muduo::net::Buffer &buffer) override;

        byte header=0x00;

        long affectedRows;

        long insertId;

        int serverStatus;

        int warningCount;

        std::vector<byte > message;


        std::vector<byte> OKPACKET={
                7, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0
        };
        std::vector<byte > AUTHOKPACKET={
                7, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0
        };
    private:
        byte fieldCount=0x00;
    };

}


#endif //MUDUO_SERVER_OKPACKET_H

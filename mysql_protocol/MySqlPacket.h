//
// Created by zhukovasky on 2020/9/17.
//

#ifndef MUDUO_SERVER_MYSQLPACKET_H
#define MUDUO_SERVER_MYSQLPACKET_H

#include <muduo/net/Buffer.h>
#include <common/Common.h>
#include <muduo/net/TcpServer.h>
namespace MyProtocol{
    class MySQLPacket {

    public:

        int packetLength;

        byte packetId=1;

    public:


        virtual int calPacketSize()=0;

        virtual std::string getPacketInfo()=0;

        virtual void write(const muduo::net::TcpConnectionPtr &conn, muduo::net::Buffer &buffer)=0;

        virtual muduo::net::Buffer& writeBuf(muduo::net::Buffer &buffer)=0;
    };

}


#endif //MUDUO_SERVER_MYSQLPACKET_H

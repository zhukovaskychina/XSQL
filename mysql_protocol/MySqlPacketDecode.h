//
// Created by zhukovasky on 2020/9/17.
//

#ifndef MUDUO_SERVER_MYSQLPACKETDECODE_H
#define MUDUO_SERVER_MYSQLPACKETDECODE_H


#include <muduo/base/noncopyable.h>
#include <muduo/net/TcpConnection.h>
#include <utils/BufferUtils.h>
#include <list>
#include <iostream>
#include <utils/ByteUtils.h>
#include <mysql_protocol/packet/BinaryPacket.h>
#include <mysql_protocol/packet/AuthPacket.h>
#include <Exceptions.h>
using namespace std;
class MySqlPacketDecode : muduo::noncopyable {
public:
    typedef std::function<void (const muduo::net::TcpConnectionPtr&,
                                const MyProtocol::BinaryPacket *message,
                                muduo::Timestamp)> MySQLPacketMessageCallBack_;


    explicit MySqlPacketDecode(const MySQLPacketMessageCallBack_& cb)
            : messageCallback_(cb)
    {
    }

    void onMessage(const muduo::net::TcpConnectionPtr& conn,
                   muduo::net::Buffer* buf,
                   muduo::Timestamp receiveTime){
        std::string tcpInfoStrings=conn.get()->getTcpInfoString();
        cout<<tcpInfoStrings<<endl;
        while (buf->readableBytes()>=kHeaderLen){
           // buf->retrieve(kHeaderLen);
            try {
                int size=buf->readableBytes();
                int length=BufferUtils::readU3(buf);
                unsigned char packetId=buf->readInt8();
                std::vector<char> arrays= ByteUtils::readRestByte(buf,length);
                MyProtocol::BinaryPacket *binaryPacket=new MyProtocol::BinaryPacket();
                binaryPacket->packetId=packetId;
                binaryPacket->packetLength=length;
                binaryPacket->setData(arrays);
                buf->retrieveAll();
                messageCallback_(conn,binaryPacket,receiveTime);
                delete(binaryPacket);
            }catch (std::exception& e){
                cout<<e.what()<<endl;
            }


            break;
        }
    }
private:
    MySQLPacketMessageCallBack_ messageCallback_;
    const static size_t kHeaderLen = 8;
};


#endif //MUDUO_SERVER_MYSQLPACKETDECODE_H

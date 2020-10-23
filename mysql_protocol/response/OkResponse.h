//
// Created by zhukovasky on 2020/10/9.
//

#ifndef XSQL_OKRESPONSE_H
#define XSQL_OKRESPONSE_H

#include <muduo/net/Buffer.h>
#include <muduo/net/TcpConnection.h>
#include <mysql_protocol/packet/OkPacket.h>

using namespace muduo;
using namespace muduo::net;
class OkResponse {
public:
    static void responseOK(const TcpConnectionPtr &conn){
        MyProtocol::OkPacket *okPacket = new MyProtocol::OkPacket();
        Buffer buffer;
        okPacket->write(conn,buffer);
        buffer.retrieveAll();
        delete(okPacket);
    }

    static void responseWithAffectedRows(const TcpConnectionPtr &conn,long affectedRows){
        MyProtocol::OkPacket *okPacket = new MyProtocol::OkPacket();
        okPacket->affectedRows=affectedRows;
        Buffer buffer;
        okPacket->write(conn,buffer);
        delete(okPacket);
    }
};


#endif //XSQL_OKRESPONSE_H

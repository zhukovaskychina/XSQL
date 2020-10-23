//
// Created by zhukovasky on 2020/10/9.
//

#ifndef XSQL_ERRORRESPONSE_H
#define XSQL_ERRORRESPONSE_H

#include <muduo/net/Buffer.h>
#include <muduo/net/TcpConnection.h>
#include <mysql_protocol/packet/ErrorPacket.h>


using namespace muduo;
using namespace muduo::net;
class ErrorResponse {
public :
    static void response(const TcpConnectionPtr &conn,std::string errMsg) {
        if (!errMsg.empty()) {
            MyProtocol::ErrorPacket *errorPacket = new MyProtocol::ErrorPacket();
            errorPacket->message=Utils::StringUtils::convertStringToBytes(errMsg);
            Buffer buffer;
            errorPacket->write(conn,buffer);
            buffer.retrieveAll();
            delete(errorPacket);
        }
    }

};


#endif //XSQL_ERRORRESPONSE_H

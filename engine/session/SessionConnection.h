//
// Created by zhukovasky on 2020/9/22.
//

#ifndef MUDUO_SERVER_SESSIONCONNECTION_H
#define MUDUO_SERVER_SESSIONCONNECTION_H


#include <mysql_protocol/packet/BinaryPacket.h>
#include <engine/handler/SqlQueryHandler.h>
#include <iostream>
using namespace std;
class SqlQueryHandler;
//定义session
class SessionConnection {

public:
    SessionConnection(const muduo::net::TcpConnectionPtr &connectionPtr);

    void query(MyProtocol::BinaryPacket *binaryPacket);

    void ping();

    void close();

    int status();

    void changeStatus(int status);

    void writeOk();

    virtual ~SessionConnection();

    SqlQueryHandler *getSqlQueryHandler() const;

    void setSqlQueryHandler(SqlQueryHandler *sqlQueryHandler);

    void errorResponse(string errorMessage);
private:
    int authStatus;
    int charsetIndex;
    std::string user;
public:
    void setSchema(const string &schema);

private:
    std::string host;
    std::string schema;

    SqlQueryHandler *sqlQueryHandler;
    muduo::net::TcpConnectionPtr connectionPtr;
public:
    const muduo::net::TcpConnectionPtr &getConnectionPtr() const;

    void setConnectionPtr(const muduo::net::TcpConnectionPtr &connectionPtr);


};


#endif //MUDUO_SERVER_SESSIONCONNECTION_H

//
// Created by zhukovasky on 2020/9/22.
//

#include <mysql_protocol/packet/MySqlMessage.h>
#include <iostream>
#include <mysql_protocol/packet/OkPacket.h>
#include <engine/interpreter.h>
#include <utils/StringUtils.h>
#include <mysql_protocol/packet/ErrorPacket.h>
#include "SessionConnection.h"

void SessionConnection::query(MyProtocol::BinaryPacket *binaryPacket) {
    MyProtocol:: MySQLMessage *mySqlMessage=new MyProtocol::MySQLMessage(binaryPacket->getData());
    mySqlMessage->positionPoint(1);
    std::string sql=mySqlMessage->readString();
    std::cout<<sql<<std::endl;
    Interpreter itp;
    itp.ExecSQL(sql);
}

void SessionConnection::ping() {

}

void SessionConnection::close() {
    this->connectionPtr.get()->forceClose();

}

void SessionConnection::writeOk() {

    muduo::net::Buffer buffer;
    MyProtocol::OkPacket *okPacket=new MyProtocol::OkPacket();
    okPacket->packetId=1;
    okPacket->header=0x00;
    okPacket->affectedRows=0;
    okPacket->serverStatus=2;
    okPacket->warningCount=0;
    dynamic_cast<MyProtocol::BinaryPacket*>(okPacket)->setData(OKPACKET);
    okPacket->write(this->connectionPtr,buffer);
    delete(okPacket);
}

int SessionConnection::status() {
    return this->authStatus;
}

void SessionConnection::changeStatus(int status) {
    this->authStatus=status;
}

SessionConnection::SessionConnection(const muduo::net::TcpConnectionPtr &connectionPtr) : connectionPtr(
        connectionPtr) {
    this->connectionPtr=connectionPtr;
    this->authStatus=AuthEnums ::UN_AUTN;
}

SessionConnection::~SessionConnection() {

}

SqlQueryHandler *SessionConnection::getSqlQueryHandler() const {
    return sqlQueryHandler;
}

void SessionConnection::setSqlQueryHandler(SqlQueryHandler *sqlQueryHandler) {
    this->sqlQueryHandler = sqlQueryHandler;
}

void SessionConnection::errorResponse(string errorMessage) {
    if(!errorMessage.empty()){
        MyProtocol::ErrorPacket *errorPacket = new MyProtocol::ErrorPacket();
        errorPacket->message=Utils::StringUtils::convertStringToBytes(errorMessage);
        muduo::net::Buffer buffer;
        errorPacket->write(this->connectionPtr,buffer);
        buffer.retrieveAll();
        delete(errorPacket);
    }
}

const muduo::net::TcpConnectionPtr &SessionConnection::getConnectionPtr() const {
    return connectionPtr;
}

void SessionConnection::setConnectionPtr(const muduo::net::TcpConnectionPtr &connectionPtr) {
    SessionConnection::connectionPtr = connectionPtr;
}

void SessionConnection::setSchema(const string &schema) {
    SessionConnection::schema = schema;
}



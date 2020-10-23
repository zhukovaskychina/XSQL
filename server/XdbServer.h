//
// Created by zhukovasky on 2020/9/21.
//

#ifndef MUDUO_SERVER_XDBSERVER_H
#define MUDUO_SERVER_XDBSERVER_H

#include <muduo/base/Logging.h>
#include <muduo/base/Mutex.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpServer.h>
#include <muduo/base/noncopyable.h>
#include <set>
#include <mysql_protocol/MySqlPacketDecode.h>
#include <engine/session/SessionConnection.h>
#include <engine/interpreter.h>
#include <engine/handler/SqlQueryHandler.h>

using namespace muduo;
using namespace muduo::net;
class XDBServer: muduo::noncopyable {

public:
    XDBServer(EventLoop* loop,const InetAddress& listenAddress);

    void start();

private:
    void onMySQLPacketMessage(const TcpConnectionPtr &conn,const MyProtocol::BinaryPacket *binaryPacket,Timestamp);
    void onConnection(const TcpConnectionPtr& conn);

    void processPacket(const muduo::net::TcpConnectionPtr &conn,
                       muduo::net::Buffer *buf);
    int getServerCapabilities();

    void sendHandshakePacket(const TcpConnectionPtr& conn);
    typedef std::set<TcpConnectionPtr> ConnectionList;
    typedef std::map<TcpConnectionPtr,SessionConnection*> ConnectionMap;
    TcpServer server_;
    MySqlPacketDecode codec_;
    ConnectionList connections_;
    ConnectionMap connectionMap;
    Interpreter *interpreter;
    SQLInterpret *sqlInterpret;
};


#endif //MUDUO_SERVER_XDBSERVER_H

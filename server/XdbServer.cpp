//
// Created by zhukovasky on 2020/9/21.
//

#include <mysql_protocol/packet/HandshakePacket.h>
#include <utils/RandomUtils.h>
#include <mysql_protocol/Capabilities.h>
#include <mysql_protocol/MySqlProtocolEnums.h>
#include <mysql_protocol/packet/AuthPacket.h>
#include <engine/session/SessionConnection.h>
#include <mysql_protocol/response/OkResponse.h>
#include "XdbServer.h"
using std::placeholders::_1;
using std::placeholders::_2;
using std::placeholders::_3;
XDBServer::XDBServer(EventLoop* loop,const InetAddress& listenAddress) : server_(loop,listenAddress,"XDBServer"),
codec_(std::bind(&XDBServer::onMySQLPacketMessage,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3)) {
    server_.setConnectionCallback(std::bind(&XDBServer::onConnection,this,muduo::_1));
    server_.setMessageCallback(std::bind(&MySqlPacketDecode::onMessage,&codec_,muduo::_1,muduo::_2,muduo::_3));
    this->sqlInterpret=new SQLInterpret();
}

void XDBServer::onMySQLPacketMessage(const TcpConnectionPtr &conn, const MyProtocol::BinaryPacket *binaryPacket, Timestamp) {
    SessionConnection *sessionConnection=this->connectionMap.at(conn);
    if(sessionConnection->status()==AuthEnums::UN_AUTN){
        MyProtocol::AuthPacket *authPacket = new MyProtocol::AuthPacket();
        authPacket->read(binaryPacket);
        std::string user=authPacket->user;
        std::string password=ByteUtils::readBytesToString(authPacket->password);
        if(user=="SUPERUSER"){
            sessionConnection->changeStatus(AUTH_SUCCESS);
            OkResponse::responseOK(conn);
            return;
        }
        std::string databasesql="";
        databasesql.append("use ");
        databasesql.append(authPacket->database);
        databasesql.append(";");
        std::string sql=Utils::StringUtils::toUpper(databasesql);
        this->sqlInterpret->ExecSQL(sql,*sessionConnection);
        sessionConnection->changeStatus(AUTH_SUCCESS);
    } else{
        sessionConnection->getSqlQueryHandler()->query(const_cast<MyProtocol::BinaryPacket *>(binaryPacket), sessionConnection);
        LOG_INFO << "发送请求结束" << "";
    }



}

void XDBServer::onConnection(const TcpConnectionPtr &conn) {
    LOG_INFO << conn->localAddress().toIpPort() << " -> "
             << conn->peerAddress().toIpPort() << " is "
             << (conn->connected() ? "UP" : "DOWN");
    if (conn->connected())
    {

        SessionConnection *sessionConnection=new SessionConnection(conn);
        SqlQueryHandler *sqlQueryHandler=new SqlQueryHandler();
        sqlQueryHandler->setSqlInterpreter(this->sqlInterpret);
        sessionConnection->setSqlQueryHandler(sqlQueryHandler);
        LOG_INFO << "有链接进入" << "/n";
        this->sendHandshakePacket(conn);
        connectionMap.insert(std::pair<TcpConnectionPtr,SessionConnection*>(conn,sessionConnection));
        LOG_INFO << "握手发送请求结束" << "";
    }
    else
    {


        connectionMap.erase(conn);
    }
}

void XDBServer::start() {
    server_.start();
}

int XDBServer::getServerCapabilities() {
    int flag = 0;
    flag |= Capabilities::CLIENT_LONG_PASSWORD;
    flag |= Capabilities::CLIENT_FOUND_ROWS;
    flag |= Capabilities::CLIENT_LONG_FLAG;
    flag |= Capabilities::CLIENT_CONNECT_WITH_DB;
    // flag |= Capabilities::CLIENT_NO_SCHEMA;
    // flag |= Capabilities::CLIENT_COMPRESS;
    flag |= Capabilities::CLIENT_ODBC;
    // flag |= Capabilities::CLIENT_LOCAL_FILES;
    flag |= Capabilities::CLIENT_IGNORE_SPACE;
    flag |= Capabilities::CLIENT_PROTOCOL_41;
    flag |= Capabilities::CLIENT_INTERACTIVE;
    // flag |= Capabilities::CLIENT_SSL;
    flag |= Capabilities::CLIENT_IGNORE_SIGPIPE;
    flag |= Capabilities::CLIENT_TRANSACTIONS;
    // flag |= ServerDefs.CLIENT_RESERVED;
    flag |= Capabilities::CLIENT_SECURE_CONNECTION;
    return flag;
}

void XDBServer::processPacket(const muduo::net::TcpConnectionPtr &conn, muduo::net::Buffer *buf) {
    muduo::net::TcpConnection *tcpConnection = conn.get();
    int size=buf->readableBytes();
    int i=BufferUtils::readLength(buf);
    unsigned char packetId=buf->readInt8();
    std::vector<char> arrays= ByteUtils::readRestByte(buf,i);
    MyProtocol::BinaryPacket *binaryPacket=new MyProtocol::BinaryPacket();
    binaryPacket->packetId=packetId;
    binaryPacket->packetLength=i;
    binaryPacket->setData(arrays);


}

void XDBServer::sendHandshakePacket(const TcpConnectionPtr &conn) {
    Buffer buf;
    std::vector<byte> rand1=RandomUtils::randomBytes(8);
    std::vector<byte> rand2=RandomUtils::randomBytes(12);
    MyProtocol::HandshakePacket *handshakePacket=new MyProtocol::HandshakePacket();
    handshakePacket->packetId=0;
    handshakePacket->protocolVersion=10;
    handshakePacket->threadId=1;
    for (int j = 0; j < rand1.size(); ++j) {
        handshakePacket->seed.push_back(rand1[j]);
    }
    for (int k = 0; k < rand2.size(); ++k) {
        handshakePacket->seed.push_back(rand2[k]);
    }
    handshakePacket->serverCapabilities=this->getServerCapabilities();
    handshakePacket->serverStatus=2;
    handshakePacket->setCharsetIndex=1;
    handshakePacket->restOfScrambleBuff=rand2;
    handshakePacket->write(conn, buf);
}


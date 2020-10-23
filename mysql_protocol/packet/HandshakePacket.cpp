//
// Created by zhukovasky on 2020/9/18.
//

#include <utils/BufferUtils.h>
#include <iostream>
#include "HandshakePacket.h"
namespace MyProtocol{


    int HandshakePacket::calPacketSize() {
        int size = 1;
        size += serverVersion.size();
        size += 5;
        size += seed.size();
        size += 19;
        size += restOfScrambleBuff.size();
        size += 1;
        return size;
    }

    std::string HandshakePacket::getPacketInfo() {
        return std::__cxx11::string("MySQL HandshakePacket");
    }

    void HandshakePacket::read(BinaryPacket *bin) {
        this->packetLength=bin->packetLength;
        this->packetId=bin->packetId;

    }

    void HandshakePacket::write(const muduo::net::TcpConnectionPtr &conn, muduo::net::Buffer &buffer) {
        muduo::net::Buffer buf;
        BufferUtils::writeU3(buf, calPacketSize());
        BufferUtils::writeByte(buf,this->packetId);
        BufferUtils::writeByte(buf,this->protocolVersion);
        BufferUtils::writeWithNull(buf,this->serverVersion);
        BufferUtils::writeU4(buf,this->threadId);
        BufferUtils::writeWithNull(buf,this->seed);
        BufferUtils::writeU2(buf,this->serverCapabilities);
        BufferUtils::writeByte(buf,this->serverCharsetIndex);
        BufferUtils::writeU2(buf,this->serverStatus);
        BufferUtils::writeBytes(buf,this->FILLER_13);
        BufferUtils::writeWithNull(buf,this->restOfScrambleBuff);
        conn.get()->send(&buf);
        buf.retrieveAll();
    }

    muduo::net::Buffer &HandshakePacket::writeBuf(muduo::net::Buffer &buffer) {
        return buffer;
    }
}
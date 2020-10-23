//
// Created by zhukovasky on 2020/10/2.
//

#include <utils/BufferUtils.h>
#include "ErrorPacket.h"


int MyProtocol::ErrorPacket::calPacketSize() {
    int size = 14;// 1 + 2 + 1 + 5
    if (!message.empty()) {
        size += message.size();
    }
    return size;
}

std::string MyProtocol::ErrorPacket::getPacketInfo() {
    return BinaryPacket::getPacketInfo();
}

void MyProtocol::ErrorPacket::write(const muduo::net::TcpConnectionPtr &conn, muduo::net::Buffer &buffer) {
    BufferUtils::writeU3(buffer, this->calPacketSize());
    BufferUtils::writeByte(buffer,packetId);
    BufferUtils::writeByte(buffer,header);
    BufferUtils::writeByte(buffer,fieldCount);
    BufferUtils::writeU2(buffer, errNo);
    BufferUtils::writeByte(buffer,mark);
    BufferUtils::writeBytes(buffer,sqlState);
    if (!message .empty()) {
        BufferUtils::writeBytes(buffer,message);
    }
    conn.get()->send(&buffer);
}

//
// Created by zhukovasky on 2020/10/8.
//

#include <utils/BufferUtils.h>
#include "ResultSetHeaderPacket.h"
#include "MySqlMessage.h"

int MyProtocol::ResultSetHeaderPacket::calPacketSize() {
    int size = BufferUtils::getLength(fieldCount);
    if (extra > 0) {
        size += BufferUtils::getLength(extra);
    }
    return size;
}

std::string MyProtocol::ResultSetHeaderPacket::getPacketInfo() {
    return "MySQL ResultSetHeader Packet";
}

muduo::net::Buffer &MyProtocol::ResultSetHeaderPacket::writeBuf(muduo::net::Buffer &buffer) {
    int size = calPacketSize();
    BufferUtils::writeU3(buffer, size);
    BufferUtils::writeByte(buffer,packetId);
    BufferUtils::writeLength(buffer, fieldCount);
    if (extra > 0) {
        BufferUtils::writeLength(buffer, extra);
    }
    return buffer;
}

void MyProtocol::ResultSetHeaderPacket::read(std::vector<byte> data) {
    MySQLMessage *mm = new MySQLMessage(data);
    this->packetLength = mm->readU3();
    this->packetId = mm->read();
    this->fieldCount = (int) mm->readLength();
    if (mm->hasRemaining()) {
        this->extra = mm->readLength();
    }
    delete(mm);
}

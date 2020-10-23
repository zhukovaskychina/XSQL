//
// Created by zhukovasky on 2020/10/8.
//

#include <utils/BufferUtils.h>
#include "EofPacket.h"
#include "MySqlMessage.h"

int MyProtocol::EOFPacket::calPacketSize() {
    return 5;
}

std::string MyProtocol::EOFPacket::getPacketInfo() {

        return "MySQL EOF Packet";
}

void MyProtocol::EOFPacket::write(const muduo::net::TcpConnectionPtr &conn, muduo::net::Buffer &buffer) {
    BinaryPacket::write(conn, buffer);
}

void MyProtocol::EOFPacket::read(MyProtocol::BinaryPacket *bin) {
    packetLength = bin->packetLength;
    packetId = bin->packetId;
    MySQLMessage *mm = new MySQLMessage(bin->getData());
    fieldCount = mm->read();
    warningCount = mm->readU2();
    status = mm->readU2();
    delete(mm);
}

void MyProtocol::EOFPacket::read(std::vector<byte> data) {
    MySQLMessage *mm = new MySQLMessage(data);
    packetLength = mm->readU3();
    packetId = mm->read();
    fieldCount = mm->read();
    warningCount = mm->readU2();
    status = mm->readU2();
    delete(mm);
}

muduo::net::Buffer &MyProtocol::EOFPacket::writeBuf(muduo::net::Buffer &buffer) {

    int size = calPacketSize();
    BufferUtils::writeU3(buffer, size);
    BufferUtils::writeByte(buffer,packetId);
    BufferUtils::writeByte(buffer,fieldCount);
    BufferUtils::writeU2(buffer, warningCount);
    BufferUtils::writeU2(buffer, status);
    return buffer;

    return BinaryPacket::writeBuf(buffer);
}

//
// Created by zhukovasky on 2020/10/8.
//

#include <utils/BufferUtils.h>
#include <utils/StringUtils.h>
#include "RowDataPacket.h"
#include "MySqlMessage.h"

int MyProtocol::RowDataPacket::calPacketSize() {
    int size = 0;
    for (int i = 0; i < fieldCount; i++) {
        std::vector<byte> v = fieldValues.at(i);
        size += (v .empty() || v.size() == 0) ? 1 : BufferUtils::getLength(v);
    }
    return size;
}

std::string MyProtocol::RowDataPacket::getPacketInfo() {
    return "MySQL RowData Packet";
}

void MyProtocol::RowDataPacket::write(const muduo::net::TcpConnectionPtr &conn, muduo::net::Buffer &buffer) {
    this->writeBuf(buffer);
    conn.get()->send(&buffer);
}

muduo::net::Buffer &MyProtocol::RowDataPacket::writeBuf(muduo::net::Buffer &buffer) {
    BufferUtils::writeU3(buffer, calPacketSize());
    BufferUtils::writeByte(buffer,packetId);
    for (int i = 0; i < fieldCount; i++) {
        std::vector<byte> fv = fieldValues.at(i);
        if (fv .empty() || fv.size() == 0) {
            BufferUtils::writeByte(buffer,RowDataPacket::NULL_MARK);
        } else {
            BufferUtils::writeLength(buffer, fv.size());
            BufferUtils::writeBytes(buffer,fv);
        }
    }
    return buffer;
}

MyProtocol::RowDataPacket::RowDataPacket(int fieldCount) : fieldCount(0) {
    this->fieldCount=fieldCount;
}

MyProtocol::RowDataPacket::~RowDataPacket() {

}

void MyProtocol::RowDataPacket::add(std::vector<byte> value) {
    fieldValues.push_back(value);
}

void MyProtocol::RowDataPacket::read(MyProtocol::BinaryPacket *bin) {
    this->packetLength = bin->packetLength;
    packetId = bin->packetId;
    MySQLMessage *mm = new MySQLMessage(bin->getData());
    for (int i = 0; i < fieldCount; i++) {
        std::vector<byte> bytes = mm->readBytesWithLength();
        this->fieldValues.push_back(bytes);
        fieldStrings.push_back(Utils::StringUtils::newString(bytes));
    }
}

//
// Created by zhukovasky on 2020/10/8.
//

#include <utils/BufferUtils.h>
#include "FieldPacket.h"

int MyProtocol::FieldPacket::calPacketSize() {
    int size = (catalog .empty() ? 1 : BufferUtils::getLength(catalog));
    size += (db .empty() ? 1 : BufferUtils::getLength(db));
    size += (table .empty() ? 1 : BufferUtils::getLength(table));
    size += (orgTable .empty() ? 1 : BufferUtils::getLength(orgTable));
    size += (name .empty() ? 1 : BufferUtils::getLength(name));
    size += (orgName .empty() ? 1 : BufferUtils::getLength(orgName));
    size += 13;// 1+2+4+1+2+1+2
    if (definition .empty()) {
        size += BufferUtils::getLength(definition);
    }
    return size;
}

std::string MyProtocol::FieldPacket::getPacketInfo() {
    return "MySQL Field Packet";
}

muduo::net::Buffer &MyProtocol::FieldPacket::writeBuf(muduo::net::Buffer &buffer) {
    int size = calPacketSize();
    BufferUtils::writeU3(buffer, size);
    BufferUtils::writeByte(buffer,packetId);
    writeBody(buffer);
    return buffer;
}

void MyProtocol::FieldPacket::readBody(MyProtocol::MySQLMessage *mm) {
    this->catalog = mm->readBytesWithLength();
    this->db = mm->readBytesWithLength();
    this->table = mm->readBytesWithLength();
    this->orgTable = mm->readBytesWithLength();
    this->name = mm->readBytesWithLength();
    this->orgName = mm->readBytesWithLength();
    mm->move(1);
    this->charsetIndex = mm->readU2();
    this->length = mm->readU4();
    this->type = mm->read() & 0xff;
    this->flags = mm->readU2();
    this->decimals = mm->read();
    mm->move(FILLER.size());
    if (mm->hasRemaining()) {
        this->definition = mm->readBytesWithLength();
    }
}

void MyProtocol::FieldPacket::read(MyProtocol::BinaryPacket *bin) {
    this->packetLength = bin->packetLength;
    this->packetId = bin->packetId;
    readBody(new MySQLMessage(bin->getData()));
}

void MyProtocol::FieldPacket::writeBody(muduo::net::Buffer &buffer) {
    byte nullVal = 0;
    BufferUtils::writeWithLength(buffer, catalog, nullVal);
    BufferUtils::writeWithLength(buffer, db, nullVal);
    BufferUtils::writeWithLength(buffer, table, nullVal);
    BufferUtils::writeWithLength(buffer, orgTable, nullVal);
    BufferUtils::writeWithLength(buffer, name, nullVal);
    BufferUtils::writeWithLength(buffer, orgName, nullVal);
    BufferUtils::writeByte(buffer,(byte) 0x0C);
    BufferUtils::writeU2(buffer, charsetIndex);
    BufferUtils::writeU4(buffer, length);
    BufferUtils::writeByte(buffer,(byte) (type & 0xff));
    BufferUtils::writeU2(buffer, flags);
    BufferUtils::writeByte(buffer,decimals);
    BufferUtils::writeBytes(buffer,FILLER);
    if (!definition .empty()) {
        BufferUtils::writeWithLength(buffer, definition);
    }
}

void MyProtocol::FieldPacket::read(std::vector<byte> data) {
    MySQLMessage *mm = new MySQLMessage(data);
    this->packetLength = mm->readU3();
    this->packetId = mm->read();
    readBody(mm);
}

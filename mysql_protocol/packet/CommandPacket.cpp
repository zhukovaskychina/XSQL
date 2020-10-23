//
// Created by zhukovasky on 2020/10/8.
//

#include <utils/StringUtils.h>
#include <utils/BufferUtils.h>
#include "CommandPacket.h"
#include "MySqlMessage.h"

MyProtocol::CommandPacket::CommandPacket(std::string query,byte command) : command(command) {
    this->command=command;
    this->arg =Utils::StringUtils::convertStringToBytes(query);
    this->packetId=0;
}

MyProtocol::CommandPacket::CommandPacket(std::string query) {
    this->command=3;
    this->arg =Utils::StringUtils::convertStringToBytes(query);
    this->packetId=0;
}

int MyProtocol::CommandPacket::calPacketSize() {
        return 1 + arg.size();
}

std::string MyProtocol::CommandPacket::getPacketInfo() {
    return "MySQL Command Packet";
}

void MyProtocol::CommandPacket::write(const muduo::net::TcpConnectionPtr &conn, muduo::net::Buffer &buffer) {
    BufferUtils::writeU3(buffer, calPacketSize());
    BufferUtils::writeByte(buffer,packetId);
    BufferUtils::writeByte(buffer,command);
    BufferUtils::writeBytes(buffer,arg);
}

void MyProtocol::CommandPacket::read(std::vector<byte> data) {
    MySQLMessage *mm = new MySQLMessage(data);
    packetLength = mm->readU3();
    packetId = mm->read();
    command = mm->read();
    arg = mm->readBytes();
}

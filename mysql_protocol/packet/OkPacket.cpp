//
// Created by zhukovasky on 2020/9/17.
//

#include <utils/BufferUtils.h>
#include <iostream>
#include "OkPacket.h"
#include "mysql_protocol/packet/MySqlMessage.h"

namespace MyProtocol{


    int OkPacket::calPacketSize() {
        int i = 1;
        i += BufferUtils::getLength(affectedRows);
        i += BufferUtils::getLength(insertId);
        i += 4;
        if (!message.empty()) {
            i += BufferUtils::getLength(message);
        }
        return i;

    }

    std::string OkPacket::getPacketInfo() {
        return std::__cxx11::string("MySQL OK Packet");
    }

    void OkPacket::read(MyProtocol::BinaryPacket *binaryPacket) {
        this->packetLength=binaryPacket->packetLength;
        this->packetId=binaryPacket->packetId;
        MyProtocol::MySQLMessage *mySqlMessage=new MyProtocol::MySQLMessage(binaryPacket->getData());

        this->fieldCount=mySqlMessage->read();
        this->affectedRows=mySqlMessage->readLength();
        this->insertId=mySqlMessage->readLength();
        this->serverStatus=mySqlMessage->readU2();
        this->warningCount=mySqlMessage->readU2();

        if(mySqlMessage->hasRemaining()){
            this->message=mySqlMessage->readBytesWithLength();
        }
    }

    OkPacket::OkPacket() {}

    void OkPacket::write(const muduo::net::TcpConnectionPtr &conn, muduo::net::Buffer &buffer) {
        BufferUtils::writeU3(buffer, this->calPacketSize());
        BufferUtils::writeByte(buffer,packetId);
        BufferUtils::writeByte(buffer,header);
        BufferUtils::writeByte(buffer,fieldCount);
        BufferUtils::writeLength(buffer, affectedRows);
        BufferUtils::writeLength(buffer, insertId);
        BufferUtils::writeU2(buffer, serverStatus);
        BufferUtils::writeU2(buffer, warningCount);
        if (!message.empty()) {
            BufferUtils::writeWithLength(buffer, message);
        }
        conn.get()->send(&buffer);
    }


}
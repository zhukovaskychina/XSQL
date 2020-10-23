//
// Created by zhukovasky on 2020/9/21.
//

#include "AuthPacket.h"
#include <mysql_protocol/packet/MySqlMessage.h>
#include <utils/ByteUtils.h>
#include <mysql_protocol/Capabilities.h>
#include <utils/BufferUtils.h>

namespace MyProtocol{
    void AuthPacket::read(const BinaryPacket *binaryPacket) {
        this->packetLength=binaryPacket->packetLength;
        this->packetId=binaryPacket->packetId;
        MyProtocol::MySQLMessage *mySqlMessage=new MyProtocol::MySQLMessage(binaryPacket->getData());
        this->clientFlag=mySqlMessage->readU4();
        this->maxPacketSize=mySqlMessage->readU4();
        this->charsetIndex=mySqlMessage->read()&0xff;
        int current=mySqlMessage->positionPoint();
        int length=mySqlMessage->readLength();
        if(length>0&&length<23){
            this->extra=ByteUtils::copySpecifiedData(binaryPacket->getData(),mySqlMessage->positionPoint(),length);
        }
        mySqlMessage->positionPoint(current+23);
        this->user=mySqlMessage->readStringWithNull();
        this->password=mySqlMessage->readBytesWithLength();

        if (((this->clientFlag && Capabilities::CLIENT_CONNECT_WITH_DB) != 0) && mySqlMessage->hasRemaining()) {
            database = mySqlMessage->readStringWithNull();
        }
    }

    void AuthPacket::write(const muduo::net::TcpConnectionPtr &conn, muduo::net::Buffer &buffer) {
       // ByteBuf buffer = c.alloc().buffer();
        BufferUtils::writeU3(buffer,calPacketSize());
        BufferUtils::writeByte(buffer,packetId);
        BufferUtils::writeU4(buffer, clientFlag);
        BufferUtils::writeU4(buffer, maxPacketSize);
        BufferUtils::writeByte(buffer,charsetIndex);

        BufferUtils::writeBytes(buffer,FILTER);
        if (user.empty()) {

            BufferUtils::writeByte(buffer,0);
        } else {
            std::vector<byte> userData = Utils::StringUtils::convertStringToBytes(user);
            BufferUtils::writeWithNull(buffer, userData);
        }
        if (password .empty()) {
            BufferUtils::writeByte(buffer,0);

        } else {
            BufferUtils::writeWithLength(buffer,password);
        }
        if (database .empty()) {
            BufferUtils::writeByte(buffer,(byte) 0);
        } else {
            std::vector<byte> databaseData = Utils::StringUtils::convertStringToBytes(database);
            BufferUtils::writeWithNull(buffer, databaseData);
        }

        conn.get()->send(&buffer);
        buffer.retrieveAll();

    }

    int AuthPacket::calPacketSize() {
        int size = 32;// 4+4+1+23;
        size += (user .empty()) ? 1 : user.length() + 1;
        size += (password .empty()) ? 1 : BufferUtils::getLength(password);
        size += (database .empty()) ? 1 : database.length() + 1;
        return size;
    }

    AuthPacket::AuthPacket() {
        for (int i = 0; i < 23; ++i) {
            this->FILTER.push_back(NULL);
        }
    }

}

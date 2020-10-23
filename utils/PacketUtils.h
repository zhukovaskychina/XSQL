//
// Created by zhukovasky on 2020/10/9.
//

#ifndef XSQL_PACKETUTILS_H
#define XSQL_PACKETUTILS_H


#include <string>
#include <mysql_protocol/packet/ResultSetHeaderPacket.h>
#include <mysql_protocol/packet/FieldPacket.h>
#include <mysql_protocol/packet/ErrorPacket.h>
#include <common/Exceptions.h>
#include "CharsetUtils.h"

typedef std::string String;
static std::string CODE_PAGE_1252 = "Cp1252";

class PacketUtils {
private :


public :
    static MyProtocol::ResultSetHeaderPacket *getHeader(int fieldCount) {
        MyProtocol::ResultSetHeaderPacket *packet = new MyProtocol::ResultSetHeaderPacket();
        packet->packetId = 1;
        packet->fieldCount = fieldCount;
        return packet;
    }

    static std::vector<byte> encode(std::string src, String charset) {
        if (src.empty()) {
            std::vector<byte> empty;
            return empty;
        }
        return Utils::StringUtils::convertStringToBytes(src);
    }

    static MyProtocol::FieldPacket *getField(std::string name, String orgName, int type) {
        MyProtocol::FieldPacket *packet = new MyProtocol::FieldPacket();
        packet->charsetIndex = CharsetUtils::getIndex(CODE_PAGE_1252);
        packet->name = encode(name, CODE_PAGE_1252);
        packet->orgName = encode(orgName, CODE_PAGE_1252);
        packet->type = (byte) type;
        return packet;
    }

    static MyProtocol::FieldPacket* getField(String name, int type) {
        MyProtocol::FieldPacket *packet = new MyProtocol::FieldPacket();
        packet->charsetIndex = CharsetUtils::getIndex(CODE_PAGE_1252);
        packet->name = encode(name, CODE_PAGE_1252);
        packet->type = (byte) type;
        return packet;
    }

    static MyProtocol::ErrorPacket *getShutdown() {
        MyProtocol::ErrorPacket *error = new MyProtocol::ErrorPacket();
        error->packetId = 1;
        error->errNo = MySQLErrorCode::ER_SERVER_SHUTDOWN;
        error->message = Utils::StringUtils::convertStringToBytes("The server has been shutdown");
        return error;
    }

    static  MyProtocol::FieldPacket* getField(MyProtocol::BinaryPacket *src,String fieldName) {
        MyProtocol::FieldPacket *field = new MyProtocol::FieldPacket();
        field->read(src);
        field->name = encode(fieldName, CODE_PAGE_1252);
        field->packetLength = field->calPacketSize();
        return field;
    }
};


#endif //XSQL_PACKETUTILS_H

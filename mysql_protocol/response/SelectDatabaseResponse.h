//
// Created by zhukovasky on 2020/10/9.
//

#ifndef XSQL_SELECTDATABASERESPONSE_H
#define XSQL_SELECTDATABASERESPONSE_H


#include <mysql_protocol/packet/EofPacket.h>
#include <utils/PacketUtils.h>
#include <mysql_protocol/packet/RowDataPacket.h>

class SelectDatabaseResponse {

public :
    static void response(const muduo::net::TcpConnectionPtr &conn) {

        MyProtocol::EOFPacket *eof = new MyProtocol::EOFPacket();

        const int FIELD_COUNT = 1;

        MyProtocol::ResultSetHeaderPacket *header = PacketUtils::getHeader(FIELD_COUNT);

        std::vector<MyProtocol::FieldPacket*> fields( 1 );
        int i = 0;
        byte packetId = 0;
        header->packetId = ++packetId;

        fields[i] = PacketUtils::getField("DATABASE()", COLUMNENUMS::FIELD_TYPE_VAR_STRING);

        fields[i++]->packetId = ++packetId;
        eof->packetId = ++packetId;

        muduo::net::Buffer buffer;
        buffer = header->writeBuf(buffer);
        for (MyProtocol::FieldPacket *field : fields) {
            buffer = field->writeBuf(buffer);
        }
        buffer = eof->writeBuf(buffer);

        byte packetIds = eof->packetId;
        MyProtocol::RowDataPacket *row = new MyProtocol::RowDataPacket(FIELD_COUNT);
        row->add(Utils::StringUtils::convertStringToBytes("XSQL"));
        row->packetId = ++packetIds;
        buffer = row->writeBuf(buffer);
        MyProtocol::EOFPacket *lastEof = new MyProtocol::EOFPacket();
        lastEof->packetId = ++packetIds;
        buffer = lastEof->writeBuf(buffer);
        conn.get()->send(&buffer);
    }

};


#endif //XSQL_SELECTDATABASERESPONSE_H

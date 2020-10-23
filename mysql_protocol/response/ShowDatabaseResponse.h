//
// Created by zhukovasky on 2020/10/14.
//

#ifndef XSQL_SHOWDATABASERESPONSE_H
#define XSQL_SHOWDATABASERESPONSE_H


#include <muduo/net/TcpConnection.h>
#include <engine/catalog_manager.h>
#include <utils/PacketUtils.h>
#include <mysql_protocol/packet/EofPacket.h>
#include <mysql_protocol/packet/RowDataPacket.h>

using namespace MyProtocol;

using namespace muduo::net;

class ShowDatabaseResponse {

    int FIELD_COUNT=1;

public:
    static void response(const muduo::net::TcpConnectionPtr &conn,std::vector<Database> dataBaseList){
        int FIELD_COUNT=1;
        ResultSetHeaderPacket *header = PacketUtils::getHeader(FIELD_COUNT);
        std::vector<FieldPacket*> fields(FIELD_COUNT);
        EOFPacket *eofPacket=new EOFPacket();


        int index=0;
        byte packetId=0;
        header->packetId=++packetId;
        fields[index]=PacketUtils::getField("DATABASE",FIELD_TYPE_VAR_STRING);
        fields[index]->packetId=++packetId;
        eofPacket->packetId=++packetId;

        //resultSetHeaderPacket
        Buffer buffer;
        header->writeBuf(buffer);
        //fieldPacket
        for (int i = 0; i < fields.size(); ++i) {
            buffer=fields[i]->writeBuf(buffer);
        }
        //eofPacket
        buffer=eofPacket->writeBuf(buffer);
        //write rows
        byte packetIds=eofPacket->packetId;
        for (int j = 0; j < dataBaseList.size(); ++j) {
            RowDataPacket *row = new RowDataPacket(FIELD_COUNT);
            row->add(Utils::StringUtils::convertStringToBytes(dataBaseList.at(j).db_name()));

            row->packetId = ++packetIds;
            buffer = row->writeBuf(buffer);
        }

        // write lastEof
        EOFPacket *lastEof = new EOFPacket();
        lastEof->packetId = ++packetIds;
        buffer = lastEof->writeBuf(buffer);

        conn.get()->send(&buffer);
        buffer.retrieveAll();
    }
};


#endif //XSQL_SHOWDATABASERESPONSE_H

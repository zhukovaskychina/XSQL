//
// Created by zhukovasky on 2020/10/15.
//

#ifndef XSQL_SHOWDESCRIBETABLERESPONSE_H
#define XSQL_SHOWDESCRIBETABLERESPONSE_H


#include <vector>
#include <engine/catalog_manager.h>
#include <muduo/net/TcpConnection.h>
#include <muduo/net/TcpConnection.h>
#include <engine/catalog_manager.h>
#include <utils/PacketUtils.h>
#include <mysql_protocol/packet/EofPacket.h>
#include <mysql_protocol/packet/RowDataPacket.h>

using namespace MyProtocol;

using namespace muduo::net;
class ShowDescribeTableResponse {
public:
    static void response(const muduo::net::TcpConnectionPtr &conn,std::vector<Attribute> ats_){
        int FIELD_COUNT=2;
        ResultSetHeaderPacket *header = PacketUtils::getHeader(FIELD_COUNT);
        std::vector<FieldPacket*> fields(FIELD_COUNT);
        EOFPacket *eofPacket=new EOFPacket();


        byte packetId=0;
        header->packetId=++packetId;
        fields[0]=PacketUtils::getField("NAME",FIELD_TYPE_VAR_STRING);
        fields[0]->packetId=++packetId;

        fields[1]=PacketUtils::getField("DATATYPE",FIELD_TYPE_VAR_STRING);
        fields[1]->packetId=++packetId;



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
        for (int j = 0; j <ats_.size(); ++j) {
            RowDataPacket *row = new RowDataPacket(FIELD_COUNT);
            row->add(Utils::StringUtils::convertStringToBytes(ats_.at(j).attr_name()));
            row->add(Utils::StringUtils::convertStringToBytes(ats_.at(j).data_type_length()));
            row->packetId = ++packetIds;
            buffer = row->writeBuf(buffer);
            delete row;
        }

        // write lastEof
        EOFPacket *lastEof = new EOFPacket();
        lastEof->packetId = ++packetIds;
        buffer = lastEof->writeBuf(buffer);

        conn.get()->send(&buffer);
        buffer.retrieveAll();


        fields.clear();
        delete(lastEof);
        delete(header);
        delete(eofPacket);
    }
};


#endif //XSQL_SHOWDESCRIBETABLERESPONSE_H

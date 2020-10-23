//
// Created by zhukovasky on 2020/10/8.
//

#ifndef XSQL_ROWDATAPACKET_H
#define XSQL_ROWDATAPACKET_H

#include <mysql_protocol/MySqlPacket.h>
#include "BinaryPacket.h"

namespace MyProtocol {
    class RowDataPacket : public BinaryPacket {
    public:
        int calPacketSize() override;

        std::string getPacketInfo() override;

        void write(const muduo::net::TcpConnectionPtr &conn, muduo::net::Buffer &buffer) override;

        muduo::net::Buffer &writeBuf(muduo::net::Buffer &buffer) override;

        RowDataPacket(int fieldCount);

        ~RowDataPacket();

        void add(std::vector<byte> value);

        void read(BinaryPacket *bin);
    private:

        static const byte NULL_MARK = (byte) 251;


    public:
        int fieldCount;
        std::vector<std::vector<byte>> fieldValues;

        std::vector<std::string> fieldStrings;
    };
}


#endif //XSQL_ROWDATAPACKET_H

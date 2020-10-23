//
// Created by zhukovasky on 2020/10/8.
//

#ifndef XSQL_FIELDPACKET_H
#define XSQL_FIELDPACKET_H

#include <utils/StringUtils.h>
#include "BinaryPacket.h"
#include "MySqlMessage.h"

namespace MyProtocol {
    class FieldPacket : public MyProtocol::BinaryPacket {
    public:
        const std::vector<byte> DEFAULT_CATALOG = Utils::StringUtils::convertStringToBytes("def");
        const std::vector<byte> FILLER;

        std::vector<byte> catalog = DEFAULT_CATALOG;
        std::vector<byte> db;
        std::vector<byte> table;
        std::vector<byte> orgTable;
        std::vector<byte> name;
        std::vector<byte> orgName;
        int charsetIndex;
        long length;
        int type;
        int flags;
        byte decimals;
        std::vector<byte> definition;

        int calPacketSize() override;

        std::string getPacketInfo() override;

        muduo::net::Buffer &writeBuf(muduo::net::Buffer &buffer) override;

        void read(BinaryPacket *bin);

        void read(std::vector<byte> data);
    private:

        void readBody(MySQLMessage *mm);

        void writeBody(muduo::net::Buffer &buffer);
    };
};


#endif //XSQL_FIELDPACKET_H

//
// Created by zhukovasky on 2020/10/2.
//

#ifndef XSQL_ERRORPACKET_H
#define XSQL_ERRORPACKET_H

#include <utils/StringUtils.h>
#include "BinaryPacket.h"

namespace MyProtocol{
    class ErrorPacket: public MyProtocol::BinaryPacket {

    public:

        const byte FIELD_COUNT = (byte) 0xff;

        const byte SQLSTATE_MARKER = (byte) '#';

        std::vector<byte > message;

        std::vector<byte> DEFAULT_SQLSTATE =Utils::StringUtils::convertStringToBytes("HY000");

        byte fieldCount = FIELD_COUNT;

        int errNo;

        byte mark = SQLSTATE_MARKER;

        std::vector<byte> sqlState = DEFAULT_SQLSTATE;

        byte header=(byte) (0xff)&0xff;


        int calPacketSize() override;

        std::string getPacketInfo() override;

        void write(const muduo::net::TcpConnectionPtr &conn, muduo::net::Buffer &buffer) override;
    };
};



#endif //XSQL_ERRORPACKET_H

//
// Created by zhukovasky on 2020/9/17.
//

#ifndef MUDUO_SERVER_BINARYPACKET_H
#define MUDUO_SERVER_BINARYPACKET_H

#include <mysql_protocol/MySqlPacket.h>
#include <list>

const static std::vector<byte> OKPACKET={
        7, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0
};
const static std::vector<byte > AUTHOKPACKET={
        7, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0
};
namespace MyProtocol{
    class BinaryPacket: public MyProtocol::MySQLPacket {
    public:

        int calPacketSize() override;

        std::string getPacketInfo() override;

        const std::vector<char> &getData() const;

        void setData(const std::vector<char> &data);

        void write(const muduo::net::TcpConnectionPtr &conn, muduo::net::Buffer &buffer) override;

        muduo::net::Buffer &writeBuf(muduo::net::Buffer &buffer) override;

    private:
        std::vector<char>  data;
    };

}


#endif //MUDUO_SERVER_BINARYPACKET_H

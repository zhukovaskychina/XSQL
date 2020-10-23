//
// Created by zhukovasky on 2020/9/17.
//

#include <muduo/net/TcpConnection.h>
#include "BinaryPacket.h"
namespace MyProtocol{


    int BinaryPacket::calPacketSize() {
        return 0;
    }

    std::string BinaryPacket::getPacketInfo() {
        return std::__cxx11::string("MySQL Binary Packet");
    }
    const std::vector<char> &BinaryPacket::getData() const {
        return data;
    }
    void BinaryPacket::setData(const std::vector<char> &data) {
        BinaryPacket::data = data;
    }

    void BinaryPacket::write(const muduo::net::TcpConnectionPtr &conn, muduo::net::Buffer &buffer) {

    }

    muduo::net::Buffer &BinaryPacket::writeBuf(muduo::net::Buffer &buffer) {
        return buffer;
    }
}
//
// Created by zhukovasky on 2020/9/17.
//

#ifndef MUDUO_SERVER_MYSQLMESSAGE_H
#define MUDUO_SERVER_MYSQLMESSAGE_H


#include <list>
#include <common/Common.h>
#include <vector>
#include <string>
namespace MyProtocol{
    class MySQLMessage {

    public:
        MySQLMessage(std::vector<byte> data);
        ~MySQLMessage();

        byte read(int i);

        byte read();

        int readU2();

        int readU3();

        long readU4();

        long readLength();

        long readLong();

        long readLong(int length);

        bool hasRemaining();

        int positionPoint();

        int positionPoint(int ps);

        std::vector<byte > readBytesWithLength();

        std::string readStringWithNull();

        std::string readString();

        std::vector<byte> readBytes();

        void move(int i);

    private:
        const std::vector< byte> EMPTY_BYTES = {};
        std::vector<byte > data;
        int length;
        int position;
    };

}


#endif //MUDUO_SERVER_MYSQLMESSAGE_H

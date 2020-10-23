//
// Created by zhukovasky on 2020/9/17.
//

#include <utils/StringUtils.h>
#include "MySqlMessage.h"
#include <common/Common.h>
#include <utils/ByteUtils.h>

namespace MyProtocol{
    MySQLMessage::MySQLMessage(std::vector<byte> data) {
        this->length=data.size();
        this->data=data;
        this->position=0;
    }

    MySQLMessage::~MySQLMessage() {
        data.clear();

    }

    byte MySQLMessage::read(int i) {
        return this->data[i];
    }

    byte MySQLMessage::read() {
        return this->data[this->position++];
    }

    int MySQLMessage::readU2() {
        const std::vector<byte> b=this->data;
        int i =b[position++] & 0xff;
        i |= (b[position++] & 0xff) << 8;
        return i;
    }

    int MySQLMessage::readU3() {
        const std::vector<byte> b=this->data;
        int i =b[position++] & 0xff;
        i |= (b[position++] & 0xff) << 8;
        i |= (b[position++] & 0xff) << 16;
        return 0;
    }

    long MySQLMessage::readLength() {
        int length=(data[position++])&0xff;
        switch (length){
            case 251:{
                return -1;
            }
            case 252:{
                return readU2();
            }
            case 253:{
                return readU3();
            }
            case 254:{
                return readLong();
            }
            default:
                return length;
        }
        return 0;
    }

    long MySQLMessage::readLong() {
        const std::vector<byte> b=this->data;
        long i =b[position++] & 0xff;
        i |= (b[position++] & 0xff) << 8;
        i |= (b[position++] & 0xff) << 16;
        i |= (b[position++] & 0xff) << 24;
        i |= (b[position++] & 0xff) << 32;
        i |= (b[position++] & 0xff) << 40;
        i |= (b[position++] & 0xff) << 48;
        i |= (b[position++] & 0xff) << 48;
        return i;
    }

    long MySQLMessage::readLong(int length) {
        return 0;
    }

    bool MySQLMessage::hasRemaining() {
        return this->length>this->position;
    }

    std::vector<byte> MySQLMessage::readBytesWithLength() {
        std::vector<byte > resultVector;
        int length = (int) readLength();
        if (length <= 0) {
            return resultVector;
        }

        resultVector=ByteUtils::copySpecifiedData(data,position,length);
        position += length;
        return resultVector;
    }

    long MySQLMessage::readU4() {
        const std::vector<byte> b=this->data;
        long i =b[position++] & 0xff;
        i |= (b[position++] & 0xff) << 8;
        i |= (b[position++] & 0xff) << 16;
        i |= (b[position++] & 0xff) << 24;
        return i;
    }

    int MySQLMessage::positionPoint() {
        return this->position;
    }

    int MySQLMessage::positionPoint(int ps) {
        return this->position=ps;
    }

    std::string MySQLMessage::readStringWithNull() {
        std::vector<byte> b = this->data;
        if (position >= length) {
            return "";
        }
        int offset = -1;
        for (int i = position; i < length; i++) {
            if (b[i] == 0) {
                offset = i;
                break;
            }
        }
        if (offset == -1) {
            std::string s = Utils::StringUtils::newString(b, position, length - position);

            position = length;
            return s;
        }
        if (offset > position) {
            std::string s = Utils::StringUtils::newString(b, position, offset - position);
            position = offset + 1;
            return s;
        } else {
            position++;
            return "";
        }
    }

    std::string MySQLMessage::readString() {
        if(this->position>=this->length){
            return "";
        }
        char* datastr=new char[length-position+1];

        for (int i = 0; i < (length-position); ++i) {
            datastr[i]=this->data[position+i];
        }
        datastr[length-position+1]='\0';
        position=length;
        return std::__cxx11::string(datastr);
    }

    std::vector<byte> MySQLMessage::readBytes() {
        if (position >= length) {
            return EMPTY_BYTES;
        }

        std::vector<byte> ab=ByteUtils::copySpecifiedData(data,position,length);

        position = length;
        return ab;
    }

    void MySQLMessage::move(int i) {
        this->position=this->position+i;
    }

}
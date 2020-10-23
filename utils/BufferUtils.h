//
// Created by zhukovasky on 2020/9/17.
//

#ifndef MUDUO_SERVER_BUFFERUTILS_H
#define MUDUO_SERVER_BUFFERUTILS_H


#include <muduo/net/Buffer.h>
#include <common/Common.h>
#include <list>
class BufferUtils {


public:
    static int readU2(muduo::net::Buffer *buf){
        int i=buf->readInt8()&0xff;
        i|= ((buf->readInt8())&0xff)<<8;
        return i;
    }


    static int readU3(muduo::net::Buffer *buf){
        int i=buf->readInt8()&0xff;
        i|= ((buf->readInt8())&0xff)<<8;
        i|= ((buf->readInt8())&0xff)<<16;
        return i;
    }

    static int readU4(muduo::net::Buffer *buf){
        int i=buf->readInt8()&0xff;
        i|= ((buf->readInt8())&0xff)<<8;
        i|= ((buf->readInt8())&0xff)<<16;
        i|= ((buf->readInt8())&0xff)<<24;
        return i;
    }

    static long readLong(muduo::net::Buffer *buf){
        long i=buf->readInt8()&0xff;
        i|= ((buf->readInt8())&0xff)<<8;
        i|= ((buf->readInt8())&0xff)<<16;
        i|= ((buf->readInt8())&0xff)<<24;
        i|= ((buf->readInt8())&0xff)<<32;
        i|= ((buf->readInt8())&0xff)<<40;
        i|= ((buf->readInt8())&0xff)<<48;
        i|= ((buf->readInt8())&0xff)<<56;
        return i;
    }

    static long readLength(muduo::net::Buffer *data) {
        int length = data->readableBytes() & 0xff;
        switch (length) {
            case 251:
                return -1;
            case 252:
                return readU2(data);
            case 253:
                return readU3(data);
            case 254:
                return readLong(data);
            default:
                return length;
        }
    }

     static int decodeLength(long length) {
        if (length < 251) {
            return 1;
        } else if (length < 0x10000L) {
            return 3;
        } else if (length < 0x1000000L) {
            return 4;
        } else {
            return 9;
        }
    }

    static muduo::net::Buffer writeByte(muduo::net::Buffer &buffer,byte i){
        buffer.appendInt8(i);
        return buffer;
    }
    static muduo::net::Buffer writeU2(muduo::net::Buffer &buffer,int i){
        writeByte(buffer,(i&0xff));
        writeByte(buffer,(((unsigned) i)>>8));
        return buffer;
    }

    static muduo::net::Buffer writeWithNull(muduo::net::Buffer buffer,std::vector<byte> src){
        writeBytes(buffer,src);
        writeByte(buffer,0);
        return buffer;
    }

    static muduo::net::Buffer writeU4(muduo::net::Buffer &buffer,long i){
        writeByte(buffer,(byte)(1&0xff));
        writeByte(buffer,((unsigned)i)>>8);
        writeByte(buffer,((unsigned)i)>>16);
        writeByte(buffer,((unsigned)i)>>24);
        return buffer;
    }

    static muduo::net::Buffer writeBytes(muduo::net::Buffer &buffer,std::vector<byte> byteArrays){

        for (int i = 0; i < byteArrays.size(); ++i) {
            buffer.appendInt8(byteArrays[i]);
        }
        return buffer;
    }

    static void writeU3(muduo::net::Buffer &buffer,int i){
        writeByte(buffer,(byte) (((unsigned)i) & 0xff));
        writeByte(buffer,(byte) (((unsigned)i) >> 8));
        writeByte(buffer,(byte) (((unsigned) i) >> 16));
    }
    static  void writeLong(muduo::net::Buffer &buffer, long l) {
        writeByte(buffer,(byte) (l & 0xff));
        writeByte(buffer,(byte) (((unsigned)l) >> 8));
        writeByte(buffer,(byte) (((unsigned)l)>> 16));
        writeByte(buffer,(byte) (((unsigned)l)>> 24));
        writeByte(buffer,(byte) (((unsigned)l)>> 32));
        writeByte(buffer,(byte) (((unsigned)l) >> 40));
        writeByte(buffer,(byte) (((unsigned)l)>> 48));
        writeByte(buffer,(byte) (((unsigned)l)>> 56));
    }
     static  void writeLength(muduo::net::Buffer &buffer, long l) {
        if (l < 251) {

            buffer.appendInt8(l);
        } else if (l < 0x10000L) {

            buffer.appendInt8(252);
            writeU2(buffer, (int) l);
        } else if (l < 0x1000000L) {
            buffer.appendInt8(253);
            writeU3(buffer, (int) l);
        } else {

            writeByte(buffer,(byte) 254);
            writeLong(buffer, l);
        }
    }

    static void writeWithLength(muduo::net::Buffer &pBuffer, std::vector<byte> vector) {
        int length = vector.size();
        if (length < 251) {
            writeByte(pBuffer,(byte) length);
        } else if (length < 0x10000L) {
            writeByte(pBuffer,(byte) 252);
            writeU2(pBuffer, length);
        } else if (length < 0x1000000L) {
            writeByte(pBuffer,(byte) 253);
            writeU3(pBuffer, length);
        } else {
            writeByte(pBuffer,(byte) 254);
            writeLong(pBuffer, length);
        }
        writeBytes(pBuffer,vector);
    }
    static  void writeWithLength(muduo::net::Buffer &pBuffer, std::vector<byte> vector, byte nullValue) {
        if (vector.empty()) {
            writeByte(pBuffer,nullValue);
        } else {
            writeWithLength(pBuffer, vector);
        }
    }
    static const int getLength(long length) {
        if (length < 251) {
            return 1;
        } else if (length < 0x10000L) {
            return 3;
        } else if (length < 0x1000000L) {
            return 4;
        } else {
            return 9;
        }
    }

    static const int getLength(std::vector<byte> src) {
        int length = src.size();
        if (length < 251) {
            return 1 + length;
        } else if (length < 0x10000L) {
            return 3 + length;
        } else if (length < 0x1000000L) {
            return 4 + length;
        } else {
            return 9 + length;
        }
    }

};


#endif //MUDUO_SERVER_BUFFERUTILS_H

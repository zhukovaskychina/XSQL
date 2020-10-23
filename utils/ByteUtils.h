//
// Created by zhukovasky on 2020/9/17.
//

#ifndef MUDUO_SERVER_BYTEUTILS_H
#define MUDUO_SERVER_BYTEUTILS_H


#include <cstdint>
#include <muduo/net/Buffer.h>
#include <list>
#include <utils/StringUtils.h>
class ByteUtils {

public:



    static std::vector<char> readRestByte(muduo::net::Buffer *buffer,int length){
       // std::vector<uint8_t > list;
        std::vector<char> charList;
        const char* data=buffer->peek();

        for (int i = 0; i < length-1; ++i) {
         //   list.push_back(buffer->readInt8());
            charList.push_back(data[i]);
        }
        return charList;
    }

    static std::string readBytesToString(std::vector<char> data){
        std::string s="";
        for (int i = 1; i < data.size(); ++i) {
            s.push_back(data[i]);
        }
        std::string result=Utils::StringUtils::trim(s,"");
        return result;
    }

    static std::vector<byte > copySpecifiedData(std::vector<byte> orignal,int position,int length){
        std::vector<byte > result;
        for (int i = 0; i < length; ++i) {
            result.push_back(orignal[position+i]);
        }
        return result;
    }
};


#endif //MUDUO_SERVER_BYTEUTILS_H

//
// Created by zhukovasky on 2020/9/18.
//

#ifndef MUDUO_SERVER_RANDOMUTILS_H
#define MUDUO_SERVER_RANDOMUTILS_H


#include <vector>
#include <time.h>

typedef char byte;
static const std::vector<byte> bytes = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'q', 'w', 'e', 'r', 't',
                                 'y', 'u', 'i', 'o', 'p', 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'z', 'x', 'c', 'v', 'b', 'n', 'm',
                                 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'Z', 'X',
                                 'C', 'V', 'B', 'N', 'M'};
static const long multiplier = 0x5DEECE66DL;
static long addend = 0xBL;
static long mask = (1L << 48) - 1;
const long integerMask = (1L << 33) - 1;
const long seedUniquifier = 8682522807148012L;

long seed=0;
class RandomUtils {
private:


    static void loadSystem(){
        seed=0;
        long s=seedUniquifier+time(NULL);
        s=(s^multiplier)&mask;
        seed=s;
    }

    static byte randomByte(std::vector<byte > b) {
        int ran = (int) ((next() & integerMask) >> 16);
        return b[ran % b.size()];
    }

    static long next() {
        long oldSeed = seed;
        long nextSeed = 0L;
        do {
            nextSeed = (oldSeed * multiplier + addend) & mask;
        } while (oldSeed == nextSeed);
        seed = nextSeed;
        return nextSeed;
    }

public:
    static std::vector<byte> randomBytes(int size) {
        loadSystem();
        std::vector<byte> bb=bytes;
        std::vector<byte> ab;
        for (int i = 0; i < size; i++) {

            ab.push_back(randomByte(bb));
        }
        return ab;
    }
};


#endif //MUDUO_SERVER_RANDOMUTILS_H

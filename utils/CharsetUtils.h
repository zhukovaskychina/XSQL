//
// Created by zhukovasky on 2020/9/18.
//

#ifndef MUDUO_SERVER_CHARSETUTILS_H
#define MUDUO_SERVER_CHARSETUTILS_H

#include <string>
#include <map>
#include <vector>
#include "StringUtils.h"

static std::vector<std::string> INDEX_TO_CHARSET;
static std::map<std::string, int> CHARSET_TO_INDEX;

class CharsetUtils {
private:

    static void loadSystem() {
        // index --> charset
        INDEX_TO_CHARSET.push_back("big5");
        INDEX_TO_CHARSET.push_back("czech");
        INDEX_TO_CHARSET.push_back("dec8");
        INDEX_TO_CHARSET.push_back("dos");
        INDEX_TO_CHARSET.push_back("german1");
        INDEX_TO_CHARSET.push_back("hp8");
        INDEX_TO_CHARSET.push_back("koi8_ru");
        INDEX_TO_CHARSET.push_back("latin1");
        INDEX_TO_CHARSET.push_back("latin2");
        INDEX_TO_CHARSET.push_back("swe7");
        INDEX_TO_CHARSET.push_back("usa7");
        INDEX_TO_CHARSET.push_back("ujis");
        INDEX_TO_CHARSET.push_back("sjis");
        INDEX_TO_CHARSET.push_back("cp1251");
        INDEX_TO_CHARSET.push_back("danish");
        INDEX_TO_CHARSET.push_back("hebrew");
        INDEX_TO_CHARSET.push_back("tis620");
        INDEX_TO_CHARSET.push_back("euc_kr");
        INDEX_TO_CHARSET.push_back("estonia");
        INDEX_TO_CHARSET.push_back("hungarian");
        INDEX_TO_CHARSET.push_back("koi8_ukr");
        INDEX_TO_CHARSET.push_back("win1251ukr");
        INDEX_TO_CHARSET.push_back("gb2312");
        INDEX_TO_CHARSET.push_back("greek");
        INDEX_TO_CHARSET.push_back("win1250");
        INDEX_TO_CHARSET.push_back("croat");
        INDEX_TO_CHARSET.push_back("gbk");
        INDEX_TO_CHARSET.push_back("cp1257");
        INDEX_TO_CHARSET.push_back("latin5");
        INDEX_TO_CHARSET.push_back("latin1_de");
        INDEX_TO_CHARSET.push_back("armscii8");
        INDEX_TO_CHARSET.push_back("utf8");
        INDEX_TO_CHARSET.push_back("win1250ch");
        INDEX_TO_CHARSET.push_back("ucs2");
        INDEX_TO_CHARSET.push_back("cp866");
        INDEX_TO_CHARSET.push_back("keybcs2");
        INDEX_TO_CHARSET.push_back("macce");
        INDEX_TO_CHARSET.push_back("macroman");
        INDEX_TO_CHARSET.push_back("pclatin2");
        INDEX_TO_CHARSET.push_back("latvian");
        INDEX_TO_CHARSET.push_back("latvian1");
        INDEX_TO_CHARSET.push_back("maccebin");
        INDEX_TO_CHARSET.push_back("macceciai");
        INDEX_TO_CHARSET.push_back("maccecias");
        INDEX_TO_CHARSET.push_back("maccecsas");
        INDEX_TO_CHARSET.push_back("latin1bin");
        INDEX_TO_CHARSET.push_back("latin1cias");
        INDEX_TO_CHARSET.push_back("latin1csas");
        INDEX_TO_CHARSET.push_back("cp1251bin");
        INDEX_TO_CHARSET.push_back("cp1251cias");
        INDEX_TO_CHARSET.push_back("cp1251csas");
        INDEX_TO_CHARSET.push_back("macromanbin");
        INDEX_TO_CHARSET.push_back("macromancias");
        INDEX_TO_CHARSET.push_back("macromanciai");
        INDEX_TO_CHARSET.push_back("macromancsas");
        INDEX_TO_CHARSET.push_back("cp1256");
        INDEX_TO_CHARSET.push_back("binary");
        INDEX_TO_CHARSET.push_back("armscii");
        INDEX_TO_CHARSET.push_back("ascii");
        INDEX_TO_CHARSET.push_back("cp1250");
        INDEX_TO_CHARSET.push_back("cp1256");
        INDEX_TO_CHARSET.push_back("cp866");
        INDEX_TO_CHARSET.push_back("dec8");
        INDEX_TO_CHARSET.push_back("greek");
        INDEX_TO_CHARSET.push_back("hebrew");
        INDEX_TO_CHARSET.push_back("hp8");
        INDEX_TO_CHARSET.push_back("keybcs2");
        INDEX_TO_CHARSET.push_back("koi8r");
        INDEX_TO_CHARSET.push_back("koi8ukr");
        INDEX_TO_CHARSET.push_back("latin2");
        INDEX_TO_CHARSET.push_back("latin5");
        INDEX_TO_CHARSET.push_back("latin7");
        INDEX_TO_CHARSET.push_back("cp850");
        INDEX_TO_CHARSET.push_back("cp852");
        INDEX_TO_CHARSET.push_back("swe7");
        INDEX_TO_CHARSET.push_back("utf8");
        INDEX_TO_CHARSET.push_back("big5");
        INDEX_TO_CHARSET.push_back("euckr");
        INDEX_TO_CHARSET.push_back("gb2312");
        INDEX_TO_CHARSET.push_back("gbk");
        INDEX_TO_CHARSET.push_back("sjis");
        INDEX_TO_CHARSET.push_back("tis620");
        INDEX_TO_CHARSET.push_back("ucs2");
        INDEX_TO_CHARSET.push_back("ujis");
        INDEX_TO_CHARSET.push_back("geostd8");
        INDEX_TO_CHARSET.push_back("geostd8");
        INDEX_TO_CHARSET.push_back("latin1");
        INDEX_TO_CHARSET.push_back("cp932");
        INDEX_TO_CHARSET.push_back("cp932");
        INDEX_TO_CHARSET.push_back("eucjpms");
        INDEX_TO_CHARSET.push_back("eucjpms");

        // charset --> index
        for (int i = 0; i < INDEX_TO_CHARSET.size(); i++) {
            std::string charset = INDEX_TO_CHARSET[i];
            if (charset != "" && CHARSET_TO_INDEX[charset] == NULL) {
                CHARSET_TO_INDEX[charset] = i;
            }
        }
        CHARSET_TO_INDEX["iso-8859-1"] = 14;
        CHARSET_TO_INDEX["iso_8859_1"] = 14;
        CHARSET_TO_INDEX["utf-8"] = 33;
    }

public:
    static const std::string getCharset(int index) {
        loadSystem();
        return INDEX_TO_CHARSET[index];
    }

    static int getIndex(std::string charset) {
        loadSystem();
        if (charset == "" || charset.length() == 0) {
            return 0;
        } else {
            int i = CHARSET_TO_INDEX[Utils::StringUtils::toLower(charset)];
            return (i == NULL) ? 0 : i;
        }
    }

};


#endif //MUDUO_SERVER_CHARSETUTILS_H

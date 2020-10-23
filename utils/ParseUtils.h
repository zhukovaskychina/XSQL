//
// Created by zhukovasky on 2020/9/30.
//

#ifndef XSQL_PARSEUTILS_H
#define XSQL_PARSEUTILS_H


#include <iostream>
#include "StringUtils.h"

//用来解析ＳＱＬ
class ParseUtils {

public:
 static int parse(std::string stmt) {
        for (int i = 0; i < stmt.length(); ++i) {
            switch (stmt.at(i)) {
                case ' ':
                case '\t':
                case '\r':
                case '\n':
                    continue;
                case '/':
                case '#':
                    i = parseComment(stmt, i);
                    continue;
                case 'B':
                case 'b':
                    return beginCheck(stmt, i);
                case 'C':
                case 'c':
                    return createSchemaAndCommit(stmt, i);
                case 'D':
                case 'd':
                    return deleteCheck(stmt, i);
                case 'E':
                case 'e':
                    return explainCheck(stmt, i);
                case 'I':
                case 'i':
                    return insertCheck(stmt, i);
                case 'R':
                case 'r':
                    return rCheck(stmt, i);
                case 'S':
                case 's':
                    return sCheck(stmt, i);
                case 'U':
                case 'u':
                    return uCheck(stmt, i);
                case 'K':
                case 'k':
                    return killCheck(stmt, i);
                default:
                    return OTHER;
            }
        }
        return OTHER;
    }

    static int parseComment(std::string stmt,int offset){
        int len=stmt.length();
        int n=offset;
        switch (stmt.at(n)){
            case '/':{
                if (len > ++n && stmt.at(n++) == '*' && len > n + 1 && stmt.at(n) != '!') {
                    for (int i = n; i < len; ++i) {
                        if (stmt.at(i) == '*') {
                            int m = i + 1;
                            if (len > m && stmt.at(m) == '/') return m;
                        }
                    }
                }
                break;
            }
            case '#':{
                for (int i = n + 1; i < len; ++i) {
                    if (stmt.at(i) == '\n') return i;
                }
                break;
            }
        }
        return offset;
    }
    static int createSchemaAndCommit(std::string stmt, int offset) {
        if(Utils::StringUtils::startsWith(stmt,"create")||Utils::StringUtils::startsWith(stmt,"CREATE")){

            std::string stmtNew = stmt.substr(6, stmt.length());
            std::string stmtRs=Utils::StringUtils::trim(stmtNew," ");

            if (Utils::StringUtils::startsWith(stmtRs,"database")||Utils::StringUtils::startsWith(stmtRs,"DATABASE")) {
                char c1 = stmtRs.at(offset++);
                char c2 = stmtRs.at(offset++);
                char c3 = stmtRs.at(offset++);
                char c4 = stmtRs.at(offset++);
                char c5 = stmtRs.at(offset++);
                char c6 = stmtRs.at(offset++);
                char c7 = stmtRs.at(offset++);
                char c8 = stmtRs.at(offset++);
                if ((c1 == 'd' || c1 == 'D') && (c2 == 'a' || c2 == 'A') && (c3 == 't' || c3 == 'T') && (c4 == 'a' || c4
                                                                                                                      == 'A')
                    && (c5 == 'b' || c5 == 'B') && (c6 == 'a' || c6 == 'A') && (c7 == 's' || c7 == 'S') &&
                    (c8 == 'e' || c8 == 'E')) {
                    return CREATE_DATABASE;
                }

            }

            if(Utils::StringUtils::startsWith(stmtRs,"table")||Utils::StringUtils::startsWith(stmtRs,"TABLE")){
                char c1 = stmtRs.at(offset++);
                char c2 = stmtRs.at(offset++);
                char c3 = stmtRs.at(offset++);
                char c4 = stmtRs.at(offset++);
                char c5 = stmtRs.at(offset++);
                if((c1=='t'||c1=='T')&&(c2=='a'||c2=='A')&&(c3=='B'||c3=='b')&&(c4=='L')&&(c5=='E')){
                    return CREATE_TABLE;
                }
            }

            if(stmtRs.length()<7){
                char c1 = stmtRs.at(offset++);
                char c2 = stmtRs.at(offset++);
                char c3 = stmtRs.at(offset++);
                char c4 = stmtRs.at(offset++);
                char c5 = stmtRs.at(offset++);
                if((c1=='t'||c1=='T')&&(c2=='a'||c2=='A')&&(c3=='B'||c3=='b')&&(c4=='L')&&(c5=='E')){
                    return CREATE_TABLE;
                }
            }
        }
        return commitCheck(stmt, offset);
    }
    // COMMIT
    static int commitCheck(std::string stmt, int offset) {
        if (stmt.length() > offset + 5) {
            char c1 = stmt.at(++offset);
            char c2 = stmt.at(++offset);
            char c3 = stmt.at(++offset);
            char c4 = stmt.at(++offset);
            char c5 = stmt.at(++offset);
            if ((c1 == 'O' || c1 == 'o') && (c2 == 'M' || c2 == 'm') && (c3 == 'M' || c3 == 'm')
                && (c4 == 'I' || c4 == 'i') && (c5 == 'T' || c5 == 't')
                && (stmt.length() == ++offset || isEOF(stmt.at(offset)))) {
                return COMMIT;
            }
        }
        return OTHER;
    }

    // EXPLAIN' '
    static int explainCheck(std::string stmt, int offset) {
        std::string XPLAIN="XPLAIN ";
        if (stmt.length() > offset + XPLAIN.length()) {
            char c1 = stmt.at(++offset);
            char c2 = stmt.at(++offset);
            char c3 = stmt.at(++offset);
            char c4 = stmt.at(++offset);
            char c5 = stmt.at(++offset);
            char c6 = stmt.at(++offset);
            char c7 = stmt.at(++offset);
            if ((c1 == 'X' || c1 == 'x') && (c2 == 'P' || c2 == 'p') && (c3 == 'L' || c3 == 'l')
                && (c4 == 'A' || c4 == 'a') && (c5 == 'I' || c5 == 'i') && (c6 == 'N' || c6 == 'n')
                && (c7 == ' ' || c7 == '\t' || c7 == '\r' || c7 == '\n')) {
                return (offset << 8) | EXPLAIN;
            }
        }
        return OTHER;
    }

    // KILL' '
    static int killCheck(std::string stmt, int offset) {
        std::string ILL="ILL ";
        if (stmt.length() > offset + ILL.length()) {
            char c1 = stmt.at(++offset);
            char c2 = stmt.at(++offset);
            char c3 = stmt.at(++offset);
            char c4 = stmt.at(++offset);
            if ((c1 == 'I' || c1 == 'i') && (c2 == 'L' || c2 == 'l') && (c3 == 'L' || c3 == 'l')
                && (c4 == ' ' || c4 == '\t' || c4 == '\r' || c4 == '\n')) {
                while (stmt.length() > ++offset) {
                    switch (stmt.at(offset)) {
                        case ' ':
                        case '\t':
                        case '\r':
                        case '\n':
                            continue;
                        case 'Q':
                        case 'q':
                            return killQueryCheck(stmt, offset);
                        default:
                            return (offset << 8) | KILL;
                    }
                }
                return OTHER;
            }
        }
        return OTHER;
    }

    // KILL QUERY' '
    static int killQueryCheck(std::string stmt, int offset) {
        std::string UERY="UERY ";
        if (stmt.length() > offset + UERY.length()) {
            char c1 = stmt.at(++offset);
            char c2 = stmt.at(++offset);
            char c3 = stmt.at(++offset);
            char c4 = stmt.at(++offset);
            char c5 = stmt.at(++offset);
            if ((c1 == 'U' || c1 == 'u') && (c2 == 'E' || c2 == 'e') && (c3 == 'R' || c3 == 'r')
                && (c4 == 'Y' || c4 == 'y') && (c5 == ' ' || c5 == '\t' || c5 == '\r' || c5 == '\n')) {
                while (stmt.length() > ++offset) {
                    switch (stmt.at(offset)) {
                        case ' ':
                        case '\t':
                        case '\r':
                        case '\n':
                            continue;
                        default:
                            return (offset << 8) | KILL_QUERY;
                    }
                }
                return OTHER;
            }
        }
        return OTHER;
    }

    // BEGIN
    static int beginCheck(std::string stmt, int offset) {
        if (stmt.length() > offset + 4) {
            char c1 = stmt.at(++offset);
            char c2 = stmt.at(++offset);
            char c3 = stmt.at(++offset);
            char c4 = stmt.at(++offset);
            if ((c1 == 'E' || c1 == 'e') && (c2 == 'G' || c2 == 'g') && (c3 == 'I' || c3 == 'i')
                && (c4 == 'N' || c4 == 'n') && (stmt.length() == ++offset || isEOF(stmt.at(offset)))) {
                return BEGIN;
            }
        }
        return OTHER;
    }

    // DELETE' '
    static int deleteCheck(std::string stmt, int offset) {
        if (stmt.length() > offset + 6) {
            char c1 = stmt.at(++offset);
            char c2 = stmt.at(++offset);
            char c3 = stmt.at(++offset);
            char c4 = stmt.at(++offset);
            char c5 = stmt.at(++offset);
            char c6 = stmt.at(++offset);
            if ((c1 == 'E' || c1 == 'e') && (c2 == 'L' || c2 == 'l') && (c3 == 'E' || c3 == 'e')
                && (c4 == 'T' || c4 == 't') && (c5 == 'E' || c5 == 'e')
                && (c6 == ' ' || c6 == '\t' || c6 == '\r' || c6 == '\n')) {
                return DELETE;
            }
        }

        if(Utils::StringUtils::startsWith(stmt,"DESC")){
//            char c1 = stmt.at(++offset);
//            char c2 = stmt.at(++offset);
//            char c3 = stmt.at(++offset);
//            char c4=stmt.at(++offset);
//            if((c1=='E'||c1=='e')&&(c2=='S'||c2=='s')&&(c3=='C'||(c3=='c'))
//            &&(c4==' '|| c4 == '\t' || c4 == '\r' || c4 == '\n')
//            ){
                return DESC;
//            }
        }
        return OTHER;
    }

    // INSERT' '
    static int insertCheck(std::string stmt, int offset) {
        if (stmt.length() > offset + 6) {
            char c1 = stmt.at(++offset);
            char c2 = stmt.at(++offset);
            char c3 = stmt.at(++offset);
            char c4 = stmt.at(++offset);
            char c5 = stmt.at(++offset);
            char c6 = stmt.at(++offset);
            if ((c1 == 'N' || c1 == 'n') && (c2 == 'S' || c2 == 's') && (c3 == 'E' || c3 == 'e')
                && (c4 == 'R' || c4 == 'r') && (c5 == 'T' || c5 == 't')
                && (c6 == ' ' || c6 == '\t' || c6 == '\r' || c6 == '\n')) {
                return INSERT;
            }
        }
        return OTHER;
    }

    static int rCheck(std::string stmt, int offset) {
        if (stmt.length() > ++offset) {
            switch (stmt.at(offset)) {
                case 'E':
                case 'e':
                    return replaceReloadCheck(stmt, offset);
                case 'O':
                case 'o':
                    return rollabckCheck(stmt, offset);
                default:
                    return OTHER;
            }
        }
        return OTHER;
    }

    static int replaceReloadCheck(std::string stmt, int offset) {
        if (stmt.length() > offset + 6) {
            char c1 = stmt.at(++offset);
            char c2 = stmt.at(++offset);
            char c3 = stmt.at(++offset);
            char c4 = stmt.at(++offset);
            char c5 = stmt.at(++offset);
            char c6 = stmt.at(++offset);
            if ((c1 == 'P' || c1 == 'p') && (c2 == 'L' || c2 == 'l') && (c3 == 'A' || c3 == 'a')
                && (c4 == 'C' || c4 == 'c') && (c5 == 'E' || c5 == 'e')
                && (c6 == ' ' || c6 == '\t' || c6 == '\r' || c6 == '\n')) {
                return REPLACE;
            }
        }
        if (stmt.length() > offset + 4) {
            char c1 = stmt.at(++offset);
            char c2 = stmt.at(++offset);
            char c3 = stmt.at(++offset);
            char c4 = stmt.at(++offset);
            if ((c1 == 'l' || c1 == 'L') && (c2 == 'o' || c2 == 'O') && (c3 == 'a' || c3 == 'A')
                && (c4 == 'd' || c4 == 'D')) {
                return RELOAD;
            }
        }
        return OTHER;
    }

    // ROLLBACK
    static int rollabckCheck(std::string stmt, int offset) {
        if (stmt.length() > offset + 6) {
            char c1 = stmt.at(++offset);
            char c2 = stmt.at(++offset);
            char c3 = stmt.at(++offset);
            char c4 = stmt.at(++offset);
            char c5 = stmt.at(++offset);
            char c6 = stmt.at(++offset);
            if ((c1 == 'L' || c1 == 'l') && (c2 == 'L' || c2 == 'l') && (c3 == 'B' || c3 == 'b')
                && (c4 == 'A' || c4 == 'a') && (c5 == 'C' || c5 == 'c') && (c6 == 'K' || c6 == 'k')
                && (stmt.length() == ++offset || isEOF(stmt.at(offset)))) {
                return ROLLBACK;
            }
        }
        return OTHER;
    }

    static int sCheck(std::string stmt, int offset) {
        if (stmt.length() > ++offset) {
            switch (stmt.at(offset)) {
                case 'A':
                case 'a':
                    return savepointCheck(stmt, offset);
                case 'E':
                case 'e':
                    return seCheck(stmt, offset);
                case 'H':
                case 'h':
                    return showCheck(stmt, offset);
                case 'T':
                case 't':
                    return startCheck(stmt, offset);
                default:
                    return OTHER;
            }
        }
        return OTHER;
    }

    // SAVEPOINT
    static int savepointCheck(std::string stmt, int offset) {
        if (stmt.length() > offset + 8) {
            char c1 = stmt.at(++offset);
            char c2 = stmt.at(++offset);
            char c3 = stmt.at(++offset);
            char c4 = stmt.at(++offset);
            char c5 = stmt.at(++offset);
            char c6 = stmt.at(++offset);
            char c7 = stmt.at(++offset);
            char c8 = stmt.at(++offset);
            if ((c1 == 'V' || c1 == 'v') && (c2 == 'E' || c2 == 'e') && (c3 == 'P' || c3 == 'p')
                && (c4 == 'O' || c4 == 'o') && (c5 == 'I' || c5 == 'i') && (c6 == 'N' || c6 == 'n')
                && (c7 == 'T' || c7 == 't') && (c8 == ' ' || c8 == '\t' || c8 == '\r' || c8 == '\n')) {
                return SAVEPOINT;
            }
        }
        return OTHER;
    }

    static int seCheck(std::string stmt, int offset) {
        if (stmt.length() > ++offset) {
            switch (stmt.at(offset)) {
                case 'L':
                case 'l':
                    return selectCheck(stmt, offset);
                case 'T':
                case 't':
                    if (stmt.length() > ++offset) {
                        char c = stmt.at(offset);
                        if (c == ' ' || c == '\r' || c == '\n' || c == '\t' || c == '/' || c == '#') {
                            return (offset << 8) | SET;
                        }
                    }
                    return OTHER;
                default:
                    return OTHER;
            }
        }
        return OTHER;
    }

    // SELECT' '
    static int selectCheck(std::string stmt, int offset) {
        if (stmt.length() > offset + 4) {
            char c1 = stmt.at(++offset);
            char c2 = stmt.at(++offset);
            char c3 = stmt.at(++offset);
            char c4 = stmt.at(++offset);
            if ((c1 == 'E' || c1 == 'e') && (c2 == 'C' || c2 == 'c') && (c3 == 'T' || c3 == 't')
                && (c4 == ' ' || c4 == '\t' || c4 == '\r' || c4 == '\n' || c4 == '/' || c4 == '#')) {
             
                return  SELECT;
            }
        }
        return OTHER;
    }

    // SHOW' '
    static int showCheck(std::string stmt, int offset) {
        if (stmt.length() > offset + 3) {
            char c1 = stmt.at(++offset);
            char c2 = stmt.at(++offset);
            char c3 = stmt.at(++offset);
            if ((c1 == 'O' || c1 == 'o') && (c2 == 'W' || c2 == 'w')
                && (c3 == ' ' || c3 == '\t' || c3 == '\r' || c3 == '\n')) {
                return  SHOW;
            }
        }
        return OTHER;
    }

    // START' '
    static int startCheck(std::string stmt, int offset) {
        if (stmt.length() > offset + 4) {
            char c1 = stmt.at(++offset);
            char c2 = stmt.at(++offset);
            char c3 = stmt.at(++offset);
            char c4 = stmt.at(++offset);
            if ((c1 == 'A' || c1 == 'a') && (c2 == 'R' || c2 == 'r') && (c3 == 'T' || c3 == 't')
                && (c4 == ' ' || c4 == '\t' || c4 == '\r' || c4 == '\n')) {
                return (offset << 8) | START;
            }
        }
        return OTHER;
    }

    // UPDATE' ' | USE' '
    static int uCheck(std::string stmt, int offset) {
        if (stmt.length() > ++offset) {
            switch (stmt.at(offset)) {
                case 'P':
                case 'p':
                    if (stmt.length() > offset + 5) {
                        char c1 = stmt.at(++offset);
                        char c2 = stmt.at(++offset);
                        char c3 = stmt.at(++offset);
                        char c4 = stmt.at(++offset);
                        char c5 = stmt.at(++offset);
                        if ((c1 == 'D' || c1 == 'd') && (c2 == 'A' || c2 == 'a') && (c3 == 'T' || c3 == 't')
                            && (c4 == 'E' || c4 == 'e') && (c5 == ' ' || c5 == '\t' || c5 == '\r' || c5 == '\n')) {
                            return UPDATE;
                        }
                    }
                    break;
                case 'S':
                case 's':
                    if (stmt.length() > offset + 2) {
                        char c1 = stmt.at(++offset);
                        char c2 = stmt.at(++offset);
                        if ((c1 == 'E' || c1 == 'e') && (c2 == ' ' || c2 == '\t' || c2 == '\r' || c2 == '\n')) {
                            //return (offset << 8) | USE;
                            return USE;
                        }
                    }
                    break;
                default:
                    return OTHER;
            }
        }
        return OTHER;
    }
    static bool isEOF(char c) {
        return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == ';');
    }
};


#endif //XSQL_PARSEUTILS_H

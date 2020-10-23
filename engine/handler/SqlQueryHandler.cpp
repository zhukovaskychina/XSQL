//
// Created by zhukovasky on 2020/9/23.
//

#include <mysql_protocol/MySqlProtocolEnums.h>
#include <iostream>
#include <utils/ByteUtils.h>
#include <engine/sqlparser/MySQLParser.h>
#include <fstream>
#include <libs/antlr4-cpp-runtime-4.7.2/src/ANTLRInputStream.h>
#include <engine/sqlparser/MySQLLexer.h>
#include <libs/antlr4-cpp-runtime-4.7.2/src/CommonTokenStream.h>

#include "SqlQueryHandler.h"
#include <vector>
#include <common/Exceptions.h>


using namespace antlr4;
using namespace std;

void SqlQueryHandler::query(MyProtocol::BinaryPacket *binaryPacket, SessionConnection *sessionConnection) {
    std::vector<byte> data = binaryPacket->getData();
    uint8_t firstTag = data[0];

        switch (firstTag) {
            case MySQLProtocolEnums::COM_SLEEP: {
                break;
            }
            case MySQLProtocolEnums::COM_BINLOG_DUMP: {
                break;
            }
            case MySQLProtocolEnums::COM_QUERY: {
                std::cout << "查询语句" << std::endl;
                std::string result = ByteUtils::readBytesToString(binaryPacket->getData());
                std::cout << result << std::endl;
                std::string UPPERSQL=Utils::StringUtils::toUpper(result);
                this->sqlInterpreters->ExecSQL(UPPERSQL,*sessionConnection);
                break;
            }
            case MySQLProtocolEnums::COM_QUIT: {
                break;
            }
            case MySQLProtocolEnums::COM_STMT_PREPARE: {
                break;
            }
            case MySQLProtocolEnums::COM_STMT_EXECUTE: {
                break;
            }
            case MySQLProtocolEnums::COM_STMT_CLOSE: {
                break;
            }
            case MySQLProtocolEnums::COM_HEARTBEAT: {
                break;
            }
            default:
                break;
        }


}

SQLInterpret *SqlQueryHandler::getSqlInterpreter() const {
    return sqlInterpreters;
}

void SqlQueryHandler::setSqlInterpreter(SQLInterpret *sqlInterpreter) {
    SqlQueryHandler::sqlInterpreters = sqlInterpreter;
}


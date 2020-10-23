//
// Created by zhukovasky on 2020/9/23.
//

#ifndef MUDUO_SERVER_SQLQUERYHANDLER_H
#define MUDUO_SERVER_SQLQUERYHANDLER_H


#include <mysql_protocol/packet/BinaryPacket.h>
#include <engine/session/SessionConnection.h>
#include <engine/interpreter.h>
#include <engine/interpret/SqlInterpret.h>
class SessionConnection;
class SQLInterpret;
class SqlQueryHandler {

public:
    void query(MyProtocol::BinaryPacket *binaryPacket,SessionConnection *sessionConnection);

private:

    SQLInterpret *sqlInterpreters;
public:
    SQLInterpret *getSqlInterpreter() const;

    void setSqlInterpreter(SQLInterpret *sqlInterpreters);
};


#endif //MUDUO_SERVER_SQLQUERYHANDLER_H

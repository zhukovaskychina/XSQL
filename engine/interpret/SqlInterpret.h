//
// Created by zhukovasky on 2020/9/30.
//

#ifndef XSQL_SQLINTERPRET_H
#define XSQL_SQLINTERPRET_H


#include <string>
#include <engine/minidb_api.h>
#include <engine/core/XApi.h>
#include <engine/session/SessionConnection.h>
class SessionConnection;
class SQLInterpret {
private:
   // MiniDBAPI* api;

    XApi* xapi;
    std::string sql_statement_;

    int sql_type_;

    void Run();

    void checkSQLType();
public:
    SQLInterpret();
    ~SQLInterpret();
    void ExecSQL(std::string statement,SessionConnection &sessionConnection);
};



#endif //XSQL_SQLINTERPRET_H

//
// Created by zhukovasky on 2020/10/14.
//

#ifndef XSQL_SHOWDATABASELISTENER_H
#define XSQL_SHOWDATABASELISTENER_H


#include <engine/sqlparser/MySQLParserBaseListener.h>

class ShowDatabaseListener : public parser::MySQLParserBaseListener{
public:
    int showType;

    std::string descTableName;

    void enterShowCreateDb(parser::MySQLParser::ShowCreateDbContext *context) override;

    void enterShowCreateUser(parser::MySQLParser::ShowCreateUserContext *context) override;

    void enterShowEngine(parser::MySQLParser::ShowEngineContext *context) override;

    void enterShowIndexes(parser::MySQLParser::ShowIndexesContext *context) override;


    void enterShowFromschemaFilter(parser::MySQLParser::ShowFromschemaFilterContext  *ctx) override;

    void enterAdministration_statement(parser::MySQLParser::Administration_statementContext * ctx) override;

    void enterShowObjWithFilter(parser::MySQLParser::ShowObjWithFilterContext *ctx) override;

    void enterSimple_describe_statement(parser::MySQLParser::Simple_describe_statementContext *context) override;
};


#endif //XSQL_SHOWDATABASELISTENER_H

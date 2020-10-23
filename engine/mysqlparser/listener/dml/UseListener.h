//
// Created by zhukovasky on 2020/10/1.
//

#ifndef XSQL_USELISTENER_H
#define XSQL_USELISTENER_H


#include <engine/sqlparser/MySQLParserBaseListener.h>

class UseListener : public parser::MySQLParserBaseListener {

public:
    UseListener();

    std::string dbName;
    void enterUtility_statement(parser::MySQLParser::Utility_statementContext *ctx) override;

    void exitUtility_statement(parser::MySQLParser::Utility_statementContext *context) override;

    virtual ~UseListener();
};

#endif //XSQL_USELISTENER_H

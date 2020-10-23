//
// Created by zhukovasky on 2020/10/13.
//

#ifndef XSQL_CHECKSQLSTATEMENTLISTENER_H
#define XSQL_CHECKSQLSTATEMENTLISTENER_H


#include <engine/sqlparser/MySQLParserBaseListener.h>

class CheckSqlStatementListener: public parser::MySQLParserBaseListener {
public:
    void exitSql_statement(parser::MySQLParser::Sql_statementContext *context) override;

    void enterSql_statement(parser::MySQLParser::Sql_statementContext *context) override;
};


#endif //XSQL_CHECKSQLSTATEMENTLISTENER_H

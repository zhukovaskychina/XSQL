//
// Created by zhukovasky on 2020/10/13.
//

#include "CheckSqlStatementListener.h"

void CheckSqlStatementListener::exitSql_statement(parser::MySQLParser::Sql_statementContext *context) {
    MySQLParserBaseListener::exitSql_statement(context);
}


void CheckSqlStatementListener::enterSql_statement(parser::MySQLParser::Sql_statementContext *context) {
    MySQLParserBaseListener::enterSql_statement(context);
}

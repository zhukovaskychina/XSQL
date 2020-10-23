//
// Created by zhukovasky on 2020/9/30.
//

#ifndef XSQL_CREATEDATABASELISTENER_H
#define XSQL_CREATEDATABASELISTENER_H


#include <engine/sqlparser/MySQLParserBaseListener.h>

class CreateDataBaseListener: public parser::MySQLParserBaseListener {

public:
    std::string databaseName;

    CreateDataBaseListener();
    ~CreateDataBaseListener();

    void enterCreate_database_option(parser::MySQLParser::Create_database_optionContext *context) override;

    void exitCreate_database_option(parser::MySQLParser::Create_database_optionContext *context) override;

    void enterCreate_database(parser::MySQLParser::Create_databaseContext *context) override;

    void exitCreate_database(parser::MySQLParser::Create_databaseContext *context) override;

    void visitErrorNode(antlr4::tree::ErrorNode *node) override;

};



#endif //XSQL_CREATEDATABASELISTENER_H

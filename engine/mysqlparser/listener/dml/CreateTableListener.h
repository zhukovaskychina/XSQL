//
// Created by zhukovasky on 2020/9/30.
//

#ifndef XSQL_CREATETABLELISTENER_H
#define XSQL_CREATETABLELISTENER_H


#include <engine/sqlparser/MySQLParserBaseListener.h>
#include <engine/catalog_manager.h>
#include <iostream>
class CreateTableListener : public parser::MySQLParserBaseListener {


private:
    int processDataType(std::string dataType);
public:
    std::string tableName;
    bool ifNotExists;
    std::vector<Attribute> attributes;
    void enterColCreateTable(parser::MySQLParser::ColCreateTableContext *context) override;

    void enterColumnDefinition(parser::MySQLParser::ColumnDefinitionContext * ctx) override;

    void enterColumn_definition(parser::MySQLParser::Column_definitionContext * ctx) override;
};


#endif //XSQL_CREATETABLELISTENER_H

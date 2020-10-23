//
// Created by zhukovasky on 2020/9/29.
//

#ifndef MYSQL_PARSER_INSERTTABLESTATMENTLISTENER_H
#define MYSQL_PARSER_INSERTTABLESTATMENTLISTENER_H


#include <engine/sqlparser/MySQLParserBaseListener.h>
#include <engine/catalog_manager.h>

class InsertTableStatmentListener:public parser::MySQLParserBaseListener {
private:
    std::string tableName;
    std::vector<std::string> colAttrName;
    std::vector<SQLValue> value_;
public:
    const std::string &getTableName() const;

    const std::vector<std::string> &getColAttrName() const;

    const std::vector<SQLValue> &getValue() const;

    void enterInsert_statement(parser::MySQLParser::Insert_statementContext * ctx) override;

    void enterInsert_statement_value(parser::MySQLParser::Insert_statement_valueContext * ctx) override;
};


#endif //MYSQL_PARSER_INSERTTABLESTATMENTLISTENER_H

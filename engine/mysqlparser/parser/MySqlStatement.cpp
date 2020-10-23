//
// Created by zhukovasky on 2020/9/30.
//

#include <engine/sqlparser/MySQLLexer.h>
#include <engine/mysqlparser/listener/SqlErrorListener.h>
#include <engine/mysqlparser/listener/dml/CreateDataBaseListener.h>
#include <common/Common.h>
#include <engine/mysqlparser/listener/dml/CreateTableListener.h>
#include <engine/mysqlparser/listener/dml/UseListener.h>
#include <engine/mysqlparser/listener/dml/SetListener.h>
#include <engine/mysqlparser/listener/CheckSqlStatementListener.h>
#include <engine/mysqlparser/listener/ddl/InsertTableStatmentListener.h>
#include <engine/mysqlparser/listener/ddl/ShowDatabaseListener.h>
#include "MySqlStatement.h"



SQLParser::SQLParser() {
    this->sql_type_=-1;
}

SQLParser::~SQLParser() {

}

void CreateDataBaseParser::ParseSQL(std::string sql) {
    antlr4::ANTLRInputStream input(sql.data(), sql.size());
    parser::MySQLLexer lexers(&input);
    antlr4::CommonTokenStream tokens(&lexers);
    parser::MySQLParser parser(&tokens);
    SQLErrorListener *sqlErrorListener=new SQLErrorListener();
    parser.addErrorListener(sqlErrorListener);
    parser.removeParseListeners();
    CreateDataBaseListener *createDataBaseListener=new CreateDataBaseListener();
    antlr4::tree::ParseTreeWalker::DEFAULT.walk(createDataBaseListener,parser.create_database());
    std::string dbName=createDataBaseListener->databaseName;
    this->databaseName=dbName;
    this->sql_type_=SQLTYPE::CREATE_DATABASE;
    delete(createDataBaseListener);
    delete(sqlErrorListener);
}
std::string CreateDataBaseParser::getDataBaseName() {
    return this->databaseName;
}

std::list<std::string> CreateDataBaseParser::getDBOptions() {
    return std::list<std::string>();
}


void CreateTableParser::ParseSQL(std::string sql) {
    antlr4::ANTLRInputStream input(sql.data(), sql.size());
    parser::MySQLLexer lexers(&input);
    antlr4::CommonTokenStream tokens(&lexers);
    parser::MySQLParser parser(&tokens);

    SQLErrorListener *sqlErrorListener=new SQLErrorListener();
    parser.addErrorListener(sqlErrorListener);
    parser.removeParseListeners();
    CreateTableListener *createTableListener=new CreateTableListener();
    antlr4::tree::ParseTreeWalker::DEFAULT.walk(createTableListener,parser.create_table());
    std::string tableName=createTableListener->tableName;
    this->attrs_=createTableListener->attributes;
    this->sql_type_=SQLTYPE::CREATE_TABLE;
    this->tableName=tableName;
    delete(createTableListener);
    delete(sqlErrorListener);
}

std::string CreateTableParser::getTableName() {
    return std::__cxx11::string(this->tableName);
}

std::vector<Attribute> CreateTableParser::getAttributes() {
    return std::vector<Attribute>(this->attrs_);
}

void UseDBParser::ParseSQL(std::string sql) {
    antlr4::ANTLRInputStream input(sql.data(), sql.size());
    parser::MySQLLexer lexers(&input);
    antlr4::CommonTokenStream tokens(&lexers);
    parser::MySQLParser parser(&tokens);
    SQLErrorListener *sqlErrorListener=new SQLErrorListener();  parser.addErrorListener(sqlErrorListener);
    parser.removeParseListeners();
    UseListener *useListener=new UseListener();
    antlr4::tree::ParseTreeWalker::DEFAULT.walk(useListener,parser.sql_statement());
    std::string dbName=useListener->dbName;
    this->sql_type_=SQLTYPE ::USE;
    this->dbName=dbName;
    delete(sqlErrorListener);
    delete(useListener);
}

std::string UseDBParser::getDBName() {
    return std::__cxx11::string(this->dbName);
}

void SetParser::ParseSQL(std::string sql) {
    antlr4::ANTLRInputStream input(sql.data(), sql.size());
    parser::MySQLLexer lexers(&input);
    antlr4::CommonTokenStream tokens(&lexers);
    parser::MySQLParser parser(&tokens);
    SQLErrorListener *sqlErrorListener=new SQLErrorListener();  parser.addErrorListener(sqlErrorListener);
    parser.removeParseListeners();
    SetListener *setListener=new SetListener();
    antlr4::tree::ParseTreeWalker::DEFAULT.walk(setListener,parser.set_statement());
    int setType=setListener->getSetType();
    std::string setTypeValue=setListener->getSetTypeValue();
    this->setTypeValue=setTypeValue;
    this->setType=setType;
    delete(setListener);
    delete(sqlErrorListener);
}

std::string SetParser::getSetTypeValue() {
    return std::__cxx11::string(this->setTypeValue);
}

int SetParser::getSetType() {
    return this->setType;
}

void InsertParser::ParseSQL(std::string sql) {
    antlr4::ANTLRInputStream input(sql.data(), sql.size());
    parser::MySQLLexer lexers(&input);
    antlr4::CommonTokenStream tokens(&lexers);
    parser::MySQLParser parser(&tokens);
    SQLErrorListener *sqlErrorListener=new SQLErrorListener();  parser.addErrorListener(sqlErrorListener);
    parser.removeParseListeners();
    InsertTableStatmentListener *setListener=new InsertTableStatmentListener();
    antlr4::tree::ParseTreeWalker::DEFAULT.walk(setListener,parser.insert_statement());

    this->tableName=setListener->getTableName();
    this->insertColName=setListener->getColAttrName();
    this->values=setListener->getValue();

    delete(setListener);
    delete(sqlErrorListener);

}

void SqlCheckParser::ParseSQL(std::string sql) {
    antlr4::ANTLRInputStream input(sql.data(), sql.size());
    parser::MySQLLexer lexers(&input);
    antlr4::CommonTokenStream tokens(&lexers);
    parser::MySQLParser parser(&tokens);
    SQLErrorListener *sqlErrorListener=new SQLErrorListener(); parser.addErrorListener(sqlErrorListener);
    parser.removeParseListeners();
    CheckSqlStatementListener *setListener=new CheckSqlStatementListener();
    antlr4::tree::ParseTreeWalker::DEFAULT.walk(setListener,parser.sql_statement());

    delete(setListener);
}

void ShowHandleParser::ParseSQL(std::string sql) {
    antlr4::ANTLRInputStream input(sql.data(), sql.size());
    parser::MySQLLexer lexers(&input);
    antlr4::CommonTokenStream tokens(&lexers);
    parser::MySQLParser parser(&tokens);
    SQLErrorListener *sqlErrorListener=new SQLErrorListener();  parser.addErrorListener(sqlErrorListener);
    parser.removeParseListeners();
    ShowDatabaseListener *setListener=new ShowDatabaseListener();
    antlr4::tree::ParseTreeWalker::DEFAULT.walk(setListener,parser.administration_statement());
    this->showType=setListener->showType;
    delete(setListener);
    delete(sqlErrorListener);
}

void DescParser::ParseSQL(std::string sql) {
    antlr4::ANTLRInputStream input(sql.data(), sql.size());
    parser::MySQLLexer lexers(&input);
    antlr4::CommonTokenStream tokens(&lexers);
    parser::MySQLParser parser(&tokens);
    SQLErrorListener *sqlErrorListener=new SQLErrorListener();  parser.addErrorListener(sqlErrorListener);
    parser.removeParseListeners();
    ShowDatabaseListener *setListener=new ShowDatabaseListener();
    antlr4::tree::ParseTreeWalker::DEFAULT.walk(setListener,parser.simple_describe_statement());
    this->tableName=setListener->descTableName;
    delete(setListener);
    std::cout<<"";
    delete(sqlErrorListener);
}

//
// Created by zhukovasky on 2020/9/30.
//

#ifndef XSQL_MYSQLSTATEMENT_H
#define XSQL_MYSQLSTATEMENT_H

#include <iostream>
#include <engine/catalog_manager.h>
#include <list>
class Attribute;
//使用antlr4，解析mysql语法
class SQLParser{
protected:
    //sql 类型
    int sql_type_;

    std::string errorMsg;

public:
    SQLParser();
    ~SQLParser();
    virtual void ParseSQL(std::string sql)=0;
};

class SqlCheckParser:public SQLParser{
public:
    void ParseSQL(std::string sql) override;
};
class CreateDataBaseParser:public SQLParser{
private:
    std::string databaseName;
    std::list<std::string> dbOptionsList;
public:

    std::string getDataBaseName();

    std::list<std::string> getDBOptions();

    void ParseSQL(std::string sql) override;
};


class CreateTableParser:public SQLParser{
private:
    std::string tableName;
    std::vector<Attribute> attrs_;
public:
    void ParseSQL(std::string sql) override;

    std::string getTableName();

    std::vector<Attribute> getAttributes();
};

class ShowHandleParser:public SQLParser{
public:
    int showType;
    void ParseSQL(std::string sql) override;
};

class UseDBParser:public SQLParser{
private:
    std::string dbName;
public:
    std::string getDBName();
    void ParseSQL(std::string sql) override;
};

class SetParser:public SQLParser{
private:
    std::string setTypeValue;
    int setType;
public:
    void ParseSQL(std::string sql) override;

    std::string getSetTypeValue();

    int getSetType();
};
typedef struct {
    int data_type;
    std::string value;

} SQLValue;
class InsertParser:public SQLParser{
public:
    std::string tableName;
    std::vector<SQLValue> values;
    std::vector<std::string> insertColName;
    void ParseSQL(std::string sql) override;
};

class DescParser:public SQLParser{
public:
    std::string tableName;

    void ParseSQL(std::string sql) override;
};
#endif //XSQL_MYSQLSTATEMENT_H

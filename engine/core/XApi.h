//
// Created by zhukovasky on 2020/9/30.
//

#ifndef XSQL_XAPI_H
#define XSQL_XAPI_H


#include <engine/buffer_manager.h>
#include <engine/catalog_manager.h>
#include <engine/mysqlparser/parser/MySqlStatement.h>

class XApi {
private:
    std::string path_;
    CatalogManager* cm_;
    BufferManager* hdl_;
    std::string curr_db_;
public:
    XApi(std::string p);
    virtual ~XApi();
    void createDataBase(CreateDataBaseParser &createDataBaseParser);

    void createTable(CreateTableParser &createTableParser);

    void useDataBase(UseDBParser &useDbParser);

    std::vector<Database> showDataBases();

    std::vector<Table> showTables();

    void insertTable(InsertParser &insertParser);

    std::vector<Attribute> descTable(std::string tableName);
};


#endif //XSQL_XAPI_H

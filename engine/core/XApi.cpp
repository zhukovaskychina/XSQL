//
// Created by zhukovasky on 2020/9/30.
//

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <fstream>
#include "XApi.h"
#include <Exceptions.h>
#include <common/Exceptions.h>
#include <engine/record_manager.h>

XApi::XApi(std::string p):path_(p) {
    cm_ = new CatalogManager(p);
}

XApi::~XApi() {

}

void XApi::createDataBase(CreateDataBaseParser &createDataBaseParser) {
    std::string dbName=createDataBaseParser.getDataBaseName();
    std::cout << "Creating database: " << dbName << std::endl;
    std::string folder_name(path_ + dbName);
    boost::filesystem::path folder_path(folder_name);

    folder_path.imbue(std::locale("en_US.UTF-8"));

    if (cm_->GetDB(dbName) != NULL) {
        throw DatabaseAlreadyExistsException();
    }
    if (boost::filesystem::exists(folder_path)) {
        boost::filesystem::remove_all(folder_path);
        std::cout << "Database folder exists and deleted!" << std::endl;
    }
    boost::filesystem::create_directories(folder_path);
    std::cout << "Database folder created!" << std::endl;
    cm_->CreateDatabase(dbName);
    std::cout << "Catalog written!" << std::endl;
    cm_->WriteArchiveFile();
}

void XApi::createTable(CreateTableParser &createTableParser) {
    std::string tbName=createTableParser.getTableName();
    std::cout << "Creating table: " << tbName  << std::endl;
    if (curr_db_.length() == 0) {
        throw NoDatabaseSelectedException();
    }

    Database *db = cm_->GetDB(curr_db_);
    if (db == NULL) {
        throw DatabaseNotExistException();
    }

    if (db->GetTable(tbName) != NULL) {
        throw TableAlreadyExistsException();
    }

    std::string file_name(path_ + curr_db_ + "/" + tbName + ".records");
    boost::filesystem::path folder_path(file_name);

    if (boost::filesystem::exists(file_name)) {
        boost::filesystem::remove(file_name);
        std::cout << "Table file already exists and deleted!" << std::endl;
    }

    std::ofstream ofs(file_name);
    ofs.close();
    std::cout << "Table file created!" << std::endl;

    db->CreateTable(createTableParser);
    std::cout << "Catalog written!" << std::endl;
    cm_->WriteArchiveFile();
}

void XApi::useDataBase(UseDBParser& useDbParser) {
    std::string dbName=useDbParser.getDBName();
    Database *db = cm_->GetDB(dbName);

    if (db == NULL) {
        throw DatabaseNotExistException();
    }

    if (curr_db_.length() != 0) {
        std::cout << "Closing the old database: " << curr_db_ << std::endl;
        cm_->WriteArchiveFile();
        delete hdl_;
    }
    curr_db_ =dbName;
    hdl_ = new BufferManager(path_);
}

std::vector<Database> XApi::showDataBases() {
    std::vector<Database> dbs = cm_->dbs();
    std::cout << "DATABASE LIST:" << std::endl;
    for (unsigned int i = 0; i < dbs.size(); ++i) {
        Database db = dbs[i];
        std::cout << "\t" << db.db_name() << std::endl;
    }
    return dbs;
}

std::vector<Table> XApi::showTables() {
    if (curr_db_.length() == 0) {
        throw NoDatabaseSelectedException();
    }

    Database *db = cm_->GetDB(curr_db_);
    if (db == NULL) {
        throw DatabaseNotExistException();
    }
    std::cout << "CURRENT DATABASE: " << curr_db_ << std::endl;
    std::cout << "TABLE LIST:" << std::endl;
    std::vector<Table> tbList;
    for (int i=0; i<db->tbs().size(); ++i) {
        Table tb = db->tbs()[i];
        std::cout << "\t" << tb.tb_name() << std::endl;
        tbList.push_back(tb);
    }
    return tbList;
}

void XApi::insertTable(InsertParser &insertParser) {


    RecordManager *rm = new RecordManager(cm_, hdl_, curr_db_);
    rm->Insert(insertParser);
    delete rm;

}

std::vector<Attribute> XApi::descTable(std::string tbName) {
    if (curr_db_.length() == 0) {
        throw NoDatabaseSelectedException();
    }

    Database *db = cm_->GetDB(curr_db_);
    if (db == NULL) {
        throw DatabaseNotExistException();
    }
    Table *tb = db->GetTable(tbName);
    if(tb==NULL){
        throw TableNotExistException();
    }
    std::vector<Attribute> rs=tb->getAttribute();

    return rs;
}

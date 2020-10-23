//
// Created by zhukovasky on 2020/9/30.
//

#include <utils/ParseUtils.h>
#include <common/Exceptions.h>
#include "SqlInterpret.h"
#include <iostream>
#include <mysql_protocol/response/SelectDatabaseResponse.h>
#include <mysql_protocol/response/ErrorResponse.h>
#include <mysql_protocol/response/OkResponse.h>
#include <mysql_protocol/response/ShowDatabaseResponse.h>
#include <mysql_protocol/response/ShowTableResponse.h>
#include <mysql_protocol/response/ShowDescribeTableResponse.h>
using namespace std;
void SQLInterpret::Run() {

}

SQLInterpret::SQLInterpret() {
    string p = string(getenv("HOME")) + "/XDB/";
    this->xapi = new XApi(p);
}

SQLInterpret::~SQLInterpret() {
    delete(this->xapi);
}

void SQLInterpret::ExecSQL(std::string statement,SessionConnection &sessionConnection) {
    std::string errorMsg="";
    //解析SQLｔｙｐｅ
    int parsedStmtType=ParseUtils::parse(statement);
    try {

        SqlCheckParser *sqlCheckParser=new SqlCheckParser();
        sqlCheckParser->ParseSQL(statement);
        delete(sqlCheckParser);

        switch (parsedStmtType){

            case OTHER:{
                SqlCheckParser *sqlCheckParser=new SqlCheckParser();
                sqlCheckParser->ParseSQL(statement);
                delete(sqlCheckParser);
                break;
            }
            case BEGIN:{
                break;
            }
            case COMMIT:{
                break;
            }
            case DELETE:{
                break;
            }
            case DESC:{
                DescParser *descParser=new DescParser();
                descParser->ParseSQL(statement);
                std::vector<Attribute> atts=this->xapi->descTable(descParser->tableName);
                ShowDescribeTableResponse::response(sessionConnection.getConnectionPtr(),atts);
                break;
            }
            case INSERT:{
                InsertParser *insertParser=new InsertParser();
                insertParser->ParseSQL(statement);

                this->xapi->insertTable(*insertParser);
                break;
            }
            case REPLACE:{
                break;
            }
            case ROLLBACK:{
                break;
            }
            case SELECT:{
                break;
            }
            case SET:{


                break;
            }
            case SHOW:{
                ShowHandleParser *showHandleParser=new ShowHandleParser();
                showHandleParser->ParseSQL(statement);
                int showType=showHandleParser->showType;
                switch (showType){
                    case SHOWTYPEENUMS ::DATABASE:{
                        std::vector<Database> databaseResult=this->xapi->showDataBases();
                        ShowDatabaseResponse::response(sessionConnection.getConnectionPtr(),databaseResult);
                        break;
                    }
                    case SHOWTYPEENUMS ::TABLES:{
                        std::vector<Table> tableResult=this->xapi->showTables();
                        ShowTableResponse::response(sessionConnection.getConnectionPtr(),tableResult);
                        break;
                    }
                }
                break;
            }
            case START:{
                break;
            }
            case UPDATE:{
                break;
            }
            case KILL:{
                break;
            }
            case SAVEPOINT:{
                break;
            }
            case USE:{
                UseDBParser *useDbParser=new UseDBParser();
                useDbParser->ParseSQL(statement);
                this->xapi->useDataBase(*useDbParser);
                sessionConnection.setSchema(useDbParser->getDBName());
                OkResponse::responseOK(sessionConnection.getConnectionPtr());
                delete(useDbParser);
                break;
            }
            case EXPLAIN:{
                break;
            }
            case KILL_QUERY:{
                break;
            }
            case CREATE_DATABASE:{
                CreateDataBaseParser *createDataBaseParser=new CreateDataBaseParser();
                createDataBaseParser->ParseSQL(statement);
                this->xapi->createDataBase(*createDataBaseParser);
                OkResponse::responseOK(sessionConnection.getConnectionPtr());
                delete(createDataBaseParser);
                break;
            }
            case RELOAD:{
                break;
            }
            case CREATE_TABLE:{
                CreateTableParser *createTableParser=new CreateTableParser();
                createTableParser->ParseSQL(statement);
                this->xapi->createTable(*createTableParser);
                OkResponse::responseOK(sessionConnection.getConnectionPtr());
                delete(createTableParser);

                break;
            }
            default:{
                SqlCheckParser *sqlCheckParser=new SqlCheckParser();
                sqlCheckParser->ParseSQL(statement);
                delete(sqlCheckParser);
                break;
            }
        }
    }
    catch (SyntaxParseException& e){
        ErrorResponse::response(sessionConnection.getConnectionPtr(),e.msg);
        return;
    }
    catch (SyntaxErrorException& e) {
        cerr << "Syntax Error!" << endl;
        errorMsg.append("Syntax Error!\n");
    } catch (NoDatabaseSelectedException& e) {
        cerr << "No database selected!" << endl;
        errorMsg.append("No database selected!");
        errorMsg.append("Syntax Error!");
    } catch (DatabaseNotExistException& e) {
        cerr << "Database doesn't exist!" << endl;
        errorMsg.append("Database doesn't exist!");
        errorMsg.append("Syntax Error!");
    } catch (DatabaseAlreadyExistsException& e) {
        cerr << "Database already exists!" << endl;
        errorMsg.append("Database already exists!");
        errorMsg.append("Syntax Error!");
    } catch (TableNotExistException& e) {
        cerr << "Table doesn't exist!" << endl;
        errorMsg.append("Syntax Error!");
    } catch (OneIndexEachTableException& e) {
        cerr << "Each table could only have one index!" << endl;
        errorMsg.append("Syntax Error!");
    } catch (BPlusTreeException& e) {
        cerr << "BPlusTree exception!" << endl;
        errorMsg.append("Syntax Error!");
    } catch (TableAlreadyExistsException& e) {
        cerr << "Table already exists!" << endl;
        errorMsg.append("Syntax Error!");
    } catch (IndexAlreadyExistsException& e) {
        cerr << "Index already exists!" << endl;
        errorMsg.append("Syntax Error!");
    } catch (IndexNotExistException& e) {
        cerr << "Index doesn't exist!" << endl;
        errorMsg.append("Syntax Error!");
    } catch (IndexMustBeCreatedOnPKException& e) {
        cerr << "Index must be created on primary key!" << endl;
        errorMsg.append("Syntax Error!");
    } catch (PrimaryKeyConflictException& e) {
        cerr << "Primary key conflicts!" << endl;
        errorMsg.append("Syntax Error!");
    }
    if(!errorMsg.empty()){
        ErrorResponse::response(sessionConnection.getConnectionPtr(),errorMsg);
    }

}

void SQLInterpret::checkSQLType() {

}

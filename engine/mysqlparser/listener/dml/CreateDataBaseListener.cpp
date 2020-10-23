//
// Created by zhukovasky on 2020/9/30.
//

#include <utils/StringUtils.h>
#include "CreateDataBaseListener.h"


void CreateDataBaseListener::enterCreate_database(parser::MySQLParser::Create_databaseContext *context) {
    if(!context->children.empty()){
        parser::MySQLParser::Id_Context *idContext=context->id_();
        if(idContext!=NULL){
            std::string dbName=idContext->getText();
            std::string replaceName=dbName;
            if(Utils::StringUtils::startsWith(dbName,"`")){
                replaceName=Utils::StringUtils::replaceAll(dbName,"`","");
            }
            this->databaseName=replaceName;
        }

        parser::MySQLParser::If_not_existsContext *if_not_existsContext=context->if_not_exists();
        if(if_not_existsContext!=NULL){
            if_not_existsContext->getText();
        }
    }
}

void CreateDataBaseListener::enterCreate_database_option(parser::MySQLParser::Create_database_optionContext *context) {
    MySQLParserBaseListener::enterCreate_database_option(context);
}

void CreateDataBaseListener::exitCreate_database_option(parser::MySQLParser::Create_database_optionContext *context) {
    MySQLParserBaseListener::exitCreate_database_option(context);
}

void CreateDataBaseListener::exitCreate_database(parser::MySQLParser::Create_databaseContext *context) {
    MySQLParserBaseListener::exitCreate_database(context);
}

void CreateDataBaseListener::visitErrorNode(antlr4::tree::ErrorNode *node) {
    MySQLParserBaseListener::visitErrorNode(node);
}

CreateDataBaseListener::CreateDataBaseListener() {

}

CreateDataBaseListener::~CreateDataBaseListener() {

}

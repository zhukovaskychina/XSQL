//
// Created by zhukovasky on 2020/10/14.
//

#include <common/Common.h>
#include "ShowDatabaseListener.h"

void ShowDatabaseListener::enterShowCreateDb(parser::MySQLParser::ShowCreateDbContext *context) {
    antlr4::tree::TerminalNode *dataBaseTerminal = context->DATABASE();
    if(dataBaseTerminal!= nullptr){
        std::string text=dataBaseTerminal->getText();
        std::cout<<text<<std::endl;
    }
    MySQLParserBaseListener::enterShowCreateDb(context);
}

void ShowDatabaseListener::enterShowCreateUser(parser::MySQLParser::ShowCreateUserContext *context) {
    MySQLParserBaseListener::enterShowCreateUser(context);
}

void ShowDatabaseListener::enterShowEngine(parser::MySQLParser::ShowEngineContext *context) {
    MySQLParserBaseListener::enterShowEngine(context);
}

void ShowDatabaseListener::enterShowIndexes(parser::MySQLParser::ShowIndexesContext *context) {
    MySQLParserBaseListener::enterShowIndexes(context);
}

void ShowDatabaseListener::enterShowFromschemaFilter(parser::MySQLParser::ShowFromschemaFilterContext *ctx) {
    antlr4::tree::TerminalNode *tableTerminal = ctx->TABLES();
    if(tableTerminal!= nullptr){
        this->showType=SHOWTYPEENUMS ::TABLES;
    }

}

void ShowDatabaseListener::enterAdministration_statement(parser::MySQLParser::Administration_statementContext *ctx) {
    ctx->show_statement();
    MySQLParserBaseListener::enterAdministration_statement(ctx);
}

void ShowDatabaseListener::enterShowObjWithFilter(parser::MySQLParser::ShowObjWithFilterContext *ctx) {
    antlr4::tree::TerminalNode *dataBaseTerminalNode = ctx->DATABASES();

    if(dataBaseTerminalNode!= nullptr){
        this->showType=SHOWTYPEENUMS ::DATABASE;
    }
//    delete(dataBaseTerminalNode);
    //MySQLParserBaseListener::enterShowObjWithFilter(ctx);
}

void
ShowDatabaseListener::enterSimple_describe_statement(parser::MySQLParser::Simple_describe_statementContext *context) {
    parser::MySQLParser::Table_nameContext *tbCtx = context->table_name();
    if(tbCtx!= nullptr){
       std::string tbName= tbCtx->getText();
       this->descTableName=tbName;
    }
    MySQLParserBaseListener::enterSimple_describe_statement(context);
}

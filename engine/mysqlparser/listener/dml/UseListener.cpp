//
// Created by zhukovasky on 2020/10/1.
//

#include "UseListener.h"

void UseListener::enterUtility_statement(parser::MySQLParser::Utility_statementContext *ctx) {
    parser::MySQLParser::Use_statementContext *useStatementContext = ctx->use_statement();

    parser::MySQLParser::Simple_idContext *simpleIdCtx = useStatementContext->id_()->simple_id();

    std::string dbName=simpleIdCtx->getText();

    this->dbName=dbName;

  //  delete simpleIdCtx;
  //  delete useStatementContext;
}

UseListener::UseListener() {

}

UseListener::~UseListener() {

}

void UseListener::exitUtility_statement(parser::MySQLParser::Utility_statementContext *context) {
   // context->exitRule(this);
    //MySQLParserBaseListener::exitUtility_statement(context);

}

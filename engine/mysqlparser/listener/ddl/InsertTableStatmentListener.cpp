//
// Created by zhukovasky on 2020/9/29.
//

#include "InsertTableStatmentListener.h"
using namespace parser;
void InsertTableStatmentListener::enterInsert_statement(parser::MySQLParser::Insert_statementContext *ctx) {
    parser::MySQLParser::Table_nameContext *tableNameContext = ctx->table_name();
    this->tableName=tableNameContext->getText();
    parser::MySQLParser::Insert_statement_valueContext *insertValueCtx = ctx->insert_statement_value();
    const std::vector<MySQLParser::Id_listContext *> &idlist = ctx->id_list();

    if(idlist.empty()){

    }else{
        for (int i = 0; i < idlist.size(); ++i) {
            MySQLParser::Id_listContext * id_ = idlist.at(i);
            const std::vector<parser::MySQLParser::Id_Context *> &_id_list = id_->id_();
            for (int j = 0; j < _id_list.size(); ++j) {
                std::string idText=_id_list.at(j)->getText();
                std::cout<<"idText:-"<<idText<<std::endl;
                this->colAttrName.push_back(idText);
            }
        }
    }

    const std::vector<parser::MySQLParser::Expression_listContext *> &expressList = insertValueCtx->expression_list();
    for (int i = 0; i < expressList.size(); ++i) {
        std::string values=expressList.at(0)->getText();
        const std::vector<parser::MySQLParser::ExpressionContext *> &exprList = expressList.at(i)->expression();
        for (int j = 0; j < exprList.size(); ++j) {
            std::string exprValue=exprList.at(j)->getText();
            std::cout<<exprValue<<std::endl;
            SQLValue sqlValue;
            sqlValue.value=exprValue;
            this->value_.push_back(sqlValue);
            malloc(sizeof(sqlValue));
        }
    }
    for (int j = 0; j < idlist.size(); ++j) {

        std::string idValue=idlist.at(j)->getText();
        idlist.at(j)->id_();
        std::cout<<idValue<<std::endl;
    }
}

void InsertTableStatmentListener::enterInsert_statement_value(parser::MySQLParser::Insert_statement_valueContext *ctx) {


    MySQLParserBaseListener::enterInsert_statement_value(ctx);

}

const std::string &InsertTableStatmentListener::getTableName() const {
    return tableName;
}

const std::vector<std::string> &InsertTableStatmentListener::getColAttrName() const {
    return colAttrName;
}

const std::vector<SQLValue> &InsertTableStatmentListener::getValue() const {
    return value_;
}

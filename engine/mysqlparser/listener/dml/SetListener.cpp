//
// Created by zhukovasky on 2020/10/1.
//

#include <common/Common.h>
#include "SetListener.h"

void SetListener::enterSetNames(parser::MySQLParser::SetNamesContext *ctx) {
    std::string charsetName=ctx->charset_name()->getText();
    this->setType=SETTYPE::NAMES;
    this->setTypeValue=charsetName;
}

void SetListener::enterSetTransaction(parser::MySQLParser::SetTransactionContext *ctx) {
    MySQLParserBaseListener::enterSetTransaction(ctx);
    std::string transactionValue=ctx->set_transaction_statement()->getText();
    this->setType=SETTYPE ::TRANSACTION;
    this->setTypeValue=transactionValue;
}

void SetListener::enterSetAutocommit(parser::MySQLParser::SetAutocommitContext *ctx) {
    MySQLParserBaseListener::enterSetAutocommit(ctx);
    std::string autoCommitValue=ctx->set_autocommit_statement()->getText();
    this->setType=SETTYPE ::AUTOCOMMIT;
    this->setTypeValue=autoCommitValue;
}

std::string SetListener::getSetTypeValue() {
    return std::__cxx11::string(this->setTypeValue);
}

int SetListener::getSetType() {
    return this->setType;
}

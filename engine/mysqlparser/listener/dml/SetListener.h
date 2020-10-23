//
// Created by zhukovasky on 2020/10/1.
//

#ifndef XSQL_SETLISTENER_H
#define XSQL_SETLISTENER_H


#include <engine/sqlparser/MySQLParserBaseListener.h>

class SetListener : public parser::MySQLParserBaseListener  {
private:
    int setType;
    std::string setTypeValue;
public:
     void enterSetNames(parser::MySQLParser::SetNamesContext * ctx) override;

     void enterSetTransaction(parser::MySQLParser::SetTransactionContext * ctx) override;

     void enterSetAutocommit(parser::MySQLParser::SetAutocommitContext * ctx) override;


     int getSetType();

     std::string getSetTypeValue();
};


#endif //XSQL_SETLISTENER_H

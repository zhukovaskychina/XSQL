//
// Created by zhukovasky on 2020/9/30.
//

#include <utils/StringUtils.h>
#include "CreateTableListener.h"

void CreateTableListener::enterColCreateTable(parser::MySQLParser::ColCreateTableContext *context) {
    parser::MySQLParser::Table_nameContext *tbContext = context->table_name();
    std::string tbName = tbContext->getText();
    parser::MySQLParser::If_not_existsContext *ifContxt = context->if_not_exists();
    if (ifContxt != NULL) {
        std::string ifExistsString = ifContxt->getText();
    }


    this->tableName = tbName;
    this->ifNotExists = false;
    delete ifContxt;
}

void CreateTableListener::enterColumnDefinition(parser::MySQLParser::ColumnDefinitionContext *ctx) {
    MySQLParserBaseListener::enterColumnDefinition(ctx);
    parser::MySQLParser::Column_definitionContext *columnDefinitions = ctx->column_definition();

    std::string columnName = ctx->id_()->getText();
    Attribute attribute;
    attribute.set_attr_name(columnName);
    parser::MySQLParser::Column_definitionContext *cldfs = ctx->column_definition();
    int childrenSize = cldfs->children.size();
    if (childrenSize > 0) {


        std::vector<antlr4::tree::ParseTree *> dc = cldfs->data_type()->children;
        if (dc.size() > 0) {
            std::string dataType = cldfs->data_type()->children.at(0)->getText();
            attribute.set_data_type_length(cldfs->data_type()->getText());
            int dataTypeInt=this->processDataType(dataType);
            attribute.set_data_type(dataTypeInt);
            int pureSize=cldfs->data_type()->children.size();

            if (pureSize> 1) {
                std::vector<antlr4::tree::ParseTree *> dcclength=cldfs->data_type()->children.at(1)->children;
                if(dcclength.size()>0){
                    std::string length = cldfs->data_type()->children.at(1)->children.at(1)->getText();
                    std::cout << length << std::endl;
                    int integerLength = Utils::StringUtils::convertStringToInteger(length);
                    attribute.set_length(integerLength);
                }else{
                    int rl=-1;
                    switch (dataTypeInt){
                        case COLUMNENUMS ::FIELD_TYPE_TINY:{
                            rl=1;
                            break;
                        }
                        case COLUMNENUMS ::FIELD_TYPE_SHORT:{
                            rl=2;
                            break;
                        }
                        case COLUMNENUMS ::FIELD_TYPE_INT24:{
                            rl=4;
                            break;
                        }
                        case COLUMNENUMS ::FIELD_TYPE_FLOAT:{
                            rl=4;
                            break;
                        }
                    }
                    attribute.set_length(rl);
                }

            }
        }
    } else {
        //int，long,blob 类型
        std::string dataType = cldfs->data_type()->getText();
        attribute.set_data_type(this->processDataType(dataType));
    }

    this->attributes.push_back(attribute);

}

void CreateTableListener::enterColumn_definition(parser::MySQLParser::Column_definitionContext *ctx) {

    MySQLParserBaseListener::enterColumn_definition(ctx);
}
/**
 *
 *     FIELD_TYPE_DECIMAL = 0,
    FIELD_TYPE_TINY = 1,
    FIELD_TYPE_SHORT = 2,
    FIELD_TYPE_LONG = 3,
    FIELD_TYPE_FLOAT = 4,
    FIELD_TYPE_DOUBLE = 5,
    FIELD_TYPE_NULL = 6,
    FIELD_TYPE_TIMESTAMP = 7,
    FIELD_TYPE_LONGLONG = 8,
    FIELD_TYPE_INT24 = 9,
    FIELD_TYPE_DATE = 10,
    FIELD_TYPE_TIME = 11,
    FIELD_TYPE_DATETIME = 12,
    FIELD_TYPE_YEAR = 13,
    FIELD_TYPE_NEWDATE = 14,
    FIELD_TYPE_VARCHAR = 15,
    FIELD_TYPE_BIT = 16,
    FIELD_TYPE_NEW_DECIMAL = 246,
    FIELD_TYPE_ENUM = 247,
    FIELD_TYPE_SET = 248,
    FIELD_TYPE_TINY_BLOB = 249,
    FIELD_TYPE_MEDIUM_BLOB = 250,
    FIELD_TYPE_LONG_BLOB = 251,
    FIELD_TYPE_BLOB = 252,
    FIELD_TYPE_VAR_STRING = 253,
    FIELD_TYPE_STRING = 254,
    FIELD_TYPE_GEOMETRY = 255,
 * **/
int CreateTableListener::processDataType(std::string dataType) {
    std::string upperType=Utils::StringUtils::toUpper(dataType);
    if(upperType=="VARCHAR"){
        return COLUMNENUMS ::FIELD_TYPE_VARCHAR;
    }
    if(upperType=="CHAR"){
        return COLUMNENUMS ::FIELD_TYPE_VARCHAR;
    }


    if(upperType=="INT"){
        return COLUMNENUMS ::FIELD_TYPE_INT24;
    }
    if(upperType=="BIGINT"){
        return COLUMNENUMS ::FIELD_TYPE_LONG;
    }
    if(upperType=="SMALLINT"){
        return COLUMNENUMS ::FIELD_TYPE_SHORT;
    }
    if(upperType=="TINYINT"){
        return COLUMNENUMS ::FIELD_TYPE_TINY;
    }
    if(upperType=="DATE"){
       return COLUMNENUMS ::FIELD_TYPE_DATE;
    }
    if(upperType=="YEAR"){
        return COLUMNENUMS ::FIELD_TYPE_YEAR;
    }
    if(upperType=="DATETIME"){
        return COLUMNENUMS ::FIELD_TYPE_DATETIME;
    }
    if(upperType=="TIMESTAMP"){
        return COLUMNENUMS ::FIELD_TYPE_TIMESTAMP;
    }

    if(upperType=="TIME"){
        return COLUMNENUMS ::FIELD_TYPE_TIME;
    }
    return -1;
}

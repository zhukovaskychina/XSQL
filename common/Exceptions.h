//
// Created by zhukovasky on 2020/10/1.
//

#ifndef XSQL_EXCEPTIONS_H
#define XSQL_EXCEPTIONS_H

#include <iostream>

#include <exception>



class SyntaxParseException:public std::exception{
public:
    std::string msg;
public:
    SyntaxParseException(std::string msg):msg( msg) {
        this->msg;
    }
    ~SyntaxParseException() throw () {
    }

    virtual const char* what() const throw () {
        return msg.c_str();
    }

};

class SyntaxErrorException : public std::exception {


};

class NoDatabaseSelectedException : public std::exception {

};

class DatabaseNotExistException : public std::exception {

};

class DatabaseAlreadyExistsException : public std::exception {

};

class TableNotExistException : public std::exception {

};

class TableAlreadyExistsException : public std::exception {

};

class IndexAlreadyExistsException : public std::exception {

};

class IndexNotExistException : public std::exception {

};

class OneIndexEachTableException : public std::exception {

};

class BPlusTreeException : public std::exception {

};

class IndexMustBeCreatedOnPKException : public std::exception {

};

class PrimaryKeyConflictException : public std::exception {

};



#endif //XSQL_EXCEPTIONS_H

//
// Created by zhukovasky on 2020/9/30.
//

#ifndef XSQL_SQLERRORLISTENER_H
#define XSQL_SQLERRORLISTENER_H


#include <libs/antlr4-cpp-runtime-4.7.2/src/ANTLRErrorListener.h>

class SQLErrorListener : public antlr4::ANTLRErrorListener{
public:
    SQLErrorListener();

    ~SQLErrorListener() override;

    void
    syntaxError(antlr4::Recognizer *recognizer, antlr4::Token *offendingSymbol, size_t line, size_t charPositionInLine,
                const std::string &msg, std::exception_ptr e) override;

    void reportAmbiguity(antlr4::Parser *recognizer, const antlr4::dfa::DFA &dfa, size_t startIndex, size_t stopIndex,
                         bool exact, const antlrcpp::BitSet &ambigAlts, antlr4::atn::ATNConfigSet *configs) override;

    void reportAttemptingFullContext(antlr4::Parser *recognizer, const antlr4::dfa::DFA &dfa, size_t startIndex,
                                     size_t stopIndex, const antlrcpp::BitSet &conflictingAlts,
                                     antlr4::atn::ATNConfigSet *configs) override;

    void reportContextSensitivity(antlr4::Parser *recognizer, const antlr4::dfa::DFA &dfa, size_t startIndex,
                                  size_t stopIndex, size_t prediction, antlr4::atn::ATNConfigSet *configs) override;
};


#endif //XSQL_SQLERRORLISTENER_H

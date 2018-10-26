#ifndef _PARSER_H
#define _PARSER_H

#include "lexer.h"

class Parser {
public:
    Parser(Lexer& lexer): lexer(lexer) {}
    void parse();

private:
    Lexer& lexer;
    Token token;
    void input();
    void stmt_list();
    void P_stmt_list();
    void stmt();
    void P_stmt();
    void expr();
    void P_expr();
    void term();
    void P_term();
    void factor();
};

#endif

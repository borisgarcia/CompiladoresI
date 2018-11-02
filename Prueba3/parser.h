#ifndef _PARSER_H
#define _PARSER_H

#include "lexer.h"
#include <deque>

class Parser {
public:
    Parser(Lexer& lexer): lexer(lexer) {}
    void parse();

private:
    Lexer& lexer;
    Token token;

    std::deque<Token> Table(Token term , Token noTerm);


private:
    std::deque<Token> stack;
    std::deque<Token> input;
    std::deque<Token> prod1 = {Token::stmt_list};
    std::deque<Token> prod2 = {Token::stmt,Token::P_stmt_list};
    std::deque<Token> prod3 = {Token::Semicolon,Token::stmt,Token::P_stmt_list};
    std::deque<Token> prod4 = {Token::Ident,Token::OpAssign,Token::expr};
    std::deque<Token> prod5 = {Token::KwPrint,Token::expr};
    std::deque<Token> prod6 = {Token::term,Token::P_expr};
    std::deque<Token> prod7 = {Token::OpAdd,Token::term,Token::P_expr};
    std::deque<Token> prod8 = {Token::factor,Token::P_term};
    std::deque<Token> prod9 = {Token::OpMult,Token::factor,Token::P_term};
    std::deque<Token> prod10 = {Token::Ident};
    std::deque<Token> prod11 = {Token::Number};
    std::deque<Token> prod12 = {Token::OpenPar,Token::expr,Token::ClosePar};
    std::deque<Token> epsilon = {Token::Epsilon};
    std::deque<Token> prodFin = {Token::Null};
};

#endif

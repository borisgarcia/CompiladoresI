#include "parser.h"

void Parser::parse() 
{
    token = lexer.getNextToken();
    input();
}

void Parser::input()
{
    stmt_list();
}
void Parser::stmt_list()
{
    stmt();
    P_stmt_list();
}

void Parser::P_stmt_list()
{
    if(token==Token::Semicolon)
    {
        token = lexer.getNextToken();
        stmt();
        P_stmt_list();
    }
    else
    {
        //Nada
    }

}

void Parser::stmt()
{
    if(token==Token::Ident)
    {
        token = lexer.getNextToken();
        if(token == Token::OpAssign)
        {
            token = lexer.getNextToken();
            expr();
        }
    }
    else if(token == Token::KwPrint)
    {
        token = lexer.getNextToken();
        expr();
    }
    else
    {
        //Nada
    }
}

void Parser::expr()
{
    term();
    P_expr();
}

void Parser::P_expr()
{
    if(token == Token::OpAdd)
    {
        token = lexer.getNextToken();
        term();
        P_expr();
    }
    else
    {
        //Nada
    }
}
void Parser::term()
{
    factor();
    P_term();
}

void Parser::P_term()
{
    if(token == Token::OpMult)
    {
        token = lexer.getNextToken();
        factor();
        P_term();
    }
    else
    {
        //Nada
    }
}

void Parser::factor()
{
    if(token == Token::Ident)
    {
        token = lexer.getNextToken();
    }
    else if(token == Token::Number)
    {
        token = lexer.getNextToken();
    }
    else if(token == Token::OpenPar)
    {
        token = lexer.getNextToken();
        expr();
        if(token == Token::ClosePar)
        {
            token = lexer.getNextToken();
        }
        else
        {
            std::cout << "Error" << '\n';
            throw std::invalid_argument( "\nSintax Error" );
        }
    }
    else
    {
        std::cout << "Error" << '\n';
        throw std::invalid_argument( "\nSintax Error" );
    }
}
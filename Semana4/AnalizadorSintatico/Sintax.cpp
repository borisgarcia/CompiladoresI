#include "Sintax.h"

void Sintax::initParser()
{
    resp = 0;
    currVal = 0;
    cont = 0;
    token = lexer.getNextToken();
    int final_ = E();
    token = lexer.getNextToken();
    if(token != Token::Eof)
    {
        throw std::invalid_argument( "\nSintax Error" );
    }
    std::cout <<'\n'<< final_ << '\n';
}

int Sintax::E()
{
    int x;
    x = T();
    while(token == Token::Add)
    {
        std::cout << "+";
        token = lexer.getNextToken();
        x += T();
    }
    
    return x;
}

int Sintax::T()
{
    std::cout << "T";
    int x = 1;
    x = F();
    while(token == Token::Multi)
    {
        std::cout << "*";
        token = lexer.getNextToken();
        x =  F() * x;
    }
    return x;
}

int Sintax::F()
{
    std::cout << "F->";
    currVal = 0;
    if(token == Token::Number)
    {
        currVal = std::stoi(lexer.getText());
        token = lexer.getNextToken();
        std::cout << currVal;
        return currVal;
    }
    else if(token == Token::OpenPar)
    {
        std::cout << "(";
        token = lexer.getNextToken();
        currVal = E();
        std::cout << "E = " << currVal;
        if(token!=Token::ClosePar)
        {
            throw std::invalid_argument( "\nerror: expected ')'" );
        }
        std::cout << ")";
        token = lexer.getNextToken();

    }
    else
    {
        throw std::invalid_argument( "\nSintax Error" );
    }
    return currVal;
}
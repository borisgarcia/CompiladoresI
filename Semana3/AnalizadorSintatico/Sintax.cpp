#include "Sintax.h"

void Sintax::initParser()
{
    token = lexer.getNextToken();
    E();
}

void Sintax::E()
{
    //std::cout << "E" << '\n';
    T();
    Ep();
}

void Sintax::Ep()
{
    //std::cout << "Ep" << '\n';
    if(token == Token::Add)
    {
        token = lexer.getNextToken();
        T();
        Ep();
    }
    else
    {
        //Nada;
    }
}

void Sintax::T()
{
    //std::cout << "T" << '\n';
    F();
    Tp();
}

void Sintax::Tp()
{
    //std::cout << "Tp" << '\n';
    if(token == Token::Multi)
    {
        token = lexer.getNextToken();
        F();
        Tp();
    }
    else
    {
        //Nada;
    }
}

void Sintax::F()
{
    //std::cout << "F" << '\n';
    //std::cout << "Hi" << '\n';
    if(token == Token::OpenPar)
    {
        //std::cout << "Hi2" << '\n';
        token = lexer.getNextToken();
        E();
        
        if(token!=Token::ClosePar)
        {
            throw std::invalid_argument( "\nerror: expected ')'" );
        }
    }
    else if(token == Token::Number)
    {
        token = lexer.getNextToken();
    }
    else
    {
        throw std::invalid_argument( "\nUnexpected" );
    }

}




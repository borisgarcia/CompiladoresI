#include "Sintax.h"

void Sintax::initParser()
{
    token = lexer.getNextToken();
    E();
    token = lexer.getNextToken();
    if(token != Token::Eof)
    {
        throw std::invalid_argument( "\nSintax Error" );
    }
}

int Sintax::E()
{
    std::cout << "E()";
    T();
    Ep();
    return 0;
}

int Sintax::Ep()
{
    std::cout << "Ep()";
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
    return 0;
}

int Sintax::T()
{
    int x,y;
    std::cout << "T()";
    x = F();
    y = Tp();
    return x * y;
}

int Sintax::Tp()
{
    int x=1;
    int y=0;
    std::cout << "Tp()";
    if(token == Token::Multi)
    {
        token = lexer.getNextToken();
        y = F();
        std::cout << "Res" << y <<'\n';
        Tp();
    }
    else
    {
        //Nada;
    }
    
    return y;
}

int Sintax::F()
{
    std::cout << "F()";
    int x;
    if(token == Token::OpenPar)
    {
        token = lexer.getNextToken();
        x = E();
        
        if(token!=Token::ClosePar)
        {
            throw std::invalid_argument( "\nerror: expected ')'" );
        }
    }
    else if(token == Token::Number)
    {
        //std::cout << lexer.getText()<< '\n';
        x = std::stoi(lexer.getText());
        token = lexer.getNextToken();
        return x;
    }
    else
    {
        throw std::invalid_argument( "\nSintax Error" );
    }
    return 0;
}
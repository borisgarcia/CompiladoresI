#include "Parser.h"

void Parser::initParser()
{
    ExprList all;
    Expr a;
    ObtenerToken();
    while(1)
    {
        a = E();
        if(a != nullptr)
            all.push_back(std::move(a));
        if(token == Token::Eof)break;
    }
    for(auto const& x: all)
        std::cout << "Expression: " << x->toString() <<" = " << x->Eval() << '\n';
          
    
}

Expr Parser::E()
{
    std::cout << "E" << '\n';
    Expr a = Ep();

    if(token == Token::Semicolon)
    {
        ObtenerToken();
    }
    else if(token == Token::Unknown)
    {
        std::cerr<<"Unknown Token! \n";
        exit(1);
    }
    else
    {
        std::cerr<<"Expected ; Token! \n";
        exit(1);
    }
    return std::move(a);
}

Expr Parser::Ep()
{
    std::cout << "Ep" << '\n';
    Expr a = T();
    Expr b;
    Token curr;
    while(token == Token::Add || token == Token::Sub)
    {
        curr = token;
        ObtenerToken();
        b = T();
        if(curr == Token::Add) 
        {
            a = std::make_unique<AddExpression>(std::move(a), std::move(b));
            continue;
        }
        if(curr == Token::Sub) 
        {
            a = std::make_unique<SubExpression>(std::move(a), std::move(b));
            continue;
        }
    }
    return std::move(a);
}

Expr Parser::T()
{
    std::cout << "T" << '\n';
    Expr x = F();
    Token curr;
    Expr y;
    while(token == Token::Multi || token == Token::Div)
    {
        curr = token;
        ObtenerToken();
        y = F();
        if(curr == Token::Multi) 
        {
            x = std::make_unique<MultiExpression>(std::move(x), std::move(y));
            continue;
        }
        if(curr == Token::Div) 
        {
            x = std::make_unique<DivExpression>(std::move(x), std::move(y));
            continue;
        }
    }
    return std::move(x);
}

Expr Parser::F()
{
    std::cout << "F" << '\n';
    if(token == Token::Number)
    {
        Expr a = std::make_unique<numberExpression>(strtol(lexer.tk.c_str(), NULL, 10)) ;
        ObtenerToken();
        return std::move(a);
    }
    if(token == Token::Ident)
    {
        ObtenerToken();
    }
    else if(token == Token::OpenPar)
    {
        ObtenerToken();
        Expr b = E();
        if(token==Token::ClosePar)
        {
            ObtenerToken();
            return std::move(b);    
        }
        else
        {
            std::cerr<<"Expected ) before '" << lexer.tk<<"'\n";
            exit(1);
        }
    }
    else
    {
        std::cerr << "Unexpected Token: " << lexer.tk <<"\n";
        exit(1);
    }
}
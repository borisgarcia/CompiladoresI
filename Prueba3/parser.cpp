#include "parser.h"

void Parser::parse() {
    while(1)
    {
        token = lexer.getNextToken();
        if(token == Token::Eof)break;
        else if(token == Token::Unknown) 
            throw std::invalid_argument( "\nSintax Error");
        input.push_back(token);
    }
    stack.push_front(Token::input);
    stack.push_front(Token::Top);
    input.push_back(Token::Top);
    Token currStack, currInput;
    std::deque<Token> temp;
    
    while (1)
    {
        if(input.front() == Token::Top && stack.back()==Token::Top)break;
        
        currStack = stack.back();
        if(currStack == Token::Null)
            throw std::invalid_argument("Sintax Error");
        currInput = input.front();
        if(currStack == currInput)
        {
            stack.pop_back();
            input.pop_front();
            continue;
        }
        else if(currStack == Token::Epsilon)
        {
            stack.pop_back();    
            continue;
        }
        stack.pop_back();
        temp = Table(currInput,currStack);
        for(int a = temp.size();a>0;a--)
            stack.push_back(temp.at(a-1));
    }
}


std::deque<Token> Parser::Table(Token term , Token noTerm)
{
    switch(noTerm)
    {
        case Token::input:
            switch(term)
            {
                case Token::Semicolon: return prod1;
                case Token::Ident:  return prod1;
                case Token::KwPrint:  return prod1;
                case Token::Top:  return prod1;
                default: return prodFin;
            }
        case Token::stmt_list:
            switch(term)
            {
                case Token::Semicolon: return prod2;
                case Token::Ident:  return prod2;
                case Token::KwPrint:  return prod2;
                case Token::Top:  return prod2;
                default: return prodFin;
            }
        case Token::P_stmt_list:
            switch(term)
            {
                case Token::Semicolon: return prod3;
                case Token::Top:  return epsilon;
                default: return prodFin;
            }
        case Token::stmt:
            switch(term)
            {
                case Token::Semicolon: return epsilon;
                case Token::Ident:  return prod4;
                case Token::KwPrint:  return prod5;
                case Token::Top:  return epsilon;
                default: return prodFin;
            }
        case Token::expr:
            switch(term)
            {
                case Token::Ident: return prod6;
                case Token::Number:  return prod6;
                case Token::OpenPar:  return prod6;
                default: return prodFin;
            }
        case Token::P_expr:
            switch(term)
            {
                case Token::Semicolon: return epsilon;
                case Token::OpAdd:  return prod7;
                case Token::ClosePar:  return epsilon;
                case Token::Top:  return epsilon;
                default: return prodFin;
            }
        case Token::term:
            switch(term)
            {
                case Token::Ident: return prod8;
                case Token::Number:  return prod8;
                case Token::OpenPar:  return prod8;
                default: return prodFin;
            }
        case Token::P_term:
            switch(term)
            {
                case Token::Semicolon: return epsilon;
                case Token::OpAdd:  return epsilon;
                case Token::OpMult:  return prod9;
                case Token::ClosePar:  return epsilon;
                case Token::Top:  return epsilon;
                default: return prodFin;
            }
        case Token::factor:
            switch(term)
            {
                case Token::Ident: return prod10;
                case Token::Number:  return prod11;
                case Token::OpenPar:  return prod12;
                default: return prodFin;
            }
        default:
            return prodFin;            
    }
}
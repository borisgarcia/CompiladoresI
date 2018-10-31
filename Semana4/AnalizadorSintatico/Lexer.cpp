#include "Lexer.h"

Lexer::Lexer(char * path)
{
    file.open(path, std::ifstream::in);
    initLexer();
}

std::string Lexer::getText()
{
    return tk;
}

int Lexer::getNextChar()
{
    return file.get();
}

void Lexer::ungetChar()
{
    file.unget();
}

void Lexer::initLexer()
{
    currCh = getNextChar();
}

void Lexer::getToken()
{
    std::cout<<"----------Init Lexer----------"<<std::endl;
    while(file.peek() != EOF )
    {
        Token res = getNextToken();
        std::cout<<"Token: "<<tk<<" es de tipo: "<<TokenValue(res)<<std::endl;
    }
    file.close();
}

Token Lexer::getNextToken()
{ 
    tk = "";
    while(1) 
    {
        if(currCh == EOF)
        {
            return Token::Eof;
        }
        else if(currCh == ' ' || currCh == '\t' || currCh == '\n')
        {
            currCh = getNextChar();
            continue;
        }
        else if(currCh == '/')
        {
            currCh = getNextChar();
            if(currCh == '/')
            {
                while(currCh != '\n')
                {
                    currCh = getNextChar();
                }   
                continue;
            }
            else if(currCh == '*')
            {
                while(1)
                {
                    currCh = getNextChar();
                    if(currCh == '*')
                    {
                        currCh = getNextChar();
                        if(currCh == '/')
                        {
                            currCh = getNextChar();
                            break;
                        }
                    }
                    if(currCh == EOF)
                    {
                        return Token::Eof;
                    }
                }   
                continue;
            }   
        }
        else if(isdigit(currCh))
        {
            tk += char(currCh);
            currCh = getNextChar();
            std::string s = getSequence(isdigit);
            tk += s;
            //std::cout << tk;
            
            return Token::Number;
            
        }
        else if(currCh == '*')
        {
            tk += char(currCh);
            currCh = getNextChar();
            //std::cout << tk;
            return Token::Multi;
        }
        else if(currCh == '+')
        {
            tk += char(currCh);
            currCh = getNextChar();
            //std::cout << tk;
            return Token::Add;
        }
        else if(currCh == '(')
        {
            tk += char(currCh);
            currCh = getNextChar();
            //std::cout << tk;
            return Token::OpenPar;
        }
        else if(currCh == ')')
        {
            tk += char(currCh);
            currCh = getNextChar();
            //std::cout << tk;
            return Token::ClosePar;
        }
        else
        {
            return Token::Unknown;
        }
    }
}

std::string Lexer::TokenValue(Token t)
{
    if(t == Token::Number)
        return "Number";
    else if(t==Token::Eof)
        return "Eof";
    else if(t==Token::Add)
        return "Add";
    else if(t==Token::Multi)
        return "Multi";
    else if(t==Token::OpenPar)
        return "OpenPar";
    else if(t==Token::ClosePar)
        return "ClosePar";
    else
        return "Unknown";
}

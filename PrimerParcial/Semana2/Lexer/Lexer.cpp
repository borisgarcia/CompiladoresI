#include "Lexer.h"

Lexer::Lexer(char * path)
{
    file.open(path, std::ifstream::in);
    initLexer();
}

int Lexer::getNextChar()
{
    return file.get();
}

void Lexer::initLexer()
{
    currState = 0;
    currCh = getNextChar();
}

void Lexer::getToken()
{
    while(file.peek() != EOF )
    {
        currState = 0;
        if(getNextToken()==Token::Unknown)
        {
            return;
        }
    }
    file.close();
}

Token Lexer::getNextToken()
{ 
    tk = "";
    while(1) 
    {
        switch(currState)
        {
            case 0:
                if(currCh == ' ' || currCh == '\t' || currCh == '\n')
                {
                    currCh = getNextChar();
                    continue;
                }
                if(isdigit(currCh))
                {
                    currState = 1;
                    tk += currCh;
                    currCh = getNextChar();
                } else
                {
                    currState = 3;
                }
                break;
            case 1:
                if(isdigit(currCh))
                {
                    currState = 1;
                    tk += currCh;
                    currCh = getNextChar();
                } else
                { 
                    currState = 2;
                }
                break;
            case 2:
                std::cout<<"Number"<<std::endl;
                return Token::Number;
            case 3:
                if(currCh == '_' || isalpha(currCh)!=0)
                {
                    currState = 4;
                    tk += currCh;
                    currCh = getNextChar();
                }
                else
                {
                    currState = 6;
                }
                break;
            case 4:
                if(currCh == '_' || isdigit(currCh)|| isalpha(currCh)!=0)
                {
                    currState = 4;
                    tk += currCh;
                    currCh = getNextChar();
                }
                else
                {
                    currState = 5;
                }
                break;
            case 5:
                std::cout<<"Ident"<<std::endl;
                return Token::Ident;
            case 6:
                std::cout<<"Unknown"<<std::endl;
                return Token::Unknown;
        }
    }
}

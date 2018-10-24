#include "LexerV2.h"

LexerV2::LexerV2(char * path)
{
    file.open(path, std::ifstream::in);
    initLexerV2();
}

int LexerV2::getNextChar()
{
    return file.get();
}

void LexerV2::ungetChar()
{
    file.unget();
}

void LexerV2::initLexerV2()
{
    currCh = getNextChar();
}

void LexerV2::getToken()
{
    std::cout<<"----------Init LexerV2----------"<<std::endl;
    while(file.peek() != EOF )
    {
        Token res = getNextToken();
        std::cout<<"Token: "<<tk<<" es de tipo: "<<TokenValue(res)<<std::endl;
    }
    file.close();
}

Token LexerV2::getNextToken()
{ 
    tk = "";
    while(1) 
    {
        if(currCh == ' ' || currCh == '\t' || currCh == '\n')
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
        else if(isdigit(currCh) && currCh != '0')
        {
            tk += char(currCh);
            currCh = getNextChar();
            std::string s = getSequence(isdigit);
            tk += s;
            if(s.empty())
                return Token::Unknown;
            return Token::Decimal;
            
        }
        else if(currCh == '0')
        {
            tk += char(currCh);
            currCh = getNextChar();
            
            if(currCh == 'x' || currCh == 'X')
            {
                tk += char(currCh);
                currCh = getNextChar();
                std::string s = getSequence(isxdigit);
                tk += s;
                if(s.empty()) 
                    return Token::Unknown;
                return Token::Hexadecimal;
            }
            else if(currCh == 'b' || currCh == 'B')
            {
                tk += char(currCh);
                currCh = getNextChar();
                std::string s = getSequence([](char ch) { return ch == '0' || ch == '1'; } );
                tk += s;
                if(s.empty())
                    return Token::Unknown;
                return Token::Binario;
            }
            else if(currCh > 48 && currCh <=55)
            {   
                tk += char(currCh);
                currCh = getNextChar();
                std::string s = getSequence([](char ch) { return ch == '0' || ch == '1'; } );
                tk += s; 
                if(s.empty())
                    return Token::Unknown;
                return Token::Octal;
            }
            else
            {
                return Token::Decimal;
            }
        }
        else
        {
            tk += char(currCh);
            currCh = getNextChar();
            return Token::Unknown;
        }
    
    }
}

std::string LexerV2::TokenValue(Token t)
{
    if(t == Token::Decimal)
        return "Decimal";
    else if(t==Token::Hexadecimal)
        return "Hexadecimal";
    else if(t==Token::Octal)
        return "Octal";
    else if(t==Token::Binario)
        return "Binario";
    else if(t==Token::Eof)
        return "Eof";
    else
        return "Unknown";
}

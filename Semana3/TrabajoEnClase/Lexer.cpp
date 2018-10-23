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
    comment = "";
    while(1) 
    {
        if(currCh == ' ' || currCh == '\t' || currCh == '\n')
        {
            //std::cout<<"Consumiendo Espacio"<<std::endl;
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
                    comment += char(currCh);
                }   
                //std::cout<<"Comment: "<<comment<<std::endl;
                comment = "";
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
                    comment += char(currCh);
                }   
                //std::cout<<"Comment type 2: "<<comment<<std::endl;
                comment = "";
                continue;
            }   
        }
        else if(isdigit(currCh) && currCh != '0')
        {
            //printf("%c",currCh);
            //std::cout<<" - Prefijo Digito"<<std::endl;
            
            tk += char(currCh);
            currCh = getNextChar();
            
            while(isdigit(currCh))
            {
                //printf("%c",currCh);
                //std::cout<<" - Repeticion Digito"<<std::endl;
                tk += char(currCh);
                currCh = getNextChar();
            }
            return Token::Decimal;
        }
        else if(currCh == '0')
        {
            //printf("%c",currCh);
            //std::cout<<" - Prefijo 0"<<std::endl;
            
            tk += char(currCh);
            currCh = getNextChar();
            
            if(currCh == 'x' || currCh == 'X')
            {
                tk += currCh;
                currCh = getNextChar();
                while(isxdigit(currCh))
                {
                    //printf("%c",currCh);
                    //std::cout<<" - Repeticion Hexadecimal"<<std::endl;
                    tk += char(currCh);
                    currCh = getNextChar();
                }
                return Token::Hexadecimal;
            }
            else if(currCh == 'b' || currCh == 'B')
            {
                tk += currCh;
                currCh = getNextChar();
                while(currCh == '1' || currCh == '0')
                {
                    //printf("%c",currCh);
                    //std::cout<<" - Repeticion Binario"<<std::endl;
                    tk += char(currCh);
                    currCh = getNextChar();
                }
                return Token::Binario;
            }
            else if(currCh > 48 && currCh <=55)
            {
                tk += currCh;
                currCh = getNextChar();
                while(currCh >= 48 && currCh <=57)
                {
                    //printf("%c",currCh);
                    //std::cout<<" - Repeticion Octal"<<std::endl;
                    tk += char(currCh);
                    currCh = getNextChar();
                }
                return Token::Octal;
            }
            else
            {
                return Token::Decimal;
            }
        }
        else
        {
            //std::cout<<"Token is unknown"<<std::endl;
            tk += char(currCh);
            currCh = getNextChar();
            return Token::Unknown;
        }
    
    }
}


std::string Lexer::TokenValue(Token t)
{
    if(t == Token::Decimal)
        return "Decimal";
    else if(t==Token::Hexadecimal)
        return "Hexadecimal";
    else if(t==Token::Octal)
        return "Octal";
    else if(t==Token::Binario)
        return "Binario";
    else
        return "Unknown";
}
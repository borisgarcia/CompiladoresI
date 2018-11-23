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
    do
    {
        currState = 0;
        Token res = getNextToken();
        std::cout<<"Token: "<<tk<<" es de tipo: "<<TokenValue(res)<<std::endl;
    }
    while(file.peek() != EOF );
    file.close();
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

Token Lexer::getNextToken()
{ 
    tk = "";
    while(1) 
    {
        switch(currState)
        {
            case 0:
                //std::cout<<"Case 0 - ";
                //printf("%c \n",currCh);
            
                if(currCh == ' ' || currCh == '\t' || currCh == '\n')
                {
                    currCh = getNextChar();
                    continue;
                }
                if(isdigit(currCh)&&currCh!='0')
                {
                    currState = 1;
                    tk += char(currCh);
                    currCh = getNextChar();
                } else if(currCh=='0')
                {
                    currState = 3;
                }
                else
                {
                    tk += char(currCh);
                    currState = 11;
                }
                break;
            case 1:
                //std::cout<<"Case 1 - ";
                //printf("%c \n",currCh);
            
                if(isdigit(currCh))
                {
                    currState = 1;
                    tk += char(currCh);
                    currCh = getNextChar();
                } else
                { 
                    currState = 2;
                }
                break;
            
            case 2:
                return Token::Decimal;
            
            case 3:
                //std::cout<<"Case 3 - ";
                //printf("%c \n",currCh);
                if(currCh == '0')
                {
                    currState = 4;
                    tk += char(currCh);
                    currCh = getNextChar();
                }
                else
                {
                    currState = 11;
                }
                break;
            case 4:
                //std::cout<<"Case 4 - ";
                //printf("%c \n",currCh);
                if(currCh == 'x' || currCh == 'X')
                {
                    currState = 5;
                    tk += char(currCh);
                    currCh = getNextChar();
                }
                else if(currCh == 'b' || currCh == 'B')
                {
                    currState = 7;
                    tk += char(currCh);
                    currCh = getNextChar();
                }
                else if(isdigit(currCh) && currCh!='8' && currCh!='9' && currCh!='0')
                {
                    tk += char(currCh);
                    currState = 9;
                    currCh = getNextChar();
                }
                else
                {
                    currState = 2;   
                }
                break;
            case 5:
                //std::cout<<"Case 5 - ";
                //printf("%c \n",currCh);        
                if(isxdigit(currCh))
                {
                    currState = 55;
                    tk += char(currCh);
                    currCh = getNextChar();
                } else
                {
                    file.unget();
                    currState = 11;
                }       
                break;
            case 55:
                //std::cout<<"Case 5.5 - ";
                //printf("%c \n",currCh);        
                if(isxdigit(currCh))
                {
                    currState = 55;
                    tk += char(currCh);
                    currCh = getNextChar();
                } else
                { 
                    currState = 6;
                }       
                break;

            case 6:
                return Token::Hexadecimal; 
            case 7:
                //std::cout<<"Case 7 - ";
                //printf("%c \n",currCh);
                if(currCh =='1' || currCh == '0')
                {
                    currState = 77;
                    tk += char(currCh);
                    currCh = getNextChar();
                } else
                {
                    file.unget();
                    currState = 11;
                }       
                break;
            case 77:
                //std::cout<<"Case 7.7 - ";
                //printf("%c \n",currCh);
                if(currCh =='1' || currCh == '0')
                {
                    currState = 77;
                    tk += char(currCh);
                    currCh = getNextChar();
                } else
                { 
                    currState = 8;
                }       
                break;
            case 8:
                return Token::Binario; 
            case 9:
                //std::cout<<"Case 9 - ";
                //printf("%c \n",currCh);
                if(currCh =='0' || currCh == '1'|| currCh == '2'|| currCh == '3'|| currCh == '4'|| currCh == '5'|| currCh == '6'|| currCh == '7')
                {
                    currState = 9;
                    tk += char(currCh);
                    currCh = getNextChar();
                } else
                { 
                    currState = 10;
                }       
                break;
            case 10:
                return Token::Octal;
            case 11:
                currCh = getNextChar();
                return Token::Unknown;   

        }
    }
}

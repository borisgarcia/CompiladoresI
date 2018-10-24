#include "lexer.h"

void Lexer::unGetChar()
{
    for(int x = 0;x<=cont;x++)
    {
        in.unget();
    }
    text = "";
    cont = 0;
}


Token Lexer::getNextToken() {
    currChar = in.get();
    text = "";
    cont = 0;
    currState = 0;
    while(1)
    {
        switch(currState){
            case 0:
                if(currChar == ' ')
                {
                    currChar = in.get();
                }
                else if(isxdigit(currChar))
                {
                    currState = 1;
                    text += char(currChar);
                    currChar = in.get();
                    cont++;
                }
                else if(currChar == EOF)
                {
                    return Token::Eof;
                }
                else 
                {
                    currState = 3;
                }
                break;
            case 1:
                if(isxdigit(currChar))
                {
                    currState = 1;
                    text += char(currChar);
                    currChar = in.get();
                    cont++;
                }
                else if(currChar == 'h' || currChar == 'H')
                {
                    currState = 2;
                    text += char(currChar);
                    currChar = in.get();
                    cont++;
                }
                else
                {
                    unGetChar();
                    currChar = in.get();
                    currState = 20;
                }
                break;
            case 2:
                return Token::Hex;
            case 5:
                if(currChar == '1' || currChar == '0')
                {
                    currState = 6;
                    text += char(currChar);
                    currChar = in.get();
                    cont++;
                }
                else 
                {
                    currState = 8;
                }
                break;
            case 6:
                if(currChar == '1' || currChar == '0')
                {
                    currState = 6;
                    text += char(currChar);
                    currChar = in.get();
                    cont++;
                }
                else if(currChar == 'b' || currChar == 'B')
                {
                    currState = 7;
                    text += char(currChar);
                    currChar = in.get();
                    cont++;
                }
                else
                {
                    unGetChar();
                    currChar = in.get();
                    currState = 8;
                }
                break;
            case 7:
                return Token::Binary;
            case 8:
                if(currChar == '0' || currChar == '1' || currChar == '2' || currChar == '3' || currChar == '4' || currChar == '5' || currChar == '6'|| currChar == '7')
                {
                    currState = 9;
                    text += char(currChar);
                    currChar = in.get();
                    cont++;
                }
                else 
                {
                    currState = 11;
                }
                break;
            case 9:
                if(currChar == '0' || currChar == '1' || currChar == '2' || currChar == '3' || currChar == '4' || currChar == '5' || currChar == '6'|| currChar == '7')
                {
                    currState = 9;
                    text += char(currChar);
                    currChar = in.get();
                    cont++;
                }
                else if(currChar == 'o' || currChar == 'O')
                {
                    currState = 10;
                    text += char(currChar);
                    currChar = in.get();
                    cont++;
                }
                else
                {
                    unGetChar();
                    currChar = in.get();
                    currState = 11;
                }
                break;
            case 10:
                return Token::Octal;
            case 11:
                return Token::Eof;
            
            case 20:
                if(isdigit(currChar))
                {
                    currState = 20;
                    text += char(currChar);
                    currChar = in.get();
                    cont++;
                }
                else if(currChar == ' ')
                {
                    currState = 21;
                }
                else
                {
                    unGetChar(); 
                    currChar = in.get();                  
                    currState = 5;
                }
                break;
            case 21:
                return Token::Decimal;
        }
    }
}


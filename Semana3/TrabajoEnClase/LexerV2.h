#include <ctype.h>
#include <iostream>
#include <fstream>
#include <string> 
#include <functional>

enum class Token
{
    Decimal,
    Hexadecimal,
    Binario,
    Octal,
    Unknown,
    Eof
};

class LexerV2
{
    public:
        LexerV2(char * path);
        void getToken();

    private:
        Token getNextToken();
        void initLexerV2();
        void ungetChar();
        int getNextChar();
        
        std::string TokenValue(Token t);
        
        std::string getSequence(std::function<bool(char)>func)
        {
            std::string temp; 
            
            while(func(currCh))
            {
                temp += char(currCh);
                currCh = getNextChar();
            }
            return temp;
        }

        int currCh;
        std::ifstream file;
        std::string tk;
        
};
#include <ctype.h>
#include <iostream>
#include <fstream>
#include <string> 
#include <functional>

enum class Token
{
    Add,
    Sub,
    Multi,
    Div,
    OpenPar,
    ClosePar,
    Number,
    Semicolon,
    Ident,
    Unknown,
    Eof
};

class Lexer
{
    public:
        Lexer(char * path);
        Token getNextToken();
        void getToken();
        int currCh;
        std::string TokenValue(Token t);
        std::string tk;
    private:
        void initLexer();
        void ungetChar();
        int getNextChar();
        
        
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

        std::ifstream file;
        
        
};
#include <ctype.h>
#include <iostream>
#include <fstream>
#include <string> 
#include <functional>

enum class Token
{
    Add,
    Multi,
    OpenPar,
    ClosePar,
    Number,
    Unknown,
    Eof
};

class Lexer
{
    public:
        Lexer(char * path);
        Token getNextToken();
        void getToken();
        std::string TokenValue(Token t);
        std::string getText();

    private:
        std::ifstream file;
        void initLexer();
        int currCh;
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
    
        std::string tk;
        
};
#include <ctype.h>
#include <iostream>
#include <fstream>
#include <string> 
#include <functional>
#include <deque>

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

enum class Symbol : int
{
    //Terminales
    Add = 0,
    Multi = 1,
    OpenPar = 2,
    ClosePar = 3,
    Number = 4,
    Epsilon= 5,

    //No Term
    E = 100,
    Ep = 101,
    T = 102,
    Tp = 103,
    F = 104,

    //Especial
    Top = 200,
    Eof = 201,
    Unknown = 202,
    Null = 203
};

class Lexer
{
    public:
        Lexer(char * path);
        Symbol getNextToken();
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
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
    Div = 6,
    Sub = 7,

    //States
    state0 = 99,
    state1 = 100,   
    state2 = 101,
    state3 = 102,
    state4 = 103,
    state5 = 104,
    state6 = 105,
    state7 = 106,
    state8 = 107,
    state9 = 108,
    state10 = 109,
    state11 = 110,
    state12 = 111,
    state13 = 112,
    state14 = 113,
    state15 = 114,
    stateNull = 115,

    //noTerm
    A = 200,
    E = 201,
    T = 202,
    F = 203,

    //Especial
    Top = 400,
    Eof = 401,
    Unknown = 402,
    Null = 403
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
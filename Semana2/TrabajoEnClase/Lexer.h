#include <ctype.h>
#include <iostream>
#include <fstream>
#include <string> 

enum class Token
{
    Decimal,
    Hexadecimal,
    Binario,
    Octal,
    Unknown
};

class Lexer
{
    public:
        Lexer(char * path);
        void getToken();

    private:
        Token getNextToken();
        int getNextChar();
        void initLexer();
        std::string toString();
        std::string TokenValue(Token t);

        int currState,currCh;
        std::ifstream file;
        std::string tk;
};
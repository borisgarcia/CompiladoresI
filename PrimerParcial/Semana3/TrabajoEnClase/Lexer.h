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
    Unknown,
    Eof
};

class Lexer
{
    public:
        Lexer(char * path);
        void getToken();

    private:
        Token getNextToken();
        int getNextChar();
        void ungetChar();

        void initLexer();
        std::string toString();
        std::string TokenValue(Token t);

        int currCh;
        std::ifstream file;
        std::string tk;
        std::string comment;
};
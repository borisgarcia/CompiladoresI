#include <ctype.h>
#include <iostream>
#include <fstream>

enum class Token
{
    Number,
    Ident,
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
        int currState;
        int currCh;
        std::ifstream file;
        std::string tk;
};
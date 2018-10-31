#include "Lexer.h"




class Sintax
{
    public:
        Sintax(Lexer &lexer):lexer(lexer){}
        void initParser();
        int eval();

    private:
        int E();
        int T();
        int F();
        Token token;
        Lexer &lexer;
        int resp;
        int op;
        int currVal;
        int cont;        
};

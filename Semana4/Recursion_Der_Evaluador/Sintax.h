#include "Lexer.h"




class Sintax
{
    public:
        Sintax(Lexer &lexer):lexer(lexer){}
        void initParser();


    private:
        int E();
        int Ep();
        int T();
        int Tp();
        int F();
        Token token;
        Lexer &lexer;
        int resul;        
};

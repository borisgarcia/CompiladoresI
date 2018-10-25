#include "Lexer.h"




class Sintax
{
    public:
        Sintax(Lexer &lexer):lexer(lexer){}
        void initParser();


    private:
        void E();
        void Ep();
        void T();
        void Tp();
        void F();
        void error();
        Token token;
        Lexer &lexer;        
};

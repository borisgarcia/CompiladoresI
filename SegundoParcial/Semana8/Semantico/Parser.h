#include "Lexer.h"
#include "AST.h"
#include <functional>

class Parser
{
    public:
        Parser(Lexer &lexer):lexer(lexer){}

        void initParser();
        Expr E();
        Expr Ep();
        Expr T();
        Expr F();
    
    private:
        Token token;
        Lexer &lexer;
        void ObtenerToken() 
        {
		    token = lexer.getNextToken();
	    }        
};

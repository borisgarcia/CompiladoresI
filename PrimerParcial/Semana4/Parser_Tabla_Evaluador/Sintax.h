#include "Lexer.h"
#include <vector>

class Sintax
{
    public:
        Sintax(Lexer &lexer):lexer(lexer){}
        void initParser();
        void init();
        std::deque<Symbol> Table(Symbol term , Symbol noTerm);
        
    private:
        Lexer &lexer;
        Symbol symbol;
        std::deque<Symbol> mystack;
        std::deque<Symbol> input;
        std::deque<Symbol> T_Ep = {Symbol::T,Symbol::Ep};
        std::deque<Symbol> F_Tp = {Symbol::F,Symbol::Tp};
        std::deque<Symbol> Add_T_Ep = {Symbol::Add,Symbol::T,Symbol::Ep};
        std::deque<Symbol> Multi_T_Ep = {Symbol::Multi,Symbol::F,Symbol::Tp};
        std::deque<Symbol> NUM = {Symbol::Number};
        std::deque<Symbol> E_expr = {Symbol::OpenPar,Symbol::E,Symbol::ClosePar};
        std::deque<Symbol> Epsilon = {Symbol::Epsilon};
        std::deque<Symbol> Null = {Symbol::Null};
        
        std::string toString(Symbol sym);
};

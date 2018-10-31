#include "Lexer.h"
#include <vector>

class Sintax
{
    public:
        Sintax(Lexer &lexer):lexer(lexer){}
        void initParser();


    private:
        Token token;
        Lexer &lexer;
        void initTable();
        void init();
        std::vector<std::string> Table[6][7];
        std::deque<std::string> mystack;
        std::deque<std::string> input;
        
};

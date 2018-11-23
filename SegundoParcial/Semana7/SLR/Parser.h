#include "Lexer.h"
#include <vector>
#include <utility>
#include <deque>


struct pair{
    Act act;
    Token tok;
};


class Parser
{
    public:
        Parser(Lexer &lexer):lexer(lexer){}
        void initParser();
        void init();


    private:
        Lexer &lexer;
        Token token;
        
        struct pair Action(Token term , Token state);
        Token GoTO(Token noTerm , Token state);

        std::deque<Token> stack;
        std::deque<Token> input;

        std::string toString(Token sym);
        struct pair s4 = {Act::S, Token::state4}; 
        struct pair s5 = {Act::S, Token::state5};
        struct pair s6 = {Act::S, Token::state6};
        struct pair s7 = {Act::S, Token::state7};
        struct pair s8 = {Act::S, Token::state8};
        struct pair s9 = {Act::S, Token::state9};
        struct pair s15 ={Act::S, Token::state15};
        struct pair r1 = {Act::R, Token::E};
        struct pair r2 = {Act::R, Token::E};
        struct pair r3 = {Act::R, Token::E};
        struct pair r4 = {Act::R, Token::T};
        struct pair r5 = {Act::R, Token::T};
        struct pair r6 = {Act::R, Token::T};
        struct pair r7 = {Act::R, Token::F};
        struct pair r8 = {Act::R, Token::F};
        struct pair acc = {Act::ACC , Token::stateNull};
        struct pair null = {Act::null , Token::stateNull};
    
        Token st1 = Token::state1;
        Token st2 = Token::state2;
        Token st3 = Token::state3;
        Token st10 = Token::state10;
        Token st11 = Token::state11;
        Token st12 = Token::state12;
        Token st13 = Token::state13;
        Token st14 = Token::state14;

};

#include "Parser.h"

void Parser::init()
{   
    while(1)
    {
        token = lexer.getNextToken();
        if(token == Token::Eof)break;
        else if(token == Token::Unknown) 
            throw std::invalid_argument( "\nParser Error");
        input.push_back(token);
    }
    stack.push_front(Token::state0);
    input.push_back(Token::Top);
}

void Parser::initParser()
{
    init();
    Token currInput;
    Token currStack;
    Act currAction;
    Token currState = Token::state0;
    struct pair temp;
    int cont;
    while (currAction != Act::ACC)
    {
        for (size_t i = 0; i < stack.size(); i++) std::cout << toString( stack.at(i))<< " ";
        std::cout << " | ";

        for (size_t i = 0; i < input.size(); i++) std::cout << toString(input.at(i));
        std::cout << '\n';

        currInput = input.front();
        currStack = stack.back();
        temp = Action(currInput,currState);

        if(temp.act == Act::null && temp.tok == Token::stateNull)
        {
            if(GoTO(currStack,currState)!=Token::Null)
            {
                currState = GoTO(currStack,currState);
                stack.push_back(currState);
            }
            else
            {
                throw std::invalid_argument("Error");
            }
        }
        else
        {
            if(temp.act == Act::R)
            {
                /*int find = 0;
                int cont = 0;
                for (size_t i = stack.size()-1; i > 0; i--)
                {
                    if(stack.back() == stack.at(i) && i != stack.size()-1)
                    {
                        find = 1;
                        break;
                    }    
                    cont++;
                } 
                if(find = 0)
                { */
                    stack.pop_back();
                    stack.pop_back();
                    currState = stack.back();
                    stack.push_back(temp.tok);
                /*}
                else
                {
                    for(int x = 0;x<cont;x++)
                        stack.pop_back();
                }*/
            }
            else if(temp.act == Act::S)
            {
                currState = temp.tok;
                input.pop_front();
                stack.push_back(currInput);
                stack.push_back(currState);
            }
            else if(temp.act == Act::ACC)
                break;
        }
        
    }
}

struct pair Parser::Action(Token term , Token state)
{
    switch(term)
    {
        case Token::Add:
            switch(state)
            {
                case Token::state1: return s6; 
                case Token::state2: return r3;
                case Token::state3: return r6;
                case Token::state5: return r8;
                case Token::state10: return s6;
                case Token::state11: return r1;
                case Token::state12: return r2;
                case Token::state13: return r4;
                case Token::state14: return r5;
                case Token::state15: return r7;
                default: return null;
            }
        case Token::Sub:
            switch(state)
            {
                case Token::state1: return s7; 
                case Token::state2: return r3;
                case Token::state3: return r6;
                case Token::state5: return r8;
                case Token::state10: return s7;
                case Token::state11: return r1;
                case Token::state12: return r2;
                case Token::state13: return r4;
                case Token::state14: return r5;
                case Token::state15: return r7;
                default: return null;
            }
        case Token::Multi:
            switch(state)
            {
                case Token::state2: return s8;
                case Token::state3: return r6;
                case Token::state5: return r8;
                case Token::state11: return s8;
                case Token::state12: return s8;
                case Token::state13: return r4;
                case Token::state14: return r5;
                case Token::state15: return r7;
                default: return null;
            }
        case Token::Div:
            switch(state)
            {
                case Token::state2: return s9;
                case Token::state3: return r6;
                case Token::state5: return r8;
                case Token::state11: return s9;
                case Token::state12: return s9;
                case Token::state13: return r4;
                case Token::state14: return r5;
                case Token::state15: return r7;
                default: return null;
            }
        case Token::OpenPar:
            switch(state)
            {
                case Token::state0: return s4;
                case Token::state4: return s4;
                case Token::state6: return s4;
                case Token::state7: return s4;
                case Token::state8: return s4;
                case Token::state9: return s4;
                default: return null;
            }
        case Token::ClosePar:
            switch(state)
            {
                case Token::state2: return r3;
                case Token::state3: return r6;
                case Token::state5: return r8;
                case Token::state10: return s15;
                case Token::state11: return r1;
                case Token::state12: return r2;
                case Token::state13: return r4;
                case Token::state14: return r5;
                case Token::state15: return r7;
                default: return null;
            }
        case Token::Number:
            switch(state)
            {
                case Token::state0: return s5;
                case Token::state4: return s5;
                case Token::state6: return s5;
                case Token::state7: return s5;
                case Token::state8: return s5;
                case Token::state9: return s5;
                default: return null;
            }
        case Token::Top:
            switch(state)
            {
                case Token::state1: return acc;
                case Token::state2: return r3;
                case Token::state3: return r6;
                case Token::state5: return r8;
                case Token::state11: return r1;
                case Token::state12: return r2;
                case Token::state13: return r4;
                case Token::state14: return r5;
                case Token::state15: return r7;
                default: return null;
            }
        default: return null;
    }
}

Token Parser::GoTO(Token noTerm , Token state)
{
    switch(noTerm)
    {
        case Token::E:
            switch(state)
            {
                case Token::state0: return st1;
                case Token::state4: return st10;
                default: return Token::Null;
            }
        case Token::T:
            switch(state)
            {
                case Token::state0: return st2;
                case Token::state4: return st2;
                case Token::state6: return st11;
                case Token::state7: return st12;
                default: return Token::Null;
            }
        case Token::F:
            switch(state)
            {
                case Token::state0: return st3;
                case Token::state4: return st3;
                case Token::state6: return st3;
                case Token::state7: return st3;
                case Token::state8: return st13;
                case Token::state9: return st14;
                default: return Token::Null;
            }
        default: return Token::Null;
    }
}

std::string Parser::toString(Token sym)
{
    int x = static_cast<unsigned int>(sym);
    switch (x)
    {
        case 0: return "+";
        case 1: return "*";
        case 2: return "(";
        case 3: return ")";
        case 4: return "NUM";
        case 5: return "";
        case 6: return "/";
        case 7: return "-";
        case 99: return "0";
        case 100: return "1";
        case 101: return "2";
        case 102: return "3";
        case 103: return "4";
        case 104: return "5";
        case 105: return "6";
        case 106: return "7";
        case 107: return "8";
        case 108: return "9";
        case 109: return "10";
        case 110: return "11";
        case 111: return "12";
        case 112: return "13";
        case 113: return "14";
        case 114: return "15";
        
        case 200: return "A";
        case 201: return "E";
        case 202: return "T";
        case 203: return "F";  
    
        case 400: return "$";
        case 401: return "Eof";
        case 402: return "Unknown";
        case 403: return "Null";
        default: return "Error";
    }
}
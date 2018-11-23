#include "Sintax.h"

void Sintax::init()
{   
    while(1)
    {
        symbol = lexer.getNextToken();
        if(symbol == Symbol::Eof)break;
        else if(symbol == Symbol::Unknown) 
            throw std::invalid_argument( "\nSintax Error");
        input.push_back(symbol);
    }
    mystack.push_front(Symbol::E);
    mystack.push_front(Symbol::Top);
    input.push_back(Symbol::Top);
}

void Sintax::initParser()
{
    init();
    Symbol currStack, currInput;
    std::deque<Symbol> temp;
    while (1)
    {
        if(toString(input.front()) == "$" && toString(mystack.back())=="$")break;
        for (size_t i = 0; i < mystack.size(); i++) std::cout << toString( mystack.at(i));
        std::cout << " | ";

        for (size_t i = 0; i < input.size(); i++) std::cout << toString(input.at(i));
        std::cout << '\n';

        currStack = mystack.back();

        if(currStack == Symbol::Null)
            throw std::invalid_argument("Sintax Error");
        currInput = input.front();

        if(currStack == currInput)
        {
            mystack.pop_back();
            input.pop_front();
            continue;
        }
        else if(currStack == Symbol::Epsilon)
        {
            mystack.pop_back();    
            continue;
        }

        mystack.pop_back();

        temp = Table(currInput,currStack);
        for(int a = temp.size();a>0;a--)
            mystack.push_back(temp.at(a-1));
    }
}


std::deque<Symbol> Sintax::Table(Symbol term , Symbol noTerm)
{
    switch(noTerm)
    {
        case Symbol::E:
            switch(term)
            {
                case Symbol::OpenPar: return T_Ep;
                case Symbol::Number:  return T_Ep;
            }
        case Symbol::Ep:
            switch(term)
            {
                case Symbol::Add: return Add_T_Ep;
                case Symbol::ClosePar: return Epsilon;                
                case Symbol::Top: return Epsilon;
            }
        case Symbol::T:
            switch(term)
            {
                case Symbol::OpenPar: return F_Tp;
                case Symbol::Number: return F_Tp;
            }
        case Symbol::Tp:
            switch(term)
            {
                case Symbol::Add: return Epsilon; 
                case Symbol::Multi: return Multi_T_Ep;
                case Symbol::OpenPar: return Epsilon; 
                case Symbol::Top:return Epsilon; 
            }
        case Symbol::F:
            switch(term)
            {
                case Symbol::OpenPar: return E_expr;
                case Symbol::Number: return NUM;
            }
        default:
            return Null;            
    }
}

std::string Sintax::toString(Symbol sym)
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
        case 100: return "E";
        case 101: return "Ep";
        case 102: return "T";
        case 103: return "Tp";
        case 104: return "F";
        case 200: return "$";
        case 201: return "Eof";
        case 202: return "Unknown";
        case 203: return "Null";
        default: return "Error";
    }
}
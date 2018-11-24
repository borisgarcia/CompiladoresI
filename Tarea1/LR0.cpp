#include "LR0.h"

void LR0::computeDFA() {
    for (size_t i = 0; i < gr.getRules().size(); i++) 
        for (size_t j = 0; j < gr.getRules().at(i).rhs.size(); j++)
            check(gr.getRules().at(i).rhs.at(j));
}


void LR0::check(std::string symbol)
{
    const std::set<std::string>& temp = gr.getNonTerminals();
    for (std::set<std::string>::iterator it; it=temp.begin(); it!=myset.end(); ++it)
    {
        std::cout << ' ' << *it;
    
    }

}

void LR0::getClosure(std::string symbol)
{

}
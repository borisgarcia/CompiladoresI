#include "LR0.h"

void LR0::computeDFA() 
{
    getClosure(gr.getRules().at(0).lhs,0,gr.getRules().at(0).rhs);
    for (size_t i = 0; i < gr.getRules().size(); i++) 
    {
        check(gr.getRules().at(i).lhs,gr.getRules().at(i).rhs);
    }
}


void LR0::check(std::string symbol,string_vector_t transi)
{
    int rule_size = transi.size();   
    for(size_t i = 1; i <= rule_size; i++)
    {
        getClosure(symbol,i,transi);
    }
}

void LR0::getClosure(std::string symbol,int pos_dot,string_vector_t transi)
{
    temp _closure;
    int terminal;
    already_check.clear();
    if(pos_dot < transi.size())
    {
        _closure.symbol = symbol;
        _closure.dot_position = pos_dot;
        _closure.items = transi;
        std::cout << symbol << "->"<< pos_dot<<'\n';
        if(!check_is_term(transi.at(pos_dot)))
        {
            already_check.push_back(transi.at(pos_dot));
            search_non_term(transi.at(pos_dot));
        }
        std::cout << "-------" << '\n';
    }
    else
    {
        _closure.symbol = symbol;
        _closure.dot_position = pos_dot;
        _closure.items = transi;
        std::cout << symbol << "->"<< pos_dot<<'\n';
        std::cout << "-------" << '\n';
    }
}

int LR0::check_is_term(std::string symbol)
{
    for (size_t i = 0; i < gr.getRules().size(); i++)
    {
        if(gr.getRules().at(i).lhs == symbol)
            return 0;
    }
    return 1;
}

void LR0::search_non_term(std::string nonTerm)
{
    temp _closure;
    for (size_t i = 0; i < gr.getRules().size(); i++)
    {
        if(gr.getRules().at(i).lhs == nonTerm)
        {
            _closure.symbol = gr.getRules().at(i).lhs;
            _closure.dot_position = 0;
            _closure.items = gr.getRules().at(i).rhs;
            std::cout << gr.getRules().at(i).lhs << "->"<< 0<<'\n';
            if(!check_is_term(gr.getRules().at(i).rhs.at(0))&&!not_checked(gr.getRules().at(i).rhs.at(0)))
            {
                already_check.push_back(gr.getRules().at(i).rhs.at(0));
                search_non_term(gr.getRules().at(i).rhs.at(0));
            }
            
        }
    }
}

int LR0::not_checked(std::string symbol)
{
    for (size_t i = 0; i < already_check.size(); i++)
    {
        if(already_check.at(i) == symbol)
        {
            //std::cout << "Checked: " << symbol<<'\n';
            return 1;
        }
    }
    return 0;
}

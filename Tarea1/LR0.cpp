#include "LR0.h"

void LR0::computeDFA() 
{
    getClosure(gr.getRules().at(0).lhs,0,gr.getRules().at(0).rhs);
    for (size_t i = 0; i < gr.getRules().size(); i++) 
    {
        check(gr.getRules().at(i).lhs,gr.getRules().at(i).rhs);
    }
    printDFA();
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
    int terminal;
    already_check.clear();
    State state_temp;
    if(pos_dot < transi.size())
    {
        Item item_temp(pos_dot);
        item_temp.symbol = symbol;
        item_temp.transitions = transi;
        state_temp.items.push_back(item_temp);
        if(!check_is_term(transi.at(pos_dot)))
        {
            already_check.push_back(transi.at(pos_dot));
            search_non_term(transi.at(pos_dot),state_temp);
        }
        dfa.push_back(state_temp);
    }
    else
    {
        Item item_temp(pos_dot);
        item_temp.symbol = symbol;
        item_temp.transitions = transi;
        state_temp.items.push_back(item_temp);
        dfa.push_back(state_temp);
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

void LR0::search_non_term(std::string nonTerm,State &state)
{
    for (size_t i = 0; i < gr.getRules().size(); i++)
    {
        if(gr.getRules().at(i).lhs == nonTerm)
        {
            Item item_temp(0);
            item_temp.symbol = gr.getRules().at(i).lhs;
            item_temp.transitions = gr.getRules().at(i).rhs;
            state.items.push_back(item_temp);
            if(!check_is_term(gr.getRules().at(i).rhs.at(0))&&!not_checked(gr.getRules().at(i).rhs.at(0)))
            {
                already_check.push_back(gr.getRules().at(i).rhs.at(0));
                search_non_term(gr.getRules().at(i).rhs.at(0),state);
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
            return 1;
        }
    }
    return 0;
}

void LR0::printDFA()
{
    for(size_t i = 0; i < dfa.size(); i++)
    {
        for(size_t j = 0; j < dfa.at(i).items.size(); j++)
        {
            std::cout << dfa.at(i).items.at(j).symbol<<" -> ";
            for (size_t a = 0; a < dfa.at(i).items.at(j).transitions.size(); a++)
            {
                if(a == dfa.at(i).items.at(j).dot_pos)
                    std::cout << " . ";
                std::cout <<  dfa.at(i).items.at(j).transitions.at(a)<<" ";
                
            }
            if(dfa.at(i).items.at(j).transitions.size() == dfa.at(i).items.at(j).dot_pos)
                std::cout<< " . ";
            std::cout<< " | ";
        }
        std::cout<< '\n';
    }
    
}

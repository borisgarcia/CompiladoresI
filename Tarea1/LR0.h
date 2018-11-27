#ifndef _LR0DFAGEN_H_
#define _LR0DFAGEN_H_
#include <iostream>
#include <vector>
#include "grammar.h"


class LR0 {
public:
    struct temp {
        std::string symbol;
        int dot_position;
        std::vector<std::string> items;
    };
    struct temp_0{
        std::string symbol;
        int dot_position;
        std::vector<std::string> items;

        std::vector<temp> closure;
    };

    temp_0 _dfa;

    struct Item {
        Item(const Grammar::Production &prod, int dot_pos):
            prod(prod), dot_pos(dot_pos) {}

        bool operator==(const Item& rhs) {
            return (&prod == &(rhs.prod)) && (dot_pos == rhs.dot_pos);
        }

        bool operator!=(const Item& rhs) {
            return !(*this == rhs);
        }

        const Grammar::Production &prod;
        int dot_pos;
    };

    struct State;

    struct Transition {
        Transition(const std::string &symbol, State& next_state):
            symbol(symbol), next_state(next_state) {}

        std::string symbol;
        State& next_state;
    };

    struct State {
        bool operator==(const State& rhs) {
            if (items.size() != rhs.items.size()) {
                return false;
            }

            for (int i = 0; i < items.size(); i++) {
                if (items[i] != rhs.items[i]) {
                    return false;
                }
            }

            return true;
        }

        bool operator!=(const State& rhs) {
            return !(*this == rhs);
        }

        std::vector<Item> items;
        std::vector<Transition> transitions;
    };

    using DFA = std::vector<State>;

    LR0(Grammar &gr): gr(gr) {
        computeDFA();
    }
    const DFA& getDFA() { return dfa; }

private:
    void computeDFA();
    void check(std::string symbol,string_vector_t transi);
    void getClosure(std::string symbol,int pos_dot,string_vector_t transi);
    int check_is_term(std::string symbol);
    void search_non_term(std::string nonTerm);
    int not_checked(std::string symbol);
private:
    Grammar &gr;
    DFA dfa;
    std::vector<std::string> already_check;
};

#endif

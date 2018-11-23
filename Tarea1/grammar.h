#ifndef _GRAMMAR_H_
#define _GRAMMAR_H_

#include <string>
#include <vector>
#include <istream>
#include <set>

using string_vector_t = std::vector<std::string>;

class Grammar {
public:
    struct Production {
        Production(const std::string& lhs, string_vector_t&& rhs):
            lhs(lhs), rhs(std::move(rhs)) {}

        std::string lhs;
        string_vector_t rhs;

        std::string toString() const;
    };

    Grammar(std::istream& in);

    bool isLoaded() { return loaded; }
    const std::set<std::string>& getTerminals() { return ts; }
    const std::set<std::string>& getNonTerminals() { return nts; }
    const std::vector<Production>& getRules() { return rules; }

private:
    bool load(std::istream& in);
    bool parseProduction(const std::string &p, std::string &lhs, string_vector_t &rhs);

private:
    bool loaded;
    std::set<std::string> symbs; // All grammar symbols
    std::set<std::string> nts; // Non terminal symbols
    std::set<std::string> ts; // Terminal symbols
    std::vector<Production> rules; // Grammar rules
};

#endif


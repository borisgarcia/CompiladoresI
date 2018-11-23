#include <algorithm>
#include <iostream>
#include <sstream>
#include "str_util.h"
#include "grammar.h"

std::string Grammar::Production::toString() const {
    std::ostringstream out;

    out << lhs << " -> ";

    for (const auto& s : rhs) {
        out << s << " ";
    }
    out << "\n";

    return out.str();
}

Grammar::Grammar(std::istream& in) {
    loaded = load(in);
}

bool Grammar::load(std::istream& in) {
    std::set<std::string> ntsSet;
    std::string line;
    int prodIndex = 0, ntsIndex = 0;

    while (!in.eof()) {
        std::getline(in, line);
        trim(line);

        if (line.empty()) {
            continue;
        }

        std::string lhs;
        string_vector_t rhs;

        if (!parseProduction(line, lhs, rhs)) {
            std::cerr << "Invalid production '" << line << "'" << std::endl;
            return false;
        }

        int inserted = ntsSet.insert(lhs).second;

        if (inserted) {
            nts.insert(lhs);
        }
        symbs.insert(lhs);

        for (const auto &s : rhs) {
            symbs.insert(s);
        }

        rules.emplace_back(lhs, std::move(rhs));
    }

    string_vector_t tsv;

    std::set_difference(symbs.begin(), symbs.end(), ntsSet.begin(), ntsSet.end(), std::back_inserter(tsv));

    for (const auto& s : tsv) {
        ts.insert(s);
    }

    symbs.insert("$");
    ts.insert("$");

    return true;
}

bool Grammar::parseProduction(const std::string &p, std::string &lhs, string_vector_t &rhs) {
    int pos = p.find("->"); 

    if (pos == -1) {
        return false;
    }

    lhs = p.substr(0, pos);
    std::string rhsStr = p.substr(pos + 2);
    trim(lhs);
    trim(rhsStr);

    splitStrings(rhsStr, " ", std::back_inserter(rhs));

    return true;
}

#include <cstring>
#include <iostream>
#include <fstream>
#include "grammar.h"
#include "LR0.h"

void usage(const char *progname);

int main(int argc, char *argv[]) {
    const char *progname = argv[0];

    if (argc != 3) {
        usage(progname);    
        return 1;
    }
    
    std::string grFileName;

    argc--;
    argv++;

    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-g") == 0) {
            if (i < argc - 1) {
                grFileName = argv[i+1];
                i++;
            } else {
                usage(progname);
                return 1;
            }
        } else {
            usage(progname);
            std::cerr << "Invalid option '" << argv[i] << "'" << std::endl;
            return 1;
        }
    }

    if (grFileName.empty()) {
        usage(progname);
        std::cerr << "Missing grammar file argument" << std::endl;
        return 1;
    }

    std::ifstream grIn(grFileName, std::ios::in);

    if (!grIn.is_open()) {
        std::cerr << "Cannot open grammar file '" << grFileName << "'" << std::endl;
        return 1;
    }

    Grammar gr(grIn);

    if (!gr.isLoaded()) {
        std::cerr << "Cannot load grammar file '" << grFileName << "'" << std::endl;
        grIn.close();
        return 1;
    } else {
        LR0 lr0(gr);
        const LR0::DFA& dfa = lr0.getDFA();

        /* TODO: Print dfa in 'dot' format */
        
        const std::set<std::string>& ts = gr.getTerminals();
        const std::set<std::string>& nts = gr.getNonTerminals();

        std::cout << "Terminal symbols\n";
        for (const auto& s : ts) {
            std::cout << s << "\n";
        }

        std::cout << "Non terminal symbols\n";
        for (const auto& s : nts) {
            std::cout << s << "\n";
        }

        const std::vector<Grammar::Production>& grules = gr.getRules();

        std::cout << "Grammar rules\n";
        for (const auto& rule : grules) {
            std::cout << rule.toString();
        }
    }
}

void usage(const char *progname) {
    std::cerr << "Usage: " << progname << " -g <grammar file>\n"
              << "Ex:  " << progname << " -g grammar.txt\n";
}

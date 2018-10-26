#ifndef _LEXER_H
#define _LEXER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

enum class Token { 
    KwPrint,
    Ident,
    Semicolon,
    OpenPar, 
    ClosePar, 
    OpAssign,
    OpAdd, 
    OpMult, 
    Number, 
    Unknown, 
    Eof
};

using TokenInfo = std::pair<Token, std::string>;

class Lexer {
public:
	Lexer(const std::vector<TokenInfo>& tklst): tklist(tklst) {
        it = tklist.begin();
    }

    Token getNextToken() {
        Token tk = it->first;
        text = it->second;
        
        if (it != tklist.end()) {
            it++;
        }
        
        return tk;
    }
    
    bool hasTokens() { return it != tklist.end(); }
    std::string getText() { return text; }

private:
    std::string text;
    std::vector<TokenInfo> tklist;
    std::vector<TokenInfo>::iterator it;
};
#endif

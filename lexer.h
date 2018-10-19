#ifndef _EXPR_LEXER_H
#define _EXPR_LEXER_H
#include <iostream>
#include <fstream>
#include <string>

enum class Token {
    Decimal,
    Hex,
    Binary,
    Octal,
    Eof
};

class Lexer {
public:
    Lexer(std::istream &in): in(in) {}
    ~Lexer() {}

    Token getNextToken();
    std::string getText() { return text; }

private:
    int currState;
    std::istream &in;
    std::string text;
    int currChar;
    void getNextChar();
    int cont;
    void unGetChar();

};
#endif

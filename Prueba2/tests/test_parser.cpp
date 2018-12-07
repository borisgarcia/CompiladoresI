#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "Lexer.h"
#include "Parser.h"

std::vector<TokenInfo> test1 = { 
    std::make_pair(Token::IDENT, "x"), 
    std::make_pair(Token::ASSIGN_OP, "="),
    std::make_pair(Token::NUMBER, "10"),
    std::make_pair(Token::SEMICOLON, ";"),
    std::make_pair(Token::Eof, "EOF")
};

/*std::vector<TokenInfo> test2 = { 
    std::make_pair(Token::KwPrint, "print"), 
    std::make_pair(Token::OpenPar, "("),
    std::make_pair(Token::Number, "10"),
    std::make_pair(Token::OpAdd, "+"),
    std::make_pair(Token::Number, "20"),
    std::make_pair(Token::ClosePar, ")"),
    std::make_pair(Token::OpMult, "*"),
    std::make_pair(Token::Number, "45"),
    std::make_pair(Token::Semicolon, ";"),
    std::make_pair(Token::Eof, "EOF")
};

std::vector<TokenInfo> test3 = { 
    std::make_pair(Token::Ident, "x"), 
    std::make_pair(Token::OpAssign, "="),
    std::make_pair(Token::Number, "10"),
    std::make_pair(Token::Semicolon, ";"),
    std::make_pair(Token::Ident, "y"), 
    std::make_pair(Token::OpAssign, "="),
    std::make_pair(Token::Number, "20"),
    std::make_pair(Token::Semicolon, ";"),
    std::make_pair(Token::KwPrint, "print"), 
    std::make_pair(Token::OpenPar, "("),
    std::make_pair(Token::Ident, "x"),
    std::make_pair(Token::OpAdd, "+"),
    std::make_pair(Token::Ident, "y"),
    std::make_pair(Token::ClosePar, ")"),
    std::make_pair(Token::Semicolon, ";"),
    std::make_pair(Token::Eof, "EOF")
};*/

TEST_CASE("Simple Assign") {
    Lexer l(test1);
    Parser p(l);
    
    bool parseSuccess = false;
    try {
        p.parse();
        parseSuccess = true;
    } catch (...) {
        parseSuccess = false;
    }
    REQUIRE(!l.hasTokens());
    CHECK(parseSuccess);
}

/*TEST_CASE("Simple Print") {
    Lexer l(test2);
    Parser p(l);
    
    bool parseSuccess = false;
    try {
        p.parse();
        parseSuccess = true;
    } catch (...) {
        parseSuccess = false;
    }
    REQUIRE(!l.hasTokens());
    CHECK(parseSuccess);
}

TEST_CASE("Assign/Print") {
    Lexer l(test3);
    Parser p(l);
    
    bool parseSuccess = false;
    try {
        p.parse();
        parseSuccess = true;
    } catch (...) {
        parseSuccess = false;
    }
    REQUIRE(!l.hasTokens());
    CHECK(parseSuccess);
}*/

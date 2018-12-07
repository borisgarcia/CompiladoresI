#ifndef _AST_H
#define _AST_H

#include <ctype.h>
#include <stdlib.h>
#include <memory>
#include <string> 
#include <iostream>
#include <utility>
#include <vector>

#define DEFINE_OP(opname,oper) \
    class opname##Expr : public binExpr { \
        public: \
            opname##Expr(expre expresion1, expre expresion2) : binExpr(std::move(expresion1), std::move(expresion2)) {} \
            std::string getOp() override { return oper; } \
    }

class ASTNode {
    public:
        ASTNode() { }
        virtual std::string toString() = 0;
};

using expre = ASTNode *;

class binExpr : public ASTNode{
    public:
        binExpr(expre expresion1, expre expresion2) : expresion1(std::move(expresion1)),expresion2(std::move(expresion2)){}
        std::string toString();
        virtual std::string getOp()=0;
        expre expresion1;
        expre expresion2;
};

class NumExpr : public ASTNode {
    public:
        int value;
        NumExpr(int val)
        {
          value = val;
        } 
        std::string toString();
};
class IdExpr : public ASTNode {
    public:
        std::string value;
        IdExpr(std::string val)
        {
          value = val;
        } 
        std::string toString();
};

DEFINE_OP(Add, "+");
DEFINE_OP(Mul, "*");
DEFINE_OP(Sub, "-");
DEFINE_OP(Div, "/");
DEFINE_OP(Mod, "%");



#endif

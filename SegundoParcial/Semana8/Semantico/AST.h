#include <ctype.h>
#include <stdlib.h>
#include <memory>
#include <string> 
#include <iostream>
#include <utility>
#include <vector>

#define DEFINE_OP(opname,oper) \
  class opname##Expression : public binExpression { \
    public: \
      opname##Expression(Expr expresion1, Expr expresion2) : binExpression(std::move(expresion1), std::move(expresion2)) {} \
      std::string getOp() override { return oper; } \
      int Eval(); \
  }

  class Expression {
    public:
      Expression() { }
      virtual int Eval() = 0;
      virtual std::string toString() = 0;
  };

  using Expr = std::unique_ptr<Expression>;
  using ExprList = std::vector<Expr>;

  class binExpression : public Expression{
    public:
      binExpression(Expr expresion1, Expr expresion2) : expresion1(std::move(expresion1)),expresion2(std::move(expresion2)){}
      
      int Eval();
      std::string toString();
      virtual std::string getOp()=0;
      Expr expresion1;
      Expr expresion2;
  };

  DEFINE_OP(Add, "+");
  DEFINE_OP(Multi, "*");
  DEFINE_OP(Sub, "-");
  DEFINE_OP(Div, "/");

  class numberExpression : public Expression {
    public:
      int value;
      numberExpression(int val)
      {
        value = val;
      } 
      int Eval();
      std::string toString();
  };
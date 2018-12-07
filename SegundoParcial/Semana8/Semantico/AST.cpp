#include "AST.h"

int AddExpression::Eval()
{
    return expresion1->Eval() + expresion2->Eval();
}
int SubExpression::Eval()
{
    return expresion1->Eval() - expresion2->Eval();
}
int MultiExpression::Eval()
{
    return expresion1->Eval() * expresion2->Eval();
}
int DivExpression::Eval()
{
    return expresion1->Eval() / expresion2->Eval();
}

int binExpression::Eval() 
{
    return expresion1->Eval() + expresion2->Eval();
}

int numberExpression::Eval()
{
    return this->value;
}

std::string binExpression::toString()
{
    return expresion1->toString() + " " + this->getOp() + " " + expresion2->toString() + ' ';
}

std::string numberExpression::toString()
{
    return std::to_string(this->value);
}


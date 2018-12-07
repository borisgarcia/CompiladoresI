#include "expr_ast.h"

std::string binExpr::toString()
{
    return "("+expresion1->toString()+")"+ this->getOp() + "(" + expresion2->toString() + ")";
}

std::string NumExpr::toString()
{
    return std::to_string(this->value);
}

std::string IdExpr::toString()
{
    return this->value;
}


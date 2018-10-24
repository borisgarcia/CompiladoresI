void E()
{
    T();
    Ep();
}

void Ep()
{
    if(token == Token::Add)
    {
        token == lexer.getNextToken();
        T();
        Ep();
    }
    else
    {
        return;
    }
}

void T()
{
    F();
    Tp();
}

void Tp()
{
    if(token == Token::Multi)
    {
        token == lexer.getNextToken();
        F();
        Tp();
    }
    else
    {
        return;
    }
}

void F()
{
    if(token == Token::Parentesis)
    {
        token == lexer.getNextToken();
        E();
    }
    else
    (
        return NUMBER;
    )

}
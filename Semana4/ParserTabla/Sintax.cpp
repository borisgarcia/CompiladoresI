#include "Sintax.h"

void Sintax::initParser()
{
    init();
    int cont = 0;
    std::string currStack, currInput; 
    int x = 0,y = 0;
    while(1)
    {                
        if(input.size() == 1 && mystack.size()==0)break;

        //Imprimo el Input y el Stack
        for (size_t i = 0; i < input.size(); i++) std::cout << input.at(i);
        std::cout << " | ";
        for (size_t i = 0; i < mystack.size(); i++) std::cout << mystack.at(i);
        std::cout << '\n';

        currStack = mystack.back();
        if(currStack == "NULL")
            throw std::invalid_argument("Sintax Error");

        currInput = input.front();
        
        if(currStack == currInput)
        {
            mystack.pop_back();
            input.pop_front();
            continue;
        }
        else if(currStack == "")
        {
            mystack.pop_back();    
            continue;
        }
        
        for(x = 1; x < 6; x++)
            if(Table[x][0].back() == currStack)
                break;
        
        for(y = 1; y < 7; y++)
            if(Table[0][y].back() == currInput)
                break;

        mystack.pop_back();
        for(int a = Table[x][y].size();a>0;a--)
            mystack.push_back(Table[x][y].at(a-1));
    }
    
    if(mystack.size()!=0)
    {
        throw std::invalid_argument( "\nSintax Error" );
    }
}

void Sintax::init()
{
    initTable();
    mystack.push_front("E");
    lexer.getToken();
    input = lexer.getInput();
    input.push_back("$");
}

void Sintax::initTable()
{
    //Rows
    Table[1][0].push_back("E");
    Table[2][0].push_back("Ep");
    Table[3][0].push_back("T");
    Table[4][0].push_back("Tp");
    Table[5][0].push_back("F");
    
    //Cols
    Table[0][1].push_back("+");
    Table[0][2].push_back("*");
    Table[0][3].push_back("(");
    Table[0][4].push_back(")");
    Table[0][5].push_back("NUM");
    Table[0][6].push_back("$");

    //E
    Table[1][1].push_back("NULL");
    Table[1][2].push_back("NULL");
    Table[1][3].push_back("T");
    Table[1][3].push_back("Ep");
    Table[1][4].push_back("NULL");
    Table[1][5].push_back("T");
    Table[1][5].push_back("Ep");
    Table[1][6].push_back("NULL");
    
    //Ep
    Table[2][1].push_back("+");
    Table[2][1].push_back("T");
    Table[2][1].push_back("Ep");
    Table[2][2].push_back("NULL");
    Table[2][3].push_back("NULL");
    Table[2][4].push_back("");
    Table[2][5].push_back("NULL");
    Table[2][6].push_back("");

    //T
    Table[3][1].push_back("NULL");
    Table[3][2].push_back("NULL");
    Table[3][3].push_back("F");
    Table[3][3].push_back("Tp");
    Table[3][4].push_back("NULL");
    Table[3][5].push_back("F");
    Table[3][5].push_back("Tp");
    Table[3][6].push_back("NULL");

    //Tp
    Table[4][1].push_back("");
    Table[4][2].push_back("*");
    Table[4][2].push_back("F");
    Table[4][2].push_back("Tp");
    Table[4][3].push_back("NULL");
    Table[4][4].push_back("");
    Table[4][5].push_back("NULL");
    Table[4][6].push_back("");


    //F
    Table[5][1].push_back("NULL");
    Table[5][2].push_back("NULL");
    Table[5][3].push_back("(");
    Table[5][3].push_back("E");
    Table[5][3].push_back(")");
    Table[5][4].push_back("NULL");
    Table[5][5].push_back("NUM");
    Table[5][6].push_back("NULL");
}

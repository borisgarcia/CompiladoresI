#include "LexerV2.h"

int main( int argc, char * argv [] )
{
    if(argc != 2)
    {
        std::cout<<"Se necesitan 2 parametros"<<std::endl;
        return 1;
    }

    LexerV2 lexer(argv[1]);
    lexer.getToken();
        
    return 0;
}

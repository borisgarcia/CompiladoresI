#include "Parser.h"

int main( int argc, char * argv [] )
{
    if(argc != 2)
    {
        std::cout<<"Se necesitan 2 parametros"<<std::endl;
        return 1;
    }

    Lexer lexer(argv[1]);

    Parser parser(lexer);

    try
    {
        parser.initParser();
        std::cout << "\nValid Expression" << '\n';
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << e.what() << '\n';
    }    
    return 0;
}

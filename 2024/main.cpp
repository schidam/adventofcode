#include <iostream>
#include "1\1.h"

int 
main(int argc, char * argv[])
{
    Puzzle p;
    std::string fn = "1/1a.txt";
    // std::string fn = "1/ex.txt";
    p.load_data(fn);
    std::cout << "Result: " << p.solveB() << std::endl;
    // p.print_data();
    return 0;
}
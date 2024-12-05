#include <iostream>
#include "4\4.h"

int 
main(int argc, char * argv[])
{
    Puzzle p;
    std::string fn = "4/4.txt";
    // fn = "4/ex.txt";
    std::cout << "Result: " << p.solveB(fn) << std::endl;
    return 0;
}
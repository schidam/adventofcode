#include <iostream>
#include "7\7.h"

int 
main(int argc, char * argv[])
{
    Puzzle p;
    std::string fn = "7/7.txt";
    // fn = "7/ex.txt";
    std::cout << "Result: " << p.solveA(fn) << std::endl;
    return 0;
}
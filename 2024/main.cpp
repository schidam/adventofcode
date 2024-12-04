#include <iostream>
#include "2\2.h"

int 
main(int argc, char * argv[])
{
    Puzzle p;
    std::string fn = "3/3.txt";
    // fn = "3/ex.txt";
    std::cout << "Result: " << p.solve(fn) << std::endl;
    return 0;
}
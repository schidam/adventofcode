#include <iostream>
#include "8\8.h"

int 
main(int argc, char * argv[])
{
    Puzzle p;
    std::string fn = "8/8.txt";
    // fn = "8/ex.txt";
    std::cout << "Result: " << p.solve(fn) << std::endl;
    return 0;
}
#include <iostream>
#include "2\2.h"

int 
main(int argc, char * argv[])
{
    Puzzle p;
    std::string fn = "2/2.txt";
    // fn = "2/ex.txt";
    std::cout << "Result: " << p.solve(fn) << std::endl;
    // p.print_data();
    return 0;
}
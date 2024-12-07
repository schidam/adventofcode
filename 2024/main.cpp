#include <iostream>
#include "5\5.h"

int 
main(int argc, char * argv[])
{
    Puzzle p;
    std::string fn = "5/5.txt";
    // fn = "5/ex.txt";
    std::cout << "Result: " << p.solveB(fn) << std::endl;
    return 0;
}
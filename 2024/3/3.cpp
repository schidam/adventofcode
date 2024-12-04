#include "3.h"
#include <fstream>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <regex>

int
Puzzle::solve(std::string fn) 
{
    int result = 0;
    std::cout << "Loading file: " << fn << std::endl;
    std::ifstream infile(fn);
    
    if (!infile.is_open()) {
        std::cerr << "Failed to open file: " << fn << std::endl;
        return -1;
    }

    std::string line;
    while (std::getline(infile, line)) {
        result += solveB(line);
    }

    return result;
}
int Puzzle::solveA(std::string a) {
    // std::regex r(R'mul(\d*,\d*)');
    // for (std::smatch sm; regex_search(a, sm, r);)
    // {
    //     std::cout << sm.str() << '\n';
    // }
    std::regex r(R"(mul\(\d\d*,\d\d*\))", std::regex::ECMAScript|std::regex::icase);
    std::regex integer(R"(\d\d*)");
    int tres = 0;
    for (std::smatch sm; regex_search(a, sm, r);)
    {
        std::string b = sm.str();
        // std::cout << b << '\n';

        int mres = 1;
        int match = false;
        for (std::smatch sm2; regex_search(b, sm2, integer);) 
        {
            // std::cout << sm2.str() << '\n';
            mres *= std::stoi(sm2.str());
            b = sm2.suffix();
            match = true;
        }
        tres += mres;
        a = sm.suffix();
    }
    return tres;
}

int
Puzzle::solveB(std::string a) 
{    
    std::regex r(R"(do\(\)|mul\(\d\d*,\d\d*\)|don\'t\(\))", std::regex::ECMAScript|std::regex::icase);
    std::regex integer(R"(\d\d*)");
    int tres = 0;
    static bool do_it = true;
    for (std::smatch sm; regex_search(a, sm, r);)
    {
        std::string b = sm.str();
        // std::cout << b << '\n';
        if(do_it || b == "do()") {
            do_it = true;
        }
        if (b == "don't()") {
            do_it = false;
        }

        if (do_it) {
            int mres = 1;
            int match = false;
            for (std::smatch sm2; regex_search(b, sm2, integer);) 
            {
                // std::cout << sm2.str() << '\n';
                mres *= std::stoi(sm2.str());
                b = sm2.suffix();
                match = true;
            }
            if (match)
                tres += mres;
        }
        a = sm.suffix();
    }
    return tres;
}

#include "2.h"
#include <fstream>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <sstream>

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
    std::vector<int> numbers;
    int ln = 0;
    while (std::getline(infile, line)) {
        std::stringstream ss(line);
        ln++;
        int num;
        std::vector<int> a;
        while (ss >> num) {
            a.push_back(num);
        }
        if(solveB(a) == 0) {
            result+=1;
        }
    }

    return result;
}
int Puzzle::solveA(std::vector<int> a) {
    bool safe = true;
    int break_index = 0;
    int d0=0;
    for (int i=1; i < a.size(); ++i) {
        int d = a[i] - a[i-1];
        if(abs(d) == 0) {
            safe = false;
            break_index = i;
            // std::cout << "Found two " << ln << std::endl;
            break;
        }
        if(abs(d) > 3) {
            safe = false;
            break_index = i;
            // std::cout << "Found three " << ln << " "<< a[i] << a[i-1] <<std::endl;
            break;
        }
        int d1 = (d>0) ? 1 : -1;
        if (d0!=0 && d1!=d0) {
            safe = false;
            break_index = i;
            // std::cout << "Found four " <<  " "<< d0 << d1 <<std::endl;
            break;
        }
        d0 = d1;
    }
    return break_index;
}

int
Puzzle::solveB(std::vector<int> a) 
{    
    int safe = 0;
    int break_index = solveA(a);
    int og = break_index;
    if (break_index == 0)
        return 0;
    else {
        std::vector<int> b(a);
        std::vector<int> c(a);

        a.erase(a.begin()+og);
        break_index = solveA(a);
        if (break_index == 0)
            return 0;
        
        if (og >= 2) {
            b.erase(b.begin()+og-2);
            break_index = solveA(b);
            if (break_index == 0)
                return 0;
        }
        if (og >= 1) {
            c.erase(c.begin()+og-1);
            break_index = solveA(c);
            if (break_index == 0)
                return 0;
        }

    }

    return 1;
}

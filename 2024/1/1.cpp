#include "1.h"
#include <fstream>
#include <algorithm>
#include <cmath>
#include <cstdlib>

void 
Puzzle::load_data(std::string fn) 
{
    std::cout << "Loading file: " << fn << std::endl;
    std::ifstream infile(fn);

    int a, b;
    while (infile >> a >> b)
    {
        // std::cout << "Line " << " " << a << " " << b << std::endl;
        line1.push_back(std::move(a));
        line2.push_back(std::move(b));
    }
}

void 
Puzzle::print_data() 
{
    std::cout << "Printing data: " << std::endl;
    for(auto a : line1)
        std::cout << "Line1 " << a << std::endl; 
    for(auto a : line2)
        std::cout << "Line2 " << a << std::endl; 
}

int
Puzzle::solveA() 
{
    // Sort line 1
    std::sort(line1.begin(), line1.end());
    // Sort line 2
    std::sort(line2.begin(), line2.end());
    
    int result = 0;
    for(int i=0; i<line1.size(); ++i) {
        //std::cout << i << " " << line1[i] << " " << line2[i] << std::endl;
        result += abs(line1[i] - line2[i]);
    }
    return result;
}

int
Puzzle::solveB() 
{
    // Sort line 1
    //std::sort(line1.begin(), line1.end());
    // Sort line 2
    std::sort(line2.begin(), line2.end());

    int i=0;
    int j=0;
    std::unordered_map<int,int> line2_counts;
    while(i < line2.size()) {
        int count = 0;
        while(line2[i] == line2[j]) {
            j++;
            count+=1;
        }
        line2_counts[line2[i]] = count;
        i=j;
    }
    
    int result = 0;
    for(auto a: line1) {
        if (line2_counts.contains(a)) {
            result += a*line2_counts[a];
        }
    }
    return result;
}
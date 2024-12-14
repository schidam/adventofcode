#include "7.h"
#include <cassert>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <cstring>
#include <iostream>


void 
Puzzle::loadData(std::string fn) {
    // debug = true;
    std::cout << "Loading file: " << fn << std::endl;
    std::ifstream infile(fn);
    
    if (!infile.is_open()) {
        std::cerr << "Failed to open file: " << fn << std::endl;
    }

    std::vector<uint> input; 
    std::string line;
    while (std::getline(infile, line)) {
        if(debug) std::cout << line << std::endl;
        std::string delimiter = ":";
        std::pair<uint, std::vector<uint>> my_pair;
        
        uint token = stoull(line.substr(0, line.find(delimiter)));
        line.erase(line.begin(), line.begin() + line.find(delimiter) + 2);
        my_pair.first = token;

        std::stringstream row(line);

        std::string s;
        while (std::getline(row,s, ' ')) {
            my_pair.second.push_back((uint)(stoull(s)));
        }
        input_data.push_back(my_pair);
    }
   
    if(debug) {
        for(auto &i: input_data) {
            std::cout << i.first << ":>>";
            for (auto &j: i.second) {
                std::cout << j << " ";
            }
            std::cout << std::endl;
        }
    }
}

uint
Puzzle::solveA(std::string fn) 
{
    uint result = 0;
    // debug = false;
    // debug = true;

    loadData(fn);

    for (auto &p: input_data) {
        // if(debug) std::cout << "INTIAL vec size " << p.second.size() << std::endl;

        bool correct = calculate(p.first, p.second, 1);

        if(correct) {

            if(debug) std::cout << "This line matched with result " << p.first <<std::endl;
            result += p.first;
        }
        
    }
    return result;
}

bool Puzzle::calculate(uint result, std::vector<uint> vec, int level) {
    bool ret = false;
    if(debug) std::cout << std::string( level*4, ' ' ) << "Checking on " << result << " and " << vec.back() << std::endl;
    if( (result % vec.back()) == 0) {
        if(debug) std::cout <<  std::string( level*4, ' ' ) << "YES DIVISIBLE" << std::endl;

        if(vec.size() > 1) {
            if(debug) std::cout <<  std::string( level*4, ' ' ) << "recursing after MUL (DIV)" << std::endl;
            std::vector<uint> vec1(vec);
            vec1.erase(vec1.end());
            ret = calculate(result/vec.back(), vec1, ++level) ;
        } 
        else {
            if(debug) std::cout << std::string( level*4, ' ' ) <<  "size of vec is == 1 in MUL" << std::endl; 
            ret = (result == vec.back()) ? true : false;
        }
    }
    if(!ret) {
        //if not divisible, try -
        if(vec.size() > 1) {
            if(debug) std::cout << std::string( level*4, ' ' ) <<  "recursing after ADD (SUB)" << std::endl;
            std::vector<uint> vec1(vec);
            vec1.erase(vec1.end());
            ret = calculate(result - vec.back(), vec1,++level);
        } else {
            if(debug) std::cout << std::string( level*4, ' ' ) <<  "size of vec is == 1 in ADD" << std::endl; 
            ret = (result == vec.back()) ? true : false;
        }          
    }
    // last element, if true - then check equality
    return ret;
}


int
Puzzle::solveB(std::string fn) 
{
    int result = 0;
    debug = false;

    loadData(fn);
    
    return result;
}

#include "5.h"
#include <fstream>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <regex>

void 
Puzzle::loadData(std::string fn) {
    bool debug = false;
    std::cout << "Loading file: " << fn << std::endl;
    std::ifstream infile(fn);
    
    if (!infile.is_open()) {
        std::cerr << "Failed to open file: " << fn << std::endl;
    }

    std::vector<std::string> input; 
    std::string line;
    while (std::getline(infile, line)) {
        // if(debug) std::cout << line << std::endl;
        if (line.find('|') != std::string::npos) {
            std::stringstream test(line);
            std::string segment;
            std::vector<int> numbers;
            while(std::getline(test, segment, '|')) {
                numbers.push_back(std::stoi(segment));
            }
            ordering_map[numbers[0]].push_back(numbers[1]);
        }
        else {
            std::stringstream test(line);
            std::string segment;
            std::vector<int> numbers;
            if(debug) std::cout << line <<std::endl;

            while(std::getline(test, segment, ',')) {
                int n = std::stoi(segment);
                numbers.push_back(n);
            }
            test_lines.push_back(numbers);
        }
    }
}
int
Puzzle::solveA(std::string fn) 
{
    int result = 0;
    bool debug = false;
    std::cout << "Loading file: " << fn << std::endl;
    std::ifstream infile(fn);
    
    if (!infile.is_open()) {
        std::cerr << "Failed to open file: " << fn << std::endl;
        return -1;
    }

    std::vector<std::string> input; 
    std::string line;
    while (std::getline(infile, line)) {
        // if(debug) std::cout << line << std::endl;
        if (line.find('|') != std::string::npos) {
            std::stringstream test(line);
            std::string segment;
            std::vector<int> numbers;
            while(std::getline(test, segment, '|')) {
                numbers.push_back(std::stoi(segment));
            }
            ordering_map[numbers[0]].push_back(numbers[1]);
        }
        else {
            std::stringstream test(line);
            std::string segment;
            std::vector<int> numbers;
            bool safe = true;
            if(debug) std::cout << line <<std::endl;

            while(std::getline(test, segment, ',')) {
                int n = std::stoi(segment);
                if(ordering_map.contains(n)) {
                    for(auto &i: numbers) {
                        if(std::find(ordering_map[n].begin(), ordering_map[n].end(), i) != ordering_map[n].end())
                            safe = false;
                    }
                }
                if (!safe) {
                    if (debug) std::cout << "               NOT SAFE" << numbers.size() << std::endl;
                    break;
                }
                numbers.push_back(n);
            }

            if(safe && numbers.size() > 0) {
                int index = numbers.size()/2;
                result += numbers[index];
            }
        }
    }
    if (debug) {
        for (auto &i: ordering_map) {
            std::cout << i.first << "\t\t\t"; 
            for (auto &j: i.second) {
                std::cout << j << "|"; 
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    return result;
}

// check if should be before (<) b in the list
bool Puzzle::compare(int a, int b) {
    bool debug = false;
    if(debug) std::cout << "Comparing " << a << " " << b <<std::endl;

    // check if a exists in ordering map    
    if(ordering_map.contains(a)) {
        // if exists, then check if b exists in the list
        if(std::find(ordering_map[a].begin(), ordering_map[a].end(), b) != ordering_map[a].end()) {
            // if b exists, then a < b nd we return true
            return true;
        }
    }
    // else we return false
    return false;
}

int
Puzzle::solveB(std::string fn) 
{
    int result = 0;
    debug = false;

    loadData(fn);
    
    for (auto v: test_lines) {
        if(v.size() > 0) {
            if (!std::is_sorted(std::begin(v), std::end(v), [this](int a, int b) { return compare(a, b); })) {
                std::sort(std::begin(v), std::end(v), [this](int a, int b) { return compare(a, b); });
                if(debug) {
                    for (auto i:v) {
                        std::cout << i << " ";
                    }
                }
                int index = v.size()/2;
                result += v[index];
            }
            if(debug) std::cout <<std::endl;
        }
    }
    return result;
}

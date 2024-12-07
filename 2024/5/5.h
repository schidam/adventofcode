#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

struct Puzzle {
    bool  debug = false;
    std::unordered_map<int, std::vector<int>> ordering_map;
    std::vector<std::vector<int>> test_lines;
    void loadData(std::string);
    int solveA(std::string);
    int solveB(std::string);
    bool compare(int, int);
};

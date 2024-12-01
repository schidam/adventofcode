#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

struct Puzzle {
    std::vector<int> line1;
    std::vector<int> line2;
    std::unordered_map<int, int> similiar_map;
    
    void load_data(std::string fn);
    void print_data();
    int solveA();
    int solveB();
};

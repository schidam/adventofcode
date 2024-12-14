#include "6.h"
#include <fstream>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <regex>
#include <cstring>
#include <ranges>

void 
Puzzle::loadData(std::string fn) {
    debug = true;
    std::cout << "Loading file: " << fn << std::endl;
    std::ifstream infile(fn);
    
    if (!infile.is_open()) {
        std::cerr << "Failed to open file: " << fn << std::endl;
    }

    std::vector<std::string> input; 
    std::string line;
    int line_num = 0;
    while (std::getline(infile, line)) {
        std::stringstream map_row(line);
        // if(debug) std::cout << line <<std::endl;

        std::vector<char> map_row_vector;
        // for(auto &s: line) {
        for (auto const& [index, s] : std::views::enumerate(line)) {
            if(s == guard[0]) {
                guard_loc.x = line_num;
                guard_loc.y = index;
                if(debug) std::cout <<  "guard found at: " << s << " " << guard_loc.x << " " << guard_loc.y << std::endl;
            }
            map_row_vector.push_back(s);
        }
        map.push_back(map_row_vector);
        line_num++;
    }
   
    if(debug) {
        for(auto &i: map) {
            for (auto &j: i) {
                std::cout << j;
            }
            std::cout << std::endl;
        }
    }
}
int
Puzzle::solveA(std::string fn) 
{
    int result = 0;
    debug = false;

    loadData(fn);

    while(move(guard_loc));

    for(auto &i: map) {
        for (auto &j: i) {
            if(debug) std::cout << j;
            if(j == marker[0] || j == guard[0])
                result++;
        }
        if(debug) std::cout << std::endl;
    }

    return result;
}

bool
Puzzle::move(GuardLocation &guard_loc)
{
    int new_x, new_y;
    if(guard_loc.direction == Direction::UP) {
        new_x = guard_loc.x-1;   
        new_y = guard_loc.y;

        if(outOfBounds(new_x, new_y)) {
            // guard escaped. 
            // This is exit condition for game
            return false;
        }
        else if (map[new_x][new_y] == block[0]) {
            // hit block, change direction
            if(debug) std::cout << "Changing direction to right" << std::endl;
            guard_loc.direction = Direction::RIGHT;
        }
    }
    if(guard_loc.direction == Direction::RIGHT) {
        new_x = guard_loc.x;   
        new_y = guard_loc.y+1;

        if(outOfBounds(new_x, new_y)) {
            // guard escaped. 
            // This is exit condition for game
            return false;

        }
        else if (map[new_x][new_y] == block[0]) {
            if(debug) std::cout << "Changing direction to down" << std::endl;
            // hit block, change direction
            guard_loc.direction = Direction::DOWN;
        }
    }
    if(guard_loc.direction == Direction::DOWN) {
        new_x = guard_loc.x+1;   
        new_y = guard_loc.y;

        if(outOfBounds(new_x, new_y)) {
            // guard escaped. 
            // This is exit condition for game
            return false;

        }
        else if (map[new_x][new_y] == block[0]) {
            // hit block, change direction
            guard_loc.direction = Direction::LEFT;
        }
    }
    if(guard_loc.direction == Direction::LEFT) {
        new_x = guard_loc.x;   
        new_y = guard_loc.y-1;

        if(outOfBounds(new_x, new_y)) {
            // guard escaped. 
            // This is exit condition for game
            return false;

        }
        else if (map[new_x][new_y] == block[0]) {
            // hit block, change direction
            guard_loc.direction = Direction::UP;
            new_x = guard_loc.x-1;   
            new_y = guard_loc.y; 
        }
    }
    
    guard_loc.x = new_x;
    guard_loc.y = new_y;
    if(map[new_x][new_y] == marker[0]) {
        std::cout << "Cross detected" << std::endl;
    }
    map[new_x][new_y] = marker[0];

    return true;
}

bool
Puzzle::outOfBounds(int x, int y)
{
    return (x<0 || y <0 || x>=map.size() || y>=map.size())? true : false;
}


int
Puzzle::solveB(std::string fn) 
{
    int result = 0;
    debug = false;

    loadData(fn);
    
    return result;
}

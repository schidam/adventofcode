#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>

enum class Direction {UP=0, RIGHT=1, DOWN=2, LEFT=3};

struct GuardLocation {
    int x;
    int y;
    Direction direction = Direction::UP;

    void print_location() {
        std::cout << "Guard Located at " << x << "," << y <<std::endl;
    }
};

struct Puzzle {
    bool debug = false;
    std::vector<std::vector<char>> map;
    const char* guard = "^";
    const char* block = "#";
    const char* marker = "X";
    GuardLocation guard_loc;

    bool move(GuardLocation &g);
    bool outOfBounds(int, int);

    void loadData(std::string);
    int solveA(std::string);
    int solveB(std::string);
};

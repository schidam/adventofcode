#include <string>
#include <utility>
#include <vector>

typedef long long uint;
enum class OPERATION {ADD=0, MUL=1, ANY=3};

struct Puzzle {
    bool debug = false;
    std::vector<std::pair<uint, std::vector<uint>>> input_data;

    void loadData(std::string);
    uint solveA(std::string);
    int solveB(std::string);

    bool calculate(const uint, std::vector<uint>, int level);
};

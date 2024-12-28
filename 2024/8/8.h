#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

typedef long long uint;
enum class OPERATION {ADD=0, MUL=1, ANY=3};

struct loc {
    int x;
    int y;

    loc(int a, int b) : x(a), y(b) {}
    std::string print() const {
        std::string ret = '"' + std::to_string(x) + "," + std::to_string(y) + '"';
        return  ret;
    }

    bool operator==(const loc& A) const { return (A.x==x && A.y==y); }

};

// Define hash specialization for `loc`
namespace std {
    template <>
    struct hash<loc> {
        std::size_t operator()(const loc& l) const {
            return std::hash<int>()(l.x) ^ (std::hash<int>()(l.y) << 1);
        }
    };
}

struct Puzzle {
    bool debug = false;
    std::vector<std::string> input_data;

    std::unordered_map<char, std::vector<loc>> map;

    void loadData(std::string);
    int solve(std::string);
    int addTowers(std::pair<const char, std::vector<loc>>&, std::unordered_set<loc>&);

    bool calculate(const uint, std::vector<uint>, int level);

    bool checkBounds(loc L);
    std::vector<loc> get_towers(loc A, loc B);
};

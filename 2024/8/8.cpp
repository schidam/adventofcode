#include "8.h"
#include <cassert>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <unordered_map>
#include <utility>
#include <vector>
#include <cstring>
#include <iostream>
#include <unordered_set>

void
Puzzle::loadData(std::string fn) {
    debug = false;
    std::cout << "Loading file: " << fn << std::endl;
    std::ifstream infile(fn);

    if (!infile.is_open()) {
        std::cerr << "Failed to open file: " << fn << std::endl;
    }

    std::vector<uint> input;
    std::string line;
    int x = 0;
    while (std::getline(infile, line)) {
        if(debug) std::cout << line << std::endl;
        input_data.push_back(line);
        int y = 0;
        for(auto &j : line) {
            if (j != '.') {
                if(debug) std::cout << "Found " << j << " at " << x << "," << y << std::endl;
                map[j].push_back(loc(x,y));
            }
            y++;
        }
        x++;
    }
    debug = true;
    if(debug) {
        std::cout << "GRID SIZE: " << input_data.size() << " by " << input_data.at(0).size() <<std::endl;
        for(auto &i: input_data) {
            for (auto &j: i) {
                std::cout << j << " ";
            }
            std::cout << std::endl;
        }

        for(auto &i: map) {
            std::cout << i.first << "\t";
            for(auto &j: i.second) {
                std::cout << j.print() << " ";
            }
            std::cout << std::endl;
        }
    }    
    debug = false;
}


std::vector<loc>
Puzzle::get_towers(loc A, loc B)
{
    debug = false;
    int x_dist = A.x - B.x;
    int y_dist = A.y - B.y;
    std::vector<loc> towers{};

    if(x_dist == 0 && y_dist == 0) {
        exit(20);
    }
    else {
        if(debug) std::cout << "Case 1 " << x_dist << " " << y_dist <<std::endl;
        bool new_nodes_added = true;
        for(int i=1; new_nodes_added == true; i++) {
            loc node = loc(A.x + x_dist*i, A.y + y_dist*i);
            if(debug) std::cout << "Checking node " << node.print();
            if(Puzzle::checkBounds(node)) {
                towers.push_back(node);
                new_nodes_added = true;
                if(debug) std::cout << "\tIn bounds" << std::endl;
            } else {
                new_nodes_added = false;
                if(debug) std::cout << "\tOt bounds" << std::endl;
            }
        }
        new_nodes_added = true;
        for(int i=1; new_nodes_added == true; i++) {
            loc node = loc(B.x - x_dist*i, B.y - y_dist*i);
            if(debug) std::cout << "Checking node " << node.print();
            if(Puzzle::checkBounds(node)) {
                towers.push_back(node);
                new_nodes_added = true;
                if(debug) std::cout << "\tIn bounds" << std::endl;
            } else {
                new_nodes_added = false;
                if(debug) std::cout << "\tOt bounds" << std::endl;
            }
        }
    }
    return towers;
}

bool
Puzzle::checkBounds(loc L) {
    return ((L.x <0) || (L.y < 0) || (L.y >= input_data.at(0).size()) || (L.x >= input_data.size())) ? false : true;
}

int
Puzzle::solve(std::string fn)
{
    int result = 0;
    int common = 0;

    loadData(fn);
    std::unordered_set<loc> main_results{};

    for (auto &p: map) {
        if (p.second.size() > 1) {
            std::unordered_set<loc> results{};
            int new_towers = addTowers(p, results);
            // results has all the locs where a node was added. 
            // new_towers has the number of locs added. 
            result += new_towers;
            result += p.second.size();
            if(debug) std::cout << "Added Towers Count: " << results.size() << std::endl;
            for (auto &i: results) {
                if(main_results.contains(i)) {
                    common++;
                    if(debug) std::cout << "Common Node: " << i.print() << std::endl;
                }
            }
            main_results.merge(results);

            for (auto &i: main_results) {
                if(input_data[i.x][i.y] == '.') {
                    input_data[i.x][i.y] = '#';
                }
            }

            if(debug) {
                for(auto &i: input_data) {
                    for (auto &j: i) {
                        if(debug) std::cout << j << " ";
                    }
                    if(debug) std::cout << std::endl;
                }
            }
        }
    }

    if(debug) {
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;

        for(auto &i: input_data) {
            for (auto &j: i) {
                std::cout << j << " ";
            }
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "\tRes:\t" << result << "\tCommon:\t" << common << std::endl;
    
    return result-common;
}

// results has all the locs where a node was added. 
// we return the size of towers
int 
Puzzle::addTowers(std::pair<const char, std::vector<loc>> &p, std::unordered_set<loc> &results)
{
    if(debug) {
        if(debug) std::cout << "P contains\t\t";
        for(auto &i: p.second) {
            if(debug) std::cout << i.print() << ", ";
        }
        if(debug) std::cout << std::endl;
    }
    int new_towers = 0;
    for (size_t i=0; i<p.second.size(); i++) {
        for (size_t j=i+1; j<p.second.size(); j++) {
            if(debug) std::cout << "Char: "<< p.first << "\tA: " << p.second[i].print() << "\t, B:" << p.second[j].print() << std::endl;
            std::vector<loc> towers = get_towers(p.second[i], p.second[j]);

            for(auto &A : towers) {
                results.insert(A);
                new_towers++;
            }
        }
    }
    for(auto &A : p.second) {
        results.insert(A);
    }

    return new_towers;
}
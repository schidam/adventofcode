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
    debug = true;
    // debug = false;
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
}


std::vector<loc>
get_towers(loc A, loc B)
{
    bool debug = true;
    debug = false;
    int x_dist = A.x - B.x;
    int y_dist = A.y - B.y;

    if(x_dist < 0 && y_dist < 0) {
        //Case: -1, -1
        //      A .
        //      . B
        if(debug) std::cout << "Case 1 " << x_dist << " " << y_dist <<std::endl;
        return std::vector{loc(A.x + x_dist, A.y + y_dist), loc(B.x - x_dist, B.y - y_dist)};

    } else if (x_dist < 0 && y_dist > 0) {
        //Case: -1, 1
        //      . A
        //      B .
        if(debug) std::cout << "Case 2" << x_dist << " " << y_dist << std::endl;
        return std::vector{loc(A.x + x_dist, A.y + y_dist), loc(B.x - x_dist, B.y - y_dist)};

    // } else if (x_dist > 0 && y_dist < 0) {
    //     //Case: 1, -1
    //     //      . B
    //     //      A .
    //     if(debug) std::cout << "Case 3" << x_dist << " " << y_dist << std::endl;
    //     return std::make_pair(loc(A.x - x_dist, A.y + y_dist), loc(B.x + x_dist, B.y + y_dist));

    // } else if (x_dist > 0 && y_dist > 0) {
    //     //Case: 1, 1
    //     //      B .
    //     //      . A
    //     if(debug) std::cout << "Case 4" << x_dist << " " << y_dist << std::endl;
    //     return std::make_pair(loc(A.x + x_dist, A.y + y_dist), loc(B.x - x_dist, B.y - y_dist));
    } else {
        assert(0);
    }
}

bool
Puzzle::check_bounds(loc L) {
    return ((L.x <0) || (L.y < 0) || (L.y >= input_data.at(0).size()) || (L.x >= input_data.size())) ? false : true;
}

int
Puzzle::solve(std::string fn)
{
    int result = 0;
    int common = 0;
    // debug = false;
    // debug = true;

    loadData(fn);
    std::unordered_set<loc> main_results{};

    for (auto &p: map) {
        if (p.second.size() > 1) {
            std::unordered_set<loc> results{};
            for (size_t i=0; i<p.second.size(); i++) {
                for (size_t j=i+1; j<p.second.size(); j++) {
                    if(debug) std::cout << "Char: "<< p.first << "\tA: " << p.second[i].print() << "\t, B:" << p.second[j].print() << std::endl;
                    std::vector<loc> towers = get_towers(p.second[i], p.second[j]);

                    for(auto &A : towers) {
                        if(check_bounds(A)) {
                            results.insert(A);
                        }
                    }
                }
            }
            result += results.size();
            for (auto &i: results) {
                if(main_results.contains(i)) {
                    common++;
                }
            }
            main_results.merge(results);
        }
    }

    // result = 0;
    if(debug) {
        for(auto &i: input_data) {
            for (auto &j: i) {
                std::cout << j << " ";
                // if (j == '#') 
                    // result++;
            }
            std::cout << std::endl;
        }
    }
    return result-common;
}


                    // if(debug) std::cout << "\t\tTowers at: "; 
                    // if(check_bounds(towers.first)) {
                    //     if(debug) std::cout << towers.first.print();
                    //     results.insert(towers.first);
                    //     int x = towers.first.x;
                    //     int y = towers.first.y;

                    //     if(input_data[x][y] == '#') 
                    //         common++;
                    //     if(input_data[x][y] == '.') 
                    //         input_data[x][y] = '#';
                    // }  
                    // if(debug) std::cout << "\t";
                    // if(check_bounds(towers.second)) {
                    //     if(debug) std::cout << towers.second.print();
                    //     results.insert(towers.second);

                    //     int x = towers.second.x;
                    //     int y = towers.second.y;

                    //     if(input_data[x][y] == '#') 
                    //         common++;
                        
                    //     input_data[x][y] = '#';

                    // }
                    // if(debug) std::cout << std::endl;
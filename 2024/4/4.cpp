#include "4.h"
#include <fstream>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <regex>

int
Puzzle::solveA(std::string fn) 
{
    int result = 0;
    std::cout << "Loading file: " << fn << std::endl;
    std::ifstream infile(fn);
    
    if (!infile.is_open()) {
        std::cerr << "Failed to open file: " << fn << std::endl;
        return -1;
    }

    // define xmas kernel
    std::string X = "X";
    std::string E = "XMAS";
    std::string W = "SAMX";
    
    std::vector<std::string> input;
    std::string l;
    bool debug = true;
    while (std::getline(infile, l)) {
        input.push_back(l);
    }

    for(int h=0; h<input.size(); h++) {
        if(debug) std::cout << input[h] << " " << h << std::endl;
        // iterate of each element of the current line:
        for(int i=0; i<input[h].size(); i++) {
            if(input[h].at(i) == X.at(0)) { // If pos matches X, then
                if(debug) std::cout << "  match X at " << h << " " << i << std::endl;

                if( (i<=input[h].size()-4) && solveX(input[h].substr(i, 4), E) ) {
                    result += 1;
                    if(debug) std::cout << "      Found E match at " << h << " " << i << std::endl;
                }
                
                if( (i>=3) && solveX(input[h].substr(i-3, 4), W) ) {
                    result += 1;
                    if(debug) std::cout << "      Found W match " << input[h].substr(i-3, 4) << "at " << h << " " << i << std::endl;
                }

                if( (h>=3) ) {
                    std::string str = "";
                    for (int j=h-3; j<=h; j++) {
                        str += input[j][i];
                    }
                    if(solveX(str, W)) {
                        if(debug) std::cout << "      Found N match " << h << " " << i << std::endl;
                        result+=1;
                    }
                }

                if( (h<=input.size()-4) ) {
                    std::string str = "";
                    for (int j=h; j<=h+3; j++) {
                        str += input[j][i];
                    }
                    if(solveX(str, E)) {
                        if(debug) std::cout << "      Found S match " << h << " " << i << std::endl;
                        result+=1;
                    }
                }

                // NW h- i-
                if( h>=3 && i>=3) {
                    std::string str = "";
                    for (int j=0; j<=3; j++) {
                        str += input[h-j][i-j];
                    }
                    if(solveX(str, E)) {
                        if(debug) std::cout << "      Found NW match " << h << " " << i << std::endl;
                        result+=1;
                    }
                }

                // NE h- i+
                if( h>=3 && (i<=input[h].size()-4)) {
                    std::string str = "";
                    for (int j=0; j<=3; j++) {
                        str += input[h-j][i+j];
                    }
                    if(solveX(str, E)) {
                        if(debug) std::cout << "      Found NE match " << h << " " << i << std::endl;
                        result+=1;
                    }
                }

                //SE h+ i+
                if( (h<=input.size()-4) && (i<=input[h].size()-4)) {
                    std::string str = "";
                    for (int j=0; j<=3; j++) {
                        str += input[h+j][i+j];
                    }
                    if(solveX(str, E)) {
                        if(debug) std::cout << "      Found SE match " << h << " " << i << std::endl;
                        result+=1;
                    }
                }

                // SW h+ i-
                if( (h<=input.size()-4) && i>=3) {
                    std::string str = "";
                    for (int j=0; j<=3; j++) {
                        str += input[h+j][i-j];
                    }
                    if(solveX(str, E)) {
                        if(debug) std::cout << "      Found SW match " << h << " " << i << std::endl;
                        result+=1;
                    }
                }
            }
        }
        
    }

    return result;
}
bool Puzzle::solveX(std::string a, std::string EW) {
    bool debug = true;;
    if(debug) std::cout << "Comparing " << a << " " << EW <<std::endl;
    return (a == EW) ? true : false;
}

int
Puzzle::solveB(std::string fn) 
{
    int result = 0;
    std::cout << "Loading file: " << fn << std::endl;
    std::ifstream infile(fn);
    
    if (!infile.is_open()) {
        std::cerr << "Failed to open file: " << fn << std::endl;
        return -1;
    }

    // define xmas kernel
    std::string A = "A";
    
    std::vector<std::string> input;
    std::string l;
    bool debug = false;
    while (std::getline(infile, l)) {
        input.push_back(l);
    }

    for(int h=0; h<input.size(); h++) {
        if(debug) std::cout << input[h] << " " << h << std::endl;
        // iterate of each element of the current line:
        for(int i=0; i<input[h].size(); i++) {
            if(input[h].at(i) == A.at(0)) { // If pos matches X, then
                if(debug) std::cout << "  match A at " << h << " " << i << std::endl;

                if( h>=1 && i>=1 && (h<=input.size()-2) && (i<=input[h].size()-2) ){
                    int xmas = 1;

                    std::string diag1 = "";
                    for (int j=-1; j<=1; j++) {
                        diag1 += input[h+j][i+j];
                    }
                    if(debug) std::cout << "  diag1 " << diag1 << std::endl;
                    xmas = xmas * (diag1 == "MAS" || diag1 == "SAM")? 1:0;

                    std::string diag2 = "";
                    for (int j=1; j>=-1; j--) {
                        diag2 += input[h+j][i-j];
                    }
                    if(debug) std::cout << "  diag2 " << diag2 << std::endl;
                    xmas = xmas * (diag2 == "MAS" || diag2 == "SAM")? 1:0;

                    result += xmas;
                }
            }
        }
        
    }

    return result;
}

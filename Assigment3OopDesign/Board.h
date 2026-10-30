#pragma once
#include <vector> 
#include <iostream>
#include "string"
#include "ColorCode.h"

using namespace std;

inline const int BOARD_WIDTH = 21;
inline const int BOARD_HEIGHT = 29;

struct forBoard {
    char symbol = ' ';
    std::string color = "";
};


class Board {
private:
    std::vector<std::vector<forBoard>> grid;
public:
    Board();
    void setSym(int x, int y, char symbol, const std::string& color);
    void initBorder();
    void clearInner();
    void print();
    char getSym(int x, int y) const;
    bool isFullLine(int& y) const;
    void DelFullLine();
};
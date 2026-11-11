#pragma once
#include <vector> 
#include <iostream>
#include "string"
#include <SFML/Graphics.hpp>


using namespace std;

inline const int BOARD_WIDTH = 21; //21
inline const int BOARD_HEIGHT = 29;   //29

struct forBoard {
    char symbol = ' ';
    sf::Color color;
};


class Board {
private:
    std::vector<std::vector<forBoard>> grid;
public:
    Board();
    void setSym(int x, int y, char symbol, sf::Color color);
    void initBorder();
    void clearInner();
    char getSym(int x, int y) const;
    bool isFullLine(int& y) const;
    int DelFullLine();
    sf::Color getColor(int x, int y) const;
};
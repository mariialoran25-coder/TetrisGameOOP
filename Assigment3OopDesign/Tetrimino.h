#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "Board.h"

class Tetrimino {
protected:
    std::vector<std::vector<int>> tetrimo;
    int coordX = 0;
    int coordY = 0;
    std::string color = "white";
public:
    Tetrimino();
    virtual void updCoordinates(int newX, int newY);
    virtual void draw(Board& board);
    bool canRotate(Board& board);
    virtual void rotate(Board& board);
    std::vector<std::vector<int>> getMatrix() const;
    std::string getColor() const;
};
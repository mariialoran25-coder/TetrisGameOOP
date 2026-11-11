#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "Board.h"
#include <SFML/Graphics.hpp>

class Tetrimino {
protected:
    std::vector<std::vector<int>> tetrimo;
    int coordX = 0;
    int coordY = 0;
    sf::Color color;
public:
    Tetrimino();
    virtual ~Tetrimino() = default;
    virtual void updCoordinates(int newX, int newY);
    virtual void draw(Board& board) ;

    bool canRotate(Board& board);
    virtual void rotate(Board& board);
    virtual std::vector<std::vector<int>> getMatrix() const;

    sf::Color getColor() const;
};
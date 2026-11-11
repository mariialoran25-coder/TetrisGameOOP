#pragma once
#include <vector> 
#include <iostream>
#include "string"
#include "Board.h"
#include <SFML/Graphics.hpp>

using namespace std;

Board::Board() : grid(BOARD_HEIGHT, std::vector<forBoard>(BOARD_WIDTH)) {}

void Board::setSym(int x, int y, char symbol, sf::Color color) {
    if (x >= 0 && x < BOARD_WIDTH && y >= 0 && y < BOARD_HEIGHT) {
        grid[y][x].symbol = symbol;
        grid[y][x].color = color;
    }
}
sf::Color  Board::getColor(int x, int y) const {
    if (x >= 0 && x < BOARD_WIDTH && y >= 0 && y < BOARD_HEIGHT) {
        return grid[y][x].color;
    }
    return sf::Color::Transparent;
}


void Board::initBorder() {
    for (int i = 0; i < BOARD_HEIGHT; ++i) {
        for (int j = 0; j < BOARD_WIDTH; ++j) {
            if (i == BOARD_HEIGHT - 1) {
                grid[i][j].symbol = '-';
                grid[i][j].color = sf::Color::Blue;
            }
            else if (j == 0 || j == BOARD_WIDTH - 1) {
                grid[i][j].symbol = '|';
                grid[i][j].color = sf::Color::Blue;
            }
            else {
                grid[i][j].symbol = ' ';
                grid[i][j].color = sf::Color::Transparent;
            }
        }
    }
}

void Board::clearInner() {
    for (int i = 0; i < BOARD_HEIGHT; ++i) {
        for (int j = 0; j < BOARD_WIDTH; ++j) {
            if (i < BOARD_HEIGHT - 1 && j>0 && j < BOARD_WIDTH - 1) {
                if (grid[i][j].symbol != '#') {
                    grid[i][j].symbol = ' ';
                    grid[i][j].color = sf::Color::Transparent;
                }
            }
        }
    }
}
//void Board::print() {
//    for (int i = 0; i < BOARD_HEIGHT; ++i) {
//        for (int j = 0; j < BOARD_WIDTH; ++j) {
//            if (grid[i][j].color != sf::Color::Transparent) {
//                grid[i][j].color  = colo;
//            }
//            std::cout << grid[i][j].symbol;
//            std::cout << "\033[0m";
//        }
//        std::cout << "\n";
//    }
//}
char Board::getSym(int x, int y) const {
    if (x >= 0 && x < BOARD_WIDTH && y >= 0 && y < BOARD_HEIGHT) {
        return grid[y][x].symbol;
    }
    return ' ';
}

bool Board::isFullLine(int& y) const
{
    for (int j = 1; j < BOARD_WIDTH - 1; ++j) {
        char sym = getSym(j, y);
        if (sym != '#')
        {
            return false;
        }
    }
    return true;
}

int Board::DelFullLine() {
    int linesCleared = 0;
    for (int i = BOARD_HEIGHT - 1; i > 0; --i) {
        if (isFullLine(i)) {
            for (int row = i; row > 0; --row)
                for (int j = 1; j < BOARD_WIDTH - 1; ++j) {
                    grid[row][j] = grid[row - 1][j];
                    
                }
                
            for (int j = 1; j < BOARD_WIDTH - 1; ++j) {
                grid[0][j].symbol = ' ';
                grid[0][j].color = sf::Color::Transparent;
            }
            linesCleared++;
            ++i;
        }
    }
    return linesCleared;
}
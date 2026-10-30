#pragma once
#include <vector> 
#include <iostream>
#include "string"
#include "ColorCode.h"
#include "Board.h"
using namespace std;

Board::Board() : grid(BOARD_HEIGHT, std::vector<forBoard>(BOARD_WIDTH)) {}

void Board::setSym(int x, int y, char symbol, const std::string& color) {
    if (x >= 0 && x < BOARD_WIDTH && y >= 0 && y < BOARD_HEIGHT) {
        grid[y][x].symbol = symbol;
        grid[y][x].color = color;
    }
}
void Board::initBorder() {
    for (int i = 0; i < BOARD_HEIGHT; ++i) {
        for (int j = 0; j < BOARD_WIDTH; ++j) {
            if (i == BOARD_HEIGHT - 1) {
                grid[i][j].symbol = '-';
                grid[i][j].color = "";
            }
            else if (j == 0 || j == BOARD_WIDTH - 1) {
                grid[i][j].symbol = '|';
                grid[i][j].color = "";
            }
            else {
                grid[i][j].symbol = ' ';
                grid[i][j].color = "";
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
                    grid[i][j].color = "";
                }
            }
        }
    }
}
void Board::print() {
    for (int i = 0; i < BOARD_HEIGHT; ++i) {
        for (int j = 0; j < BOARD_WIDTH; ++j) {
            if (!grid[i][j].color.empty()) {
                ColorCode::GetColorCode(grid[i][j].color);
            }
            std::cout << grid[i][j].symbol;
            std::cout << "\033[0m";
        }
        std::cout << "\n";
    }
}
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

void Board::DelFullLine() {
    for (int i = BOARD_HEIGHT - 1; i > 0; --i) {
        if (isFullLine(i)) {
            for (int row = i; row > 1; --row)
                for (int j = 1; j < BOARD_WIDTH - 1; ++j) {
                    grid[row][j] = grid[row - 1][j];
                }
            for (int j = 1; j < BOARD_WIDTH - 1; ++j) {
                grid[1][j].symbol = ' ';
                grid[1][j].color = "";
            }
            --i;
        }
    }
}
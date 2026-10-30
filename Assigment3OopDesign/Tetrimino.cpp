#pragma once
#include "Tetrimino.h"

Tetrimino::Tetrimino() {}

void Tetrimino::updCoordinates(int newX, int newY) {
    coordX = newX;
    coordY = newY;
}
void Tetrimino::draw(Board& board) {
    size_t n = tetrimo.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (tetrimo[i][j] == 1)
            {
                int boardX = coordX + j;
                int boardY = coordY + i;
                board.setSym(boardX, boardY, '*', color);
            }
        }
    }
}

bool Tetrimino::canRotate(Board& board) {
    std::vector<std::vector<int>> temp = tetrimo;
    size_t n = tetrimo.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {

            temp[i][j] = tetrimo[j][n - 1 - i];
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (temp[i][j] == 1)
            {
                int boardX = coordX + j;
                int boardY = coordY + i;
                if (boardX < 0 || boardX >= BOARD_WIDTH || boardY >= BOARD_HEIGHT || boardY < 0) {
                    return false;
                }
                if (board.getSym(boardX, boardY) != ' ') {
                    return false;
                }
            }
        }
    }
    return true;
}

void Tetrimino::rotate(Board& board) {
    if (canRotate(board)) {
        std::vector<std::vector<int>> matrix_rotate = tetrimo;
        size_t n = tetrimo.size();
        for (int y = 0; y < n; ++y) {
            for (int x = 0; x < n; ++x)
            {
                tetrimo[x][n - 1 - y] = matrix_rotate[y][x];
            }
        }
    }
}
//{ 1,0,0,0 }, { 1,1,1,1 },
//{ 1,0,0,0 }, { 0,0,0,0 },
//{ 1,0,0,0 }, { 0,0,0,0 },
//{ 1,0,0,0 }, { 0,0,0,0 },

std::vector<std::vector<int>> Tetrimino::getMatrix() const {
    return tetrimo;
}
std::string Tetrimino::getColor() const {
    return  color;
}

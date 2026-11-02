#pragma once
#include <vector> 
#include <iostream>
#include <string>
#include "Board.h"
#include "Tetrimino.h"


class TetrisGame {
private:
    string State;
    int _score = 0;
    bool isGameOver() const;
    const int gridSize = 15;
    Board& board_;
    std::vector<int> topScores;
    void resetBoard();
public:
    TetrisGame(Board& board);
    Board& getBoard();
    void scoreLines(int linesCount);
    void saveScore();
    const std::vector<int>& getTopScores() const;
    //void collect(Point& coin);
    void SpawnNewShape(Tetrimino*& currT, Board& board, int& x, int& y);
    bool IsSpawn(Tetrimino* tet);

    bool canMoveLeft(Board& board, Tetrimino& tet, int coordX, int  coordY);
    void landTetrimino(Board& board, Tetrimino& tet, int& x, int& y);
    void moveLeft(Board& board, Tetrimino*& tet, int& x, int& y);

    bool canMoveRight(Board& board, Tetrimino& tet, int coordX, int  coordY);
    void moveRight(Board& board, Tetrimino*& tet, int& x, int& y);
    bool canSoftDrop(Board& board, Tetrimino& tet, int coordX, int  coordY);
    void SoftDrop(Board& board, Tetrimino*& tet, int& x, int& y);
    void hardDrop(Board& board, Tetrimino*& tet, int& x, int& y);

    int getScore() const;
    void addScore(int value);
    bool isGameOver(Board& board, Tetrimino& tet, int& x, int& y) const;
};
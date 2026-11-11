#pragma once
#include <vector> 
#include <iostream>
#include <string>
#include "Board.h"
#include "Tetrimino.h"


class TetrisGame {
private:
    string State;
    Board& board_;
    std::vector<int> topScores;
    sf::Time lockTimer_ = sf::Time::Zero;

    int _score = 0;
    const int gridSize = 15;
    bool gameOver_ = false;

    std::unique_ptr<Tetrimino> current_;
    int currentX_ = 0;
    int currentY_ = 0;

    bool canMoveRight( int coordX, int  coordY)const;
    bool canMoveLeft( int coordX, int  coordY)const;
    bool canSoftDrop( int coordX, int  coordY)const;


public:
    TetrisGame(Board& board);
    Board& getBoard();
    void reset();


    const std::vector<int>& getTopScores() const;
    void SpawnNewShape();
    bool hasActiveShape() const;
    bool IsSpawn(const Tetrimino* tet);

   
    void landTetrimino();
    void moveLeft();
    void moveRight();
    void SoftDrop( sf::Time dt);
    void hardDrop();
    void rotate();


    int getScore() const;
    void addScore(int value);

    void update(sf::Time dt);
    bool isGameOver() const;
    void saveScores(const std::string& path) const;
    void loadScores(const std::string& path);
    void saveScore();
    void scoreLines(int linesCount);
};
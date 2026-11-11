#pragma once
#include <string>
#include <iostream>
#include "Board.h"
#include "Tetrimino.h"
#include "TetrisGame.h"

class Renderer {
private:
    const int cellSize;
    const int windowWidth;
    const int windowHeight;
    enum state {
        stateMenu,
        stateGame,
        stateInstructuion,
        stateContinue,
        stateStatus
    };
    state curr_state = stateMenu;
    sf::RenderWindow window;
    sf::Font font;
    bool fontLoaded;

    void processEvents(TetrisGame& game, sf::Time& dropTime);
    void render(const TetrisGame& game);

public:
    Renderer();
    void GemeOver(Board& board,TetrisGame& game);
    void run(Board& board, TetrisGame& game);
};
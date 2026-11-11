#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <optional>
#include <iostream>
#include <ctime>

#include "Board.h"
#include "Tetrimino.h"
#include "TetriminoFactory.h"
#include "TetrisGame.h"
#include "Renderer.h"

using namespace std;

int main()
{
    srand(static_cast<unsigned int>(time(0)));

    Board board;
    board.initBorder(); 

    TetrisGame game(board);
    //std::string myFilePath = R"(C:\2курсПрограмнаІнженеріяKSE\CS440OopPracticesAndDesignElements\Assigment3OopDesign\scores.txt)";
    game.loadScores("scores.txt");

    if (!game.hasActiveShape()) {
        game.SpawnNewShape();
    }

    Renderer render;
    
    render.run(board,game);
    //game.saveScores("scores.txt");
 
    return 0;
}

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <optional>
#include <iostream>
#include <ctime>

#include "ColorCode.h"
#include "Board.h"
#include "Tetrimino.h"
#include "TetriminoFactory.h"
#include "TetrisGame.h"
#include "Renderer.h"

using namespace std;

//
//
//class Point {
//private:
//    int _value;
//    bool taken = false;
//public:
//    Point(int value) : _value(value) {}
//    int take() {
//        if (!taken) {
//            taken = true;
//            return _value;
//        }
//        return 0;
//    }
//    bool canTake() {
//    }
//};



int main()
{
    srand(static_cast<unsigned int>(time(0)));

    Board board;
    board.initBorder(); 

    TetrisGame game(board);
    Tetrimino* activeTermino = nullptr;
    
    int x = 0;
    int y = 0;
    game.SpawnNewShape(activeTermino, board,x,y);

    Renderer render;
    render.run(board,game, activeTermino,x,y);

    delete activeTermino;
 
    return 0;
}

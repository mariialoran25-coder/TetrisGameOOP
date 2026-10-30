#include "TetriminoFactory.h"
#include "Tetrimino.h"
#include "Tetrimo_Palka.h"
#include "Tetrimo_J.h"
#include "Tetrimo_L.h"
#include "Tetrimo_Box.h"
#include "Tetrimo_S.h"
#include "Tetrimo_T.h"
#include "Tetrimo_Z.h"

Tetrimino* TetriminoFactory::createRandom() {
    int type = rand() % 7;
    switch (type) {
    case 0:return new Tetrimo_Palka();
    case 1:return new Tetrimo_J();
    case 2:return new Tetrimo_L();
    case 3:return new Tetrimo_Box();
    case 4:return new Tetrimo_S();
    case 5:return new Tetrimo_T();
    case 6:return new Tetrimo_Z();
    default: return nullptr;
    }
}


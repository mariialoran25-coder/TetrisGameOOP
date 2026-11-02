#include "TetrisGame.h"
#include "TetriminoFactory.h"
void TetrisGame::resetBoard()
{
std::cout << "Board is clear\n";
}

Board& TetrisGame::getBoard() {
    return board_;
}

TetrisGame::TetrisGame(Board& board) :board_(board) {
    resetBoard();
}

void TetrisGame::scoreLines(int linesCount) {
    if (linesCount <= 0) return;
    int points = 0;
    if (linesCount == 1) points = 100;
    else if (linesCount == 2) points = 300;
    else if (linesCount == 3) points = 500;
    else if (linesCount == 4) points = 800;
    _score += points;

}
void TetrisGame::saveScore() {
    if (_score > 0) {
        topScores.push_back(_score);
        std::sort(topScores.rbegin(), topScores.rend());
        if (topScores.size() > 5) {
            topScores.resize(5);
        }
    }
}
const std::vector<int>& TetrisGame::getTopScores() const {
    return topScores;
}

//void TetrisGame::collect(Point& coin) {
//    int val = coin.take();
//    if (val > 0) {
//        _score = _score + val;
//        cout << " collected " << val << ", score=" << _score << "\n";
//    }
//    else {
//        cout << ": coin already taken" << "\n";
//    }
//}

void TetrisGame::SpawnNewShape(Tetrimino*& currT, Board& board, int& x, int& y) {
    currT = TetriminoFactory::createRandom();
    x = BOARD_WIDTH / 2 - 1;
    y = 0;
    currT->updCoordinates(x, y);
}

bool TetrisGame::IsSpawn(Tetrimino* tet) {
    if (tet == nullptr) {
        return false;
    }
    return true;
}
bool TetrisGame::canMoveLeft(Board& board, Tetrimino& tet, int coordX, int  coordY) {
    size_t n = tet.getMatrix().size();;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (tet.getMatrix()[i][j] == 1)
            {
                int boardX = coordX - 1 + j;
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
void TetrisGame::landTetrimino(Board& board, Tetrimino& tet, int& x, int& y) {
    size_t n = tet.getMatrix().size();;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (tet.getMatrix()[i][j] == 1)
            {
                int boardX = x + j;
                int boardY = y + i;
                board.setSym(boardX, boardY, '#', tet.getColor());

            }
        }
    }
}
void TetrisGame::moveLeft(Board& board, Tetrimino*& tet, int& x, int& y) {
    if (tet != nullptr) {
        board.clearInner();
        if (canMoveLeft(board, *tet, x, y)) {
            x = x - 1;
            tet->updCoordinates(x, y);
            //std::cout << "Moved left" << x << "\n";
        }
        else {
            //std::cout << "Can`t Move left \n";
        }
        tet->draw(board);
    }
}
bool TetrisGame::canMoveRight(Board& board, Tetrimino& tet, int coordX, int  coordY) {
    size_t n = tet.getMatrix().size();;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (tet.getMatrix()[i][j] == 1)
            {
                int boardX = coordX + 1 + j;
                int boardY = coordY + i;
                if (boardX < 0 || boardX >= BOARD_WIDTH || boardY >= BOARD_HEIGHT || boardY < 0) {
                    return false;
                }
                char sym = board.getSym(boardX, boardY);
                if (sym == '|' || sym == '-' || sym == '*')
                {
                    return false;
                }
            }
        }
    }
    return true;
}
void TetrisGame::moveRight(Board& board, Tetrimino*& tet, int& x, int& y) {
    if (tet != nullptr) {
        board.clearInner();
        if (canMoveRight(board, *tet, x, y)) {
            x = x + 1;
            tet->updCoordinates(x, y);
            //std::cout << "Moved right" << x << "\n";
        }
        else {
            //std::cout << "Can`t Move right \n";
        }
        tet->draw(board);
    }
}

bool TetrisGame::canSoftDrop(Board& board, Tetrimino& tet, int coordX, int  coordY) {
    size_t n = tet.getMatrix().size();;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (tet.getMatrix()[i][j] == 1)
            {
                int boardX = coordX + j;
                int boardY = coordY + 1 + i;
                if (boardX < 0 || boardX >= BOARD_WIDTH || boardY >= BOARD_HEIGHT || boardY < 0) {
                    return false;
                }
                char sym = board.getSym(boardX, boardY);
                if (sym == '|' || sym == '-' || sym == '#' || sym == '*')
                {
                    return false;
                }
            }
        }
    }
    return true;
}
void TetrisGame::SoftDrop(Board& board, Tetrimino*& tet, int& x, int& y) {
    if (tet != nullptr) {
        board.clearInner();
        if (canSoftDrop(board, *tet, x, y)) {

            y = y + 1;
            tet->updCoordinates(x, y);
            tet->draw(board);
            //std::cout << "Moved soft drop" << x << "\n";
        }
        else {
            tet->draw(board);
            //std::cout << "not Moved soft drop" << x << "\n";
            landTetrimino(board, *tet, x, y);
            delete tet;
            tet = nullptr;
        }
    }
}
void TetrisGame::hardDrop(Board& board, Tetrimino*& tet, int& x, int& y) {
    if (tet != nullptr) {
        board.clearInner();
        while (canSoftDrop(board, *tet, x, y)) {
            y = y + 1;
        }
        tet->updCoordinates(x, y);

        landTetrimino(board, *tet, x, y);
        delete tet;
        tet = nullptr;

        //std::cout << "Moved hard drop" << x << "\n";
    }
}

int TetrisGame::getScore() const {
    return _score;
}
void TetrisGame::addScore(int value) {
    _score += value;
}
bool TetrisGame::isGameOver(Board& board, Tetrimino& tet, int& x, int& y) const
{
    size_t n = tet.getMatrix().size();;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (tet.getMatrix()[i][j] == 1)
            {
                int boardX = x + j;
                int boardY = y + i;

                if (boardX >= 0 && boardX < BOARD_WIDTH && boardY < BOARD_HEIGHT && boardY >= 0) {
                    if (board.getSym(boardX, boardY) == '#') {
                        return true;
                    }
                }

                if (boardY < 0) {
                    return true;
                }
            }
        }
    }
    return false;
}



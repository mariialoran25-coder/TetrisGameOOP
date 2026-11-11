#include "TetrisGame.h"
#include "TetriminoFactory.h"
#include <fstream>

TetrisGame::TetrisGame(Board& board) :board_(board) {
    reset();

}

void TetrisGame::reset()
{
    _score = 0; 
    board_.initBorder();
    current_ = nullptr;
}

Board& TetrisGame::getBoard() {
    return board_;
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
        saveScores("scores.txt");
    }
}
const std::vector<int>& TetrisGame::getTopScores() const {
    return topScores;
}

void TetrisGame::SpawnNewShape() {
    current_ = std::unique_ptr<Tetrimino>(TetriminoFactory::createRandom());
    currentX_ = BOARD_WIDTH / 2 - 1;
    currentY_ = 0;
    current_->updCoordinates(currentX_, currentY_);

}

bool TetrisGame::hasActiveShape()const  {
    return current_ != nullptr;
}

bool TetrisGame::IsSpawn(const Tetrimino* tet) {
    if (tet == nullptr) {
        return false;
    }
    return true;
}


void TetrisGame::update(sf::Time dt) {
    if (gameOver_) return;
    if (!hasActiveShape()) {
        if (isGameOver()) {
            gameOver_ = true;
            return;
        }
    }
    lockTimer_ += dt;
    if (lockTimer_ >= sf::microseconds(500)) {
        SoftDrop(dt);
        int cleared = board_.DelFullLine();
        if (cleared > 0) {
            scoreLines(cleared);
        }
        lockTimer_ = sf::Time::Zero;
    }
    if (isGameOver()) {
        gameOver_ = true;
    }
}


bool TetrisGame::canMoveLeft( int coordX, int  coordY) const {
    if (!current_) return false;
    const std::vector<std::vector<int>>& matrix = current_->getMatrix();
    size_t n = matrix.size();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matrix[i][j] == 1)
            {
                int boardX = coordX-1  + j;
                int boardY = coordY + i;
                if (boardX < 0 || boardX >= BOARD_WIDTH || boardY >= BOARD_HEIGHT || boardY < 0) {
                    return false;
                }
                if (board_.getSym(boardX, boardY) != ' ') {
                    return false;
                }
            }
        }
    }
    return true;
}

void TetrisGame::moveLeft(){
    if (current_) {
        board_.clearInner();
        if (canMoveLeft(currentX_, currentY_)) {
            currentX_--;
        }
        current_->updCoordinates(currentX_, currentY_);
        current_->draw(board_);
       
    }
}


bool TetrisGame::canMoveRight( int coordX, int  coordY)const {
    if (!current_) return false;
    const std::vector<std::vector<int>>& matrix = current_->getMatrix();
    size_t n = matrix.size();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matrix[i][j] == 1)
            {
                int boardX = coordX + 1 + j;
                int boardY = coordY + i;
                if (boardX < 0 || boardX >= BOARD_WIDTH || boardY >= BOARD_HEIGHT || boardY < 0) {
                    return false;
                }
                if (board_.getSym(boardX, boardY) != ' ') {
                    return false;
                }
            }
        }
    }
    return true;
}
void TetrisGame::moveRight() {
    if (current_) {
        board_.clearInner();
        if (canMoveRight(currentX_, currentY_)) {
            currentX_++;
        }
        current_->updCoordinates(currentX_, currentY_);
        current_->draw(board_);
        
    }
}

bool TetrisGame::canSoftDrop(int coordX, int  coordY) const {
    if (!current_) return false;
    const std::vector<std::vector<int>>& matrix = current_->getMatrix();
    size_t n = matrix.size();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matrix[i][j] == 1)
            {
                int boardX = coordX + j;
                int boardY = coordY + 1 + i;
                if (boardX < 0 || boardX >= BOARD_WIDTH || boardY >= BOARD_HEIGHT || boardY < 0) {
                    return false;
                }
                char sym = board_.getSym(boardX, boardY);
                if (sym == '|' || sym == '-' || sym == '#' || sym == '*')
                {
                    return false;
                }
            }
        }
    }
    return true;
}
void TetrisGame::SoftDrop(sf::Time dt) {
    if (current_) {
        board_.clearInner();
        if (canSoftDrop(currentX_ , currentY_)) {
            currentY_++;
            current_->updCoordinates(currentX_, currentY_);
            current_->draw(board_);
            lockTimer_ = sf::Time::Zero;
        }
        else {
            //current_->draw(board_);
            current_->updCoordinates(currentX_, currentY_);
            lockTimer_ += dt;
            if (lockTimer_ >= sf::milliseconds(500)) {
                landTetrimino();
                current_.reset();
                lockTimer_ = sf::Time::Zero;
            }
        }
    }
}
void TetrisGame::hardDrop() {
    if (current_) {
        board_.clearInner();
        while (canSoftDrop(currentX_,currentY_)) {
            currentY_ +=  1;
        }
        current_->updCoordinates(currentX_, currentY_);
        landTetrimino( );
        current_.reset();
    }
}


void TetrisGame::landTetrimino() {
    const std::vector<std::vector<int>>& matrix = current_->getMatrix();
    size_t n = matrix.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matrix[i][j] == 1)
            {
                int boardX = currentX_ + j;
                int boardY = currentY_ + i;
                board_.setSym(boardX, boardY, '#', current_->getColor());

            }
        }
    }
}


int TetrisGame::getScore() const {
    return _score;
}
void TetrisGame::addScore(int value) {
    _score += value;
}
bool TetrisGame::isGameOver() const
{   
    if (!current_) return false;
    const std::vector<std::vector<int>>& matrix = current_->getMatrix();
    size_t n = matrix.size();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if ( matrix[i][j] == 1)
            {
                int boardX = currentX_ + j;
                int boardY = currentY_ + i;

                if (boardX >= 0 && boardX < BOARD_WIDTH && boardY < BOARD_HEIGHT && boardY >= 0) {
                    if (board_.getSym(boardX, boardY) == '#') {
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


void TetrisGame::saveScores(const std::string& path) const {
    std::ofstream f(path);
    if (f.is_open()) {
        for (int s : topScores) {
            f << s << '\n';
        }
    }
}

void TetrisGame::loadScores(const std::string& path) {
    std::ifstream f(path);
    if (f.is_open()) {
        topScores.clear();
        int s;
        while (f >> s) {
            topScores.push_back(s);
        }
    }
}



void TetrisGame::rotate() {
    board_.clearInner();
    current_->rotate(board_);
    current_->draw(board_);
}
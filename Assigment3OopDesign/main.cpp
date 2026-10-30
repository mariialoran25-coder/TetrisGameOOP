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
using namespace std;

//const int BOARD_WIDTH = 21;
//const int BOARD_HEIGHT = 29;
//
//struct forBoard {
//    char symbol = ' ';
//    std::string color = "";
//};

//class Board {
//private:
//    std::vector<std::vector<forBoard>> grid;
//public:
//    Board() : grid(BOARD_HEIGHT, std::vector<forBoard>(BOARD_WIDTH)) {}
//    void setSym(int x, int y, char symbol, const std::string& color) {
//        if (x >= 0 && x < BOARD_WIDTH && y >= 0 && y < BOARD_HEIGHT) {
//            grid[y][x].symbol = symbol;
//            grid[y][x].color = color;
//        }
//    }
//    void initBorder() {
//        for (int i = 0; i < BOARD_HEIGHT; ++i) {
//            for (int j = 0; j < BOARD_WIDTH; ++j) {
//                if ( i == BOARD_HEIGHT - 1) {
//                    grid[i][j].symbol = '-';
//                    grid[i][j].color = "";
//                }
//                else if (j == 0 || j == BOARD_WIDTH - 1) {
//                    grid[i][j].symbol = '|';
//                    grid[i][j].color = "";
//                }
//                else {
//                    grid[i][j].symbol = ' ';
//                    grid[i][j].color = "";
//                }
//            }
//        }
//    }
//
//    void clearInner() {
//        for (int i = 0; i < BOARD_HEIGHT; ++i) {
//            for (int j = 0; j < BOARD_WIDTH; ++j) {
//                if (i < BOARD_HEIGHT - 1 && j>0 && j < BOARD_WIDTH - 1) {
//                    if (grid[i][j].symbol != '#') {
//                        grid[i][j].symbol = ' ';
//                        grid[i][j].color = "";
//                    }
//                }
//            }
//        }
//    }
//    void print() {
//        for (int i = 0; i < BOARD_HEIGHT; ++i) {
//            for (int j = 0; j < BOARD_WIDTH; ++j) {
//                if (!grid[i][j].color.empty()) {
//                    ColorCode::GetColorCode(grid[i][j].color);
//                }
//                std::cout << grid[i][j].symbol;
//                std::cout << "\033[0m";
//            }
//            std::cout << "\n";
//        }
//    }
//    char getSym(int x, int y) const {
//        if (x >= 0 && x < BOARD_WIDTH && y >= 0 && y < BOARD_HEIGHT) {
//            return grid[y][x].symbol;
//        }
//        return ' ';
//    }
//    bool isFullLine(int& y) const
//    {
//        for (int j = 1; j < BOARD_WIDTH - 1; ++j) {
//            char sym = getSym(j, y);
//            if (sym != '#')
//            {
//                return false;
//            }
//        }
//        return true;
//    }
//    void DelFullLine() {
//        for (int i = BOARD_HEIGHT - 1; i > 0; --i) {
//            if (isFullLine(i)) {
//                for(int row = i; row > 1; --row)
//                for (int j = 1; j < BOARD_WIDTH - 1; ++j) {
//                    grid[row][j] = grid[row - 1][j];
//                }
//                for (int j = 1; j < BOARD_WIDTH - 1; ++j) {
//                    grid[1][j].symbol = ' ';
//                    grid[1][j].color = "";
//                }
//                --i;
//            }
//        }
//    }
//};

//class Tetrimino {
//protected:
//    std::vector<std::vector<int>> tetrimo;
//    int coordX =0;
//    int coordY =0;
//    std::string color = "white";
//public:
//    Tetrimino(){}
//    virtual ~Tetrimino() {}
//    virtual void updCoordinates(int newX, int newY) {
//        coordX = newX;
//        coordY = newY;
//    }
//    virtual void draw(Board& board) {
//        size_t n = tetrimo.size();
//        for (int i = 0; i < n; ++i) {
//            for (int j = 0; j < n; ++j) {
//                if (tetrimo[i][j] == 1)
//                {
//                    int boardX = coordX + j;
//                    int boardY = coordY + i;
//                    board.setSym(boardX, boardY, '*', color);
//                }
//            }
//        }
//    }
//
//    virtual void rotate(Board& board) {
//        if (canRotate(board)) {
//            std::vector<std::vector<int>> matrix_rotate = tetrimo;
//            size_t n = tetrimo.size();
//            for (int y = 0; y < n; ++y) {
//                for (int x = 0; x < n; ++x)
//                {
//                    tetrimo[x][n - 1 - y] = matrix_rotate[y][x];
//                }
//            }
//        }
//    }
//
//    std::vector<std::vector<int>> getMatrix() const {
//        return tetrimo;
//    }
//    std::string getColor() const {
//        return  color;
//    }
//    bool canRotate(Board& board) {
//        std::vector<std::vector<int>> temp = tetrimo;
//        size_t n = tetrimo.size();
//        for (int i = 0; i < n; ++i) {
//            for (int j = 0; j < n; ++j) {
//
//                temp[i][j] = tetrimo[j][n - 1 - i];
//            }
//        }
//        for (int i = 0; i < n; ++i) {
//            for (int j = 0; j < n; ++j) {
//                if (temp[i][j] == 1)
//                {
//                    int boardX = coordX + j;
//                    int boardY = coordY + i;
//                    if (boardX < 0 || boardX >= BOARD_WIDTH || boardY >= BOARD_HEIGHT || boardY < 0) {
//                        return false;
//                    }
//                    if (board.getSym(boardX, boardY) != ' ') {
//                        return false;
//                    }
//                }
//            }
//        }
//        return true;
//    }
//};


class Point {
private:
    int _value;
    bool taken = false;
public:
    Point(int value) : _value(value) {}
    int take() {
        if (!taken) {
            taken = true;
            return _value;
        }
        return 0;
    }
    bool canTake() {
       
    }
};

class TetrisGame {
private:
    string State;
    int _score = 0;
    bool isGameOver() const;
    const int gridSize = 15;
    Board& board_;
    void resetBoard()
    {
        //tetrimo.clear();
        //selectedShape = nullptr;
        //board.clear();
        std::cout << "Board is clear\n";
        //board = std::vector<std::vector<Player>>(gridSize, std::vector<Player>(gridSize, Player::None));
    }

    void checkForWinner(int lastMoveRow, int lastMoveCol)
    {
    }
public:
    TetrisGame(Board& board) :board_(board)  {
        resetBoard();
    }
    Board& getBoard() {
        return board_;
    }
    void collect(Point& coin) {
        int val = coin.take();
        if (val > 0) {
            _score = _score + val;
            cout << " collected " << val << ", score=" << _score << "\n";
        }
        else {
            cout << ": coin already taken" << "\n";
        }
    }

    void SpawnNewShape(Tetrimino*& currT, Board& board , int& x, int& y) {
        currT = TetriminoFactory::createRandom();
        x= BOARD_WIDTH / 2 -1;
        y = 0;
        currT->updCoordinates(x, y);
    }
    void reset();
    void pause();
    void resume();

    bool IsSpawn(Tetrimino* tet) {
        if (tet == nullptr) {
            return false;
        }
        return true;
    }
    bool canMoveLeft(Board& board, Tetrimino& tet, int coordX,int  coordY) {
        size_t n = tet.getMatrix().size();;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (tet.getMatrix()[i][j] == 1)
                {
                    int boardX = coordX -1 + j;
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
    void landTetrimino(Board& board, Tetrimino& tet, int& x, int& y) {
        size_t n = tet.getMatrix().size();;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (tet.getMatrix()[i][j] == 1)
                {
                    int boardX = x + j;
                    int boardY = y + i;
                    board.setSym(boardX, boardY, '#',tet.getColor());
                        
                }
            }
        }
    }
    void moveLeft(Board& board, Tetrimino*& tet,  int& x,int& y) {
        if (tet != nullptr) {
            board.clearInner();
            if (canMoveLeft(board, *tet, x, y)) {
                x = x - 1;
                tet->updCoordinates(x, y);
                std::cout << "Moved left" << x << "\n";
            }
            else {
                std::cout << "Can`t Move left \n";
            }
            tet->draw(board);
        }
    }
    bool canMoveRight(Board& board, Tetrimino& tet, int coordX, int  coordY) {
        size_t n = tet.getMatrix().size();;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (tet.getMatrix()[i][j] == 1)
                {
                    int boardX = coordX+1 + j;
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
    void moveRight(Board& board, Tetrimino*& tet, int& x, int& y) {
        if (tet != nullptr) {
            board.clearInner();
            if (canMoveRight(board, *tet, x, y)) {
                x = x + 1;
                tet->updCoordinates(x , y);
                std::cout << "Moved right" << x << "\n";
            }
            else {
                std::cout << "Can`t Move right \n";
            }
            tet->draw(board);
        }
    }

    bool canSoftDrop(Board& board, Tetrimino& tet, int coordX, int  coordY) {
        size_t n = tet.getMatrix().size();;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (tet.getMatrix()[i][j] == 1)
                {
                    int boardX = coordX + j;
                    int boardY = coordY+1 + i;
                    if (boardX < 0 || boardX >= BOARD_WIDTH || boardY >= BOARD_HEIGHT || boardY < 0) {
                        return false;
                    }
                    char sym = board.getSym(boardX, boardY); 
                    if (sym =='|' || sym =='-' || sym == '#' || sym == '*')
                    {
                        return false;
                    }
                }
            }
        }
        return true;
    }
    void SoftDrop(Board& board, Tetrimino*& tet, int& x, int& y) {
        if (tet != nullptr) {
            board.clearInner();
            if (canSoftDrop(board, *tet, x, y)) {

                y = y + 1;
                tet->updCoordinates(x, y);
                tet->draw(board);
                std::cout << "Moved soft drop" << x << "\n";
            }
            else {
                tet->draw(board);
                std::cout << "not Moved soft drop" << x << "\n";
                landTetrimino(board, *tet, x, y);
                delete tet;
                tet = nullptr;
            }
        }
    }
    void hardDrop(Board& board, Tetrimino*& tet, int& x, int& y) {
        if (tet != nullptr) {
            board.clearInner();
            while (canSoftDrop(board, *tet, x, y) ){
                y = y + 1;
            }
            tet->updCoordinates(x, y);

            landTetrimino(board, *tet, x, y);
            delete tet;
            tet = nullptr;

            std::cout << "Moved hard drop" << x << "\n";
        }
    }

    int getScore() {
        return _score;
    }
    bool isGameOver(Board& board, Tetrimino& tet, int& x, int& y) const
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
};

class Renderer {
private:
    const int cellSize;
    const int windowWidth;
    const int windowHeight;

    sf::RenderWindow window;
    sf::Font font;
    bool fontLoaded;

    void processEvents(TetrisGame& game, Tetrimino*& currentTet, int& x, int& y, sf::Time& dropTime)
    {
        while (const std::optional<sf::Event> event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                Board& board = game.getBoard();
                if (currentTet != nullptr) {
                    if (keyPressed->code == sf::Keyboard::Key::Left)
                    {
                        game.moveLeft(board, currentTet, x, y);
                    }
                    else if (keyPressed->code == sf::Keyboard::Key::Right) {
                        game.moveRight(board, currentTet, x, y);
                    }
                    else if (keyPressed->code == sf::Keyboard::Key::Down) {
                        game.SoftDrop(board, currentTet, x, y);
                        dropTime = sf::Time::Zero;
                    }
                    else if (keyPressed->code == sf::Keyboard::Key::Space) {
                        game.hardDrop(board, currentTet, x, y);
                        dropTime = sf::Time::Zero;
                    }
                    else if (keyPressed->code == sf::Keyboard::Key::Up) {
                        board.clearInner();
                        currentTet->rotate(board);
                        currentTet->draw(board);
                    }
                }
            }

        }
    }

    void render(const TetrisGame& game)
    {
        window.clear();
        Board& board = const_cast<TetrisGame&>(game).getBoard();
        for (int i = 0; i < BOARD_HEIGHT; ++i) {
            for (int j = 0; j < BOARD_WIDTH; ++j) {
                char sym = board.getSym(j, i);
                sf::RectangleShape cell(sf::Vector2f(static_cast<float>(cellSize - 1), static_cast<float>(cellSize - 1)));
                cell.setPosition(sf::Vector2f(static_cast<float>(j * cellSize), static_cast<float>(i * cellSize)));

                if (sym == '-' || sym == '|') {
                    cell.setFillColor(sf::Color::Blue);
                }
                else if (sym != ' ') {
                    cell.setFillColor(sf::Color::Red);
                    
                }
                else {
                    cell.setFillColor(sf::Color(30,30,30));
                }
                window.draw(cell);
            }
        }
        window.display();
    }

public:
    Renderer()
        : cellSize(30),
        windowWidth(BOARD_WIDTH * cellSize),
        windowHeight(BOARD_HEIGHT* cellSize),
        window(sf::VideoMode({ static_cast<unsigned int>(windowWidth), static_cast<unsigned int>(windowHeight) }), "Tic-Tac-Toe"),
        font(),
        fontLoaded(font.openFromFile("C:\\Windows\\Fonts\\arial.ttf"))
    {
        window.setFramerateLimit(60);
    }

    void GemeOver(Board& board, Tetrimino& tet, TetrisGame& game, int& x, int& y) {
        if (game.isGameOver(board, tet, x, y)) {
            window.setTitle("Game is over");
            window.close();
        }
    }

    void run(Board& board,TetrisGame& game , Tetrimino*& activeTet, int& x, int& y)
    {
        sf::Clock clock;
        sf::Time dropTime = sf::Time::Zero; //create timer
        sf::Time dropInterval = sf::milliseconds(500);
        while (window.isOpen())
        {
            sf::Time timeLeft = clock.restart();
            dropTime += timeLeft;

            if (activeTet == nullptr) {
                game.SpawnNewShape(activeTet, board, x, y);
                dropTime = sf::Time::Zero;
                if (activeTet != nullptr) {
                    GemeOver(board, *activeTet, game, x, y);
                }

            
            }
            processEvents(game, activeTet, x, y, dropTime);

            if (dropTime >= dropInterval) {
                game.SoftDrop(board, activeTet, x, y);
                dropTime = sf::Time::Zero;
            }
            if (activeTet != nullptr) {
                GemeOver(board, *activeTet,game, x, y);
            }
            window.clear();
            render(game);
            //window.display();
        }
    }
};

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

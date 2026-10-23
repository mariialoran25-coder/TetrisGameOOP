#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <optional>
#include <iostream>
using namespace std;

const int BOARD_WIDTH = 21;
const int BOARD_HEIGHT = 29;

struct forBoard {
    char symbol = ' ';
    std::string color = "";
};

class ColorCode {
private:
    struct ColorPair {
        std::string name;
        std::string code;
    };
public:
    static std::string GetColorCode(const std::string& colorName) {
        if (colorName == "red") return "\033[31m";
        if (colorName == "blue")return "\033[34m";
        if (colorName == "yellow") return "\033[33m";
        if (colorName == "green") return "\033[32m";
        if (colorName == "black") return "\033[30m";
        if (colorName == "pink") return "\033[38;2;255;192;203m";
        return "\033[0m";
    };
};



class Board {
private:
    std::vector<std::vector<forBoard>> grid;
public:
    Board() : grid(BOARD_HEIGHT, std::vector<forBoard>(BOARD_WIDTH)) {}
    void setSym(int x, int y, char symbol, const std::string& color) {
        if (x >= 0 && x < BOARD_WIDTH && y >= 0 && y < BOARD_HEIGHT) {
            grid[y][x].symbol = symbol;
            grid[y][x].color = color;
        }
    }
    void initBorder() {
        for (int i = 0; i < BOARD_HEIGHT; ++i) {
            for (int j = 0; j < BOARD_WIDTH; ++j) {
                if (i == 0 || i == BOARD_HEIGHT - 1) {
                    grid[i][j].symbol = '-';
                }
                else if (j == 0 || j == BOARD_WIDTH - 1) {
                    grid[i][j].symbol = '|';
                }
                else {
                    grid[i][j].symbol = ' ';
                }
            }
        }
    }
    void print() {
        for (int i = 0; i < BOARD_HEIGHT; ++i) {
            for (int j = 0; j < BOARD_WIDTH; ++j) {
                if (!grid[i][j].color.empty()) {
                    std::cout << ColorCode::GetColorCode(grid[i][j].color);
                }
                std::cout << grid[i][j].symbol;
                std::cout << "\033[0m";
            }
            std::cout << "\n";
        }
    }
    char getSym(int x, int y) const {
        if (x >= 0 && x < BOARD_WIDTH && y >= 0 && y < BOARD_HEIGHT) {
            return grid[y][x].symbol;
        }
        return ' ';
    }
};









class Tetrimino {
private:
    int id_shape = 0;
    int width = 0;
    int height = 0;
    int coordX = 0;
    int coordY = 0;
    int color_ = ' ';
public:
    virtual ~Tetrimino() {}
    virtual void draw(Board& board) = 0;
    virtual bool contains(int px, int py) = 0;
    virtual void updPrmtrs(int newWidth, int newHeight) = 0;
    virtual void updCoordinates(int newX, int newY) = 0;
    virtual void setColor(const std::string& newColor) = 0;
    virtual std::string serialise() = 0;
    void clear();
};

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
    //Tetrimino& tetrimo;
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
        // Перевірка рядка
        //if (board[lastMoveRow][0] == board[lastMoveRow][1] && board[lastMoveRow][1] == board[lastMoveRow][2])
        //{
        //    winner = board[lastMoveRow][0];
        //}

        //// Перевірка стовпця
        //if (board[0][lastMoveCol] == board[1][lastMoveCol] && board[1][lastMoveCol] == board[2][lastMoveCol])
        //{
        //    winner = board[0][lastMoveCol];
        //}

        //// Перевірка діагоналей
        //if ((lastMoveRow == lastMoveCol || lastMoveRow + lastMoveCol == gridSize - 1) &&
        //    ((board[0][0] == board[1][1] && board[1][1] == board[2][2]) ||
        //        (board[0][2] == board[1][1] && board[1][1] == board[2][0])))
        //{
        //    winner = board[1][1];
        //}
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
    void reset();
    void pause();
    void resume();
    void moveLeft();
    void moveRight();
    void softDrop();
    void hardDrop();

    int getScore() {
        return _score;
    }
    //void reset()
    //{
    //    resetBoard();
    //    //actionsNumber = 0;
    //    //currentPlayer = Player::X;
    //    //winner = Player::None;
    //}

    //bool isGameOver() const
    //{
    //    return true;
    //    //return winner != Player::None || actionsNumber >= 9;
    //}
};

class Renderer {
private:
    const int cellSize;
    const int windowWidth;
    const int windowHeight;

    sf::RenderWindow window;
    sf::Font font;
    bool fontLoaded;
    void processEvents(TetrisGame& game)
    {
        while (const std::optional<sf::Event> event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mousePressed->button == sf::Mouse::Button::Left)
                {
                    handleMouseClick(game, mousePressed->position.x, mousePressed->position.y);
                }
            }
        }
    }

    void handleMouseClick(TetrisGame& game, int mouseX, int mouseY)
    {
        int row = mouseY / cellSize;
        int col = mouseX / cellSize;
    }

    void render(const TetrisGame& game)
    {
        window.clear();
        Board& board = const_cast<TetrisGame&>(game).getBoard();
        for (int i = 0; i < BOARD_HEIGHT; ++i) {
            for (int j = 0; j < BOARD_WIDTH; ++j) {
                char sym = board.getSym( j,i);
                sf::RectangleShape cell(sf::Vector2f(static_cast<float>(cellSize - 1), static_cast<float>(cellSize - 1)));
                cell.setPosition(sf::Vector2f(static_cast<float>(j * cellSize), static_cast<float>(i * cellSize)));

                if (sym == '-' || sym == '|') {
                    cell.setFillColor(sf::Color::Blue);
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
        fontLoaded(font.openFromFile("C:\\Windows\\Fonts\\arial.ttf")) // Змініть шлях до шрифту за потреби
    {
        window.setFramerateLimit(60);
    }

    void run(TetrisGame& game)
    {
        while (window.isOpen())
        {
            processEvents(game);
            render(game);
        }
    }
};

int main()
{
    //Renderer renderer;
    //renderer.run(game);
    Board board;

    board.initBorder();
    TetrisGame game(board);
    Renderer render;
    render.run(game);
    std::cin.get();
    return 0;
}
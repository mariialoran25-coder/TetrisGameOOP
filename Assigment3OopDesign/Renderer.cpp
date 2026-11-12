#include "Renderer.h"

void Renderer::processEvents(TetrisGame& game, sf::Time& dropTime)
{
    while (const std::optional<sf::Event> event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            if (curr_state == stateInstructuion || curr_state == stateStatus) {
                if (keyPressed->code == sf::Keyboard::Key::Escape || keyPressed->code == sf::Keyboard::Key::Enter) {
                    curr_state = stateMenu;
                }
            }
            else if (curr_state == stateGame) {
                if (keyPressed->code == sf::Keyboard::Key::Escape) {
                    curr_state = stateMenu;
                }
                else if (game.hasActiveShape()) {
                    if (keyPressed->code == sf::Keyboard::Key::Left)
                    {
                        game.moveLeft();
                    }
                    else if (keyPressed->code == sf::Keyboard::Key::Right) {
                        game.moveRight();
                    }
                    else if (keyPressed->code == sf::Keyboard::Key::Down) {
                        game.SoftDrop(dropTime);
                        dropTime = sf::Time::Zero;
                    }
                    else if (keyPressed->code == sf::Keyboard::Key::Space) {
                        game.hardDrop();
                        dropTime = sf::Time::Zero;
                    }
                    else if (keyPressed->code == sf::Keyboard::Key::Up) {
                        Board& board = game.getBoard();
                        board.clearInner();
                        game.rotate();
                    }
                }
            }
        }
        else if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (mousePressed->button == sf::Mouse::Button::Left) {
                int mouseX = mousePressed->position.x;  
                int mouseY = mousePressed->position.y;

                if (curr_state == stateMenu) {
                    if (mouseX >= 220 && mouseX <= 420 && mouseY >= 100 && mouseY <= 180) {
                        curr_state = stateInstructuion;
                    }
                    else if (mouseX >= 220 && mouseX <= 420 && mouseY >= 250 && mouseY <= 330) {
                        game.reset();
                        game.SpawnNewShape();
                        dropTime = sf::Time::Zero;
                        curr_state = stateGame;
                    }
                    else if (mouseX >= 220 && mouseX <= 420 && mouseY >= 400 && mouseY <= 480) {
                        curr_state = stateGame;
                    }
                    else if (mouseX >= 220 && mouseX <= 420 && mouseY >= 550 && mouseY <= 630) {
                        curr_state = stateStatus;
                    }
                    else if (mouseX >= 220 && mouseX <= 420 && mouseY >= 700 && mouseY <= 750) {
                        window.close();
                    }
                }
            }
        }
    }
}

void Renderer::render(const TetrisGame& game)
{
    window.clear(sf::Color(30, 30, 30));
    Board& board = const_cast<TetrisGame&>(game).getBoard();

    if (Renderer::curr_state == stateMenu) {
        window.clear(sf::Color(143, 0, 255));
        sf::RectangleShape instruction(sf::Vector2f(200.f, 80.f));
        sf::RectangleShape start(sf::Vector2f(200.f, 80.f));
        sf::RectangleShape continuee(sf::Vector2f(200.f, 80.f));
        sf::RectangleShape status(sf::Vector2f(200.f, 80.f));
        sf::RectangleShape exit(sf::Vector2f(200.f, 50.f));

        instruction.setPosition({ 220.f, 100.f });
        instruction.setFillColor(sf::Color(224, 255, 255));
        instruction.setOutlineColor(sf::Color(0, 0, 200));
        instruction.setOutlineThickness(3.f);
        window.draw(instruction);

        start.setPosition({ 220.f, 250.f });
        start.setFillColor(sf::Color(224, 255, 255));
        start.setOutlineColor(sf::Color(0, 0, 200));
        start.setOutlineThickness(3.f);
        window.draw(start);

        continuee.setPosition({ 220.f, 400.f });
        continuee.setFillColor(sf::Color(224, 255, 255));
        continuee.setOutlineColor(sf::Color(0, 0, 200));
        continuee.setOutlineThickness(3.f);
        window.draw(continuee);

        status.setPosition({ 220.f, 550.f });
        status.setFillColor(sf::Color(224, 255, 255));
        status.setOutlineColor(sf::Color(0, 0, 200));
        status.setOutlineThickness(3.f);
        window.draw(status);

        exit.setPosition({ 220.f, 700.f });
        exit.setFillColor(sf::Color(224, 255, 255));
        exit.setOutlineColor(sf::Color(0, 0, 200));
        exit.setOutlineThickness(3.f);
        window.draw(exit);

        sf::Text titleText(font);
        titleText.setString("TETRIS");
        titleText.setCharacterSize(50);
        titleText.setFillColor(sf::Color(0, 0, 128));
        titleText.setPosition({ 235.f, 20.f });
        window.draw(titleText);



        if (fontLoaded) {
            sf::Text text1(font), text2(font), text3(font), text4(font), text5(font);
            text1.setString("Instruction for Game");
            text2.setString("Starting new Game");
            text3.setString("Continue Game");
            text4.setString("View Game Status");
            text5.setString("Exit");

            text1.setCharacterSize(20); text2.setCharacterSize(20); text3.setCharacterSize(20); text4.setCharacterSize(20); text5.setCharacterSize(20);
            text1.setFillColor(sf::Color::Black); text2.setFillColor(sf::Color::Black); text3.setFillColor(sf::Color::Black); text4.setFillColor(sf::Color::Black); text5.setFillColor(sf::Color::Black);

            text1.setPosition({ 225.f, 125.f });
            text2.setPosition({ 230.f, 275.f });
            text3.setPosition({ 240.f, 425.f });
            text4.setPosition({ 240.f, 575.f });
            text5.setPosition({ 300.f, 715.f });
            window.draw(text1); window.draw(text2); window.draw(text3); window.draw(text4); window.draw(text5);
        }
    }
    else if (curr_state == stateInstructuion) {
        window.clear(sf::Color(153, 153, 255));
        if (fontLoaded) {
            sf::Text textinstr(font);
            textinstr.setString("Instructions:\n\nTo move Left/Right side shape - use arrow left/right on keyboard \nTo Rotate the shape - use arrow up on keyboard\nTo speed up the tetrimino  - use arrow Down on keyboard\nTo drop the tetrimino - use Space on keyboard\n\nPress ENTER or ESC to go back");
            textinstr.setCharacterSize(19);
            textinstr.setFillColor(sf::Color::Black);
            textinstr.setPosition({ 50.f, 300.f });
            window.draw(textinstr);
        }
    }
    else if (curr_state == stateStatus) {
        window.clear(sf::Color(153, 153, 255));
        if (fontLoaded) {
            sf::Text title(font);
            title.setString("TOP 5 SCORES");
            title.setCharacterSize(24);
            title.setFillColor(sf::Color::Black);
            title.setPosition({ 150.f, 150.f });
            window.draw(title);

            const std::vector<int>& scores = game.getTopScores();
            float startY = 200.f;

            if (scores.empty()) {
                sf::Text noScore(font);
                noScore.setString("No scores yet");
                noScore.setCharacterSize(18);
                noScore.setFillColor(sf::Color::Black);
                noScore.setPosition({ 150.f, startY });
                window.draw(noScore);
            }
            else {
                for (size_t i = 0; i < scores.size(); ++i) {
                    sf::Text scoreItem(font);
                    scoreItem.setString(std::to_string(i + 1) + ". " + std::to_string(scores[i]));
                    scoreItem.setCharacterSize(18);
                    scoreItem.setFillColor(sf::Color::Black);
                    scoreItem.setPosition({ 150.f, startY + (i * 30.f) });
                    window.draw(scoreItem);
                }
            }

            sf::Text backHint(font);
            backHint.setString("Press ESC or ENTER to go back");
            backHint.setCharacterSize(16);
            backHint.setFillColor(sf::Color::Black);
            backHint.setPosition({ 150.f, 400.f });
            window.draw(backHint);
        }
    }
    else {
        for (int i = 0; i < BOARD_HEIGHT; ++i) {
            for (int j = 0; j < BOARD_WIDTH; ++j) {
                char sym = board.getSym(j, i);
                sf::RectangleShape cell(sf::Vector2f(static_cast<float>(cellSize - 1), static_cast<float>(cellSize - 1)));
                cell.setPosition(sf::Vector2f(static_cast<float>(j * cellSize), static_cast<float>(i * cellSize)));

                cell.setOutlineColor(sf::Color(50, 50, 50));
                cell.setOutlineThickness(1.f);


                sf::Color colorsShape = board.getColor(j, i);
                cell.setFillColor(colorsShape);

                if (sym == '-' || sym == '|') {
                    cell.setFillColor(sf::Color(76, 0, 153));
                }
                window.draw(cell);
            }
        }
        if (game.hasActiveShape()) {
            int shadowX = game.getCurrX();
            int shadowY = game.getShadowY();
            const auto& matrix = game.getCurrMatrix();

            size_t n = matrix.size();
            

            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (matrix[i][j] == 1)
                    {
                        int boardX = shadowX + j;
                        int boardY = shadowY + i ;
                        if (boardX >= 0 && boardX < BOARD_WIDTH && boardY < BOARD_HEIGHT && boardY >= 0) {
                            sf::RectangleShape shadowCell(sf::Vector2f(static_cast<float>(cellSize-1), static_cast<float>(cellSize-1)));
                            shadowCell.setPosition(sf::Vector2f(static_cast<float>(boardX* cellSize), static_cast<float>(boardY* cellSize)));

                            shadowCell.setFillColor(sf::Color::Transparent);
                            shadowCell.setOutlineColor(sf::Color(255, 255, 255));
                            shadowCell.setOutlineThickness(1.5f);
                            window.draw(shadowCell);

                        }
                    }
                }
            }
        }

        if (fontLoaded) {
            sf::Text scoreText(font);
            scoreText.setString("Score: " + std::to_string(game.getScore()));
            scoreText.setCharacterSize(20);
            scoreText.setFillColor(sf::Color::White);
            scoreText.setPosition({ static_cast<float>(BOARD_WIDTH * cellSize + 20), 50.f });
            window.draw(scoreText);
        }

    }
    window.display();
        
}


Renderer::Renderer()
    : cellSize(30),
    windowWidth(BOARD_WIDTH * cellSize+150),
    windowHeight(BOARD_HEIGHT * cellSize),
    window(sf::VideoMode({ static_cast<unsigned int>(windowWidth), static_cast<unsigned int>(windowHeight) }), "Tetris"),
    font(),
    fontLoaded(font.openFromFile("C:\\Windows\\Fonts\\arial.ttf"))
{
    window.setFramerateLimit(60);
    if (!fontLoaded) {
        std::cout << "Font not loaded" << "/n";
    }

    

}

void Renderer::GemeOver(Board& board, TetrisGame& game) {
    if (game.isGameOver()) {
        //game.saveScore();
        window.setTitle("Game is over");
        
        Renderer::curr_state = stateMenu;
    }
}

void Renderer::run(Board& board, TetrisGame& game)
{
    sf::Clock clock;
    sf::Time dropTime = sf::Time::Zero;
    sf::Time dropInterval = sf::milliseconds(500);
    while (window.isOpen())
    {

        processEvents(game, dropTime);
        if (curr_state != stateGame) {
            clock.restart();
            dropTime = sf::Time::Zero;
        }
        else {
            sf::Time timeLeft = clock.restart();
            dropTime += timeLeft;


            if (!game.hasActiveShape()) {
                game.SpawnNewShape();
                dropTime = sf::Time::Zero;
                if (game.isGameOver()) {
                    GemeOver(board, game);
                    game.saveScore();
                }
            }

            if (dropTime >= dropInterval) {

                game.SoftDrop(dropInterval);
                int cleared = board.DelFullLine();
                if (cleared > 0) {
                    game.scoreLines(cleared);
                }
                dropTime = sf::Time::Zero;
            }
            if (game.hasActiveShape()) {
                GemeOver(board, game);
            }
        }
        render(game);
    }
}
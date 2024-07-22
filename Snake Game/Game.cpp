#include "Game.h"

Game::Game()
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Snake"),
    snake(BLOCK_SIZE),
    food(BLOCK_SIZE),
    timePerMove(sf::seconds(0.1f)),
    isGameRunning(false),
    score(0),
    selectedOption(MenuOption::Start),
    gameState(GameState::MainMenu) {

    icon.loadFromFile("./icon.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    if (!font.loadFromFile("./font.ttf")) {
        window.close();
    }

    setUpText(startText, font, "Start", sf::Color::White, 35);
    startText.setPosition(350, 250);

    setUpText(restartText, font, "Restart", sf::Color::White, 35);
    restartText.setPosition(350, 250);

    setUpText(exitText, font, "Exit", sf::Color::White, 35);
    exitText.setPosition(350, 300);

    setUpText(scoreText, font, "Score: 0 " + std::to_string(score), sf::Color::White, 30);
}

Game::~Game() {}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        if (isGameRunning) {
            timeSinceLastMove += clock.restart();
            if (timeSinceLastMove >= timePerMove) {
                update();
                timeSinceLastMove = sf::Time::Zero;
            }
            render();
        }
        else {
            renderMenu();
        }
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (gameState == GameState::MainMenu) {
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                case sf::Keyboard::Up:
                    if (selectedOption == MenuOption::Exit)
                        selectedOption = MenuOption::Start;
                    break;
                case sf::Keyboard::Down:
                    if (selectedOption == MenuOption::Start)
                        selectedOption = MenuOption::Exit;
                    break;
                case sf::Keyboard::Enter:
                    if (selectedOption == MenuOption::Start) {
                        isGameRunning = true;
                        gameState = GameState::Running;
                        startGame();
                    }
                    else if (selectedOption == MenuOption::Exit)
                        window.close();
                    break;
                default:
                    break;
                }
            }
        }
        else if (gameState == GameState::GameOver) {
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                case sf::Keyboard::Up:
                    if (selectedOption == MenuOption::Exit) 
                        selectedOption = MenuOption::Restart;
                    break;
                case sf::Keyboard::Down:
                    if (selectedOption == MenuOption::Restart) 
                        selectedOption = MenuOption::Exit;
                    break;
                case sf::Keyboard::Enter:
                    if (selectedOption == MenuOption::Restart) {
                        isGameRunning = true;
                        gameState = GameState::Running;
                        startGame();
                    }
                    else if (selectedOption == MenuOption::Exit)
                        window.close();
                    break;
                default:
                    break;
                }
            }
        }
        else if (gameState == GameState::Running)
        {
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                case sf::Keyboard::Up:
                    if (snake.getDirection() != sf::Vector2f(0, snake.getBlockSize()))
                        snake.setDirection(0, -snake.getBlockSize());
                    break;
                case sf::Keyboard::Down:
                    if (snake.getDirection() != sf::Vector2f(0, -snake.getBlockSize()))
                        snake.setDirection(0, snake.getBlockSize());
                    break;
                case sf::Keyboard::Left:
                    if (snake.getDirection() != sf::Vector2f(snake.getBlockSize(), 0))
                        snake.setDirection(-snake.getBlockSize(), 0);
                    break;
                case sf::Keyboard::Right:
                    if (snake.getDirection() != sf::Vector2f(-snake.getBlockSize(), 0))
                        snake.setDirection(snake.getBlockSize(), 0);
                    break;
                default:
                    break;
                }
            }
        }
    }
}

void Game::startGame() {
    snake = Snake(BLOCK_SIZE);
    food = Food(BLOCK_SIZE);
    clock.restart();
    timeSinceLastMove = sf::Time::Zero;
    score = 0;
    scoreText.setString("Score: " + std::to_string(score));
    scoreText.setPosition(10, 10);
    scoreText.setCharacterSize(30);
}

void Game::update() {
    snake.move();

    // collision with food
    if (snake.getHead().getGlobalBounds().intersects(food.getShape().getGlobalBounds())) {
        snake.grow();
        food.spawn(WINDOW_WIDTH, WINDOW_HEIGHT);
        score += 1; 
        scoreText.setString("Score: " + std::to_string(score));
    }

    // collision with wall and self
    if (snake.checkCollision()) {
        sf::sleep(sf::seconds(0.5));
        isGameRunning = false; 
        gameState = GameState::GameOver; 
        selectedOption = MenuOption::Restart; 
    }
}

void Game::render() {
    window.clear();
    snake.drawSnake(window);
    window.draw(food.getShape());
    window.draw(scoreText);
    window.display();
}

void Game::renderMenu() {
    window.clear();

    if (gameState == GameState::MainMenu) {
        startText.setFillColor(selectedOption == MenuOption::Start ? sf::Color::Red : sf::Color::White);
        exitText.setFillColor(selectedOption == MenuOption::Exit ? sf::Color::Red : sf::Color::White);
        window.draw(startText);
    }
    else if (gameState == GameState::GameOver) {
        scoreText.setString("Score: " + std::to_string(score));
        scoreText.setCharacterSize(50);
        scoreText.setPosition(350, 100);
        window.draw(scoreText);

        restartText.setFillColor(selectedOption == MenuOption::Restart ? sf::Color::Red : sf::Color::White);
        exitText.setFillColor(selectedOption == MenuOption::Exit ? sf::Color::Red : sf::Color::White);
        window.draw(restartText);
    }

    window.draw(exitText);
    window.display();
}


void Game::setUpText(sf::Text& text, const sf::Font& font, const std::string& string, const sf::Color& color, int size) {
    text.setFont(font);
    text.setString(string);
    text.setFillColor(color);
    text.setCharacterSize(size);
}

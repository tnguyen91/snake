#ifndef GAME_H
#define GAME_H

#include "Snake.h"
#include "Food.h"

constexpr auto WINDOW_WIDTH = 800;
constexpr auto WINDOW_HEIGHT = 600;
constexpr auto BLOCK_SIZE = 20.0f;

enum class MenuOption {
    Start,
    Restart,
    Exit
};

enum class GameState {
    MainMenu,
    Running,
    GameOver
};

class Game {
public:
    Game();
    ~Game();

    void run();

private:
    void processEvents();
    void startGame();
    void update();
    void render();
    void renderMenu();
    void setUpText(sf::Text& text, const sf::Font& font, const std::string& string, const sf::Color& color, int size);

    sf::RenderWindow window;
    Snake snake;
    Food food;
    sf::Clock clock;
    sf::Time timeSinceLastMove;
    sf::Time timePerMove;

    bool isGameRunning;
    int score;
    MenuOption selectedOption;
    GameState gameState;
    sf::Font font;
    sf::Text startText;
    sf::Text restartText;
    sf::Text exitText;
    sf::Text scoreText;
};

#endif 

#pragma once
#include "AllIncludes.h"
#include "Player.h"
#include "BackGround.h"
#include "OtherMenus.h"
#include "Enemy.h"
#include "Meteor.h"
#include "Controls.h"

enum class GameState 
{
    MAIN_MENU = 0,
    PLAYING,
    PAUSE,
    GAME_OVER,
    CONTROLS
};

class Game 
{
    float deltaTime;
    float lastFrameTime;
    GameState gameState;
    long CountAllEnemys = 3;

public:
    Background background;
    Player player;
    Meteor meteor;

    Menu mainMenu;
    Menu pause;
    Menu GameOver;

    Controls controlsHepls;

    std::vector<std::unique_ptr<Enemy>> Enemys;

    float Width;
    float Height;


    static Game* instance; // Указатель на текущий экземпляр игры

    Game(int argc, char** argv, float width, float height, GameState startedGameState);
   
    void init();
    
    void display();
    
    void reshape(int width, int height);
   
    // Таймер для обновления экрана
    void timer(int value);
    
    void AddNewEnemy();
    
    void updateDeltaTime();
    float getDeltaTime() const;

    void setGameStatus(GameState state);

    void resetAll();

    void displayMainMenu();
    void displayGame();
    void displayPause();
    void displayGameOver();
    void displayControls();


public:
    // Статический метод обработка движения мыши
    static void mouseMove(int x, int y);
    // Статический метод для получения координат мыши
    static void mouseMotion(int x, int y);
    // Статический метод для нажатия на клавиши клавиатуры
    static void KeyboardClick(unsigned char key, int x, int y);
    // Статический метод для нажатия клавиш мыши
    static void mouseClick(int button, int state, int x, int y);
    // Статический метод-обертка для вызова нестатического метода display
    static void displayWrapper();
    // Статический метод-обертка для вызова нестатического метода reshape
    static void reshapeWrapper(int width, int height);
    // Статический метод-обертка для вызова нестатического метода timer
    static void timerWrapper(int value);
    
};




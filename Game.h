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


    static Game* instance; // ��������� �� ������� ��������� ����

    Game(int argc, char** argv, float width, float height, GameState startedGameState);
   
    void init();
    
    void display();
    
    void reshape(int width, int height);
   
    // ������ ��� ���������� ������
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
    // ����������� ����� ��������� �������� ����
    static void mouseMove(int x, int y);
    // ����������� ����� ��� ��������� ��������� ����
    static void mouseMotion(int x, int y);
    // ����������� ����� ��� ������� �� ������� ����������
    static void KeyboardClick(unsigned char key, int x, int y);
    // ����������� ����� ��� ������� ������ ����
    static void mouseClick(int button, int state, int x, int y);
    // ����������� �����-������� ��� ������ �������������� ������ display
    static void displayWrapper();
    // ����������� �����-������� ��� ������ �������������� ������ reshape
    static void reshapeWrapper(int width, int height);
    // ����������� �����-������� ��� ������ �������������� ������ timer
    static void timerWrapper(int value);
    
};




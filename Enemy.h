#pragma once
#include "Character.h"

enum class TypeEnemy
{
    BirdType = 0,
    BomberType,
    FighterType
};

class Enemy : public Character 
{
    
protected:

    float startX; // Начальная позиция по X

public:
    TypeEnemy Type;
    
public:
    Enemy(const std::string& textureFile, float initialX, float initialY, float initWidth, float initHeigth, float movementSpeed, int initHeals);
    void update() override;
    // Функция для рисования границ
    void drawBoundaryLines();
    void dead() override;

    TypeEnemy getType();
    
    virtual void onShot();
};


class EnemyBirdType : public Enemy
{
private:
    float verticalSpeed; // Скорость изменения высоты
    float amplitude;     // Амплитуда колебаний по высоте
    float phase;         // Фаза колебаний по высоте

public:
    EnemyBirdType(float initialX, float initialY);
    void update() override;
};


class EnemyBomberType : public Enemy
{
    float minSpeed = 0.007f; // Минимальная скорость
    float maxSpeed = 0.015f; // Максимальная скорость
public:
    EnemyBomberType(float initialX, float initialY); 
    void update() override;
    void onShot() override;
};

class EnemyFighterType : public Enemy
{
    float minSpeed = 0.007f; // Минимальная скорость
    float maxSpeed = 0.015f; // Максимальная скорость
public:
    EnemyFighterType(float initialX, float initialY);
    void update() override;
    void onDodge() override;
};

class EnemyFabric
{
public: 
    static std::unique_ptr<Enemy> CreatEnemyBird();
    static std::unique_ptr<Enemy> CreatEnemyBomber();
    static std::unique_ptr<Enemy> CreatEnemyFighter();
    static std::unique_ptr<Enemy> CreateRandomEnemy();
};

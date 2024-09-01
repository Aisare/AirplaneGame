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

    float startX; // ��������� ������� �� X

public:
    TypeEnemy Type;
    
public:
    Enemy(const std::string& textureFile, float initialX, float initialY, float initWidth, float initHeigth, float movementSpeed, int initHeals);
    void update() override;
    // ������� ��� ��������� ������
    void drawBoundaryLines();
    void dead() override;

    TypeEnemy getType();
    
    virtual void onShot();
};


class EnemyBirdType : public Enemy
{
private:
    float verticalSpeed; // �������� ��������� ������
    float amplitude;     // ��������� ��������� �� ������
    float phase;         // ���� ��������� �� ������

public:
    EnemyBirdType(float initialX, float initialY);
    void update() override;
};


class EnemyBomberType : public Enemy
{
    float minSpeed = 0.007f; // ����������� ��������
    float maxSpeed = 0.015f; // ������������ ��������
public:
    EnemyBomberType(float initialX, float initialY); 
    void update() override;
    void onShot() override;
};

class EnemyFighterType : public Enemy
{
    float minSpeed = 0.007f; // ����������� ��������
    float maxSpeed = 0.015f; // ������������ ��������
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

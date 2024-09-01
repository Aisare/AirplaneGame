#pragma once
#include "AllIncludes.h"
#include "Bullet.h"

class Character 
{
protected:
    GLuint texture;
    float x, y;  // Координаты персонажа
    float width, height; // Размеры объекта
    int Heals; //здоровье персонажа
    int startedHeals; // Начальное здоровье
    float speed; // Скорость движения

    std::vector<Bullet> allBullets;//вектор выстрелов

    Game* parent = nullptr;

    bool evased = false;

    float fireRate; // Частота стрельбы (время между выстрелами в секундах)
    float timeSinceLastShot; // Время, прошедшее с последнего выстрела

    float lowerBound = -1.0f;  // Нижний предел 
    float upperBound = -0.2f;  // Верхний предел 

public:
    // Конструктор с возможностью задания начальных координат
    Character(float startX, float startY, float startWidth, float startHeigth, int startHeals);
    // Виртуальный деструктор для корректного удаления объектов производных классов
    virtual ~Character();
    virtual void update();

    //метод для получения родителя
    void setParent(void* initParent);

    // Метод для получения границ объекта
    virtual void getBounds(float& left, float& right, float& top, float& bottom) const;

    // Метод для загрузки текстуры
    virtual void load(const std::string& filename);

    // Метод для отрисовки персонажа
    virtual void draw() const;

    virtual bool takeDamage(int damage);

    // Метод для проверки коллизии двух объектов
    virtual bool checkCollision(const Character& a);
    virtual bool checkCollision(const Bullet& b);

    virtual void dead();
    virtual void shot(float speedShot,float speedShotY, std::string texturePath);

    virtual void onDodge();
    virtual bool isEvased();

    virtual void setParametrs(float setX, float setY, float setWidth, float setHeight, float setSpeedX, float setSpeedY);
    virtual void setPosition(float setX, float setY);

};
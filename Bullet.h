#pragma once
#include "AllIncludes.h"

class Bullet
{
public:
    GLuint texture;
    float x, y;
    float width, height;
    float speed;    //скорость по X
    float speedY;   //скорость по Y
    float gravity;  // Гравитационное ускорение
    bool active;

    Bullet(float startX, float startY, float startWidth, float startHeight, float startSpeed,float startSpeedY, std::string texturePath);
    void update();
    void draw() const;

    void getBounds(float& left, float& right, float& top, float& bottom) const;
   
};

#include "Bullet.h"

Bullet::Bullet(float startX, float startY, float startWidth, float startHeight, float startSpeed,float startSpeedY, std::string texturePath)
    : x(startX), y(startY), width(startWidth), height(startHeight), speed(startSpeed),speedY(startSpeedY), active(true)
{
    texture = loadTexture(texturePath);
    gravity = 0.0005f;
}

void Bullet::update()
{
    if (active) 
    {
        x += speed; // Движение пули относительно скорости
        y -= speedY;

        speedY += gravity;//Добавляем гравитацию к скорости падаения

        // Деактивация пули, если она выходит за пределы экрана
        if (fabs(x) > 1.1f) 
        {
            active = false;
        }

        if (fabs(y) > 1.1f)
        {
            active = false;
        }

        
    }
}

void Bullet::draw() const
{
    if (active)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);

        // Включение поддержки прозрачности
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(x - width / 2, y - height / 2);//левый нижний угол квадрата
        glTexCoord2f(1.0f, 0.0f); glVertex2f(x + width / 2, y - height / 2);//правый нижний угол квадрата
        glTexCoord2f(1.0f, 1.0f); glVertex2f(x + width / 2, y + height / 2);//правый верхний угол квадрата
        glTexCoord2f(0.0f, 1.0f); glVertex2f(x - width / 2, y + height / 2);//левый верхний угол квадрата
        glEnd();

        glDisable(GL_BLEND);
        glDisable(GL_TEXTURE_2D);
    }
}

void Bullet::getBounds(float& left, float& right, float& top, float& bottom) const
{
    left = x - width / 2;
    right = x + width / 2;
    top = y + height / 2;
    bottom = y - height / 2;
}
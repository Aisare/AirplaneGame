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
        x += speed; // �������� ���� ������������ ��������
        y -= speedY;

        speedY += gravity;//��������� ���������� � �������� ��������

        // ����������� ����, ���� ��� ������� �� ������� ������
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

        // ��������� ��������� ������������
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(x - width / 2, y - height / 2);//����� ������ ���� ��������
        glTexCoord2f(1.0f, 0.0f); glVertex2f(x + width / 2, y - height / 2);//������ ������ ���� ��������
        glTexCoord2f(1.0f, 1.0f); glVertex2f(x + width / 2, y + height / 2);//������ ������� ���� ��������
        glTexCoord2f(0.0f, 1.0f); glVertex2f(x - width / 2, y + height / 2);//����� ������� ���� ��������
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
#pragma once
#include "AllIncludes.h"
#include "Bullet.h"

class Character 
{
protected:
    GLuint texture;
    float x, y;  // ���������� ���������
    float width, height; // ������� �������
    int Heals; //�������� ���������
    int startedHeals; // ��������� ��������
    float speed; // �������� ��������

    std::vector<Bullet> allBullets;//������ ���������

    Game* parent = nullptr;

    bool evased = false;

    float fireRate; // ������� �������� (����� ����� ���������� � ��������)
    float timeSinceLastShot; // �����, ��������� � ���������� ��������

    float lowerBound = -1.0f;  // ������ ������ 
    float upperBound = -0.2f;  // ������� ������ 

public:
    // ����������� � ������������ ������� ��������� ���������
    Character(float startX, float startY, float startWidth, float startHeigth, int startHeals);
    // ����������� ���������� ��� ����������� �������� �������� ����������� �������
    virtual ~Character();
    virtual void update();

    //����� ��� ��������� ��������
    void setParent(void* initParent);

    // ����� ��� ��������� ������ �������
    virtual void getBounds(float& left, float& right, float& top, float& bottom) const;

    // ����� ��� �������� ��������
    virtual void load(const std::string& filename);

    // ����� ��� ��������� ���������
    virtual void draw() const;

    virtual bool takeDamage(int damage);

    // ����� ��� �������� �������� ���� ��������
    virtual bool checkCollision(const Character& a);
    virtual bool checkCollision(const Bullet& b);

    virtual void dead();
    virtual void shot(float speedShot,float speedShotY, std::string texturePath);

    virtual void onDodge();
    virtual bool isEvased();

    virtual void setParametrs(float setX, float setY, float setWidth, float setHeight, float setSpeedX, float setSpeedY);
    virtual void setPosition(float setX, float setY);

};
#include "Character.h"


Character::Character(float startX, float startY, float startWidth, float startHeigth, int startHeals)
	: x(startX), y(startY), width(startWidth), height(startHeigth), Heals(startHeals), startedHeals(startHeals)
{

}

Character::~Character()
{
}

void Character::update()
{
    // Обновление всех пуль
    for (auto& bullet : allBullets)
    {
        bullet.update();
    }

    // Удаляем неактивные пули
    allBullets.erase(
        std::remove_if(allBullets.begin(), allBullets.end(), [](const Bullet& b) { return !b.active; }),
        allBullets.end()
    );
}

void Character::setParent(void* initParent)
{
    parent = reinterpret_cast<Game*>(initParent);
}

void Character::getBounds(float& left, float& right, float& top, float& bottom) const
{
    left = x - width / 2;
    right = x + width / 2;
    top = y + height / 2;
    bottom = y - height / 2;
}

void Character::load(const std::string& filename)
{
    texture = loadTexture(filename);
}

void Character::draw() const
{
    // Отрисовка всех пуль
    for (const auto& bullet : allBullets)
    {
        bullet.draw();
    }

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Включение поддержки прозрачности
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Отрисовка текстурированного квадрата
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(x - width / 2, y - height / 2);//левый нижний угол квадрата
    glTexCoord2f(1.0f, 0.0f); glVertex2f(x + width / 2, y - height / 2);//правый нижний угол квадрата
    glTexCoord2f(1.0f, 1.0f); glVertex2f(x + width / 2, y + height / 2);//правый верхний угол квадрата
    glTexCoord2f(0.0f, 1.0f); glVertex2f(x - width / 2, y + height / 2);//левый верхний угол квадрата
    glEnd();

    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
}

bool Character::takeDamage(int damage)
{
    Heals -= damage;
    if (Heals <= 0)
    {
        Heals = startedHeals;
        dead();
        return true;
    }
    return false;
}

bool Character::checkCollision(const Bullet& b)
{
    float leftA, rightA, topA, bottomA;
    float leftB, rightB, topB, bottomB;

    b.getBounds(leftA, rightA, topA, bottomA);
    this->getBounds(leftB, rightB, topB, bottomB);

    // Проверка пересечения границ
    return !(leftA > rightB || rightA < leftB || topA < bottomB || bottomA > topB);
}

bool Character::checkCollision(const Character& a)
{
    float leftA, rightA, topA, bottomA;
    float leftB, rightB, topB, bottomB;

    a.getBounds(leftA, rightA, topA, bottomA);
    this->getBounds(leftB, rightB, topB, bottomB);

    // Проверка пересечения границ
    return !(leftA > rightB || rightA < leftB || topA < bottomB || bottomA > topB);
}

void Character::dead()
{
}

void Character::shot(float speedShot,float speedShotY, std::string texturePath)
{
    allBullets.push_back(Bullet(x + width / 2, y, 0.05f, 0.05f, speedShot, speedShotY, texturePath));
}

void Character::onDodge()
{

}

bool Character::isEvased()
{
    return evased;
}

void Character::setParametrs(float setX, float setY, float setWidth, float setHeight, float setSpeedX, float setSpeedY)
{
    x = setX;
    y = setY;
    width = setWidth;
    height = setHeight;
}

void Character::setPosition(float setX, float setY)
{
    x = setX;
    y = setY;
}

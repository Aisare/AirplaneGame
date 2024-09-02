#include "Enemy.h"

#include "Game.h"

Enemy::Enemy(const std::string& textureFile, float initialX, float initialY, float initWidth, float initHeigth, float movementSpeed, int initHeals)
    : Character(initialX, initialY, initWidth, initHeigth, initHeals),  startX(initialX)
{
    texture = loadTexture(textureFile);
    speed = movementSpeed;
}

Enemy::~Enemy()
{
    parent = nullptr;
}

void Enemy::update()
{
    Character::update();
    if (parent != nullptr)
    {
        if (!parent->player.isInvulnerability())
        {
            // Проверка коллизий пуль врага с игроком
            for (auto& bullet : allBullets)
            {
                if (bullet.active && parent->player.checkCollision(bullet))
                {
                    bullet.active = false;  // Деактивируем пулю
                    parent->player.takeDamage(1); // Игрок получает урон
                }
            }
            
            //проверка на колизию врага с игроком
            if (this->checkCollision(parent->player))
            {
                this->dead();
                parent->player.takeDamage(1);
            }
        }
        onShot();
    }
}

void Enemy::drawBoundaryLines()
{

    glColor3f(1.0f, 0.0f, 0.0f); // Цвет линии (красный)

    // Нижняя граница
    glBegin(GL_LINES);
    glVertex2f(-1.0f, upperBound);
    glVertex2f(1.0f, upperBound);
    glEnd();

    // Верхняя граница
    glBegin(GL_LINES);
    glVertex2f(-1.0f, lowerBound);
    glVertex2f(1.0f, lowerBound);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f); // Цвет линии (белый)
}

void Enemy::dead()
{
    x = startX;
    y = (rand() / (float)RAND_MAX) * (upperBound - lowerBound) + lowerBound;
    evased = false;
}

TypeEnemy Enemy::getType()
{
    return Type;
}

void Enemy::onShot()
{
    if (parent == nullptr) return;

    if (fireRate > 0)
    {
        // Обновление таймера стрельбы
        timeSinceLastShot += parent->getDeltaTime();

        // Проверка, нужно ли стрелять
        if (timeSinceLastShot >= fireRate)
        {
            shot(-0.08f,0.0f, PathToAllShots[2]); // Скорость отрицательная, так как выстрел идет влево
            timeSinceLastShot = 0.0f; // Сбрасываем таймер
        }
    }
}

EnemyBirdType::EnemyBirdType(float initialX, float initialY)
    : Enemy(PathToEnemyImage[0], initialX, initialY, 0.1f, 0.05f, 0.004f, 1),
    verticalSpeed(0.002f), // Скорость изменения высоты
    amplitude(0.25f), // Амплитуда колебаний
    phase(0.0f) // Начальная фаза колебаний
{
    // Начальная высота установлена случайно в пределах амплитуды
    y = initialY + (rand() / (float)RAND_MAX) * amplitude - amplitude / 2.0f;
    lowerBound = -0.65f;
    upperBound = 0.0f;
    Type = TypeEnemy::BirdType;
    fireRate = 0.0f;
}

void EnemyBirdType::update()
{
    Enemy::update();
    //drawBoundaryLines();//для отладки, визуализация границ движения 

    // Двигаемся с правой стороны на левую
    x -= speed;

    // Хаотичное изменение высоты
    y += verticalSpeed * sinf(phase);
    phase += 0.1f; // Увеличиваем фазу для изменения высоты

    // Ограничиваем движение по Y
    if (y < lowerBound)
    {
        y = lowerBound;
    }
    else if (y > upperBound)
    {
        y = upperBound;
    }

    // Если враг вышел за пределы экрана по X, сбрасываем его позицию и меняем высоту
    if (x < -1.1f)
    {
        x = startX;
        y = (rand() / (float)RAND_MAX) * (upperBound - lowerBound) + lowerBound; // Случайная новая высота в пределах разрешенного диапазона
    }
}

EnemyBomberType::EnemyBomberType(float initialX, float initialY)
    : Enemy(PathToEnemyImage[1], initialX, initialY, 0.3f, 0.15f, 0.007f, 5)
{
    lowerBound = 0.0f;
    upperBound = 1.0f;
    y = (rand() / (float)RAND_MAX) * (upperBound - lowerBound) + lowerBound; // Случайная новая высота в пределах разрешенного диапазона
    Type = TypeEnemy::BomberType;
    fireRate = 2.0f;
}

void EnemyBomberType::update()
{
    Enemy::update();
    //drawBoundaryLines();//для отладки, визуализация границ движения 

    // Обновляем скорость в зависимости от высоты
    float normalizedY = (y - lowerBound) / (upperBound - lowerBound); // Нормализуем высоту
    float speed = minSpeed + (maxSpeed - minSpeed) * normalizedY; // Линейная интерполяция скорости

    // Двигаемся с правой стороны на левую
    x -= speed;

    // Если враг вышел за пределы экрана по X, сбрасываем его позицию и меняем высоту
    if (x < -1.1f)
    {
        x = startX;
        y = (rand() / (float)RAND_MAX) * (upperBound - lowerBound) + lowerBound; // Случайная новая высота в пределах разрешенного диапазона
    }
}

void EnemyBomberType::onShot()
{
    if (parent == nullptr) return;

    if (fireRate > 0)
    {
        // Обновление таймера стрельбы
        timeSinceLastShot += parent->getDeltaTime();

        // Проверка, нужно ли стрелять
        if (timeSinceLastShot >= fireRate)
        {
            shot(-0.02f, 0.05f, PathToAllShots[1]); // Скорость отрицательная, так как выстрел идет влево
            timeSinceLastShot = 0.0f; // Сбрасываем таймер
        }
    }
}

EnemyFighterType::EnemyFighterType(float initialX, float initialY)
    : Enemy(PathToEnemyImage[2], initialX, initialY, 0.2f, 0.1f, 0.005f, 3)
{
    lowerBound = -0.65f;
    upperBound = 1.0f;
    y = (rand() / (float)RAND_MAX) * (upperBound - lowerBound) + lowerBound; // Случайная новая высота в пределах разрешенного диапазона
    // Устанавливаем случайную скорость в диапазоне [minSpeed, maxSpeed]
    speed = minSpeed + (rand() / (float)RAND_MAX) * (maxSpeed - minSpeed);
    Type = TypeEnemy::FighterType;
    fireRate = 1.0f;
}

void EnemyFighterType::update()
{
    Enemy::update();
    //drawBoundaryLines();//для отладки, визуализация границ движения 


    // Двигаемся с правой стороны на левую
    x -= speed;

    // Если враг вышел за пределы экрана по X, сбрасываем его позицию и меняем высоту
    if (x < -1.1f)
    {
        x = startX;
        y = (rand() / (float)RAND_MAX) * (upperBound - lowerBound) + lowerBound; // Случайная новая высота в пределах разрешенного диапазона
        // Устанавливаем случайную скорость в диапазоне [minSpeed, maxSpeed]
        speed = minSpeed + (rand() / (float)RAND_MAX) * (maxSpeed - minSpeed);
    }
}

void EnemyFighterType::onDodge()
{
    evased = true;
    // Генерация случайного направления уклонения: вверх (1) или вниз (-1)
    float dodgeDirection = (rand() % 2 == 0) ? 1.0f : -1.0f;

    // Установим величину уклонения
    float dodgeAmount = (rand() / (float)RAND_MAX) * 0.2f; // Уклонение на 0.0f - 0.2f

    // Обновляем позицию врага
    y += dodgeDirection * dodgeAmount;

    // Убедимся, что враг остается в пределах допустимых границ
    if (y < lowerBound) 
    {
        y = lowerBound;
    }
    else if (y > upperBound) 
    {
        y = upperBound;
    }
}

std::unique_ptr<Enemy> EnemyFabric::CreatEnemyBird(void* parent)
{
    std::unique_ptr<Enemy> resultEnemy = std::make_unique<EnemyBirdType>(1.0f, (rand() / (float)RAND_MAX) * 2.0f - 1.0f);
    resultEnemy->setParent(parent);
    return std::move(resultEnemy);
}

std::unique_ptr<Enemy> EnemyFabric::CreatEnemyBomber(void* parent)
{
    std::unique_ptr<Enemy> resultEnemy = std::make_unique<EnemyBomberType>(1.0f, (rand() / (float)RAND_MAX) * 2.0f - 1.0f);
    resultEnemy->setParent(parent);
    return std::move(resultEnemy);
}

std::unique_ptr<Enemy> EnemyFabric::CreatEnemyFighter(void* parent)
{
    std::unique_ptr<Enemy> resultEnemy = std::make_unique<EnemyFighterType>(1.0f, (rand() / (float)RAND_MAX) * 2.0f - 1.0f);
    resultEnemy->setParent(parent);
    return std::move(resultEnemy);
}

std::unique_ptr<Enemy> EnemyFabric::CreateRandomEnemy(void* parent)
{
    int randomValue = rand() % 3;
    std::unique_ptr<Enemy> resultEnemy;
    switch (randomValue)
    {
    case 0: resultEnemy = CreatEnemyBird(parent); break;
    case 1: resultEnemy = CreatEnemyBomber(parent); break;
    case 2: resultEnemy = CreatEnemyFighter(parent); break;
    }

    return std::move(resultEnemy);
}

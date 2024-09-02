#include "Player.h"
#include "Game.h"

Player::Player() :
	Character(-0.8f, 0.0f, 0.2f, 0.15f, 3),
	targetY(0.0f),
	velocityY(0.0f),
	score(0)
{
	lowerBound = -0.65f;
	fireRate = 0.3f;
	speed = 0.01f;
}

void Player::update()
{
	Character::update();

	if (isShotting)
	{
		Shoting();
	}

	if (parent != nullptr)
	{
		if (invulnerability)
		{
			// Обновление таймера 
			timeLastInvulnerability += parent->getDeltaTime();

			// Изменение альфа-канала для создания эффекта мигания
			if (static_cast<int>(timeLastInvulnerability / blinkInterval) % 2 == 0) {
				glColor4f(1.0f, 1.0f, 1.0f, 0.5f); // Полупрозрачный
			}
			else {
				glColor4f(1.0f, 1.0f, 1.0f, 1.0f); // Обычный
			}

			// Проверка, прошла ли неуязвимость
			if (timeLastInvulnerability >= invulnerabilityTime)
			{
				invulnerability = false;
				timeLastInvulnerability = 0.0f;
			}
		}
		else
		{
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		}


		// Проверка коллизий пуль игрока с врагами
		for (auto& enemy : parent->Enemys)
		{
			//игрок не может убивать врагов типа птица
			if (enemy->Type == TypeEnemy::BirdType) continue;

			for (auto& bullet : allBullets)
			{
				if (bullet.active && enemy->checkCollision(bullet))
				{
					if (enemy->Type == TypeEnemy::FighterType && !enemy->isEvased())
					{
						enemy->onDodge();
						continue;
					}
					bullet.active = false; // Деактивируем пулю
					if (enemy->takeDamage(1))  // Враг получает урон
					{
						if (enemy->Type == TypeEnemy::FighterType)
							score += 10;
						else if (enemy->Type == TypeEnemy::BomberType)
							score += 5;
					}
				}
			}
		}
	}

	// Вычисляем разницу между целевой позицией и текущей
	float deltaY = targetY - y;

	// Определяем скорость на основе разницы, уменьшая ее по мере приближения к целевой позиции
	// Здесь мы используем скорость с линейным уменьшением, но можно использовать различные функции (например, экспоненциальную)
	float distance = fabs(deltaY);
	float speedAdjustment = 1.0f - std::min(distance / 2.0f, 1.0f); // Чем ближе к цели, тем меньше скорость
	float currentSpeed = speed * speedAdjustment;

	// Добавляем ограничение на максимальную скорость
	const float maxSpeed = 0.05f; // Максимальная скорость для предотвращения "вылетания"
	currentSpeed = std::min(currentSpeed, maxSpeed);

	// Обновляем скорость с учетом разницы
	velocityY += deltaY * currentSpeed;

	// Обновляем текущую позицию по Y с учетом скорости
	y += velocityY;

	// Немного замедляем скорость (демпфирование), чтобы инерция постепенно уменьшалась
	velocityY *= 0.6f;

	// Ограничиваем позицию игрока, чтобы она не выходила за пределы экрана
	float screenTop = 1.0f; // Верхняя граница экрана
	float screenBottom = -1.0f; // Нижняя граница экрана
	if (y > screenTop)
	{
		y = screenTop;
		velocityY = 0.0f; // Сбрасываем скорость при достижении верхней границы
	}
	else if (y < screenBottom)
	{
		y = screenBottom;
		velocityY = 0.0f; // Сбрасываем скорость при достижении нижней границы
	}

	//если игрок коснулся "земли"
	if (y <= lowerBound)
	{
		this->dead();
	}

	// Чтобы игрок не "перепрыгнул" целевую позицию, можно использовать небольшой порог
	if (fabs(targetY - y) < 0.01f)
	{
		y = targetY;
		velocityY = 0.0f; // Сбрасываем скорость, когда достигнута целевая позиция
	}
}

void Player::draw() const
{
	Character::draw();
	drawHPBar();
	drawScore();
}

void Player::setTargetY(float mouseY)
{
	targetY = mouseY;
}

void Player::dead()
{
	x = -0.8f;
	y = 0.0f;
	invulnerability = true;
	timeLastInvulnerability = 0.0f;

	if (parent != nullptr)
	{
		parent->GameOver.setText(0,"   Your Score: " + std::to_string(score));
		parent->setGameStatus(GameState::GAME_OVER);
	}
}

void Player::load(std::string pathPlayer, std::string pathHP)
{
	healthTexture = loadTexture(pathHP);
	Character::load(pathPlayer);
}

void Player::drawHPBar() const
{
	// Размеры квадратов здоровья
	float healthSize = 0.1f;
	float spacing = 0.05f; // Отступ между квадратами

	// Начальная позиция для отрисовки (верхний левый угол экрана)
	float startX = -1.0f + healthSize;
	float startY = 0.9f;

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, healthTexture);

	// Включение поддержки прозрачности
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (int i = 0; i < Heals; ++i)
	{
		float x = startX + i * (healthSize + spacing);

		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex2f(x, startY - healthSize);
		glTexCoord2f(1.0f, 0.0f); glVertex2f(x + healthSize, startY - healthSize);
		glTexCoord2f(1.0f, 1.0f); glVertex2f(x + healthSize, startY);
		glTexCoord2f(0.0f, 1.0f); glVertex2f(x, startY);
		glEnd();
	}

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);

	glDisable(GL_TEXTURE_2D);
}

void Player::drawScore() const
{
	std::string scoreText = "Score: " + std::to_string(score);

	glColor3f(1.0f, 1.0f, 1.0f); // Цвет текста (белый)
	glRasterPos2f(-0.9f, -0.9f);  // Позиция текста 
	for (char c : scoreText)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
	}
}

void Player::setScore(long setscorevalue)
{
	score = setscorevalue;
}

long Player::getScore() const
{
	return score;
}

bool Player::takeDamage(int value)
{
	bool result = Character::takeDamage(value);
	if (!result)
	{
		invulnerability = true;
	}
	return result;
}

bool Player::isInvulnerability()
{
	return invulnerability;
}

void Player::Shoting()
{
	if (parent == nullptr) return;

	timeSinceLastShot += parent->getDeltaTime();

	// Проверка, нужно ли стрелять
	if (timeSinceLastShot >= fireRate)
	{
		shot(0.05f, 0.0f, PathToAllShots[0]);
		timeSinceLastShot = 0.0;
	}
}

void Player::setShotingStatus(bool status)
{
	isShotting = status;
}


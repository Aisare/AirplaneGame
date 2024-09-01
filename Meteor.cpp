#include "Meteor.h"

#include "Game.h"

Meteor::Meteor()
	:Character(1.0f, 1.5f, 0.5f, 0.5f, 1)
{
	speed = 0.005f;
}

void Meteor::update()
{
	if (parent == nullptr) return;

	// ���������� �������
	timeSince += parent->getDeltaTime();

	// ��������, ����� �� ������ ����
	if (timeSince >= 5.0f)
	{
		x -= speed;//������� ������ �� ����
		y -= speed;

		speed += gravity;

		if (parent != nullptr)
		{
			if (this->checkCollision(parent->player))
			{
				parent->player.dead();
			}

			for (auto& itm : parent->Enemys)
			{
				if (itm->getType() == TypeEnemy::BirdType) continue;

				if (this->checkCollision(*itm))
				{
					itm->dead();
				}
			}
		}

		if (fabs(y) >= 1.6f)
		{
			this->dead();
		}
	}
}

void Meteor::dead()
{
	x = 0.8f + (rand() / (float)RAND_MAX) * 0.2f;//��������� ������� �� 0.8 �� 1.0
	y = 1.5f;
	timeSince = 0.0f;
	speed = 0.005f;
}

void Meteor::draw() const
{
	Character::draw();
}
